/*******************************************************************************
* File Name: Counter_Frist_Row_PM.c  
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

#include "Counter_Frist_Row.h"

static Counter_Frist_Row_backupStruct Counter_Frist_Row_backup;


/*******************************************************************************
* Function Name: Counter_Frist_Row_SaveConfig
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
*  Counter_Frist_Row_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Counter_Frist_Row_SaveConfig(void) 
{
    #if (!Counter_Frist_Row_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            Counter_Frist_Row_backup.CounterUdb = Counter_Frist_Row_ReadCounter();
            Counter_Frist_Row_backup.CounterPeriod = Counter_Frist_Row_ReadPeriod();
            Counter_Frist_Row_backup.CompareValue = Counter_Frist_Row_ReadCompare();
            Counter_Frist_Row_backup.InterruptMaskValue = Counter_Frist_Row_STATUS_MASK;
        #endif /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            Counter_Frist_Row_backup.CounterUdb = Counter_Frist_Row_ReadCounter();
            Counter_Frist_Row_backup.InterruptMaskValue = Counter_Frist_Row_STATUS_MASK;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(!Counter_Frist_Row_ControlRegRemoved)
            Counter_Frist_Row_backup.CounterControlRegister = Counter_Frist_Row_ReadControlRegister();
        #endif /* (!Counter_Frist_Row_ControlRegRemoved) */
    #endif /* (!Counter_Frist_Row_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_Frist_Row_RestoreConfig
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
*  Counter_Frist_Row_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_Frist_Row_RestoreConfig(void) 
{      
    #if (!Counter_Frist_Row_UsingFixedFunction)     
        /* Restore the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            /* Interrupt State Backup for Critical Region*/
            uint8 Counter_Frist_Row_interruptState;
        
            Counter_Frist_Row_WriteCounter(Counter_Frist_Row_backup.CounterUdb);
            Counter_Frist_Row_WritePeriod(Counter_Frist_Row_backup.CounterPeriod);
            Counter_Frist_Row_WriteCompare(Counter_Frist_Row_backup.CompareValue);
            /* Enter Critical Region*/
            Counter_Frist_Row_interruptState = CyEnterCriticalSection();
        
            Counter_Frist_Row_STATUS_AUX_CTRL |= Counter_Frist_Row_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(Counter_Frist_Row_interruptState);
            Counter_Frist_Row_STATUS_MASK = Counter_Frist_Row_backup.InterruptMaskValue;
        #endif  /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            Counter_Frist_Row_WriteCounter(Counter_Frist_Row_backup.CounterUdb);
            Counter_Frist_Row_STATUS_MASK = Counter_Frist_Row_backup.InterruptMaskValue;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(!Counter_Frist_Row_ControlRegRemoved)
            Counter_Frist_Row_WriteControlRegister(Counter_Frist_Row_backup.CounterControlRegister);
        #endif /* (!Counter_Frist_Row_ControlRegRemoved) */
    #endif /* (!Counter_Frist_Row_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_Frist_Row_Sleep
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
*  Counter_Frist_Row_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_Frist_Row_Sleep(void) 
{
    #if(!Counter_Frist_Row_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_Frist_Row_CTRL_ENABLE == (Counter_Frist_Row_CONTROL & Counter_Frist_Row_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_Frist_Row_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_Frist_Row_backup.CounterEnableState = 0u;
        }
    #endif /* (!Counter_Frist_Row_ControlRegRemoved) */
    Counter_Frist_Row_Stop();
    Counter_Frist_Row_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_Frist_Row_Wakeup
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
*  Counter_Frist_Row_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_Frist_Row_Wakeup(void) 
{
    Counter_Frist_Row_RestoreConfig();
    #if(!Counter_Frist_Row_ControlRegRemoved)
        if(Counter_Frist_Row_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_Frist_Row_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Counter_Frist_Row_ControlRegRemoved) */
    
}


/* [] END OF FILE */
