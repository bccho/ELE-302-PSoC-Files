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
#define MAIN_CLK_FREQ 100000

/* Throttle */
#define MAX_THROTTLE 999

/* Distance measurement */
#define TICK_TIMER_PERIOD 65536
#define WHEEL_DIAM 2.5 // inches

/* Steering */
// Control pulse times for steering
#define MIN_TIME_SERVO 0.00100 // seconds
//#define MIN_TIME_SERVO 0.00105 // seconds
#define MAX_TIME_SERVO 0.00175 // seconds
//#define MAX_TIME_SERVO 0.00169 // seconds

/* Camera */
#define CAM_CLK_FREQ 12000000 // Hz
#define CAMERA_TIMER_PERIOD 65536
#define EXPECTED_ROW_TIME 0.000059 // seconds
#define COUNTER_NEAR_ROW_COUNT 240
#define LINE_CYCLES_FAR 70 // far camera: 45
#define LINE_CYCLES_NEAR 80 // far camera: 70

/* PID */
#define PID_TIMER_PERIOD 2000

#endif
