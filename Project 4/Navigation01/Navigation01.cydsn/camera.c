/*-----------------------------------------------------------------*/
/* camera.c                                                        */
/*                                                                 */
/* BC Cho (bccho@) and TJ Smith (tjs8@)                            */
/*-----------------------------------------------------------------*/
#include <camera.h>
#include <device.h>
#include <hardware.h>
#include <stdio.h>
#include <math.h>

/*-----------------------------------------------------------------*/

// Printing
static char strbuffer[100];

static const double EXPECTED_ROW_CYCLES = EXPECTED_ROW_TIME * CAM_CLK_FREQ;
static int maxLineMisses = 10;
//static const int MAX_LINE_CYCLES = 250; // max number of cycles for width of line

static int numFrames = 0;
static int numCompRise = 0;
static int numCompFall = 0;

static int lineBeginCyclesNear = 0;
static int lineEndCyclesNear = 0;
static int lineBeginCyclesFar = 0;
static int lineEndCyclesFar = 0;

static double lineMidNear = 0;
static double lineMidFar = 0;
static double lineAngle = 0;

static int numMissedNear = 0;
static int numMissedFar = 0;
static int compRiseNearSeen = 0;
static int compFallNearSeen = 0;
static int compRiseFarSeen = 0;
static int compFallFarSeen = 0;

static int lineMidNearStatus = 0;
static int lineMidFarStatus = 0;

/*-----------------------------------------------------------------*/

static int checkLineMidNear();
static int checkLineMidFar();

/*-----------------------------------------------------------------*/

void Camera_printValues() {
    sprintf(strbuffer, "Frame count = %d\n", numFrames);
    UART_PutString(strbuffer);
    sprintf(strbuffer, "Comparator counts (begin) = %d\n", numCompRise);
    UART_PutString(strbuffer);
    sprintf(strbuffer, "Comparator counts (end) = %d\n", numCompFall);
    UART_PutString(strbuffer);
    sprintf(strbuffer, "Line begin cycles (close) = %d\n", lineBeginCyclesNear);
    UART_PutString(strbuffer);
    sprintf(strbuffer, "Line end cycles (close) = %d\n", lineEndCyclesNear);
    UART_PutString(strbuffer);
    sprintf(strbuffer, "Line begin cycles (far) = %d\n", lineBeginCyclesFar);
    UART_PutString(strbuffer);
    sprintf(strbuffer, "Line end cycles (far) = %d\n", lineEndCyclesFar);
    UART_PutString(strbuffer);
}


void Camera_handleCompRise() {
    // Recorded number of cycles from row beign to comparator rise
    int lineBeginCyclesTemp = CAMERA_TIMER_PERIOD - Timer_Line_Begin_ReadCapture();
    // Row number in frame (close ~= 0, far ~= 260)
    int rowNum = Counter_Near_Row_ReadCounter();
    numCompRise++;
    
//    sprintf(strbuffer, "Rise: counterVal %4d | %6d %6d | %.3f | %7d %7d\n", rowNum, lineBeginCyclesNear, lineEndCyclesNear, lineMidNear, numFrames, numCompRiseTotal);
//    sprintf(strbuffer, "R: %3d %3d\n", rowNum, lineBeginCyclesTemp);
//    UART_PutString(strbuffer);
    
    // Check whether this is a near or far row event
    if (rowNum >= COUNTER_NEAR_ROW_COUNT) {
        lineBeginCyclesNear = lineBeginCyclesTemp;
        compRiseNearSeen = 1;
    }
    else {
        lineBeginCyclesFar = lineBeginCyclesTemp;
        compRiseFarSeen = 1;
    }
}


