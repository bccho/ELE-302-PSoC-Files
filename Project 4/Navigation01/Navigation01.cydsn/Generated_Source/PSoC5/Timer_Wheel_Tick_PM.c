/*******************************************************************************
* File Name: Timer_Wheel_Tick_PM.c
* Version 2.30
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_Wheel_Tick.h"
static Timer_Wheel_Tick_backupStruct Timer_Wheel_Tick_backup;


/*******************************************************************************
* Function Name: Timer_Wheel_Tick_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Wheel_Tick_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Wheel_Tick_SaveConfig(void) 
{
    #if (!Timer_Wheel_Tick_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC5A*/
        #if (CY_PSOC5A)
            Timer_Wheel_Tick_backup.TimerUdb = Timer_Wheel_Tick_ReadCounter();
            Timer_Wheel_Tick_backup.TimerPeriod = Timer_Wheel_Tick_ReadPeriod();
            Timer_Wheel_Tick_backup.InterruptMaskValue = Timer_Wheel_Tick_STATUS_MASK;
            #if (Timer_Wheel_Tick_UsingHWCaptureCounter)
                Timer_Wheel_Tick_backup.TimerCaptureCounter = Timer_Wheel_Tick_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for PSoC5A */
        #endif /* Backup the UDB non-rentention registers for PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            Timer_Wheel_Tick_backup.TimerUdb = Timer_Wheel_Tick_ReadCounter();
            Timer_Wheel_Tick_backup.InterruptMaskValue = Timer_Wheel_Tick_STATUS_MASK;
            #if (Timer_Wheel_Tick_UsingHWCaptureCounter)
                Timer_Wheel_Tick_backup.TimerCaptureCounter = Timer_Wheel_Tick_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for PSoC3 or PSoC5LP */

        #if(!Timer_Wheel_Tick_ControlRegRemoved)
            Timer_Wheel_Tick_backup.TimerControlRegister = Timer_Wheel_Tick_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Wheel_Tick_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Wheel_Tick_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Wheel_Tick_RestoreConfig(void) 
{   
    #if (!Timer_Wheel_Tick_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            /* Interrupt State Backup for Critical Region*/
            uint8 Timer_Wheel_Tick_interruptState;

            Timer_Wheel_Tick_WriteCounter(Timer_Wheel_Tick_backup.TimerUdb);
            Timer_Wheel_Tick_WritePeriod(Timer_Wheel_Tick_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Timer_Wheel_Tick_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            Timer_Wheel_Tick_STATUS_AUX_CTRL |= Timer_Wheel_Tick_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(Timer_Wheel_Tick_interruptState);
            Timer_Wheel_Tick_STATUS_MASK =Timer_Wheel_Tick_backup.InterruptMaskValue;
            #if (Timer_Wheel_Tick_UsingHWCaptureCounter)
                Timer_Wheel_Tick_SetCaptureCount(Timer_Wheel_Tick_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for PSoC5A */
        #endif /* Restore the UDB non-rentention registers for PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            Timer_Wheel_Tick_WriteCounter(Timer_Wheel_Tick_backup.TimerUdb);
            Timer_Wheel_Tick_STATUS_MASK =Timer_Wheel_Tick_backup.InterruptMaskValue;
            #if (Timer_Wheel_Tick_UsingHWCaptureCounter)
                Timer_Wheel_Tick_SetCaptureCount(Timer_Wheel_Tick_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for PSoC3 or PSoC5LP */

        #if(!Timer_Wheel_Tick_ControlRegRemoved)
            Timer_Wheel_Tick_WriteControlRegister(Timer_Wheel_Tick_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Wheel_Tick_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Wheel_Tick_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Wheel_Tick_Sleep(void) 
{
    #if(!Timer_Wheel_Tick_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Timer_Wheel_Tick_CTRL_ENABLE == (Timer_Wheel_Tick_CONTROL & Timer_Wheel_Tick_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Wheel_Tick_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Wheel_Tick_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Wheel_Tick_Stop();
    Timer_Wheel_Tick_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Wheel_Tick_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Wheel_Tick_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Wheel_Tick_Wakeup(void) 
{
    Timer_Wheel_Tick_RestoreConfig();
    #if(!Timer_Wheel_Tick_ControlRegRemoved)
        if(Timer_Wheel_Tick_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Wheel_Tick_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
