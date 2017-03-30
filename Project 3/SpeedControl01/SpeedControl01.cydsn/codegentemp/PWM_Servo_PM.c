/*******************************************************************************
* File Name: PWM_Servo_PM.c
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
#include "PWM_Servo.h"

static PWM_Servo_backupStruct PWM_Servo_backup;


/*******************************************************************************
* Function Name: PWM_Servo_SaveConfig
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
*  PWM_Servo_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PWM_Servo_SaveConfig(void) 
{
    
    #if(!PWM_Servo_UsingFixedFunction)
        #if (CY_PSOC5A)
            PWM_Servo_backup.PWMUdb = PWM_Servo_ReadCounter();
            PWM_Servo_backup.PWMPeriod = PWM_Servo_ReadPeriod();
            #if (PWM_Servo_UseStatus)
                PWM_Servo_backup.InterruptMaskValue = PWM_Servo_STATUS_MASK;
            #endif /* (PWM_Servo_UseStatus) */
            
            #if(PWM_Servo_UseOneCompareMode)
                PWM_Servo_backup.PWMCompareValue = PWM_Servo_ReadCompare();
            #else
                PWM_Servo_backup.PWMCompareValue1 = PWM_Servo_ReadCompare1();
                PWM_Servo_backup.PWMCompareValue2 = PWM_Servo_ReadCompare2();
            #endif /* (PWM_Servo_UseOneCompareMode) */
            
           #if(PWM_Servo_DeadBandUsed)
                PWM_Servo_backup.PWMdeadBandValue = PWM_Servo_ReadDeadTime();
            #endif /* (PWM_Servo_DeadBandUsed) */
          
            #if ( PWM_Servo_KillModeMinTime)
                PWM_Servo_backup.PWMKillCounterPeriod = PWM_Servo_ReadKillTime();
            #endif /* ( PWM_Servo_KillModeMinTime) */
        #endif /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            #if(!PWM_Servo_PWMModeIsCenterAligned)
                PWM_Servo_backup.PWMPeriod = PWM_Servo_ReadPeriod();
            #endif /* (!PWM_Servo_PWMModeIsCenterAligned) */
            PWM_Servo_backup.PWMUdb = PWM_Servo_ReadCounter();
            #if (PWM_Servo_UseStatus)
                PWM_Servo_backup.InterruptMaskValue = PWM_Servo_STATUS_MASK;
            #endif /* (PWM_Servo_UseStatus) */
            
            #if(PWM_Servo_DeadBandMode == PWM_Servo__B_PWM__DBM_256_CLOCKS || \
                PWM_Servo_DeadBandMode == PWM_Servo__B_PWM__DBM_2_4_CLOCKS)
                PWM_Servo_backup.PWMdeadBandValue = PWM_Servo_ReadDeadTime();
            #endif /*  deadband count is either 2-4 clocks or 256 clocks */
            
            #if(PWM_Servo_KillModeMinTime)
                 PWM_Servo_backup.PWMKillCounterPeriod = PWM_Servo_ReadKillTime();
            #endif /* (PWM_Servo_KillModeMinTime) */
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(PWM_Servo_UseControl)
            PWM_Servo_backup.PWMControlRegister = PWM_Servo_ReadControlRegister();
        #endif /* (PWM_Servo_UseControl) */
    #endif  /* (!PWM_Servo_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Servo_RestoreConfig
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
*  PWM_Servo_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Servo_RestoreConfig(void) 
{
        #if(!PWM_Servo_UsingFixedFunction)
            #if (CY_PSOC5A)
                /* Interrupt State Backup for Critical Region*/
                uint8 PWM_Servo_interruptState;
                /* Enter Critical Region*/
                PWM_Servo_interruptState = CyEnterCriticalSection();
                #if (PWM_Servo_UseStatus)
                    /* Use the interrupt output of the status register for IRQ output */
                    PWM_Servo_STATUS_AUX_CTRL |= PWM_Servo_STATUS_ACTL_INT_EN_MASK;
                    
                    PWM_Servo_STATUS_MASK = PWM_Servo_backup.InterruptMaskValue;
                #endif /* (PWM_Servo_UseStatus) */
                
                #if (PWM_Servo_Resolution == 8)
                    /* Set FIFO 0 to 1 byte register for period*/
                    PWM_Servo_AUX_CONTROLDP0 |= (PWM_Servo_AUX_CTRL_FIFO0_CLR);
                #else /* (PWM_Servo_Resolution == 16)*/
                    /* Set FIFO 0 to 1 byte register for period */
                    PWM_Servo_AUX_CONTROLDP0 |= (PWM_Servo_AUX_CTRL_FIFO0_CLR);
                    PWM_Servo_AUX_CONTROLDP1 |= (PWM_Servo_AUX_CTRL_FIFO0_CLR);
                #endif /* (PWM_Servo_Resolution == 8) */
                /* Exit Critical Region*/
                CyExitCriticalSection(PWM_Servo_interruptState);
                
                PWM_Servo_WriteCounter(PWM_Servo_backup.PWMUdb);
                PWM_Servo_WritePeriod(PWM_Servo_backup.PWMPeriod);
                
                #if(PWM_Servo_UseOneCompareMode)
                    PWM_Servo_WriteCompare(PWM_Servo_backup.PWMCompareValue);
                #else
                    PWM_Servo_WriteCompare1(PWM_Servo_backup.PWMCompareValue1);
                    PWM_Servo_WriteCompare2(PWM_Servo_backup.PWMCompareValue2);
                #endif /* (PWM_Servo_UseOneCompareMode) */
                
               #if(PWM_Servo_DeadBandMode == PWM_Servo__B_PWM__DBM_256_CLOCKS || \
                   PWM_Servo_DeadBandMode == PWM_Servo__B_PWM__DBM_2_4_CLOCKS)
                    PWM_Servo_WriteDeadTime(PWM_Servo_backup.PWMdeadBandValue);
                #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
                #if ( PWM_Servo_KillModeMinTime)
                    PWM_Servo_WriteKillTime(PWM_Servo_backup.PWMKillCounterPeriod);
                #endif /* ( PWM_Servo_KillModeMinTime) */
            #endif /* (CY_PSOC5A) */
            
            #if (CY_PSOC3 || CY_PSOC5LP)
                #if(!PWM_Servo_PWMModeIsCenterAligned)
                    PWM_Servo_WritePeriod(PWM_Servo_backup.PWMPeriod);
                #endif /* (!PWM_Servo_PWMModeIsCenterAligned) */
                PWM_Servo_WriteCounter(PWM_Servo_backup.PWMUdb);
                #if (PWM_Servo_UseStatus)
                    PWM_Servo_STATUS_MASK = PWM_Servo_backup.InterruptMaskValue;
                #endif /* (PWM_Servo_UseStatus) */
                
                #if(PWM_Servo_DeadBandMode == PWM_Servo__B_PWM__DBM_256_CLOCKS || \
                    PWM_Servo_DeadBandMode == PWM_Servo__B_PWM__DBM_2_4_CLOCKS)
                    PWM_Servo_WriteDeadTime(PWM_Servo_backup.PWMdeadBandValue);
                #endif /* deadband count is either 2-4 clocks or 256 clocks */
                
                #if(PWM_Servo_KillModeMinTime)
                    PWM_Servo_WriteKillTime(PWM_Servo_backup.PWMKillCounterPeriod);
                #endif /* (PWM_Servo_KillModeMinTime) */
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            
            #if(PWM_Servo_UseControl)
                PWM_Servo_WriteControlRegister(PWM_Servo_backup.PWMControlRegister); 
            #endif /* (PWM_Servo_UseControl) */
        #endif  /* (!PWM_Servo_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Servo_Sleep
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
*  PWM_Servo_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Servo_Sleep(void) 
{
    #if(PWM_Servo_UseControl)
        if(PWM_Servo_CTRL_ENABLE == (PWM_Servo_CONTROL & PWM_Servo_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Servo_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Servo_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Servo_UseControl) */
    /* Stop component */
    PWM_Servo_Stop();
    
    /* Save registers configuration */
    PWM_Servo_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Servo_Wakeup
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
*  PWM_Servo_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Servo_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Servo_RestoreConfig();
    
    if(PWM_Servo_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Servo_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
