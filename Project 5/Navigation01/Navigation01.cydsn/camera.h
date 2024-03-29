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

void Camera_setMaxLineMisses(int val);
int Camera_getMaxLineMisses();

void Camera_setLineErrorTracking(int val);
int Camera_getLineErrorTracking();

double Camera_getLineMid();
double Camera_getLineMidFar();

double Camera_getLineAngle();

void Camera_handleTimer();

void Camera_reset();


#endif
