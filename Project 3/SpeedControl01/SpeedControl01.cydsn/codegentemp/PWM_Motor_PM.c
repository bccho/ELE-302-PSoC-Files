/*******************************************************************************
* File Name: PWM_Motor_PM.c
* Version 2.20
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cytypes.h"
#include "PWM_Motor.h"

static PWM_Motor_backupStruct PWM_Motor_backup;


/*******************************************************************************
* Function Name: PWM_Motor_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  PWM_Motor_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PWM_Motor_SaveConfig(void) 
{
    
    #if(!PWM_Motor_UsingFixedFunction)
        #if (CY_PSOC5A)
            PWM_Motor_backup.PWMUdb = PWM_Motor_ReadCounter();
            PWM_Motor_backup.PWMPeriod = PWM_Motor_ReadPeriod();
            #if (PWM_Motor_UseStatus)
                PWM_Motor_backup.InterruptMaskValue = PWM_Motor_STATUS_MASK;
            #endif /* (PWM_Motor_UseStatus) */
            
            #if(PWM_Motor_UseOneCompareMode)
                PWM_Motor_backup.PWMCompareValue = PWM_Motor_ReadCompare();
            #else
                PWM_Motor_backup.PWMCompareValue1 = PWM_Motor_ReadCompare1();
                PWM_Motor_backup.PWMCompareValue2 = PWM_Motor_ReadCompare2();
            #endif /* (PWM_Motor_UseOneCompareMode) */
            
           #if(PWM_Motor_DeadBandUsed)
                PWM_Motor_backup.PWMdeadBandValue = PWM_Motor_ReadDeadTime();
            #endif /* (PWM_Motor_DeadBandUsed) */
          
            #if ( PWM_Motor_KillModeMinTime)
                PWM_Motor_backup.PWMKillCounterPeriod = PWM_Motor_ReadKillTime();
            #endif /* ( PWM_Motor_KillModeMinTime) */
        #endif /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            #if(!PWM_Motor_PWMModeIsCenterAligned)
                PWM_Motor_backup.PWMPeriod = PWM_Motor_ReadPeriod();
            #endif /* (!PWM_Motor_PWMModeIsCenterAligned) */
            PWM_Motor_backup.PWMUdb = PWM_Motor_ReadCounter();
            #if (PWM_Motor_UseStatus)
                PWM_Motor_backup.InterruptMaskValue = PWM_Motor_STATUS_MASK;
            #endif /* (PWM_Motor_UseStatus) */
            
            #if(PWM_Motor_DeadBandMode == PWM_Motor__B_PWM__DBM_256_CLOCKS || \
                PWM_Motor_DeadBandMode == PWM_Motor__B_PWM__DBM_2_4_CLOCKS)
                PWM_Motor_backup.PWMdeadBandValue = PWM_Motor_ReadDeadTime();
            #endif /*  deadband count is either 2-4 clocks or 256 clocks */
            
            #if(PWM_Motor_KillModeMinTime)
                 PWM_Motor_backup.PWMKillCounterPeriod = PWM_Motor_ReadKillTime();
            #endif /* (PWM_Motor_KillModeMinTime) */
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(PWM_Motor_UseControl)
            PWM_Motor_backup.PWMControlRegister = PWM_Motor_ReadControlRegister();
        #endif /* (PWM_Motor_UseControl) */
    #endif  /* (!PWM_Motor_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Motor_RestoreConfig
