/*******************************************************************************
* File Name: ShiftReg_1.h
* Version 2.10
*
* Description:
*  This header file contains definitions associated with the Shift Register
*  component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#ifndef CY_SHIFTREG_ShiftReg_1_H
#define CY_SHIFTREG_ShiftReg_1_H

#include "cytypes.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component ShiftReg_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/***************************************
*   Conditional Compilation Parameters
***************************************/

#define ShiftReg_1_FIFO_SIZE                (4u)
#define ShiftReg_1_USE_INPUT_FIFO           (0u)
#define ShiftReg_1_USE_OUTPUT_FIFO          (0u)
#define ShiftReg_1_SR_SIZE                  (2u)


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */

typedef struct _ShiftReg_1_backupStruct
{    
    uint8 enableState;
    
    uint8 saveSrA0Reg;
    uint8 saveSrA1Reg;

    #if(CY_UDB_V0) /* CY_UDB_V0 */
        uint8 saveSrIntMask;
    #endif /* CY_UDB_V0 */

} ShiftReg_1_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  ShiftReg_1_Start(void) ;
void  ShiftReg_1_Stop(void) ; 
void  ShiftReg_1_Init(void) ;
void  ShiftReg_1_Enable(void) ; 
void  ShiftReg_1_RestoreConfig(void) ;
void  ShiftReg_1_SaveConfig(void) ;
void  ShiftReg_1_Sleep(void) ;
void  ShiftReg_1_Wakeup(void) ; 
void  ShiftReg_1_EnableInt(void) ;
void  ShiftReg_1_DisableInt(void) ;
void  ShiftReg_1_SetIntMode(uint8 interruptSource) ;
uint8 ShiftReg_1_GetIntStatus(void) ;
void  ShiftReg_1_WriteRegValue(uint8 shiftData) \
                    ;
uint8 ShiftReg_1_ReadRegValue(void) ;
uint8    ShiftReg_1_GetFIFOStatus(uint8 fifoId) ;

#if (ShiftReg_1_USE_INPUT_FIFO == 1u)
    uint8 ShiftReg_1_WriteData(uint8 shiftData)\
                    ;
#endif/*(ShiftReg_1_USE_INPUT_FIFO == 1u)*/
#if (ShiftReg_1_USE_OUTPUT_FIFO == 1u)
    uint8 ShiftReg_1_ReadData(void) ;
#endif/*(ShiftReg_1_USE_OUTPUT_FIFO == 1u)*/


/***************************************
*           API Constants
***************************************/

#define ShiftReg_1_LOAD                     (0x01u)
#define ShiftReg_1_STORE                    (0x02u)
#define ShiftReg_1_RESET                    (0x04u)

#define ShiftReg_1_IN_FIFO                  (0x01u)
#define ShiftReg_1_OUT_FIFO                 (0x02u)

#define ShiftReg_1_RET_FIFO_FULL            (0x00u)
#define ShiftReg_1_RET_FIFO_NOT_EMPTY       (0x01u)
#define ShiftReg_1_RET_FIFO_EMPTY           (0x02u)

#define ShiftReg_1_RET_FIFO_NOT_DEFINED     (0xFEu)
#define ShiftReg_1_RET_FIFO_BAD_PARAM       (0xFFu)

/***************************************
*    Enumerated Types and Parameters
***************************************/

#define ShiftReg_1__LEFT 0
#define ShiftReg_1__RIGHT 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define ShiftReg_1_SR_MASK                  (0x3u)
#define ShiftReg_1_INT_SRC                  (0u)
#define ShiftReg_1_DIRECTION                (1u)


/***************************************
*             Registers
***************************************/

/* Shift Register control register */

#define ShiftReg_1_SR_CONTROL_REG       (* (reg8 *) \
    ShiftReg_1_bSR_SyncCtl_CtrlReg__CONTROL_REG)
#define ShiftReg_1_SR_CONTROL_PTR       (  (reg8 *) \
    ShiftReg_1_bSR_SyncCtl_CtrlReg__CONTROL_REG)

/* Obsolete control reg name*/
#define ShiftReg_1_SR_CONTROL               ShiftReg_1_SR_CONTROL_REG