void Camera_handleCompFall() {
    // Recorded number of cycles from row beign to comparator rise
    int lineEndCyclesTemp = CAMERA_TIMER_PERIOD - Timer_Line_End_ReadCapture();
    // Row number in frame (close ~= 0, far ~= 260)
    int rowNum = Counter_Near_Row_ReadCounter();
    numCompFall++;
    
//    sprintf(strbuffer, "Fall: counterVal %4d | %6d %6d | %.3f\n", rowNum, lineBeginCyclesNear, lineEndCyclesNear, lineMidNear);
//    sprintf(strbuffer, "F: %3d %3d\n", rowNum, lineEndCyclesTemp);
//    UART_PutString(strbuffer);

    // Check whether this is a near or far row event
    if (rowNum >= COUNTER_NEAR_ROW_COUNT) {
        lineEndCyclesNear = lineEndCyclesTemp;
        compFallNearSeen = 1;
        
        // Calculate line width in cycles
        int lineWidthCycles = lineEndCyclesNear - lineBeginCyclesNear;
        // Verify line is reasonable width
        if (lineWidthCycles > 0.9*LINE_CYCLES_NEAR && lineWidthCycles < 1.1*LINE_CYCLES_NEAR) {
            // Middle of the line, normalized to (0,1)
            lineMidNear = ((lineEndCyclesNear + lineBeginCyclesNear)/2) / EXPECTED_ROW_CYCLES;
            numMissedNear = 0;
        }
        else {
            numMissedNear++;
        }
    }
    else {
        lineEndCyclesFar = lineEndCyclesTemp;
        compFallFarSeen = 1;
        
         // Calculate line width in cycles
        int lineWidthCycles = lineEndCyclesFar - lineBeginCyclesFar;
        // Verify line is reasonable width
        if (lineWidthCycles > 0.9*LINE_CYCLES_FAR && lineWidthCycles < 1.1*LINE_CYCLES_FAR) {
            // Middle of the line, normalized to (0,1)
            lineMidFar = ((lineEndCyclesFar + lineBeginCyclesFar)/2) / EXPECTED_ROW_CYCLES;
            numMissedFar = 0;
        }
        else {
            numMissedFar++;
        }
    }
    
//    sprintf(strbuffer, "%3d %3d %3d %3d %3d\n", rowNum, lineEndCyclesNear, lineEndCyclesFar, numMissedNear, numMissedFar);
//    UART_PutString(strbuffer);
}

void Camera_handleFrameStart() {
//    UART_PutString("Frame\n");
    Timer_Line_Begin_ClearFIFO();
    Timer_Line_End_ClearFIFO();
    numFrames++;
}

void Camera_setMaxLineMisses(int val) {
    if (val > 0) maxLineMisses = val;
}

int Camera_getMaxLineMisses() {
    return maxLineMisses;
}

double Camera_getLineMid() {
    if (lineMidNearStatus < 0) return lineMidNearStatus;
    return lineMidNear;
}

double Camera_getLineMidFar() {
    if (lineMidFarStatus < 0) return lineMidFarStatus;
    return lineMidFar;
}

double Camera_getLineAngle() {
    if (lineMidNearStatus < 0 && lineMidFarStatus < 0) {
        return -10;
    }
    lineAngle = lineMidNear - lineMidFar;
    return lineAngle;
}

void Camera_handleTimer() {
    lineMidNearStatus = checkLineMidNear();
    lineMidFarStatus = checkLineMidFar();
}

void Camera_reset() {
    numFrames = 0;
    numCompRise = 0;
    numCompFall = 0;
    
    lineBeginCyclesNear = 0;
    lineEndCyclesNear = 0;
    lineBeginCyclesFar = 0;
    lineEndCyclesFar = 0;
    
    lineMidNear = 0;
    lineMidFar = 0;
    lineAngle = 0;
    
    numMissedNear = 0;
    numMissedFar = 0;
}

static int checkLineMidNear() {
    if (numMissedNear > maxLineMisses) return -1;
    else if (compRiseNearSeen == 0) return -2;
    else if (compFallNearSeen == 0) return -3;
    else {
        compRiseNearSeen = 0;
        compFallNearSeen = 0;
        return 0;
    }
}

static int checkLineMidFar() {
    if (numMissedFar > maxLineMisses) return -1;
    else if (compRiseFarSeen == 0) return -2;
    else if (compFallFarSeen == 0) return -3;
    else {
        compRiseFarSeen = 0;
        compFallFarSeen = 0;
        return 0;
    }
}
