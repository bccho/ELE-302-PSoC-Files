/*-----------------------------------------------------------------*/
/* hardware.h                                                      */
/* For hardware-related constants and defines                      */
/*                                                                 */
/* BC Cho (bccho@) and TJ Smith (tjs8@)                            */
/*-----------------------------------------------------------------*/
#ifndef HARDWARE_H
#define HARDWARE_H

//#ifndef VAR_DECLS
//    #define VAR_DECLS
//    #define _DECL extern
//    #define _INIT(x)
//#else
//    #define _DECL
//    #define _INIT(x)  = x
//#endif


/*-----------------------------------------------------------------*/

/* Main clock */
#define MAIN_CLK_FREQ 100000

/* Throttle */
#define MAX_THROTTLE 999

/* Distance measurement */
#define TICK_TIMER_PERIOD 65536
#define WHEEL_DIAM 2.41 // inches

/* Steering */
// Control pulse times for steering
#define MIN_TIME_SERVO 0.00105 // seconds
#define MAX_TIME_SERVO 0.00169 // seconds

/* Camera */
#define CAM_CLK_FREQ 12000000 // Hz
#define CAMERA_TIMER_PERIOD 65536
#define EXPECTED_ROW_TIME 0.000059 // seconds

/* PID */
#define PID_TIMER_PERIOD 10000


///* Main clock */
//_DECL const int MAIN_CLK_FREQ _INIT(100000);
//
///* Throttle */
//_DECL const int MAX_THROTTLE _INIT(999);
//
///* Distance measurement */
//_DECL const int TICK_TIMER_PERIOD _INIT(65536);
//_DECL const double WHEEL_DIAM _INIT(2.41); // in inches
//
///* Steering */
//// Control pulse times in seconds, for steering
//_DECL const double MIN_TIME_SERVO _INIT(0.00105);
//_DECL const double MAX_TIME_SERVO _INIT(0.00169);
//
///* Camera */
//_DECL const int CAM_CLK_FREQ _INIT(12000000);
//_DECL const int CAMERA_TIMER_PERIOD _INIT(65536);
//_DECL const double EXPECTED_ROW_TIME _INIT(0.000059);
//
///* PID */
//_DECL const int PID_TIMER_PERIOD _INIT(10000);

//
///* Main clock */
//const int MAIN_CLK_FREQ = 100000;
//
///* Throttle */
//const int MAX_THROTTLE = 999;
//
///* Distance measurement */
//const int TICK_TIMER_PERIOD = 65536;
//const double WHEEL_DIAM = 2.41; // in inches
//
///* Steering */
//// Control pulse times in seconds, for steering
//const double MIN_TIME_SERVO = 0.00105;
//const double MAX_TIME_SERVO = 0.00169;
//
///* Camera */
//#define CAM_CLK_FREQ 12000000
//const double CAMERA_TIMER_PERIOD = 65536;
//#define EXPECTED_ROW_TIME 0.000059
//
///* PID */
//const int PID_TIMER_PERIOD = 10000;



#endif
