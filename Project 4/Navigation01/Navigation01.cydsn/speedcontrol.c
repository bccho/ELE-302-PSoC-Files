/*-----------------------------------------------------------------*/
/* speedcontrol.c                                                  */
/*                                                                 */
/* BC Cho (bccho@) and TJ Smith (tjs8@)                            */
/*-----------------------------------------------------------------*/
#include <speedcontrol.h>
#include <device.h>
#include <hardware.h>
#include <math.h>
#include <stdio.h>

// Printing
static char strbuffer[100];

// Speed setting
static int throttle = 0;

// Tick tracking
#define BUF_WHEEL_TICK_SIZE 3
static int bufWheelTick[BUF_WHEEL_TICK_SIZE];
static int bufWheelTickPos = 0;
static int bufWheelTickCurSize = 0;
static int oldTickCount = 0;

// Speed calculating

// Distance tracking
static double totalDistance = 0;

// Time tracking
static double elapsedTime = 0;

// Speed error derivative tracking
#define BUF_SPEED_SIZE 10
static double bufSpeed[BUF_SPEED_SIZE];
static int bufSpeedPos = 0;
static int bufSpeedLastPos = 0;

// Speed error integral tracking
static double errorIntegral = 0.0;

// PID settings
static int throttlePIDon = 0;
static int distanceTimeoutOn = 0;
static int dynamicTargetSpeedUpdateOn = 0;

static double targetSpeed = 4.0; // in feet per second
static double targetDistance = 40;
static double targetTime = 10; // do not set directly
static int throttleSS = 100;
static double coeffP = 50.0;
static double coeffI = 10.0;
static double coeffD = 10.0;

// Misc
static int verbosePrintoutOn = 0;


/*-----------------------------------------------------------------*/

static void killAll();
static int controlThrottle(double speed);
static void setThrottle(int thr);
static double getSpeed();
static void resetSpeedTracking();
static void resetDerivativeTracking();
static void resetIntegralTracking();

/*-----------------------------------------------------------------*/

/* Initialize speed control */
void SpeedControl_init() {
    resetSpeedTracking();
    resetDerivativeTracking();
    setThrottle(0);
}

/* Enable speed control */
void SpeedControl_enable() {
    resetDerivativeTracking();
    resetIntegralTracking();
    throttlePIDon = 1;
    elapsedTime = 0;
    totalDistance = 0;
}

/* Disable speed control */
void SpeedControl_disable() {
    throttlePIDon = 0;
    setThrottle(0);
}

/* Enable distance control */
void SpeedControl_enableDistanceControl() {
    distanceTimeoutOn = 1;
}

/* Disable distance control */
void SpeedControl_disableDistanceControl() {
    distanceTimeoutOn = 0;
    dynamicTargetSpeedUpdateOn = 0;
}

/* Enable dynamic target speed control */
void SpeedControl_enableDynamicTargetUpdate() {
    if (throttlePIDon) {
        UART_PutString("Cannot enable dynamic target speed update while controlling speed\n");
    } 
    else {
        dynamicTargetSpeedUpdateOn = 1;
        distanceTimeoutOn = 1;
    }
}

/* Disable dynamic target speed control */
void SpeedControl_disableDynamicTargetUpdate() {
    dynamicTargetSpeedUpdateOn = 0;
}

/* Get status of speed control */
int SpeedControl_isEnabled() {
    return throttlePIDon;
}

/* Get status of distance control */
int SpeedControl_isDistanceControlEnabled() {
    return distanceTimeoutOn;
}

/* Get status of dynamic target speed control */
int SpeedControl_isDynamicTargetUpdateEnabled() {
    return dynamicTargetSpeedUpdateOn;
}

/* Enable verbose printout */
void SpeedControl_enableVerbosePrintout() {
    verbosePrintoutOn = 1;
}

/* Disable verbose printout */
void SpeedControl_disableVerbosePrintout() {
    verbosePrintoutOn = 0;
}

/* Get status of verbose printout */
int SpeedControl_isVerbosePrintoutEnabled() {
    return verbosePrintoutOn;
}

