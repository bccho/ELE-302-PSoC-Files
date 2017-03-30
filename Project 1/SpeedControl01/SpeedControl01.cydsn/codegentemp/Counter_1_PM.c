/*******************************************************************************
* File Name: Counter_1_PM.c  
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

#include "Counter_1.h"

static Counter_1_backupStruct Counter_1_backup;


/*******************************************************************************
* Function Name: Counter_1_SaveConfig
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
*  Counter_1_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Counter_1_SaveConfig(void) 
{
    #if (!Counter_1_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            Counter_1_backup.CounterUdb = Counter_1_ReadCounter();
            Counter_1_backup.CounterPeriod = Counter_1_ReadPeriod();
            Counter_1_backup.CompareValue = Counter_1_ReadCompare();
            Counter_1_backup.InterruptMaskValue = Counter_1_STATUS_MASK;
        #endif /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            Counter_1_backup.CounterUdb = Counter_1_ReadCounter();
            Counter_1_backup.InterruptMaskValue = Counter_1_STATUS_MASK;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(!Counter_1_ControlRegRemoved)
            Counter_1_backup.CounterControlRegister = Counter_1_ReadControlRegister();
        #endif /* (!Counter_1_ControlRegRemoved) */
    #endif /* (!Counter_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_1_RestoreConfig
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
*  Counter_1_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_1_RestoreConfig(void) 
{      
    #if (!Counter_1_UsingFixedFunction)     
        /* Restore the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            /* Interrupt State Backup for Critical Region*/
            uint8 Counter_1_interruptState;
        
            Counter_1_WriteCounter(Counter_1_backup.CounterUdb);
            Counter_1_WritePeriod(Counter_1_backup.CounterPeriod);
            Counter_1_WriteCompare(Counter_1_backup.CompareValue);
            /* Enter Critical Region*/
            Counter_1_interruptState = CyEnterCriticalSection();
        
            Counter_1_STATUS_AUX_CTRL |= Counter_1_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(Counter_1_interruptState);
            Counter_1_STATUS_MASK = Counter_1_backup.InterruptMaskValue;
        #endif  /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            Counter_1_WriteCounter(Counter_1_backup.CounterUdb);
            Counter_1_STATUS_MASK = Counter_1_backup.InterruptMaskValue;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(!Counter_1_ControlRegRemoved)
            Counter_1_WriteControlRegister(Counter_1_backup.CounterControlRegister);
        #endif /* (!Counter_1_ControlRegRemoved) */
    #endif /* (!Counter_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_1_Sleep
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
*  Counter_1_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_1_Sleep(void) 
{
    #if(!Counter_1_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_1_CTRL_ENABLE == (Counter_1_CONTROL & Counter_1_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_1_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_1_backup.CounterEnableState = 0u;
        }
    #endif /* (!Counter_1_ControlRegRemoved) */
    Counter_1_Stop();
    Counter_1_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_1_Wakeup
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
*  Counter_1_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_1_Wakeup(void) 
{
    Counter_1_RestoreConfig();
    #if(!Counter_1_ControlRegRemoved)
        if(Counter_1_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_1_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Counter_1_ControlRegRemoved) */
    
}


/* [] END OF FILE */