/* Shift Regisster interupt status register */

#define ShiftReg_1_SR_STATUS_REG            (* (reg8 *) ShiftReg_1_bSR_StsReg__STATUS_REG)
#define ShiftReg_1_SR_STATUS_PTR            (  (reg8 *) ShiftReg_1_bSR_StsReg__STATUS_REG)
#define ShiftReg_1_SR_STATUS_MASK_REG       (* (reg8 *) ShiftReg_1_bSR_StsReg__MASK_REG)
#define ShiftReg_1_SR_STATUS_MASK_PTR       (  (reg8 *) ShiftReg_1_bSR_StsReg__MASK_REG)
#define ShiftReg_1_SR_AUX_CONTROL_REG       (* (reg8 *) ShiftReg_1_bSR_StsReg__STATUS_AUX_CTL_REG)
#define ShiftReg_1_SR_AUX_CONTROL_PTR       (  (reg8 *) ShiftReg_1_bSR_StsReg__STATUS_AUX_CTL_REG)

/* Obsolete names */
#define ShiftReg_1_SR_STATUS                ShiftReg_1_SR_STATUS_REG
#define ShiftReg_1_SR_STATUS_MASK           ShiftReg_1_SR_STATUS_MASK_REG
#define ShiftReg_1_SR_AUX_CONTROL           ShiftReg_1_SR_AUX_CONTROL_REG


#define ShiftReg_1_IN_FIFO_VAL_LSB_PTR      ((reg8 *) \
    ShiftReg_1_bSR_sC8_BShiftRegDp_u0__F0_REG )
#define ShiftReg_1_SHIFT_REG_LSB_PTR        ((reg8 *) \
    ShiftReg_1_bSR_sC8_BShiftRegDp_u0__A0_REG )
#define ShiftReg_1_SHIFT_REG_VALUE_LSB_PTR  ((reg8 *) \
    ShiftReg_1_bSR_sC8_BShiftRegDp_u0__A1_REG )
#define ShiftReg_1_OUT_FIFO_VAL_LSB_PTR     ((reg8 *) \
    ShiftReg_1_bSR_sC8_BShiftRegDp_u0__F1_REG )

/***************************************
*       Register Constants
***************************************/

#define ShiftReg_1_INTERRUPTS_ENABLE        (0x10u)
#define ShiftReg_1_LOAD_INT_EN              (0x01u)
#define ShiftReg_1_STORE_INT_EN             (0x02u)
#define ShiftReg_1_RESET_INT_EN             (0x04u)
#define ShiftReg_1_CLK_EN                   (0x01u)

#define ShiftReg_1_RESET_INT_EN_MASK        (0xFBu)
#define ShiftReg_1_LOAD_INT_EN_MASK         (0xFEu)
#define ShiftReg_1_STORE_INT_EN_MASK        (0xFDu)
#define ShiftReg_1_INTS_EN_MASK             (0x07u)

#define ShiftReg_1_OUT_FIFO_CLR_BIT         (0x02u)

#if (ShiftReg_1_USE_INPUT_FIFO == 1u)

    #define ShiftReg_1_IN_FIFO_MASK         (0x18u)

    #define ShiftReg_1_IN_FIFO_FULL         (0x00u)
    #define ShiftReg_1_IN_FIFO_EMPTY        (0x01u)
    #define ShiftReg_1_IN_FIFO_NOT_EMPTY    (0x02u)
    
#endif/*(ShiftReg_1_USE_INPUT_FIFO == 1u)*/

#define ShiftReg_1_OUT_FIFO_MASK            (0x60u)

#define ShiftReg_1_OUT_FIFO_EMPTY           (0x00u)
#define ShiftReg_1_OUT_FIFO_FULL            (0x01u)
#define ShiftReg_1_OUT_FIFO_NOT_EMPTY       (0x02u)
#define ShiftReg_1_IN_FIFO_SHFT_MASK        (0x03u)
#define ShiftReg_1_OUT_FIFO_SHFT_MASK       (0x05u)

#endif /* CY_SHIFTREG_ShiftReg_1_H */

/* [] END OF FILE */
