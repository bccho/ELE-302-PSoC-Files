/*-----------------------------------------------------------------*/
/* speedcontrol.h                                                  */
/*                                                                 */
/* BC Cho (bccho@) and TJ Smith (tjs8@)                            */
/*-----------------------------------------------------------------*/
#ifndef SPEED_CONTROL_H
#define SPEED_CONTROL_H

/*-----------------------------------------------------------------*/


/* Initialize speed control */
void SpeedControl_init();

/* Enable speed control */
void SpeedControl_enable();

/* Disable speed control */
void SpeedControl_disable();

/* Enable distance control */
void SpeedControl_enableDistanceControl();

/* Disable distance control */
void SpeedControl_disableDistanceControl();

/* Enable dynamic target speed control */
void SpeedControl_enableDynamicTargetUpdate();

/* Disable dynamic target speed control */
void SpeedControl_disableDynamicTargetUpdate();

/* Get status of speed control */
int SpeedControl_isEnabled();

/* Get status of distance control */
int SpeedControl_isDistanceControlEnabled();

/* Get status of dynamic target speed control */
int SpeedControl_isDynamicTargetUpdateEnabled();

/* Enable verbose printout */
void SpeedControl_enableVerbosePrintout();

/* Disable verbose printout */
void SpeedControl_disableVerbosePrintout();

/* Get status of verbose printout */
int SpeedControl_isVerbosePrintoutEnabled();

/* Set target speed (in m/s) */
void SpeedControl_setTargetSpeed(double targetSpeed);

/* Set target distance (in meters)*/
void SpeedControl_setTargetDistance(double targetDistance);

/* Set steady state throttle */
void SpeedControl_setSteadyStateThrottle(int ssThrottle);

/* Set P coefficient */
void SpeedControl_setP(double P);

/* Set I coefficient */
void SpeedControl_setI(double I);

/* Set D coefficient */
void SpeedControl_setD(double D);

/* Get target speed */
double SpeedControl_getTargetSpeed();

/* Get target distance */
double SpeedControl_getTargetDistance();

/* Get steady state throttle */
int SpeedControl_getSteadyStateThrottle();

/* Get P coefficient */
double SpeedControl_getP();

/* Get I coefficient */
double SpeedControl_getI();

/* Get D coefficient */
double SpeedControl_getD();

/* Get current speed */
double SpeedControl_getSpeed();

/* Get total distance */
double SpeedControl_getDistance();

/* Set throttle */
void SpeedControl_setThrottle(int throttle);

/* Get throttle */
int SpeedControl_getThrottle();

/* Kill throttle and speed control */
void SpeedControl_kill();

/* Handle wheel tick */
void SpeedControl_handleWheelTick();

/* Handle wheel tick timeout */
void SpeedControl_handleWheelTickTimeout();



/* Handle PID timer. Controls speed and updates time */
void SpeedControl_handleTimer();



#endif
