/*******************************************************************************
* File Name: Line_begin.h  
* Version 1.70
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PINS_Line_begin_H) /* Pins Line_begin_H */
#define CY_PINS_Line_begin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Line_begin_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Line_begin__PORT == 15 && (Line_begin__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    Line_begin_Write(uint8 value) ;
void    Line_begin_SetDriveMode(uint8 mode) ;
uint8   Line_begin_ReadDataReg(void) ;
uint8   Line_begin_Read(void) ;
uint8   Line_begin_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Line_begin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Line_begin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Line_begin_DM_RES_UP          PIN_DM_RES_UP
#define Line_begin_DM_RES_DWN         PIN_DM_RES_DWN
#define Line_begin_DM_OD_LO           PIN_DM_OD_LO
#define Line_begin_DM_OD_HI           PIN_DM_OD_HI
#define Line_begin_DM_STRONG          PIN_DM_STRONG
#define Line_begin_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Line_begin_MASK               Line_begin__MASK
#define Line_begin_SHIFT              Line_begin__SHIFT
#define Line_begin_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Line_begin_PS                     (* (reg8 *) Line_begin__PS)
/* Data Register */
#define Line_begin_DR                     (* (reg8 *) Line_begin__DR)
/* Port Number */
#define Line_begin_PRT_NUM                (* (reg8 *) Line_begin__PRT) 
/* Connect to Analog Globals */                                                  
#define Line_begin_AG                     (* (reg8 *) Line_begin__AG)                       
/* Analog MUX bux enable */
#define Line_begin_AMUX                   (* (reg8 *) Line_begin__AMUX) 
/* Bidirectional Enable */                                                        
#define Line_begin_BIE                    (* (reg8 *) Line_begin__BIE)
/* Bit-mask for Aliased Register Access */
#define Line_begin_BIT_MASK               (* (reg8 *) Line_begin__BIT_MASK)
/* Bypass Enable */
#define Line_begin_BYP                    (* (reg8 *) Line_begin__BYP)
/* Port wide control signals */                                                   
#define Line_begin_CTL                    (* (reg8 *) Line_begin__CTL)
/* Drive Modes */
#define Line_begin_DM0                    (* (reg8 *) Line_begin__DM0) 
#define Line_begin_DM1                    (* (reg8 *) Line_begin__DM1)
#define Line_begin_DM2                    (* (reg8 *) Line_begin__DM2) 
/* Input Buffer Disable Override */
#define Line_begin_INP_DIS                (* (reg8 *) Line_begin__INP_DIS)
/* LCD Common or Segment Drive */
#define Line_begin_LCD_COM_SEG            (* (reg8 *) Line_begin__LCD_COM_SEG)
/* Enable Segment LCD */
#define Line_begin_LCD_EN                 (* (reg8 *) Line_begin__LCD_EN)
/* Slew Rate Control */
#define Line_begin_SLW                    (* (reg8 *) Line_begin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Line_begin_PRTDSI__CAPS_SEL       (* (reg8 *) Line_begin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Line_begin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Line_begin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Line_begin_PRTDSI__OE_SEL0        (* (reg8 *) Line_begin__PRTDSI__OE_SEL0) 
#define Line_begin_PRTDSI__OE_SEL1        (* (reg8 *) Line_begin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Line_begin_PRTDSI__OUT_SEL0       (* (reg8 *) Line_begin__PRTDSI__OUT_SEL0) 
#define Line_begin_PRTDSI__OUT_SEL1       (* (reg8 *) Line_begin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Line_begin_PRTDSI__SYNC_OUT       (* (reg8 *) Line_begin__PRTDSI__SYNC_OUT) 


#if defined(Line_begin__INTSTAT)  /* Interrupt Registers */

    #define Line_begin_INTSTAT                (* (reg8 *) Line_begin__INTSTAT)
    #define Line_begin_SNAP                   (* (reg8 *) Line_begin__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Line_begin_H */

#endif
/* [] END OF FILE */
