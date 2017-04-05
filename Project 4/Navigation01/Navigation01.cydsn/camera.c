/*-----------------------------------------------------------------*/
/* camera.c                                                        */
/*                                                                 */
/* BC Cho (bccho@) and TJ Smith (tjs8@)                            */
/*-----------------------------------------------------------------*/
#include <camera.h>
#include <device.h>
#include <hardware.h>
#include <stdio.h>

/*-----------------------------------------------------------------*/

// Printing
static char strbuffer[100];

static const double EXPECTED_ROW_CYCLES = EXPECTED_ROW_TIME * CAM_CLK_FREQ;
static const int MAX_MISSES = 10;
static const int MAX_LINE_CYCLES = 250; // max number of cycles for width of line

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

void Camera_printValues() {
    sprintf(strbuffer, "Frame count = %d\n", numFrames);
    UART_PutString(strbuffer);
    sprintf(strbuffer, "Comparator counts (begin) = %d\n", numCompBeginTotal);
    UART_PutString(strbuffer);
    sprintf(strbuffer, "Comparator counts (end) = %d\n", numCompEndTotal);
    UART_PutString(strbuffer);
    sprintf(strbuffer, "Line begin cycles (close) = %d\n", lineBeginCyclesClose);
    UART_PutString(strbuffer);
    sprintf(strbuffer, "Line end cycles (close) = %d\n", lineEndCyclesClose);
    UART_PutString(strbuffer);
    sprintf(strbuffer, "Line begin cycles (far) = %d\n", lineBeginCyclesFar);
    UART_PutString(strbuffer);
    sprintf(strbuffer, "Line end cycles (far) = %d\n", lineEndCyclesFar);
    UART_PutString(strbuffer);
}


void Camera_handleCompRise() {
    double lineBeginCyclesTemp = CAMERA_TIMER_PERIOD - Timer_Line_Begin_ReadCapture();
    int counterVal = Counter_Last_Row_ReadCounter();
    numCompBeginTotal++;
    if (0.15*EXPECTED_ROW_CYCLES < lineBeginCyclesTemp && lineBeginCyclesTemp < 0.95*EXPECTED_ROW_CYCLES) {
        numCompBeginReal++;
        if (1) {
//        if (counterVal < COUNTER_LAST_ROW_COUNT) {
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
    if (0.15*EXPECTED_ROW_CYCLES < lineEndCyclesTemp && lineEndCyclesTemp < 0.95*EXPECTED_ROW_CYCLES) {
        numCompEndReal++;
        if (1) {
//        if (counterVal < COUNTER_LAST_ROW_COUNT) {
            lineEndCyclesClose = lineEndCyclesTemp;
            
            int diff = lineEndCyclesClose - lineBeginCyclesClose;
            if (diff < MAX_LINE_CYCLES && diff > 0) {
                lineMid = ((lineEndCyclesClose + lineBeginCyclesClose)/2)/EXPECTED_ROW_CYCLES;
                numMissed = 0;
            }
            else {
                numMissed++;
            }
//            sprintf(strbuffer, "Close line cycles: %6d %6d | %.3f\n", lineBeginCyclesClose, lineEndCyclesClose, lineMid);
//            UART_PutString(strbuffer);
        }
        else {
            lineEndCyclesFar = lineEndCyclesTemp;
            
            int diff = lineEndCyclesFar - lineBeginCyclesFar;
            if (diff < MAX_LINE_CYCLES && diff > 0) {
                lineMidFar = ((lineEndCyclesFar + lineBeginCyclesFar)/2)/EXPECTED_ROW_CYCLES;
                numMissed = 0;
            }
            else {
                numMissed++;
            }
//            sprintf(strbuffer, "Far line cycles:   %6d %6d | %.3f\n", lineBeginCyclesFar, lineEndCyclesFar, lineMidFar);
//            UART_PutString(strbuffer);
        }
    }
    else {
        //numMissed++;
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
    // TODO: line angle calculation
    return lineAngle;
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