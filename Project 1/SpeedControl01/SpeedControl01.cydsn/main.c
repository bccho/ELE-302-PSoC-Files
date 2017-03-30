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

char buildVersion[] = "Build 1";

const int MAX_THROTTLE = 255;
const int CLK_FREQ = 100000;
const int TIMER_PERIOD = 65536;
const double WHEEL_DIAM = 2.5; // in inches
#define RX_BUF_SIZE 100
#define WHEEL_TICK_BUF_SIZE 3

const double TARGET_SPEED = 4.0; // in feet per second
int ss_throttle = 0;
double PID_integral = 0.0;
#define SPEED_BUF_SIZE 10
int speed_buf_pos = 0;
int speed_buf_last_pos = 0;
double speed_buf[SPEED_BUF_SIZE];

// PID coefficients
double COEFF_P = 50.0;
double COEFF_I = 10.0;
double COEFF_D = 10.0;

int throttlePIDon = 0;

int buttonInterrupted = 0;
int rxInterrupted = 0;
int wheelTickInterrupted = 0;
int tickTimeoutInterrupted = 0;
int throttleUpdateInterrupted = 0;

int throttle;

uint8 recByte;
uint8 rx_buf[RX_BUF_SIZE];
int rx_buf_pos = 0;
int msgReceived = 0;

int wheel_tick_buf[WHEEL_TICK_BUF_SIZE];
int wheel_tick_buf_pos = 0;
int wheel_tick_buf_cur_size = 0;
int oldTickCount = 0;

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
    double cumSum = 0;
    int i;
    if (wheel_tick_buf_cur_size == 0) return 0;
    for (i = 0; i < WHEEL_TICK_BUF_SIZE; i++) {
        cumSum += (double) wheel_tick_buf[i];
    }
    double averageCount = cumSum / wheel_tick_buf_cur_size;
    double ticksPerSec = CLK_FREQ / averageCount;
    double speed = ticksPerSec * ((M_PI * WHEEL_DIAM) / 5) * (1.0/12.0);
    
//    char strbuffer[20];
//    sprintf(strbuffer, "cnt: %f\n", averageCount);
//    UART_1_PutString(strbuffer);
    
    return speed;
}