/* Set target speed */
void SpeedControl_setTargetSpeed(double ts) {
    if (dynamicTargetSpeedUpdateOn) {
        UART_PutString("Cannot change target speed while dynamic target speed updating is on\n");
    }
    else {
        targetSpeed = ts;
        targetTime = targetDistance / targetSpeed;
    }
}

/* Set target distance */
void SpeedControl_setTargetDistance(double dist) {
    if (dynamicTargetSpeedUpdateOn) {
        UART_PutString("Cannot change target distance while dynamic target speed updating is on\n");
    }
    else {
        targetDistance = dist;
        targetTime = targetDistance / targetSpeed;
    }
}

/* Set steady state throttle */
void SpeedControl_setSteadyStateThrottle(int thr) {
    throttleSS = thr;
}

/* Set P coefficient */
void SpeedControl_setP(double P) {
    coeffP = P;
}

/* Set I coefficient */
void SpeedControl_setI(double I) {
    coeffI = I;
}

/* Set D coefficient */
void SpeedControl_setD(double D) {
    coeffD = D;
}

/* Get target speed */
double SpeedControl_getTargetSpeed() {
    return targetSpeed;
}

/* Get target distance */
double SpeedControl_getTargetDistance() {
    return targetDistance;
}

/* Get P coefficient */
double SpeedControl_getP() {
    return coeffP;
}

/* Get I coefficient */
double SpeedControl_getI() {
    return coeffI;
}

/* Get D coefficient */
double SpeedControl_getD() {
    return coeffD;
}

/* Get current speed */
double SpeedControl_getSpeed() {
    return getSpeed();
}

/* Get total distance */
double SpeedControl_getDistance() {
    return totalDistance;
}

/* Get steady state throttle */
int SpeedControl_getSteadyStateThrottle() {
    return throttleSS;
}

/* Set throttle */
void SpeedControl_setThrottle(int throttle) {
    if (!throttlePIDon) setThrottle(throttle);
    else UART_PutString("Cannot change throttle when PID on\n");
}

/* Get throttle */
int SpeedControl_getThrottle() {
    return throttle;
}

/* Kill throttle and speed control */
void SpeedControl_kill() {
    killAll();
}

/* Handle wheel tick */
void SpeedControl_handleWheelTick() {
    int tickCount = Timer_Wheel_Tick_ReadCapture();
    
    // Calculate tick delta
    int tickDelta = oldTickCount - tickCount;
    tickDelta = tickDelta < 0 ? TICK_TIMER_PERIOD + tickDelta : tickDelta;
    bufWheelTick[bufWheelTickPos] = tickDelta;
    
    // Increment buffer position, and update size and old tick count
    bufWheelTickPos = (bufWheelTickPos + 1) % BUF_WHEEL_TICK_SIZE;
    if (bufWheelTickCurSize < BUF_WHEEL_TICK_SIZE) bufWheelTickCurSize++;
    oldTickCount = tickCount;
    
    // Update total distance
    totalDistance += (1.0/5.0) * (M_PI * WHEEL_DIAM) / 12.0;
}


/* Handle wheel tick timeout */
void SpeedControl_handleWheelTickTimeout() {
    // Reset speed and derivative tracking
    resetSpeedTracking();
    resetDerivativeTracking();
    UART_PutString("Wheel timeout\n");
}



/* Handle PID timer. Controls speed and updates time */
void SpeedControl_handleTimer() {
    if (throttlePIDon) {
        elapsedTime += (double) PID_TIMER_PERIOD / (double) MAIN_CLK_FREQ;
        setThrottle(controlThrottle(getSpeed()));
    }
}



/* Updates the error values, and uses them to update
 * the set point throttle for PWM control
 *
 * Inputs: speed (double)
 * Returns: newThrottle (int) */
