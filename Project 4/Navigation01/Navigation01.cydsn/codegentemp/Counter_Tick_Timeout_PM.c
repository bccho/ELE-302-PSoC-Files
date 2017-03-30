/*******************************************************************************
* File Name: Counter_Tick_Timeout_PM.c  
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

#include "Counter_Tick_Timeout.h"

static Counter_Tick_Timeout_backupStruct Counter_Tick_Timeout_backup;


/*******************************************************************************
* Function Name: Counter_Tick_Timeout_SaveConfig
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
*  Counter_Tick_Timeout_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Counter_Tick_Timeout_SaveConfig(void) 
{
    #if (!Counter_Tick_Timeout_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            Counter_Tick_Timeout_backup.CounterUdb = Counter_Tick_Timeout_ReadCounter();
            Counter_Tick_Timeout_backup.CounterPeriod = Counter_Tick_Timeout_ReadPeriod();
            Counter_Tick_Timeout_backup.CompareValue = Counter_Tick_Timeout_ReadCompare();
            Counter_Tick_Timeout_backup.InterruptMaskValue = Counter_Tick_Timeout_STATUS_MASK;
        #endif /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            Counter_Tick_Timeout_backup.CounterUdb = Counter_Tick_Timeout_ReadCounter();
            Counter_Tick_Timeout_backup.InterruptMaskValue = Counter_Tick_Timeout_STATUS_MASK;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(!Counter_Tick_Timeout_ControlRegRemoved)
            Counter_Tick_Timeout_backup.CounterControlRegister = Counter_Tick_Timeout_ReadControlRegister();
        #endif /* (!Counter_Tick_Timeout_ControlRegRemoved) */
    #endif /* (!Counter_Tick_Timeout_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_Tick_Timeout_RestoreConfig
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
*  Counter_Tick_Timeout_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_Tick_Timeout_RestoreConfig(void) 
{      
    #if (!Counter_Tick_Timeout_UsingFixedFunction)     
        /* Restore the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            /* Interrupt State Backup for Critical Region*/
            uint8 Counter_Tick_Timeout_interruptState;
        
            Counter_Tick_Timeout_WriteCounter(Counter_Tick_Timeout_backup.CounterUdb);
            Counter_Tick_Timeout_WritePeriod(Counter_Tick_Timeout_backup.CounterPeriod);
            Counter_Tick_Timeout_WriteCompare(Counter_Tick_Timeout_backup.CompareValue);
            /* Enter Critical Region*/
            Counter_Tick_Timeout_interruptState = CyEnterCriticalSection();
        
            Counter_Tick_Timeout_STATUS_AUX_CTRL |= Counter_Tick_Timeout_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(Counter_Tick_Timeout_interruptState);
            Counter_Tick_Timeout_STATUS_MASK = Counter_Tick_Timeout_backup.InterruptMaskValue;
        #endif  /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            Counter_Tick_Timeout_WriteCounter(Counter_Tick_Timeout_backup.CounterUdb);
            Counter_Tick_Timeout_STATUS_MASK = Counter_Tick_Timeout_backup.InterruptMaskValue;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(!Counter_Tick_Timeout_ControlRegRemoved)
            Counter_Tick_Timeout_WriteControlRegister(Counter_Tick_Timeout_backup.CounterControlRegister);
        #endif /* (!Counter_Tick_Timeout_ControlRegRemoved) */
    #endif /* (!Counter_Tick_Timeout_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_Tick_Timeout_Sleep
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
*  Counter_Tick_Timeout_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_Tick_Timeout_Sleep(void) 
{
    #if(!Counter_Tick_Timeout_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_Tick_Timeout_CTRL_ENABLE == (Counter_Tick_Timeout_CONTROL & Counter_Tick_Timeout_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_Tick_Timeout_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_Tick_Timeout_backup.CounterEnableState = 0u;
        }
    #endif /* (!Counter_Tick_Timeout_ControlRegRemoved) */
    Counter_Tick_Timeout_Stop();
    Counter_Tick_Timeout_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_Tick_Timeout_Wakeup
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
*  Counter_Tick_Timeout_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_Tick_Timeout_Wakeup(void) 
{
    Counter_Tick_Timeout_RestoreConfig();
    #if(!Counter_Tick_Timeout_ControlRegRemoved)
        if(Counter_Tick_Timeout_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_Tick_Timeout_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Counter_Tick_Timeout_ControlRegRemoved) */
    
}


/* [] END OF FILE */
