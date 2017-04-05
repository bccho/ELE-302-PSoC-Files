/*-----------------------------------------------------------------*/
/* navigation.c                                                    */
/*                                                                 */
/* BC Cho (bccho@) and TJ Smith (tjs8@)                            */
/*-----------------------------------------------------------------*/
#include <navigation.h>
#include <device.h>
#include <hardware.h>
//#include <math.h> // floor and ceil throw errors if included
#include <stdio.h>
#include <camera.h>

// Printing
static char strbuffer[100];

// Line (x, spatial) error integral tracking
static double lineErrorIntegral = 0.0;
static double lineErrorDoubleIntegral = 0.0;

// Line (x, spatial) error derivative tracking
#define BUF_LINE_ERROR_SIZE 10
static double bufLineError[BUF_LINE_ERROR_SIZE];
static int bufLineErrorPos = 0;
static int bufLineErrorLastPos = 0;

// Theta (angle from line) error integral tracking
static double thetaIntegral = 0.0;

// Theta (angle from line) error derivative tracking
#define BUF_THETA_SIZE 10
static double bufTheta[BUF_THETA_SIZE];
static int bufThetaPos = 0;
static int bufThetaLastPos = 0;

// PID settings
static int steeringPIDon = 0;

static double coeffPline = 2.0;
static double coeffIline = 0.0;
static double coeffIIline = 0.0;
static double coeffDline = 0.0;
static double coeffPtheta = 0.0;
static double coeffItheta = 0.0;
static double coeffDtheta = 0.0;

// Misc
static int verbosePrintoutOn = 0;


/*-----------------------------------------------------------------*/

static void killAll();
static double controlSteering(double linePos, double theta);
static void setSteering(double dir);
// static double getSteering();
// static void resetSteeringTracking();
static void resetDerivativeTracking();
static void resetIntegralTracking();
static double floor(double a);
static double ceil(double a);

/*-----------------------------------------------------------------*/

/* Initialize navigation */
void Navigation_init() {
    // resetSteeringTracking();
    resetDerivativeTracking();
    setSteering(0);
}

/* Enable navigation */
void Navigation_enable() {
    resetDerivativeTracking();
    resetIntegralTracking();
    steeringPIDon = 1;
}

/* Disable navigation */
void Navigation_disable() {
    steeringPIDon = 0;
    setSteering(0);
}

/* Get status of navigation */
int Navigation_isEnabled() {
    return steeringPIDon;
}

/* Enable verbose printout */
void Navigation_enableVerbosePrintout() {
    verbosePrintoutOn = 1;
}

/* Disable verbose printout */
void Navigation_disableVerbosePrintout() {
    verbosePrintoutOn = 0;
}

/* Get status of verbose printout */
int Navigation_isVerbosePrintoutEnabled() {
    return verbosePrintoutOn;
}

/* Set Pline coefficient */
void Navigation_setPline(double Pline) {
    coeffPline = Pline;
}

/* Set Iline coefficient */
void Navigation_setIline(double Iline) {
    coeffIline = Iline;
}

/* Set IIline coefficient */
void Navigation_setIIline(double IIline) {
    coeffIIline = IIline;
}

/* Set Dline coefficient */
void Navigation_setDline(double Dline) {
    coeffDline = Dline;
}

/* Set Ptheta coefficient */
void Navigation_setPtheta(double Ptheta) {
    coeffPtheta = Ptheta;
}

/* Set Itheta coefficient */
void Navigation_setItheta(double Itheta) {
    coeffItheta = Itheta;
}

/* Set Dtheta coefficient */
void Navigation_setDtheta(double Dtheta) {
    coeffDtheta = Dtheta;
}

/* Get Pline coefficient */
double Navigation_getPline() {
    return coeffPline;
}

/* Get Iline coefficient */
double Navigation_getIline() {
    return coeffIline;
}

/* Get IIline coefficient */
double Navigation_getIIline() {
    return coeffIIline;
}

/* Get Dline coefficient */
double Navigation_getDline() {
    return coeffDline;
}

/* Get Ptheta coefficient */
double Navigation_getPtheta() {
    return coeffPtheta;
}

/* Get Itheta coefficient */
double Navigation_getItheta() {
    return coeffItheta;
}

/* Get Dtheta coefficient */
double Navigation_getDtheta() {
    return coeffDtheta;
}

/* Set steering */
// Steering function (-1 is full left, +1 is full right, 0 is center)
void Navigation_setSteering(double dir) {
    if (!steeringPIDon) setSteering(dir);
    else UART_PutString("Cannot change steering when PID on\n");
}

/* Get steering */
double Navigation_getSteeringMillis() {
    double servoVal = PWM_Servo_ReadCompare() / MAIN_CLK_FREQ;
    return servoVal;
}

// -1 is full left, +1 is full right, 0 is center
double Navigation_getSteering() {
    double servoVal = Navigation_getSteeringMillis();
    double setVal = (servoVal - MIN_TIME_SERVO) / (MAX_TIME_SERVO - MIN_TIME_SERVO);
    return setVal * 2 - 1;
}

