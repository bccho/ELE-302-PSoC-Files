/*******************************************************************************
* File Name: Counter_2_PM.c  
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

#include "Counter_2.h"

static Counter_2_backupStruct Counter_2_backup;


/*******************************************************************************
* Function Name: Counter_2_SaveConfig
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
*  Counter_2_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Counter_2_SaveConfig(void) 
{
    #if (!Counter_2_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            Counter_2_backup.CounterUdb = Counter_2_ReadCounter();
            Counter_2_backup.CounterPeriod = Counter_2_ReadPeriod();
            Counter_2_backup.CompareValue = Counter_2_ReadCompare();
            Counter_2_backup.InterruptMaskValue = Counter_2_STATUS_MASK;
        #endif /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            Counter_2_backup.CounterUdb = Counter_2_ReadCounter();
            Counter_2_backup.InterruptMaskValue = Counter_2_STATUS_MASK;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(!Counter_2_ControlRegRemoved)
            Counter_2_backup.CounterControlRegister = Counter_2_ReadControlRegister();
        #endif /* (!Counter_2_ControlRegRemoved) */
    #endif /* (!Counter_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_2_RestoreConfig
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
*  Counter_2_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_2_RestoreConfig(void) 
{      
    #if (!Counter_2_UsingFixedFunction)     
        /* Restore the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            /* Interrupt State Backup for Critical Region*/
            uint8 Counter_2_interruptState;
        
            Counter_2_WriteCounter(Counter_2_backup.CounterUdb);
            Counter_2_WritePeriod(Counter_2_backup.CounterPeriod);
            Counter_2_WriteCompare(Counter_2_backup.CompareValue);
            /* Enter Critical Region*/
            Counter_2_interruptState = CyEnterCriticalSection();
        
            Counter_2_STATUS_AUX_CTRL |= Counter_2_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(Counter_2_interruptState);
            Counter_2_STATUS_MASK = Counter_2_backup.InterruptMaskValue;
        #endif  /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            Counter_2_WriteCounter(Counter_2_backup.CounterUdb);
            Counter_2_STATUS_MASK = Counter_2_backup.InterruptMaskValue;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(!Counter_2_ControlRegRemoved)
            Counter_2_WriteControlRegister(Counter_2_backup.CounterControlRegister);
        #endif /* (!Counter_2_ControlRegRemoved) */
    #endif /* (!Counter_2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_2_Sleep
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
*  Counter_2_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_2_Sleep(void) 
{
    #if(!Counter_2_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_2_CTRL_ENABLE == (Counter_2_CONTROL & Counter_2_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_2_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_2_backup.CounterEnableState = 0u;
        }
    #endif /* (!Counter_2_ControlRegRemoved) */
    Counter_2_Stop();
    Counter_2_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_2_Wakeup
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
*  Counter_2_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_2_Wakeup(void) 
{
    Counter_2_RestoreConfig();
    #if(!Counter_2_ControlRegRemoved)
        if(Counter_2_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_2_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Counter_2_ControlRegRemoved) */
    
}


/* [] END OF FILE */
