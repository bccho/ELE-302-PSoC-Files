/*-----------------------------------------------------------------*/
/* navigation.h                                                    */
/*                                                                 */
/* BC Cho (bccho@) and TJ Smith (tjs8@)                            */
/*-----------------------------------------------------------------*/
#ifndef NAVIGATION_H
#define NAVIGATION_H

/*-----------------------------------------------------------------*/


/* Initialize navigation control */
void Navigation_init();

/* Enable navigation */
void Navigation_enable();

/* Disable navigation */
void Navigation_disable();

/* Get status of navigation */
int Navigation_isEnabled();

/* Enable verbose printout */
void Navigation_enableVerbosePrintout();

/* Disable verbose printout */
void Navigation_disableVerbosePrintout();

/* Get status of verbose printout */
int Navigation_isVerbosePrintoutEnabled();

/* Set P coefficient */
void Navigation_setPline(double P);

/* Set I coefficient */
void Navigation_setIline(double I);

/* Set II coefficient */
void Navigation_setIIline(double II);

/* Set D coefficient */
void Navigation_setDline(double D);

/* Set P coefficient */
void Navigation_setPtheta(double P);

/* Set I coefficient */
void Navigation_setItheta(double I);

/* Set D coefficient */
void Navigation_setDtheta(double D);

/* Get P coefficient */
double Navigation_getP();

/* Get I coefficient */
double Navigation_getI();

/* Get D coefficient */
double Navigation_getD();

/* Get current speed */
double Navigation_getSpeed();

/* Get total distance */
double Navigation_getDistance();

/* Set steering */
void Navigation_setSteering(double dir);

/* Kill throttle and speed control */
void Navigation_kill();



/* Handle PID timer. Controls speed and updates time */
void Navigation_handleTimer();



#endif
