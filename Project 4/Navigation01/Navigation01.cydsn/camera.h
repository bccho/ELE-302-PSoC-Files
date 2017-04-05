/*-----------------------------------------------------------------*/
/* camera.h                                                        */
/*                                                                 */
/* BC Cho (bccho@) and TJ Smith (tjs8@)                            */
/*-----------------------------------------------------------------*/
#ifndef CAMERA_H
#define CAMERA_H

/*-----------------------------------------------------------------*/

void Camera_printValues();

void Camera_handleCompRise();

void Camera_handleCompFall();

void Camera_handleFrameStart();

double Camera_getLineMid();

double Camera_getLineAngle();

void Camera_reset();


#endif
