/*-----------------------------------------------------------------*/
/* main.c                                                          */
/*                                                                 */
/* BC Cho (bccho@) and TJ Smith (tjs8@)                            */
/*-----------------------------------------------------------------*/
#include <device.h>
#include <stdio.h>
#include <speedcontrol.h>
#include <serial.h>

char buildVersion[] = "Build 1.0.0";
char strbuffer[100];

// Function prototypes
void parseMessage();


int buttonInterrupted = 0;
int rxInterrupted = 0;
int wheelTickInterrupted = 0;
int tickTimeoutInterrupted = 0;
int pidTimerInterrupted = 0;
int camCompRiseInterrupted = 0;
int camCompFallInterrupted = 0;
int camRowInterrupted = 0;
int camFrameInterrupted = 0;

int numFrames = 0;
int numRows = 0;
int numCompBegin = 0;
int numCompEnd = 0;
int rowCycles = 0;
int lineBeginCycles = 0;
int lineEndCycles = 0;
#define CAM_CLK_FREQ 12000000
const double MAIN_CLK_FREQ = 100000;

// Control pulse times in s
const double MIN_TIME_SERVO = 0.00105;
const double MAX_TIME_SERVO = 0.00169;

const double CAMERA_TIMER_PERIOD = 65536;

#define EXPECTED_ROW_TIME 0.000059
const double EXPECTED_ROW_CYCLES = EXPECTED_ROW_TIME * CAM_CLK_FREQ;

int test6 = 0;
int test7 = 0;
int test8 = 0;
int test9 = 0;

double lineMid = 0;

double floor(double a) {
    return (double) (int) a;
}

double ceil(double a) {
    return floor(a) + 1;
}

/*
 * parseMessage()
 *
 * Parse serial input string and act on it
 *
 * Inputs: message
 * Returns: none
 */