static int controlThrottle(double speed) {
    // Handle distance timeout
    if (distanceTimeoutOn && totalDistance >= targetDistance) {
        killAll();
        
        sprintf(strbuffer, "Target distance reached in %6.2f s\n", elapsedTime);
        UART_PutString(strbuffer);
        return 0;
    }
    else {
        // Dynamically update target speed if enabled
        double dynamicTargetSpeed = targetSpeed;
        double distanceLeft = 0;
        double timeLeft = 0;
        const double MAX_SPEED = targetSpeed * 2;
        if (dynamicTargetSpeedUpdateOn) {
            distanceLeft = targetDistance - totalDistance;
            timeLeft = targetTime - elapsedTime;
            if (distanceLeft > 0) {
                if (timeLeft <= 0) {
                    dynamicTargetSpeed = MAX_SPEED;
                } else {
                    dynamicTargetSpeed = distanceLeft / timeLeft;
                    if (dynamicTargetSpeed > MAX_SPEED) dynamicTargetSpeed = targetSpeed * 2; // limit dyn target speed
                }
            }
        }

        // Calculate error
        double error = dynamicTargetSpeed - speed;
        bufSpeed[bufSpeedPos] = error;
        // Calculate derivative of error
        double errorDerivative = (bufSpeed[bufSpeedPos] - bufSpeed[bufSpeedLastPos]) / (double) BUF_SPEED_SIZE;
        bufSpeedPos = (bufSpeedPos + 1) % BUF_SPEED_SIZE;
        if (bufSpeedPos == bufSpeedLastPos) { // this gets activated when bufSpeedPos has made one loop around the ring buffer
            bufSpeedLastPos = (bufSpeedLastPos + 1) % BUF_SPEED_SIZE;
        }
        // Calculate integral of error
        errorIntegral += error;
        
        // Calculate new throttle
        int newThrottle = throttleSS + (int) (error * coeffP + errorIntegral * coeffI - errorDerivative * coeffD);
        
        if (verbosePrintoutOn) {
            sprintf(strbuffer, "%3i, %6.2f, %6.2f, %6.2f, %8.5f, %6.2f | %6.2f, %6.2f, %6.2f\n", 
                    newThrottle, speed, error, errorIntegral, errorDerivative, totalDistance, dynamicTargetSpeed, distanceLeft, timeLeft);
            UART_PutString(strbuffer);
        }
        
        return newThrottle;
    }
}


/* Turns off throttle and PID */
static void killAll() {
    setThrottle(0);
    throttlePIDon = 0;
    UART_PutString("PID and throttle killed\n");
}


/* Takes an integer between 0 and MAX_THROTTLE and
 * sets the motor PWM output to that value */
static void setThrottle(int thr) {
    if (thr < 0)
        thr = 0;
    if (thr > MAX_THROTTLE)
        thr = MAX_THROTTLE;
    
    throttle = thr;
    
    PWM_Motor_WriteCompare(throttle);
    
    LCD_ClearDisplay();
    LCD_Position(0,0);
    char lcdbuffer[4];
    sprintf(lcdbuffer, "%3i", throttle);
    LCD_PrintString(lcdbuffer);
}


/* Returns average speed (in ft/sec) over the last BUF_WHEEL_TICK_SIZE ticks */
static double getSpeed() {
    double cumSum = 0;
    int i;
    if (bufWheelTickCurSize == 0) return 0;
    for (i = 0; i < BUF_WHEEL_TICK_SIZE; i++) {
        cumSum += (double) bufWheelTick[i];
    }
    double averageCount = cumSum / bufWheelTickCurSize;
    double ticksPerSec = MAIN_CLK_FREQ / averageCount;
    double speed = ticksPerSec * ((M_PI * WHEEL_DIAM) / 5) * (1.0/12.0);
    
    return speed;
}

/* Resets tick buffer */
static void resetSpeedTracking() {
    // Clear wheel tick buffer
    bufWheelTickPos = 0;
    bufWheelTickCurSize = 0;
    int i;
    for (i = 0; i < BUF_WHEEL_TICK_SIZE; i++) bufWheelTick[i] = 0;
}


/* Resets speed error buffer */
static void resetDerivativeTracking() {
    // Clear speed buffer
    bufSpeedPos = 0;
    bufSpeedLastPos = 0;
    int i;
    for (i = 0; i < BUF_SPEED_SIZE; i++) bufSpeed[i] = 0.0;
}


/* Resets integral term */
static void resetIntegralTracking() {
    // Reset integral term
    errorIntegral = 0.0;
}


/* [] END OF FILE */
