/*-----------------------------------------------------------------*/
/* main.c                                                          */
/*                                                                 */
/* BC Cho (bccho@) and TJ Smith (tjs8@)                            */
/*-----------------------------------------------------------------*/
#include <device.h>
#include <hardware.h>
#include <stdio.h>
#include <speedcontrol.h>
#include <navigation.h>
#include <camera.h>
#include <serial.h>

static char buildVersion[] = "Build 1.0.0";
static char strbuffer[100];

// Function prototypes
static void parseMessage();


static int buttonInterrupted = 0;
static int rxInterrupted = 0;
static int wheelTickInterrupted = 0;
static int tickTimeoutInterrupted = 0;
static int pidTimerInterrupted = 0;
static int camCompRiseInterrupted = 0;
static int camCompFallInterrupted = 0;
static int camFrameInterrupted = 0;

/*
 * parseMessage()
 *
 * Parse serial input string and act on it
 *
 * Inputs: message
 * Returns: none
 */
static void parseMessage(char *message) {
    if (message == NULL) return;
    
    char msgPrefix[5];
    if (sscanf(message, "%4[A-Za-z]", msgPrefix) == 1) {
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
        
        // Messages beginning with "GS" return the throttle, speed, and PID controls
        else if (strcmp(msgPrefix, "GS") == 0) {
            sprintf(strbuffer, "Throttle: %d\nSpeed: %f ft/s\nP = %.2f\tI = %.2f\tD = %.2f\n", 
                    SpeedControl_getThrottle(), SpeedControl_getSpeed(), SpeedControl_getP(), 
                    SpeedControl_getI(), SpeedControl_getD());
            UART_PutString(strbuffer);
        }
        
        // Messages beginning with "TS" toggle speed PID control
        else if (strcmp(msgPrefix, "TS") == 0) {
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
        
        // Messages of the form "TDC" toggle distance control
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
        
        // Messages of the form "CPSx" (x integer) change the proportional term to x
        else if (strcmp(msgPrefix, "CPS") == 0) {
            int value = 0;
            if (sscanf(message + prefixLen, "%i", &value) > 0) {
                SpeedControl_setP(value);
            }

            sprintf(strbuffer, "Pspeed = %.2f\n", SpeedControl_getP());
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "CISx" (x float) change the integral term to x
        else if (strcmp(msgPrefix, "CIS") == 0) {
            double value = 0;
            if (sscanf(message + prefixLen, "%lf", &value) > 0) {
                SpeedControl_setI(value);
            }

            sprintf(strbuffer, "Ispeed = %.2f\n", SpeedControl_getI());
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "CDSx" (x integer) change the derivative term to x
        else if (strcmp(msgPrefix, "CDS") == 0) {
            int value = 0;
            if (sscanf(message + prefixLen, "%i", &value) > 0) {
                SpeedControl_setD(value);
            }

            sprintf(strbuffer, "Dspeed = %.2f\n", SpeedControl_getD());
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
        
        // Message of the form "TVS" toggle verbose printout for speed PID control
        else if (strcmp(msgPrefix, "TVS") == 0) {
            if (!SpeedControl_isVerbosePrintoutEnabled()) {
                SpeedControl_enableVerbosePrintout();
            } else {
                SpeedControl_disableVerbosePrintout();
            }
            if (SpeedControl_isVerbosePrintoutEnabled()) {
                UART_PutString("Throttle verbose printout on\n");
            } else {
                UART_PutString("Throttle verbose printout off\n");
            }
        }
        
        // Messages starting with "A" will abort
        else if (strcmp(msgPrefix, "A") == 0 || strcmp(msgPrefix, "a") == 0) {
            SpeedControl_kill();
            Navigation_kill();
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        // Messages of the form "GC" retun all camera variables
        else if (strcmp(msgPrefix, "GC") == 0) {
            Camera_printValues();
        }
        
        // Messages of the form "RC" resets camera variables
        else if (strcmp(msgPrefix, "RC") == 0) {
            Camera_reset();
            UART_PutString("Camera variables reset\n");
        }
        
        // Messages of the form "CSx" change servo direction to x (0 is full left, 1 is full right)
        else if (strcmp(msgPrefix, "CS") == 0) {
            double value = 0;
            if (sscanf(message + prefixLen, "%lf", &value) > 0) {
                if (value > 1) value = 1;
                if (value < 0) value = 0;
                Navigation_setSteering(value * 2 - 1);
            }
            double servoVal = Navigation_getSteeringMillis();
            double setVal = (Navigation_getSteering() + 1) / 2;
            sprintf(strbuffer, "Servo set to %.3f (%.3f ms)\n", setVal, servoVal);
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "CMMx" change maximum line misses to x (must be positive int)
        else if (strcmp(msgPrefix, "CMM") == 0) {
            int value = 0;
            if (sscanf(message + prefixLen, "%d", &value) > 0) {
                Camera_setMaxLineMisses(value);
            }
            sprintf(strbuffer, "Maximum line misses set to %d\n", Camera_getMaxLineMisses());
            UART_PutString(strbuffer);
        }
        
        
        
        // Messages beginning with "TN" toggle navigation/steering control
        else if (strcmp(msgPrefix, "TN") == 0) {
            if (!Navigation_isEnabled()) {
                Navigation_enable();
            } else {
                Navigation_disable();
            }
            if (Navigation_isEnabled()) {
                UART_PutString("Steering control on\n");
            } else {
                UART_PutString("Steering control off\n");
            }
        }
        
        // Messages of the form "CPLx" (x float) change the proportional line term to x
        else if (strcmp(msgPrefix, "CPL") == 0) {
            double value = 0;
            if (sscanf(message + prefixLen, "%lf", &value) > 0) {
                Navigation_setPline(value);
            }

            sprintf(strbuffer, "Pline = %.2f\n", Navigation_getPline());
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "CILx" (x float) change the integral line term to x
        else if (strcmp(msgPrefix, "CIL") == 0) {
            double value = 0;
            if (sscanf(message + prefixLen, "%lf", &value) > 0) {
                Navigation_setIline(value);
            }

            sprintf(strbuffer, "Iline = %.2f\n", Navigation_getIline());
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "CIILx" (x float) change the integral line term to x
        else if (strcmp(msgPrefix, "CIIL") == 0) {
            double value = 0;
            if (sscanf(message + prefixLen, "%lf", &value) > 0) {
                Navigation_setIIline(value);
            }

            sprintf(strbuffer, "IIline = %.2f\n", Navigation_getIIline());
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "CDLx" (x float) change the derivative line term to x
        else if (strcmp(msgPrefix, "CDL") == 0) {
            double value = 0;
            if (sscanf(message + prefixLen, "%lf", &value) > 0) {
                Navigation_setDline(value);
            }

            sprintf(strbuffer, "Dline = %.2f\n", Navigation_getDline());
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "CPTx" (x float) change the proportional theta term to x
        else if (strcmp(msgPrefix, "CPT") == 0) {
            double value = 0;
            if (sscanf(message + prefixLen, "%lf", &value) > 0) {
                Navigation_setPtheta(value);
            }

            sprintf(strbuffer, "Ptheta = %.2f\n", Navigation_getPtheta());
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "CITx" (x float) change the integral theta term to x
        else if (strcmp(msgPrefix, "CIT") == 0) {
            double value = 0;
            if (sscanf(message + prefixLen, "%lf", &value) > 0) {
                Navigation_setIline(value);
            }

            sprintf(strbuffer, "Itheta = %.2f\n", Navigation_getItheta());
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "CDTx" (x float) change the derivative theta term to x
        else if (strcmp(msgPrefix, "CDT") == 0) {
            double value = 0;
            if (sscanf(message + prefixLen, "%lf", &value) > 0) {
                Navigation_setDtheta(value);
            }

            sprintf(strbuffer, "Dtheta = %.2f\n", Navigation_getDtheta());
            UART_PutString(strbuffer);
        }
        
        // Messages of the form "CTSNx" (x float) change target speed to x ft/s for navigation
        else if (strcmp(msgPrefix, "CTSN") == 0) {
            double value = 0;
            if (sscanf(message + prefixLen, "%lf", &value) > 0) {
                Navigation_setTargetSpeed(value);
            }
            
            sprintf(strbuffer, "Navigation Target Speed = %f ft/s\n", Navigation_getTargetSpeed());
            UART_PutString(strbuffer);
        }
        
        // Message of the form "TLE" toggle line error tracking
        else if (strcmp(msgPrefix, "TLE") == 0) {
            if (!Camera_getLineErrorTracking()) {
                Camera_setLineErrorTracking(1);
            } else {
                Camera_setLineErrorTracking(0);
            }
            if (Camera_getLineErrorTracking()) {
                UART_PutString("Line error tracking on\n");
            } else {
                UART_PutString("Line error tracking off\n");
            }
        }
        
        // Message of the form "TVN" toggle verbose printout for navigation/steering PID control
        else if (strcmp(msgPrefix, "TVN") == 0) {
            if (!Navigation_isVerbosePrintoutEnabled()) {
                Navigation_enableVerbosePrintout();
            } else {
                Navigation_disableVerbosePrintout();
            }
            if (Navigation_isVerbosePrintoutEnabled()) {
                UART_PutString("Navigation verbose printout on\n");
            } else {
                UART_PutString("Navigation verbose printout off\n");
            }
        }
    }
}


/* Button interrupt */
CY_ISR(button_inter) {
    buttonInterrupted = 1;
}

/* Recieved data interrupt */
CY_ISR(rx_inter) {
    rxInterrupted = 1;
}

/* Wheel tick interrupt */
CY_ISR(wheel_inter) {
    wheelTickInterrupted = 1;
}

/* Wheel tick timeout interrupt */
CY_ISR(timeout_inter) {
    tickTimeoutInterrupted = 1;
}

/* PID timer interrupt */
CY_ISR(pid_inter) {
    pidTimerInterrupted = 1;
}

/* Camera comparator rise interrupt */
CY_ISR(cam_comp_rise_inter) {
    camCompRiseInterrupted = 1;
}

/* Camera comparator fall interrupt */
CY_ISR(cam_comp_fall_inter) {
    camCompFallInterrupted = 1;
}

/* Camera frame start interrupt */
CY_ISR(cam_frame_inter) {
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
    Navigation_setSteering(0);
    
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
    
    // Start camera timers and counters
    Timer_Line_Begin_Start();
    Timer_Line_End_Start(); 
    
    Counter_Far_Row_Start();
    Counter_Near_Row_Start();
    
    Timer_Comp_Ignore_1_Start();
    Timer_Comp_Ignore_2_Start();
    
    // Init serial
    Serial_init();
    
    // Init control
    SpeedControl_init();
    Navigation_init();
    
    // LCD initial text
    LCD_ClearDisplay();
    LCD_Position(0, 0);
    LCD_PrintString(buildVersion);
    
    for(;;)
    {
        // Handle push button interrupt
        if (buttonInterrupted) {
            if (SpeedControl_isEnabled()) {
                SpeedControl_kill();
                Navigation_kill();
            } else {
                SpeedControl_setTargetDistance(107.1);
                SpeedControl_enableDistanceControl();
                SpeedControl_enable();
                Navigation_enable();
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
            Camera_handleTimer();
            Navigation_handleTimer();
//            sprintf(strbuffer, "%6.3f %6.3f %6.3f\n", Camera_getLineMid(), Camera_getLineMidFar(), Camera_getLineAngle());
//            UART_PutString(strbuffer);
            
            pidTimerInterrupted = 0;
        }
        
        // Handle comparator rise interrupt
        if (camCompRiseInterrupted) {
            Camera_handleCompRise();
            camCompRiseInterrupted = 0;
        }
        
        // Handle comparator fall interrupt
        if (camCompFallInterrupted) {
            Camera_handleCompFall();
            camCompFallInterrupted = 0;
        }
        
        // Handle frame interrupts
        if (camFrameInterrupted) {
            Camera_handleFrameStart();
            camFrameInterrupted = 0;
        }
    }
    
    return 0;
}

/* [] END OF FILE */