void parseMessage(char *message) {
    if (message == NULL) return;
    
    char msgPrefix[4];
    if (sscanf(message, "%3[A-Za-z]", msgPrefix) == 1) {
        int prefixLen = strlen(msgPrefix);
        
        // Messages of the form "CTx" (x integer) set the duty cycle to x out of MAX_THROTTLE
        if (strcmp(msgPrefix, "CT") == 0) {
            int value = 0;
            if (sscanf(message + prefixLen, "%i", &value) > 0) {
                SpeedControl_setThrottle(value);
            }
            sprintf(strbuffer, "Throttle = %i\n", SpeedControl_getThrottle());
            UART_PutString(strbuffer);
        }
        
        // Messages beginning with "G" return the throttle, speed, and PID controls
        else if (strcmp(msgPrefix, "G") == 0) {
            sprintf(strbuffer, "Throttle: %d\nSpeed: %f ft/s\nP = %.2f\tI = %.2f\tD = %.2f\n", 
                    SpeedControl_getThrottle(), SpeedControl_getSpeed(), SpeedControl_getP(), 
                    SpeedControl_getI(), SpeedControl_getD());
            UART_PutString(strbuffer);
        }
        
        // Messages beginning with "TP" toggle PID control
        else if (strcmp(msgPrefix, "TP") == 0) {
            if (!SpeedControl_isEnabled()) {
                SpeedControl_enable();
            } else {
                SpeedControl_disable();
            }
            if (SpeedControl_isEnabled()) {
                UART_PutString("PID control on\n");
            } else {
                UART_PutString("PID control off\n");
            }
        }
        
        // Messages of the form "TPT" toggle distance control
        else if (strcmp(msgPrefix, "TDC") == 0) {
            if (!SpeedControl_isDistanceControlEnabled()) {
                SpeedControl_enableDistanceControl();
            } else {
                SpeedControl_disableDistanceControl();
            }
            if (SpeedControl_isDistanceControlEnabled()) {
                UART_PutString("Distance control on\n");
            } else {
                UART_PutString("Distance control off\n");
            }
        }
        
        // Messages beginning with "TDS" toggle whether we dynamically update target speed to reach distance
        else if (strcmp(msgPrefix, "TDS") == 0) {
            if (!SpeedControl_isDynamicTargetUpdateEnabled()) {
                SpeedControl_enableDynamicTargetUpdate();
            } else {
                SpeedControl_disableDynamicTargetUpdate();
            }
            if (SpeedControl_isDynamicTargetUpdateEnabled()) {
                UART_PutString("Dynamic target speed update on\n");
            } else {
                UART_PutString("Dynamic target speed update off\n");
            }
        }
        
        // Messages of the form "CPx" (x integer) change the proportional term to x
        else if (strcmp(msgPrefix, "CP") == 0) {
            int value = 0;
            if (sscanf(message + prefixLen, "%i", &value) > 0) {
                SpeedControl_setP(value);
            }

            sprintf(strbuffer, "P = %.2f\n", SpeedControl_getP());
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "CIx" (x float) change the integral term to x
        else if (strcmp(msgPrefix, "CI") == 0) {
            double value = 0;
            if (sscanf(message + prefixLen, "%lf", &value) > 0) {
                SpeedControl_setI(value);
            }

            sprintf(strbuffer, "I = %.2f\n", SpeedControl_getI());
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "CDx" (x integer) change the derivative term to x
        else if (strcmp(msgPrefix, "CD") == 0) {
            int value = 0;
            if (sscanf(message + prefixLen, "%i", &value) > 0) {
                SpeedControl_setD(value);
            }

            sprintf(strbuffer, "D = %.2f\n", SpeedControl_getD());
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "CSSx" (x integer) change steady state throttle to x
         else if (strcmp(msgPrefix, "CSS") == 0) {
            int value = 0;
            if (sscanf(message + prefixLen, "%i", &value) > 0) {
                SpeedControl_setSteadyStateThrottle(value);
            }
            
            sprintf(strbuffer, "SS Throttle = %i\n", SpeedControl_getSteadyStateThrottle());
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "CTSx" (x float) change target speed to x ft/s
        else if (strcmp(msgPrefix, "CTS") == 0) {
            double value = 0;
            if (sscanf(message + prefixLen, "%lf", &value) > 0) {
                SpeedControl_setTargetSpeed(value);
            }
            
            sprintf(strbuffer, "Target Speed = %f ft/s\n", SpeedControl_getTargetSpeed());
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "CTDx" (x float) change target distance to x ft
        else if (strcmp(msgPrefix, "CTD") == 0) {
            double value = 0;
            if (sscanf(message + prefixLen, "%lf", &value) > 0) {
                SpeedControl_setTargetDistance(value);
            }
            
            sprintf(strbuffer, "Target distance = %.2f ft\n", SpeedControl_getTargetDistance());
            UART_PutString(strbuffer);
        }
        
        // Message of the form "TVP" toggle verbose printout for speed PID control
        else if (strcmp(msgPrefix, "TVP") == 0) {
            if (!SpeedControl_isVerbosePrintoutEnabled()) {
                SpeedControl_enableVerbosePrintout();
            } else {
                SpeedControl_disableVerbosePrintout();
            }
            if (SpeedControl_isVerbosePrintoutEnabled()) {
                UART_PutString("Verbose printout on\n");
            } else {
                UART_PutString("Verbose printout off\n");
            }
        }
        
        // Messages starting with "A" will abort
        else if (strcmp(msgPrefix, "A") == 0) {
            SpeedControl_kill();
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        // Messages of the form "GC" retun all camera variables
        else if (strcmp(msgPrefix, "GC") == 0) {
            sprintf(strbuffer, "Frame count = %d\nRow count = %d\nComparator counts (begin) = %d\nComparator counts (end) = %d\nRow cycles = %d\nLine begin cycles = %d\nLine end cycles = %d\n",
                    numFrames, numRows, numCompBegin, numCompEnd, rowCycles, lineBeginCycles, lineEndCycles);
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "GT" retun all test variables
        else if (strcmp(msgPrefix, "GT") == 0) {
            sprintf(strbuffer, "Frame count = %d\nComparator counts (begin) = %d\nComparator counts (end) = %d\nLine begin cycles = %d\nLine end cycles = %d\n",
                    numFrames, numCompBegin, numCompEnd, lineBeginCycles, lineEndCycles);
            UART_PutString(strbuffer);
            sprintf(strbuffer, "6: %d\n7: %d\n9: %d\nLine mid: %f\n", test6, test7, test9, lineMid);
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "RC" resets camera variables
        else if (strcmp(msgPrefix, "RC") == 0) {
            numCompBegin = 0;
            numCompEnd = 0;
            numFrames = 0;
            numRows = 0;
            
            rowCycles = 0;
            lineBeginCycles = 0;
            lineEndCycles = 0;
            
            UART_PutString("Camera variables reset\n");
        }
        
        // Messages of the form "CSx" change servo direction to x (0 is full left, 1 is full right)
        else if (strcmp(msgPrefix, "CS") == 0) {
            double value = 0;
            if (sscanf(message + prefixLen, "%lf", &value) > 0) {
                if (value > 1) value = 1;
                if (value < 0) value = 0;
                double servoTime = MIN_TIME_SERVO + (MAX_TIME_SERVO - MIN_TIME_SERVO) * value;
                double servoPeriod = servoTime * MAIN_CLK_FREQ;
                double midPeriod = 0.5*(MAX_TIME_SERVO + MIN_TIME_SERVO) * MAIN_CLK_FREQ;
                if (servoPeriod > midPeriod) servoPeriod = floor(servoPeriod);
                else servoPeriod = ceil(servoPeriod);
                PWM_Servo_WriteCompare(servoPeriod);
            }
            double servoVal = PWM_Servo_ReadCompare() / MAIN_CLK_FREQ;
            double setVal = (servoVal - MIN_TIME_SERVO) / (MAX_TIME_SERVO - MIN_TIME_SERVO);
            sprintf(strbuffer, "Servo set to %.3f (%.3f ms)\n", setVal, servoVal*1000);
            UART_PutString(strbuffer);
        }
    }
}


/* Button interrupt */
CY_ISR(button_inter) {
//    if (buttonInterrupted) {
//        UART_PutString("Error 1: Interrupt not handled\n");
//    }
    buttonInterrupted = 1;
}

/* Recieved data interrupt */
CY_ISR(rx_inter) {
//    if (rxInterrupted) {
//        UART_PutString("Error 2: Interrupt not handled\n");
//    }
    rxInterrupted = 1;
}

/* Wheel tick interrupt */
CY_ISR(wheel_inter) {
//    if (wheelTickInterrupted) {
//        UART_PutString("Error 3: Interrupt not handled\n");
//    }
    wheelTickInterrupted = 1;
}

/* Wheel tick timeout interrupt */
CY_ISR(timeout_inter) {
//    if (tickTimeoutInterrupted) {
//        UART_PutString("Error 4: Interrupt not handled\n");
//    }
    tickTimeoutInterrupted = 1;
}

/* PID timer interrupt */
CY_ISR(pid_inter) {
//    if (pidTimerInterrupted) {
//        UART_PutString("Error 5: Interrupt not handled\n");
//    }
    pidTimerInterrupted = 1;
}

/* Camera comparator rise interrupt */
CY_ISR(cam_comp_rise_inter) {
//    if (camCompRiseInterrupted) {
//        UART_PutString("Error 6: Interrupt not handled\n");
//    }
//    test6++;
    camCompRiseInterrupted = 1;
}

/* Camera comparator fall interrupt */
CY_ISR(cam_comp_fall_inter) {
//    if (camCompFallInterrupted) {
//        UART_PutString("Error 7: Interrupt not handled\n");
//    }
//    test7++;
    camCompFallInterrupted = 1;
}

/* Camera frame start interrupt */
CY_ISR(cam_frame_inter) {
//    if (camFrameInterrupted) {
//        UART_PutString("Error 9: Interrupt not handled\n");
//    }
//    test9++;
    camFrameInterrupted = 1;
}

int main() {
    /* Initialization */
    CyGlobalIntEnable; // Enable global interrupts
    
    // Start LCD
    LCD_Start();
    
    // Start motor PWM
    PWM_Motor_Start();
    
    // Start servo PWM
    PWM_Servo_Start();
    PWM_Servo_WriteCompare((MIN_TIME_SERVO + MAX_TIME_SERVO)/2 * MAIN_CLK_FREQ);
    
    // Start pushbutton
    inter_button_Start();
    inter_button_SetVector(button_inter);
    
    // Start UART
    UART_Start();
    rx_rcvd_Start();
    rx_rcvd_SetVector(rx_inter);
    
    // Start wheel tick timer
    Timer_Wheel_Tick_Start();
    wheel_tick_Start();
    wheel_tick_SetVector(wheel_inter);
    
    // Start tick timeout counter
    Counter_Tick_Timeout_Start();
    tick_timeout_Start();
    tick_timeout_SetVector(timeout_inter);
    
    // Start PID update counter
    Counter_PID_Start();
    throttle_update_Start();
    throttle_update_SetVector(pid_inter);
    
    // Start camera interrupts
    camera_comp_rise_Start();
    camera_comp_rise_SetVector(cam_comp_rise_inter);
    camera_comp_fall_Start();
    camera_comp_fall_SetVector(cam_comp_fall_inter);
    camera_frame_start_Start();
    camera_frame_start_SetVector(cam_frame_inter);
    Timer_Line_Begin_Start();
    Timer_Line_End_Start(); 
    Timer_Row_Start();
    
    Counter_First_Row_Start();
    Counter_Last_Row_Start();
    
    // LCD initial text
    LCD_Position(0, 0);
    LCD_PrintString(buildVersion);
    
    // Init serial
    Serial_init();
    
    // Init speed control
    SpeedControl_init();
    
    for(;;)
    {
        // Handle push button interrupt
        if (buttonInterrupted) {
            if (SpeedControl_isEnabled()) {
                SpeedControl_kill();
            } else {
                SpeedControl_enableDistanceControl();
                SpeedControl_enable();
            }
            buttonInterrupted = 0;
        }
        
        // Handle incoming serial data
        if (rxInterrupted) {
            char *message = Serial_handleData();
            parseMessage(message);
            rxInterrupted = 0;
        }
        
        // Handle wheel ticks
        if (wheelTickInterrupted) {
            SpeedControl_handleWheelTick();
            wheelTickInterrupted = 0;
        }
        
        // Handle wheel tick timeout
        if (tickTimeoutInterrupted) {
            SpeedControl_handleWheelTickTimeout();
            tickTimeoutInterrupted = 0;
        }
        
        // Perform PID update and update time count
        if (pidTimerInterrupted) {
            SpeedControl_handleTimer();
            sprintf(strbuffer, "Line mid: %f\n", lineMid);
            UART_PutString(strbuffer);
            pidTimerInterrupted = 0;
        }
        
        // Handle comparator rise interrupt
        if (camCompRiseInterrupted) {
            double lineBeginCyclesTemp = CAMERA_TIMER_PERIOD - Timer_Line_Begin_ReadCapture();
            if (lineBeginCyclesTemp > 0.15*EXPECTED_ROW_CYCLES && lineBeginCyclesTemp < 0.95*EXPECTED_ROW_CYCLES) {
                numCompBegin++;
                lineBeginCycles = lineBeginCyclesTemp;
            }
            camCompRiseInterrupted = 0;
        }
        
        // Handle comparator fall interrupt
        if (camCompFallInterrupted) {
            double lineEndCyclesTemp = CAMERA_TIMER_PERIOD - Timer_Line_End_ReadCapture();
            if (lineEndCyclesTemp > 0.15*EXPECTED_ROW_CYCLES && lineEndCyclesTemp < 0.95*EXPECTED_ROW_CYCLES) {
                numCompEnd++;
                lineEndCycles = lineEndCyclesTemp;
                int diff = lineEndCycles - lineBeginCycles;
                if (diff < 150 && diff > 0) {
                    lineMid = ((lineEndCycles + lineBeginCycles)/2)/EXPECTED_ROW_CYCLES;
                }
            }
            camCompFallInterrupted = 0;
        }
        
        // Handle frame interrupts
        if (camFrameInterrupted) {
            numFrames++;
            camFrameInterrupted = 0;
        }
    }
    
    return 0;
}

/* [] END OF FILE */
