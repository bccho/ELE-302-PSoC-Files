/*-----------------------------------------------------------------*/
/* hardware.h                                                      */
/* For hardware-related constants and defines                      */
/*                                                                 */
/* BC Cho (bccho@) and TJ Smith (tjs8@)                            */
/*-----------------------------------------------------------------*/
#ifndef HARDWARE_H
#define HARDWARE_H

/*-----------------------------------------------------------------*/


/* Main clock */
const int MAIN_CLK_FREQ = 100000;

/* Throttle */
const int MAX_THROTTLE = 999;

/* Distance measurement */
const int TICK_TIMER_PERIOD = 65536;
const double WHEEL_DIAM = 2.41; // in inches

/* Steering */
// Control pulse times in seconds, for steering
const double MIN_TIME_SERVO = 0.00105;
const double MAX_TIME_SERVO = 0.00169;

/* Camera */
#define CAM_CLK_FREQ 12000000
const double CAMERA_TIMER_PERIOD = 65536;
#define EXPECTED_ROW_TIME 0.000059

/* PID */
const int PID_TIMER_PERIOD = 10000;



#endif
