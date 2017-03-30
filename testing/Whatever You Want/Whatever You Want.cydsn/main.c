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

CY_ISR(inter) {
    if (PWM_ReadCompare() == 0) {
        PWM_WriteCompare(99);
        LCD_Position(1,0);
        LCD_PrintString("On ");
    } else {
        PWM_WriteCompare(0);
        LCD_Position(1,0);
        LCD_PrintString("Off");
    }
}

void main() {
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    CyGlobalIntEnable;
    
    inter_2_Start();
    inter_2_SetVector(inter);
    PWM_Start();
    Counter_Start();

    LCD_Start();
    LCD_Position(0, 0);
    LCD_PrintString("LED status:");
    
    for(;;) {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
