/*-----------------------------------------------------------------*/
/* main.c                                                          */
/*                                                                 */
/* BC Cho (bccho@) and TJ Smith (tjs8@)                            */
/*-----------------------------------------------------------------*/
#include <device.h>
#include <hardware.h>
#include <serial.h>
#include <stdio.h>
#include <math.h>

static char buildVersion[] = "Build 1.0.0";
static char strbuffer[100];

static int rxInterrupted = 0;

// Function prototypes
static void parseMessage();
void driveMagPhase(double direction, double magnitude);
void drive(int dirs[], double mags[]);
//static double floor(double a);
//static double ceil(double a);
//static double absVal(double a);


int dirs[4];
double mags[4];

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
        
        // Messages of the form "CTx.y" (x integer, y float) set motor x to throttle y
        if (strcmp(msgPrefix, "CT") == 0) {
            double value = 0;
            if (sscanf(message + prefixLen, "%lf", &value) > 0) {
                int motorNum = floor(fabs(value));
                double throttleMag = fabs(value) - motorNum;
                if (throttleMag > 1) throttleMag = 1;
                if (throttleMag < 0) throttleMag = 0;
                int throttleDir = value > 0 ? 1 : 0;
                switch (motorNum) {
                    case 0:
                        PWM_Front_Left_WriteCompare(throttleMag * PWM_Front_Left_ReadPeriod());
                        break;
                    case 1:
                        PWM_Front_Right_WriteCompare(throttleMag * PWM_Front_Right_ReadPeriod());
                        break;
                    case 2:
                        PWM_Back_Left_WriteCompare(throttleMag * PWM_Back_Left_ReadPeriod());
                        break;
                    case 3:
                        PWM_Back_Right_WriteCompare(throttleMag * PWM_Back_Right_ReadPeriod());
                        break;
                }
                int regVal = Control_Reg_Direction_Read();
                int newRegVal = (regVal & ~(1 << motorNum)) | (throttleDir << motorNum);
                Control_Reg_Direction_Write(newRegVal);
                sprintf(strbuffer, "Motor Num: %d, Throttle Mag: %f, Throttle Dir: %d\n", motorNum, throttleMag, throttleDir);
                UART_PutString(strbuffer);
                sprintf(strbuffer, "Old Reg Val: %d, New Reg Val: %d\n", regVal, newRegVal);
                UART_PutString(strbuffer); 
            }
        }
        
        // Messages of the form "CPx" (x integer) set PWM to period x
        if (strcmp(msgPrefix, "CP") == 0) {
            int value = 0;
            if (sscanf(message + prefixLen, "%d", &value) > 0) {
                if (value > 100000) value = 100000;
                if (value < 0) value = 0;
                PWM_Front_Left_WritePeriod(value);
                PWM_Front_Right_WritePeriod(value);
                PWM_Back_Left_WritePeriod(value);
                PWM_Back_Right_WritePeriod(value);
                
                sprintf(strbuffer, "New Period: %d\n", value);
                UART_PutString(strbuffer);
            }
        }
        
        // Messages of the form "CDx" (x integer) set PWM to period x
        if (strcmp(msgPrefix, "CP") == 0) {
            int value = 0;
            if (sscanf(message + prefixLen, "%d", &value) > 0) {
                if (value > 100000) value = 100000;
                if (value < 0) value = 0;
                PWM_Front_Left_WritePeriod(value);
                PWM_Front_Right_WritePeriod(value);
                PWM_Back_Left_WritePeriod(value);
                PWM_Back_Right_WritePeriod(value);
                
                sprintf(strbuffer, "New Period: %d\n", value);
                UART_PutString(strbuffer);
            }
        }
        
        // Drive forward
        if (strcmp(msgPrefix, "w") == 0) {
            driveMagPhase(0, 0.5);    
            UART_PutString("Driving Forward\n");
        }
        // Drive backward
        if (strcmp(msgPrefix, "s") == 0) {
            driveMagPhase(180, 0.5);    
            UART_PutString("Driving Backward\n");
        }
        // Drive left
        if (strcmp(msgPrefix, "a") == 0) {
            driveMagPhase(90, 0.5);    
            UART_PutString("Driving Left\n");
        }
        // Drive right
        if (strcmp(msgPrefix, "d") == 0) {
            driveMagPhase(270, 0.5);    
            UART_PutString("Driving Right\n");
        }
        // Stop
        if (strcmp(msgPrefix, "q") == 0) {
            driveMagPhase(0, 0);    
            UART_PutString("Stopped\n");
        }
        
    }
}