/* Kill steering and navigation */
void Navigation_kill() {
    killAll();
}


/* Handle PID timer. Controls speed and updates time */
void Navigation_handleTimer() {
    if (steeringPIDon) {
        double x = Camera_getLineMid();
        double theta = Camera_getLineAngle();
        setSteering(controlSteering(x, theta));
    }
}

/* Floor and ceil helper functions */
static double floor(double a) {
    return (double) (int) a;
}

static double ceil(double a) {
    return floor(a) + 1;
}


// Steering function (-1 is full left, +1 is full right, 0 is center)
static void setSteering(double dir) {
    if (dir >  1) dir =  1;
    if (dir < -1) dir = -1;

    double servoTime = MIN_TIME_SERVO + (MAX_TIME_SERVO - MIN_TIME_SERVO) * (dir + 1) / 2;
    double servoPeriod = servoTime * MAIN_CLK_FREQ;
    double midPeriod = 0.5*(MAX_TIME_SERVO + MIN_TIME_SERVO) * MAIN_CLK_FREQ;
    if (servoPeriod > midPeriod) servoPeriod = floor(servoPeriod);
    else servoPeriod = ceil(servoPeriod);
    PWM_Servo_WriteCompare(servoPeriod);
}

/* Updates the steering error values, and uses them to update
 * the set point throttle for PWM control
 *
 * Inputs: linePos (double) - the position of the line closest to the car, as a fraction from 0 (left) to 1 (right)
 *         theta (double) - the angle that the car makes to the line (0 is parallel to the line)
 * Returns: newSteering (double) */
static double controlSteering(double linePos, double theta) {
    /* Ignore if invalid values */
    if (linePos < 0) {
        return 0;
    }

    /* Line position */
    // Calculate error
    double targetLinePos = 0.5;
    double lineError = linePos - targetLinePos;
    bufLineError[bufLineErrorPos] = lineError;
    // Calculate derivative of error
    double lineErrorDerivative = (bufLineError[bufLineErrorPos] - bufLineError[bufLineErrorLastPos]) / (double) BUF_LINE_ERROR_SIZE;
    bufLineErrorPos = (bufLineErrorPos + 1) % BUF_LINE_ERROR_SIZE;
    if (bufLineErrorPos == bufLineErrorLastPos) { // this gets activated when bufLineErrorPos has made one loop around the ring buffer
        bufLineErrorLastPos = (bufLineErrorLastPos + 1) % BUF_LINE_ERROR_SIZE;
    }
    // Calculate integral of error
    lineErrorIntegral += lineError;
    lineErrorDoubleIntegral += lineErrorIntegral;

    /* Theta */
    // Calculate error
    bufTheta[bufThetaPos] = theta;
    // Calculate derivative of error
    double thetaDerivative = (bufTheta[bufThetaPos] - bufTheta[bufThetaLastPos]) / (double) BUF_THETA_SIZE;
    bufThetaPos = (bufThetaPos + 1) % BUF_THETA_SIZE;
    if (bufThetaPos == bufThetaLastPos) { // this gets activated when bufThetaPos has made one loop around the ring buffer
        bufThetaLastPos = (bufThetaLastPos + 1) % BUF_THETA_SIZE;
    }
    // Calculate integral of error
    thetaIntegral += theta;

    /* Calculate new steering position */
    double newSteering = lineError * coeffPline + lineErrorIntegral * coeffIline + lineErrorDoubleIntegral * coeffIIline + lineErrorDerivative * coeffDline +
        theta * coeffPtheta + thetaIntegral * coeffItheta + thetaDerivative * coeffDtheta;

    if (verbosePrintoutOn) {
        sprintf(strbuffer, "%4.3f | %3.2f, %3.2f, %6.2f, %8.2f, %3.2f | %4.2f , %6.2f, %4.2f\n", 
                newSteering, linePos, lineError, lineErrorIntegral, lineErrorDoubleIntegral, lineErrorDerivative, 
                theta, thetaIntegral, thetaDerivative);
        UART_PutString(strbuffer);
    }

    return newSteering;
}


/* Turns off steering and PID */
static void killAll() {
    setSteering(0);
    steeringPIDon = 0;
    UART_PutString("PID and steering killed\n");
}



/* Resets error buffers */
static void resetDerivativeTracking() {
    // Clear speed buffer
    bufLineErrorPos = 0;
    bufLineErrorLastPos = 0;
    bufThetaPos = 0;
    bufThetaLastPos = 0;
    int i;
    for (i = 0; i < BUF_LINE_ERROR_SIZE; i++) bufLineError[i] = 0.0;
    for (i = 0; i < BUF_THETA_SIZE; i++) bufTheta[i] = 0.0;
}


/* Resets integral term */
static void resetIntegralTracking() {
    // Reset integral term
    thetaIntegral = 0.0;
    lineErrorIntegral = 0.0;
    lineErrorDoubleIntegral = 0.0;
}


/* [] END OF FILE */
