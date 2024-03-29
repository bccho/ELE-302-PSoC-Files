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

/* Set P coefficient */
double Navigation_getPline();

/* Set I coefficient */
double Navigation_getIline();

/* Set II coefficient */
double Navigation_getIIline();

/* Set D coefficient */
double Navigation_getDline();

/* Set P coefficient */
double Navigation_getPtheta();

/* Set I coefficient */
double Navigation_getItheta();

/* Set D coefficient */
double Navigation_getDtheta();

/* Set steering */
void Navigation_setSteering(double dir);

/* Set navigation target speed */
void Navigation_setTargetSpeed(double speed);
double Navigation_getTargetSpeed();

/* Get steering */
double Navigation_getSteering();
double Navigation_getSteeringMillis();

/* Kill steering and navigation control */
void Navigation_kill();



/* Handle PID timer. Controls steering */
void Navigation_handleTimer();



#endif
