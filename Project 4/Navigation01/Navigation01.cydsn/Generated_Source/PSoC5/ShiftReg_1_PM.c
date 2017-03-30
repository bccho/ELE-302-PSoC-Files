/*******************************************************************************
* File Name: ShiftReg_1_PM.c
* Version 2.10
*
* Description:
*  This file provides the API source code for sleep mode support for Shift 
*  Register component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ShiftReg_1.h"


static ShiftReg_1_BACKUP_STRUCT ShiftReg_1_backup = \
{
    /* enable state - disabled */
    0u
};


/*******************************************************************************
* Function Name: ShiftReg_1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ShiftReg_1_SaveConfig(void) 
{
    /* Store A0, A1 and Status Mask registers */
    #if (CY_UDB_V0)
       ShiftReg_1_backup.saveSrA0Reg   = CY_GET_REG8(ShiftReg_1_SHIFT_REG_LSB_PTR);
       ShiftReg_1_backup.saveSrA1Reg   = CY_GET_REG8(ShiftReg_1_SHIFT_REG_VALUE_LSB_PTR);
       ShiftReg_1_backup.saveSrIntMask = ShiftReg_1_SR_STATUS_MASK;

    #else
    /* Store A0, A1 only (not need to save Status Mask register  in ES3 silicon) */
       ShiftReg_1_backup.saveSrA0Reg   = CY_GET_REG8(ShiftReg_1_SHIFT_REG_LSB_PTR);
       ShiftReg_1_backup.saveSrA1Reg   = CY_GET_REG8(ShiftReg_1_SHIFT_REG_VALUE_LSB_PTR);

    #endif /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: ShiftReg_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ShiftReg_1_RestoreConfig(void) 
{
    /* Restore tha data, saved by SaveConfig()function */
    #if (CY_UDB_V0)
        CY_SET_REG8(ShiftReg_1_SHIFT_REG_LSB_PTR, ShiftReg_1_backup.saveSrA0Reg);
            CY_SET_REG8(ShiftReg_1_SHIFT_REG_VALUE_LSB_PTR, ShiftReg_1_backup.saveSrA1Reg);
            ShiftReg_1_SR_STATUS_MASK = ShiftReg_1_backup.saveSrIntMask;
    #else
            CY_SET_REG8(ShiftReg_1_SHIFT_REG_LSB_PTR, ShiftReg_1_backup.saveSrA0Reg);
            CY_SET_REG8(ShiftReg_1_SHIFT_REG_VALUE_LSB_PTR, ShiftReg_1_backup.saveSrA1Reg);

    #endif /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: ShiftReg_1_Sleep
********************************************************************************
*
* Summary:
*  Prepare the component to enter a Sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No. 
*
*******************************************************************************/
void ShiftReg_1_Sleep(void) 
{
    if((ShiftReg_1_SR_CONTROL & ShiftReg_1_CLK_EN) == ShiftReg_1_CLK_EN)
    {
        ShiftReg_1_backup.enableState = 1u;
    }
    else
    {
        ShiftReg_1_backup.enableState = 0u;
    }
    
    ShiftReg_1_Stop();
    ShiftReg_1_SaveConfig();
}


/*******************************************************************************
* Function Name: ShiftReg_1_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ShiftReg_1_Wakeup(void) 
{
    ShiftReg_1_RestoreConfig();
    
    if(ShiftReg_1_backup.enableState == 1u)
    {
        ShiftReg_1_Enable();   
    }
}

/* [] END OF FILE */
