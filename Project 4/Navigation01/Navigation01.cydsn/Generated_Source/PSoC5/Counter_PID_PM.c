/*******************************************************************************
* File Name: Counter_PID_PM.c  
* Version 2.20
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
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

#include "Counter_PID.h"

static Counter_PID_backupStruct Counter_PID_backup;


/*******************************************************************************
* Function Name: Counter_PID_SaveConfig
********************************************************************************
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
*  Counter_PID_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Counter_PID_SaveConfig(void) 
{
    #if (!Counter_PID_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            Counter_PID_backup.CounterUdb = Counter_PID_ReadCounter();
            Counter_PID_backup.CounterPeriod = Counter_PID_ReadPeriod();
            Counter_PID_backup.CompareValue = Counter_PID_ReadCompare();
            Counter_PID_backup.InterruptMaskValue = Counter_PID_STATUS_MASK;
        #endif /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            Counter_PID_backup.CounterUdb = Counter_PID_ReadCounter();
            Counter_PID_backup.InterruptMaskValue = Counter_PID_STATUS_MASK;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(!Counter_PID_ControlRegRemoved)
            Counter_PID_backup.CounterControlRegister = Counter_PID_ReadControlRegister();
        #endif /* (!Counter_PID_ControlRegRemoved) */
    #endif /* (!Counter_PID_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_PID_RestoreConfig
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
*  Counter_PID_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_PID_RestoreConfig(void) 
{      
    #if (!Counter_PID_UsingFixedFunction)     
        /* Restore the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            /* Interrupt State Backup for Critical Region*/
            uint8 Counter_PID_interruptState;
        
            Counter_PID_WriteCounter(Counter_PID_backup.CounterUdb);
            Counter_PID_WritePeriod(Counter_PID_backup.CounterPeriod);
            Counter_PID_WriteCompare(Counter_PID_backup.CompareValue);
            /* Enter Critical Region*/
            Counter_PID_interruptState = CyEnterCriticalSection();
        
            Counter_PID_STATUS_AUX_CTRL |= Counter_PID_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(Counter_PID_interruptState);
            Counter_PID_STATUS_MASK = Counter_PID_backup.InterruptMaskValue;
        #endif  /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            Counter_PID_WriteCounter(Counter_PID_backup.CounterUdb);
            Counter_PID_STATUS_MASK = Counter_PID_backup.InterruptMaskValue;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(!Counter_PID_ControlRegRemoved)
            Counter_PID_WriteControlRegister(Counter_PID_backup.CounterControlRegister);
        #endif /* (!Counter_PID_ControlRegRemoved) */
    #endif /* (!Counter_PID_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_PID_Sleep
********************************************************************************
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
*  Counter_PID_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_PID_Sleep(void) 
{
    #if(!Counter_PID_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_PID_CTRL_ENABLE == (Counter_PID_CONTROL & Counter_PID_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_PID_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_PID_backup.CounterEnableState = 0u;
        }
    #endif /* (!Counter_PID_ControlRegRemoved) */
    Counter_PID_Stop();
    Counter_PID_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_PID_Wakeup
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
*  Counter_PID_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_PID_Wakeup(void) 
{
    Counter_PID_RestoreConfig();
    #if(!Counter_PID_ControlRegRemoved)
        if(Counter_PID_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_PID_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Counter_PID_ControlRegRemoved) */
    
}


/* [] END OF FILE */
