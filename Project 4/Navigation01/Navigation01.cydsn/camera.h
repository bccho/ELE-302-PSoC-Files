/*-----------------------------------------------------------------*/
/* camera.h                                                        */
/*                                                                 */
/* BC Cho (bccho@) and TJ Smith (tjs8@)                            */
/*-----------------------------------------------------------------*/
#ifndef CAMERA_H
#define CAMERA_H

/*-----------------------------------------------------------------*/


void Camera_handleCompRise();

void Camera_handleCompFall();

void Camera_handleFrameStart();

double Camera_getLineMid();

double Camera_getLineAngle();

void Camera_reset();











/* Initializes serial communications */
void Serial_init();

/* Handles incoming serial data 
   Returns: null if transmission is not complete, the transmitted
            string otherwise */
char *Serial_handleData();



#endif
