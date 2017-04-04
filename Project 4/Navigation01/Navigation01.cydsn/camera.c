/*-----------------------------------------------------------------*/
/* camera.c                                                        */
/*                                                                 */
/* BC Cho (bccho@) and TJ Smith (tjs8@)                            */
/*-----------------------------------------------------------------*/
#include <camera.h>
#include <device.h>
#include <hardware.h>

/*-----------------------------------------------------------------*/

static const double EXPECTED_ROW_CYCLES = EXPECTED_ROW_TIME * CAM_CLK_FREQ;
static const int MAX_MISSES = 5;

static int numFrames = 0;
static int numCompBeginTotal = 0;
static int numCompEndTotal = 0;
static int numCompBeginReal = 0;
static int numCompEndReal = 0;

static int lineBeginCyclesClose = 0;
static int lineEndCyclesClose = 0;
static int lineBeginCyclesFar = 0;
static int lineEndCyclesFar = 0;

static double lineMid = 0;
static double lineMidFar = 0;
static double lineAngle = 0;

static int numMissed = 0;


/*-----------------------------------------------------------------*/


void Camera_handleCompRise() {
    double lineBeginCyclesTemp = CAMERA_TIMER_PERIOD - Timer_Line_Begin_ReadCapture();
    int counterVal = Counter_Last_Row_ReadCounter();
    numCompBeginTotal++;
    if (lineBeginCyclesTemp > 0.15*EXPECTED_ROW_CYCLES && lineBeginCyclesTemp < 0.95*EXPECTED_ROW_CYCLES) {
        numCompBeginReal++;
        if (counterVal < COUNTER_LAST_ROW_COUNT) {
            lineBeginCyclesClose = lineBeginCyclesTemp;
        }
        else {
            lineBeginCyclesFar = lineBeginCyclesTemp;
        }
    }
}


void Camera_handleCompFall() {
    double lineEndCyclesTemp = CAMERA_TIMER_PERIOD - Timer_Line_End_ReadCapture();
    int counterVal = Counter_Last_Row_ReadCounter();
    numCompEndTotal++;
    if (lineEndCyclesTemp > 0.15*EXPECTED_ROW_CYCLES && lineEndCyclesTemp < 0.95*EXPECTED_ROW_CYCLES) {
        numCompEndReal++;
        if (counterVal < COUNTER_LAST_ROW_COUNT) {
            lineEndCyclesClose = lineEndCyclesTemp;
            
            int diff = lineEndCyclesClose - lineBeginCyclesClose;
            if (diff < 150 && diff > 0) {
                lineMid = ((lineEndCyclesClose + lineBeginCyclesClose)/2)/EXPECTED_ROW_CYCLES;
                numMissed = 0;
            }
            else {
                numMissed++;
            }
        }
        else {
            lineEndCyclesFar = lineEndCyclesTemp;
            
            int diff = lineEndCyclesFar - lineBeginCyclesFar;
            if (diff < 150 && diff > 0) {
                lineMidFar = ((lineEndCyclesFar + lineBeginCyclesFar)/2)/EXPECTED_ROW_CYCLES;
                numMissed = 0;
            }
            else {
                numMissed++;
            }
        }
    }
    else {
        numMissed++;
    }
}

void Camera_handleFrameStart() {
    numFrames++;
}


double Camera_getLineMid() {
    if (numMissed > MAX_MISSES) {
        return -1;
    }
    else {
        return lineMid;
    }
}

double Camera_getLineAngle() {
    if (numMissed > MAX_MISSES) {
        return -1;
    }
    else {
        // TODO: line angle calculation
        return lineAngle;
    }
}


void Camera_reset() {
    numFrames = 0;
    numCompBeginTotal = 0;
    numCompEndTotal = 0;
    numCompBeginReal = 0;
    numCompEndReal = 0;
    
    lineBeginCyclesClose = 0;
    lineEndCyclesClose = 0;
    lineBeginCyclesFar = 0;
    lineEndCyclesFar = 0;
    
    lineMid = 0;
    lineAngle = 0;
    
    numMissed = 0;
}