// 0 deg is forward, 90 is left. magnitude is from 0 to 1
void driveMagPhase(double direction, double magnitude) {
    // angle w.r.t the axis formed by the front right and back left wheels
    double angle = direction * (M_PI/180) + (M_PI/4);
    // ratio of front left and back right wheel power to front right and back left wheel power
    double forceRatio = fabs(tan(angle));
    
    // mag1 is front left and back right wheel power
    // mag2 is front right and back left wheel power
    double mag1, mag2;
    if (forceRatio > 1) {
        mag2 = magnitude;
        mag1 = mag2 / forceRatio;
    } 
    else {
        mag1 = magnitude;
        mag2 = mag1 * forceRatio;
    }
    
    int dir1 = (angle > 0 && angle < M_PI/2) || (angle > 3*M_PI/2 && angle < 2*M_PI) ? 1 : 0;
    int dir2 = (angle > 0 && angle < M_PI) ? 1 : 0;
    
    dirs[0] = dir1; dirs[1] = dir2; dirs[2] = dir2; dirs[3] = dir1;
    mags[0] = mag1; mags[1] = mag2; mags[2] = mag2; mags[3] = mag1;
    
    drive(dirs, mags);
}

void drive(int dirs[], double mags[]) {
    int i;
    for (i = 0; i < 4; i++) {
        if (mags[i] < 0) mags[i] = 0;
        if (mags[i] > 1) mags[i] = 1;
        if (dirs[i] != 0 && dirs[i] != 1) dirs[i] = 0;
    }
    
    PWM_Front_Left_WriteCompare(mags[0] * PWM_Front_Left_ReadPeriod());
    PWM_Front_Right_WriteCompare(mags[1] * PWM_Front_Right_ReadPeriod());
    PWM_Back_Left_WriteCompare(mags[2] * PWM_Back_Left_ReadPeriod());
    PWM_Back_Right_WriteCompare(mags[3] * PWM_Back_Right_ReadPeriod());
    
    int regVal = dirs[0] | (dirs[1] << 1) | (dirs[2] << 2) | (dirs[3] << 3);
    Control_Reg_Direction_Write(regVal);
}

/* Recieved data interrupt */
CY_ISR(rx_inter) {
    rxInterrupted = 1;
}


void main()
{
    /* Initialization */
    CyGlobalIntEnable; // Enable global interrupts
    
    // Start LCD
    LCD_Start();
    LCD_PrintString(buildVersion);
    
    // Start UART
    UART_Start();
    rx_rcvd_Start();
    rx_rcvd_SetVector(rx_inter);
    
    // Start Motors
    PWM_Front_Left_Start();
    PWM_Front_Right_Start();
    PWM_Back_Left_Start();
    PWM_Back_Right_Start();
    UART_Start();
    
    // Init serial
    Serial_init();


    for(;;)
    {
       // Handle incoming serial data
        if (rxInterrupted) {
            char *message = Serial_handleData();
            parseMessage(message);
            rxInterrupted = 0;
        }
    }
}

///* Math helper functions */
//static double floor(double a) {
//    return (double) (int) a;
//}
//
//static double ceil(double a) {
//    return floor(a) + 1;
//}
//
//static double absVal(double a) {
//    if (a < 0) return -a;
//    else return a;
//}

/* [] END OF FILE */