********************************************************************************
* 
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  PWM_Motor_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Motor_RestoreConfig(void) 
{
        #if(!PWM_Motor_UsingFixedFunction)
            #if (CY_PSOC5A)
                /* Interrupt State Backup for Critical Region*/
                uint8 PWM_Motor_interruptState;
                /* Enter Critical Region*/
                PWM_Motor_interruptState = CyEnterCriticalSection();
                #if (PWM_Motor_UseStatus)
                    /* Use the interrupt output of the status register for IRQ output */
                    PWM_Motor_STATUS_AUX_CTRL |= PWM_Motor_STATUS_ACTL_INT_EN_MASK;
                    
                    PWM_Motor_STATUS_MASK = PWM_Motor_backup.InterruptMaskValue;
                #endif /* (PWM_Motor_UseStatus) */
                
                #if (PWM_Motor_Resolution == 8)
                    /* Set FIFO 0 to 1 byte register for period*/
                    PWM_Motor_AUX_CONTROLDP0 |= (PWM_Motor_AUX_CTRL_FIFO0_CLR);
                #else /* (PWM_Motor_Resolution == 16)*/
                    /* Set FIFO 0 to 1 byte register for period */
                    PWM_Motor_AUX_CONTROLDP0 |= (PWM_Motor_AUX_CTRL_FIFO0_CLR);
                    PWM_Motor_AUX_CONTROLDP1 |= (PWM_Motor_AUX_CTRL_FIFO0_CLR);
                #endif /* (PWM_Motor_Resolution == 8) */
                /* Exit Critical Region*/
                CyExitCriticalSection(PWM_Motor_interruptState);
                
                PWM_Motor_WriteCounter(PWM_Motor_backup.PWMUdb);
                PWM_Motor_WritePeriod(PWM_Motor_backup.PWMPeriod);
                
                #if(PWM_Motor_UseOneCompareMode)
                    PWM_Motor_WriteCompare(PWM_Motor_backup.PWMCompareValue);
                #else
                    PWM_Motor_WriteCompare1(PWM_Motor_backup.PWMCompareValue1);
                    PWM_Motor_WriteCompare2(PWM_Motor_backup.PWMCompareValue2);
                #endif /* (PWM_Motor_UseOneCompareMode) */
                
               #if(PWM_Motor_DeadBandMode == PWM_Motor__B_PWM__DBM_256_CLOCKS || \
                   PWM_Motor_DeadBandMode == PWM_Motor__B_PWM__DBM_2_4_CLOCKS)
                    PWM_Motor_WriteDeadTime(PWM_Motor_backup.PWMdeadBandValue);
                #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
                #if ( PWM_Motor_KillModeMinTime)
                    PWM_Motor_WriteKillTime(PWM_Motor_backup.PWMKillCounterPeriod);
                #endif /* ( PWM_Motor_KillModeMinTime) */
            #endif /* (CY_PSOC5A) */
            
            #if (CY_PSOC3 || CY_PSOC5LP)
                #if(!PWM_Motor_PWMModeIsCenterAligned)
                    PWM_Motor_WritePeriod(PWM_Motor_backup.PWMPeriod);
                #endif /* (!PWM_Motor_PWMModeIsCenterAligned) */
                PWM_Motor_WriteCounter(PWM_Motor_backup.PWMUdb);
                #if (PWM_Motor_UseStatus)
                    PWM_Motor_STATUS_MASK = PWM_Motor_backup.InterruptMaskValue;
                #endif /* (PWM_Motor_UseStatus) */
                
                #if(PWM_Motor_DeadBandMode == PWM_Motor__B_PWM__DBM_256_CLOCKS || \
                    PWM_Motor_DeadBandMode == PWM_Motor__B_PWM__DBM_2_4_CLOCKS)
                    PWM_Motor_WriteDeadTime(PWM_Motor_backup.PWMdeadBandValue);
                #endif /* deadband count is either 2-4 clocks or 256 clocks */
                
                #if(PWM_Motor_KillModeMinTime)
                    PWM_Motor_WriteKillTime(PWM_Motor_backup.PWMKillCounterPeriod);
                #endif /* (PWM_Motor_KillModeMinTime) */
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            
            #if(PWM_Motor_UseControl)
                PWM_Motor_WriteControlRegister(PWM_Motor_backup.PWMControlRegister); 
            #endif /* (PWM_Motor_UseControl) */
        #endif  /* (!PWM_Motor_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Motor_Sleep
********************************************************************************
* 
* Summary:
*  Disables block's operation and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  PWM_Motor_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Motor_Sleep(void) 
{
    #if(PWM_Motor_UseControl)
        if(PWM_Motor_CTRL_ENABLE == (PWM_Motor_CONTROL & PWM_Motor_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Motor_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Motor_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Motor_UseControl) */
    /* Stop component */
    PWM_Motor_Stop();
    
    /* Save registers configuration */
    PWM_Motor_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Motor_Wakeup
********************************************************************************
* 
* Summary:
*  Restores and enables the user configuration. Should be called just after 
*  awaking from sleep.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  PWM_Motor_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Motor_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Motor_RestoreConfig();
    
    if(PWM_Motor_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Motor_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