int controlThrottle(double speed) {
    double spd_error = TARGET_SPEED - speed;
    speed_buf[speed_buf_pos] = spd_error;
    double PID_deriv = (speed_buf[speed_buf_pos] - speed_buf[speed_buf_last_pos]) / (double) SPEED_BUF_SIZE;
    speed_buf_pos = (speed_buf_pos + 1) % SPEED_BUF_SIZE;
    if (speed_buf_pos == speed_buf_last_pos) { // this gets activated when speed_buf_pos has made one loop around the ring buffer
        speed_buf_last_pos = (speed_buf_last_pos + 1) % SPEED_BUF_SIZE;
    }
    PID_integral /= 1.1;
    PID_integral += spd_error;
    
    char str_buffer[35];
    sprintf(str_buffer, "%6.2f, %6.2f, %6.2f, %6.5f\n", speed, spd_error, PID_integral, PID_deriv);
    UART_1_PutString(str_buffer);
    
    return ss_throttle + (int) (spd_error * COEFF_P + PID_integral * COEFF_I - PID_deriv * COEFF_D);
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

/* Throttle update timeout interrupt */
CY_ISR(throttle_inter) {
    throttleUpdateInterrupted = 1;
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
    
    Counter_1_Start();
    ShiftReg_1_Start();
    tick_timeout_Start();
    tick_timeout_SetVector(timeout_inter);
    
    Counter_2_Start();
    throttle_update_Start();
    throttle_update_SetVector(throttle_inter);
    
    throttle = 0;
    PWM_WriteCompare(throttle);
    
    // LCD initial text
    LCD_Position(0, 0);
    LCD_PrintString(buildVersion);
    
    // Init RX buffer
    int i;
    for (i = 0; i < RX_BUF_SIZE; i++) rx_buf[i] = 0;
    
    // Init wheel tick buffer
    for (i = 0; i < WHEEL_TICK_BUF_SIZE; i++) wheel_tick_buf[i] = 0;
    
    // Init speed buffer
    for (i = 0; i < SPEED_BUF_SIZE; i++) speed_buf[i] = 0.0;
    
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
            if (rx_buf[0] == 'S' && rx_buf[1] != 'S') {
                int thr = 0; // kill throttle unless input is valid
                if ('0' <= rx_buf[1] && rx_buf[1] <= '9' && '0' <= rx_buf[2] && rx_buf[2] <= '9' && '0' <= rx_buf[3] && rx_buf[3] <= '9') {
                    thr = 100*(rx_buf[1]-'0') + 10*(rx_buf[2]-'0') + (rx_buf[3]-'0');
                }
                setThrottle(thr);
            }
            
            // Messages of the form "G" return the speed of the car and PID controls
            if (rx_buf[0] == 'G') {
                char strbuffer[80];
                sprintf(strbuffer, "Throttle: %d\nSpeed: %f ft/s\nP = %.2f\tI = %.2f\tD = %.2f\n", throttle, getSpeed(), COEFF_P, COEFF_I, COEFF_D);
                UART_1_PutString(strbuffer);
            }
            
            // Messages of the form "T" toggle PID control
            if (rx_buf[0] == 'T') {
                throttlePIDon = throttlePIDon ? 0 : 1;
                if (throttlePIDon) {
                    throttleUpdateInterrupted = 1;
                    UART_1_PutString("PID control on\n");
                } else {
                    throttleUpdateInterrupted = 0;
                    UART_1_PutString("PID control off\n");
                }
            }
            
            // Messages of the form "P" change the proportional term to value
            if (rx_buf[0] == 'P') {
                if ('0' <= rx_buf[1] && rx_buf[1] <= '9' && '0' <= rx_buf[2] && rx_buf[2] <= '9' && '0' <= rx_buf[3] && rx_buf[3] <= '9') {
                    COEFF_P = 100*(rx_buf[1]-'0') + 10*(rx_buf[2]-'0') + (rx_buf[3]-'0');
                }
                char strbuffer[15];
                sprintf(strbuffer, "P = %.2f\n", COEFF_P);
                UART_1_PutString(strbuffer);
            }
            
            // Messages of the form "I" change the integral term to value / 10
            if (rx_buf[0] == 'I') {
                if ('0' <= rx_buf[1] && rx_buf[1] <= '9' && '0' <= rx_buf[2] && rx_buf[2] <= '9' && '0' <= rx_buf[3] && rx_buf[3] <= '9') {
                    COEFF_I = 100*(rx_buf[1]-'0') + 10*(rx_buf[2]-'0') + (rx_buf[3]-'0');
                    COEFF_I /= 10;
                }
                char strbuffer[15];
                sprintf(strbuffer, "I = %.2f\n", COEFF_I);
                UART_1_PutString(strbuffer);
            }
            
            // Messages of the form "D" change the derivative term
            if (rx_buf[0] == 'D') {
                if ('0' <= rx_buf[1] && rx_buf[1] <= '9' && '0' <= rx_buf[2] && rx_buf[2] <= '9' && '0' <= rx_buf[3] && rx_buf[3] <= '9') {
                    COEFF_D = 100*(rx_buf[1]-'0') + 10*(rx_buf[2]-'0') + (rx_buf[3]-'0');
                }
                char strbuffer[15];
                sprintf(strbuffer, "D = %.2f\n", COEFF_D);
                UART_1_PutString(strbuffer);
            }
            
            // Message with "A" will abort
            if (rx_buf[0] == 'A') {
                setThrottle(0);
                throttlePIDon = 0;
                throttleUpdateInterrupted = 0;
                UART_1_PutString("Aborted!\n");
            }
            
            // Message with "SS" will change steady state throttle
            if (rx_buf[0] == 'S' && rx_buf[1] == 'S') {
                if ('0' <= rx_buf[2] && rx_buf[2] <= '9' && '0' <= rx_buf[3] && rx_buf[3] <= '9' && '0' <= rx_buf[4] && rx_buf[4] <= '9') {
                    COEFF_D = 100*(rx_buf[2]-'0') + 10*(rx_buf[3]-'0') + (rx_buf[4]-'0');
                }
                char strbuffer[15];
                sprintf(strbuffer, "D = %.2f\n", COEFF_D);
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
            
            wheel_tick_buf_pos = (wheel_tick_buf_pos + 1) % WHEEL_TICK_BUF_SIZE;
            if (wheel_tick_buf_cur_size < WHEEL_TICK_BUF_SIZE) wheel_tick_buf_cur_size++;
            oldTickCount = tickCount;
            wheelTickInterrupted = 0;
        }
        
        // Handle wheel tick timeout
        if (tickTimeoutInterrupted) {
            UART_1_PutString("Wheel timeout\n");
            // Clear wheel tick buffer
            wheel_tick_buf_pos = 0;
            wheel_tick_buf_cur_size = 0;
            for (i = 0; i < WHEEL_TICK_BUF_SIZE; i++) wheel_tick_buf[i] = 0;
            // Clear speed buffer
            speed_buf_pos = 0;
            speed_buf_last_pos = 0;
            for (i = 0; i < SPEED_BUF_SIZE; i++) speed_buf[i] = 0.0;
            
            tickTimeoutInterrupted = 0;
        }
            
        
        // Perform PID update
        if (throttlePIDon && throttleUpdateInterrupted) {
            setThrottle(controlThrottle(getSpeed()));
            throttleUpdateInterrupted = 0;
        }
            
    }
    
    return 0;
}

/* [] END OF FILE */
