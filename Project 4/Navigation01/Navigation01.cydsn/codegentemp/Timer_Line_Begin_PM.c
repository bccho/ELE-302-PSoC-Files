/*******************************************************************************
* File Name: Timer_Line_Begin_PM.c
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

#include "Timer_Line_Begin.h"
static Timer_Line_Begin_backupStruct Timer_Line_Begin_backup;


/*******************************************************************************
* Function Name: Timer_Line_Begin_SaveConfig
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
*  Timer_Line_Begin_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Line_Begin_SaveConfig(void) 
{
    #if (!Timer_Line_Begin_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC5A*/
        #if (CY_PSOC5A)
            Timer_Line_Begin_backup.TimerUdb = Timer_Line_Begin_ReadCounter();
            Timer_Line_Begin_backup.TimerPeriod = Timer_Line_Begin_ReadPeriod();
            Timer_Line_Begin_backup.InterruptMaskValue = Timer_Line_Begin_STATUS_MASK;
            #if (Timer_Line_Begin_UsingHWCaptureCounter)
                Timer_Line_Begin_backup.TimerCaptureCounter = Timer_Line_Begin_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for PSoC5A */
        #endif /* Backup the UDB non-rentention registers for PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            Timer_Line_Begin_backup.TimerUdb = Timer_Line_Begin_ReadCounter();
            Timer_Line_Begin_backup.InterruptMaskValue = Timer_Line_Begin_STATUS_MASK;
            #if (Timer_Line_Begin_UsingHWCaptureCounter)
                Timer_Line_Begin_backup.TimerCaptureCounter = Timer_Line_Begin_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for PSoC3 or PSoC5LP */

        #if(!Timer_Line_Begin_ControlRegRemoved)
            Timer_Line_Begin_backup.TimerControlRegister = Timer_Line_Begin_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Line_Begin_RestoreConfig
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
*  Timer_Line_Begin_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Line_Begin_RestoreConfig(void) 
{   
    #if (!Timer_Line_Begin_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            /* Interrupt State Backup for Critical Region*/
            uint8 Timer_Line_Begin_interruptState;

            Timer_Line_Begin_WriteCounter(Timer_Line_Begin_backup.TimerUdb);
            Timer_Line_Begin_WritePeriod(Timer_Line_Begin_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Timer_Line_Begin_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            Timer_Line_Begin_STATUS_AUX_CTRL |= Timer_Line_Begin_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(Timer_Line_Begin_interruptState);
            Timer_Line_Begin_STATUS_MASK =Timer_Line_Begin_backup.InterruptMaskValue;
            #if (Timer_Line_Begin_UsingHWCaptureCounter)
                Timer_Line_Begin_SetCaptureCount(Timer_Line_Begin_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for PSoC5A */
        #endif /* Restore the UDB non-rentention registers for PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            Timer_Line_Begin_WriteCounter(Timer_Line_Begin_backup.TimerUdb);
            Timer_Line_Begin_STATUS_MASK =Timer_Line_Begin_backup.InterruptMaskValue;
            #if (Timer_Line_Begin_UsingHWCaptureCounter)
                Timer_Line_Begin_SetCaptureCount(Timer_Line_Begin_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for PSoC3 or PSoC5LP */

        #if(!Timer_Line_Begin_ControlRegRemoved)
            Timer_Line_Begin_WriteControlRegister(Timer_Line_Begin_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Line_Begin_Sleep
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
*  Timer_Line_Begin_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Line_Begin_Sleep(void) 
{
    #if(!Timer_Line_Begin_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Timer_Line_Begin_CTRL_ENABLE == (Timer_Line_Begin_CONTROL & Timer_Line_Begin_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Line_Begin_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Line_Begin_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Line_Begin_Stop();
    Timer_Line_Begin_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Line_Begin_Wakeup
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
*  Timer_Line_Begin_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Line_Begin_Wakeup(void) 
{
    Timer_Line_Begin_RestoreConfig();
    #if(!Timer_Line_Begin_ControlRegRemoved)
        if(Timer_Line_Begin_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Line_Begin_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
