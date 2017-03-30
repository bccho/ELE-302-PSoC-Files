/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <device.h>
#include <stdio.h>
#include <math.h>

const int MAX_THROTTLE = 999;
const int CLK_FREQ = 100000;
const int TIMER_PERIOD = 65536;
const double WHEEL_DIAM = 2.5; // in inches
#define RX_BUF_SIZE 100
#define WHEEL_TICK_BUF_SIZE 10

double TARGET_SPEED = 4.0; // in feet per second
int SS_THROTTLE = 100;
// PID coefficients
double COEFF_P = 1.0;
double COEFF_I = 0.0;
double COEFF_D = 0.0;

int buttonInterrupted = 0;
int rxInterrupted = 0;
int wheelTickInterrupted = 0;

int throttle;

uint8 recByte;
uint8 rx_buf[RX_BUF_SIZE];
int rx_buf_pos = 0;
int msgReceived = 0;

int wheel_tick_buf[WHEEL_TICK_BUF_SIZE];
int wheel_tick_buf_pos = 0;
int oldTickCount = 0;

int i;


void setThrottle(int thr) {
    if (thr < 0)
        thr = 0;
    if (thr > MAX_THROTTLE)
        thr = MAX_THROTTLE;
    
    throttle = thr;
    
    PWM_WriteCompare(throttle);
    
    LCD_Position(1,0);
    char strbuffer[4];
    sprintf(strbuffer, "%3i", throttle);
    LCD_PrintString(strbuffer);
}

double getSpeed() {
    int cumSum = 0;
    int i;
    for (i = 0; i < WHEEL_TICK_BUF_SIZE; i++) {
        cumSum += wheel_tick_buf[i];
    }
    double averageCount = cumSum / WHEEL_TICK_BUF_SIZE;
    double ticksPerSec = CLK_FREQ / averageCount;
    double speed = ticksPerSec * ((M_PI * WHEEL_DIAM) / 5) * (1.0/12.0);
    
//    char strbuffer[20];
//    sprintf(strbuffer, "cnt: %f\n", averageCount);
//    UART_1_PutString(strbuffer);
    
    return speed;
}

int controlThrottle(double speed) {
    double spd_error = speed - TARGET_SPEED;
    
    return (int) (spd_error * COEFF_P) + SS_THROTTLE;
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

int main() {
    /* Initialization */
    CyGlobalIntEnable; // Enable global interrupts
    
    LCD_Start();
    inter_button_Start();
    inter_button_SetVector(button_inter);
    PWM_Start();
    
    UART_1_Start();
    rx_rcvd_Start();
    rx_rcvd_SetVector(rx_inter);
    
    Timer_1_Start();
    wheel_tick_Start();
    wheel_tick_SetVector(wheel_inter);
    
    throttle = 0;
    PWM_WriteCompare(throttle);
    
    // LCD initial text
    LCD_Position(0, 0);
    LCD_PrintString("Throttle:");
    
    // Init RX buffer
    for (i = 0; i < RX_BUF_SIZE; i++) rx_buf[i] = 0;
    
    for(;;)
    {
        /* Place your application code here. */
        if (buttonInterrupted) {
            if (throttle == 0) setThrottle(40);
            else setThrottle(0);
            buttonInterrupted = 0;
        }
        
        // Handle incoming serial data
        if (rxInterrupted) {
            if (msgReceived) {
                UART_1_PutString("! Buffer Overwrite !");
            } else {
                recByte = UART_1_GetChar();
                if (recByte == 0xA || recByte == 0xD || recByte == 0x4) {
                    msgReceived = 1;
                    UART_1_PutChar('$');
                    UART_1_PutChar(recByte);
                } else if (recByte > 0) {
                    if (rx_buf_pos == RX_BUF_SIZE) {
                        msgReceived = 1;
                        UART_1_PutString("! Buffer Overflow !");
                    } else {
                        rx_buf[rx_buf_pos] = recByte;
                        rx_buf_pos++;
                        UART_1_PutChar(recByte);
                    }
                } else {
                    UART_1_PutChar('!');
                }
                rxInterrupted = 0;
            }
        }
        
        // Parse received strings
        if (msgReceived) {
            // Messages of the form "Sxx" set the duty cycle to xx out of MAX_THROTTLE
            if (rx_buf[0] == 'S') {
                int thr = 0; // kill throttle unless input is valid
                if ('0' <= rx_buf[1] && rx_buf[1] <= '9' && '0' <= rx_buf[2] && rx_buf[2] <= '9' && '0' <= rx_buf[3] && rx_buf[3] <= '9') {
                    thr = 100*(rx_buf[1]-'0') + 10*(rx_buf[2]-'0') + (rx_buf[3]-'0');
                }
                setThrottle(thr);
            }
            
            // Messages of the form "G" return the speed of the car
            if (rx_buf[0] == 'G') {
                char strbuffer[25];
                sprintf(strbuffer, "Speed: %f ft/s\n", getSpeed());
                UART_1_PutString(strbuffer);
            }
            
            // Reset buffer
            for (i = 0; i < rx_buf_pos; i++) rx_buf[i] = 0;
            rx_buf_pos = 0;
            msgReceived = 0;
        }
        
        // Handle wheel ticks
        if (wheelTickInterrupted) {
            // int tickCount = Counter_1_ReadCapture();
            int tickCount = Timer_1_ReadCapture();
            int tickDelta = oldTickCount - tickCount;
            
            tickDelta = tickDelta < 0 ? TIMER_PERIOD + tickDelta : tickDelta;
            wheel_tick_buf[wheel_tick_buf_pos] = tickDelta;
            
//            char strbuffer[15];
//            sprintf(strbuffer, "Count: %i\n", tickCount);
//            UART_1_PutString(strbuffer);
//            sprintf(strbuffer, "Old Count: %i\n", oldTickCount);
//            UART_1_PutString(strbuffer);
//            sprintf(strbuffer, "Delta: %i\n\n", tickDelta);
//            UART_1_PutString(strbuffer);
            
            wheel_tick_buf_pos++;
            if (wheel_tick_buf_pos == WHEEL_TICK_BUF_SIZE) wheel_tick_buf_pos = 0;
            oldTickCount = tickCount;
            wheelTickInterrupted = 0;
        }
            
    }
    
    return 0;
}

/* [] END OF FILE */
