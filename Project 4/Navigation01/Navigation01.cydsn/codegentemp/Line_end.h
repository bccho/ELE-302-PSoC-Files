/*******************************************************************************
* File Name: Line_end.h  
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

#if !defined(CY_PINS_Line_end_H) /* Pins Line_end_H */
#define CY_PINS_Line_end_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Line_end_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Line_end__PORT == 15 && (Line_end__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    Line_end_Write(uint8 value) ;
void    Line_end_SetDriveMode(uint8 mode) ;
uint8   Line_end_ReadDataReg(void) ;
uint8   Line_end_Read(void) ;
uint8   Line_end_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Line_end_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Line_end_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Line_end_DM_RES_UP          PIN_DM_RES_UP
#define Line_end_DM_RES_DWN         PIN_DM_RES_DWN
#define Line_end_DM_OD_LO           PIN_DM_OD_LO
#define Line_end_DM_OD_HI           PIN_DM_OD_HI
#define Line_end_DM_STRONG          PIN_DM_STRONG
#define Line_end_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Line_end_MASK               Line_end__MASK
#define Line_end_SHIFT              Line_end__SHIFT
#define Line_end_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Line_end_PS                     (* (reg8 *) Line_end__PS)
/* Data Register */
#define Line_end_DR                     (* (reg8 *) Line_end__DR)
/* Port Number */
#define Line_end_PRT_NUM                (* (reg8 *) Line_end__PRT) 
/* Connect to Analog Globals */                                                  
#define Line_end_AG                     (* (reg8 *) Line_end__AG)                       
/* Analog MUX bux enable */
#define Line_end_AMUX                   (* (reg8 *) Line_end__AMUX) 
/* Bidirectional Enable */                                                        
#define Line_end_BIE                    (* (reg8 *) Line_end__BIE)
/* Bit-mask for Aliased Register Access */
#define Line_end_BIT_MASK               (* (reg8 *) Line_end__BIT_MASK)
/* Bypass Enable */
#define Line_end_BYP                    (* (reg8 *) Line_end__BYP)
/* Port wide control signals */                                                   
#define Line_end_CTL                    (* (reg8 *) Line_end__CTL)
/* Drive Modes */
#define Line_end_DM0                    (* (reg8 *) Line_end__DM0) 
#define Line_end_DM1                    (* (reg8 *) Line_end__DM1)
#define Line_end_DM2                    (* (reg8 *) Line_end__DM2) 
/* Input Buffer Disable Override */
#define Line_end_INP_DIS                (* (reg8 *) Line_end__INP_DIS)
/* LCD Common or Segment Drive */
#define Line_end_LCD_COM_SEG            (* (reg8 *) Line_end__LCD_COM_SEG)
/* Enable Segment LCD */
#define Line_end_LCD_EN                 (* (reg8 *) Line_end__LCD_EN)
/* Slew Rate Control */
#define Line_end_SLW                    (* (reg8 *) Line_end__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Line_end_PRTDSI__CAPS_SEL       (* (reg8 *) Line_end__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Line_end_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Line_end__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Line_end_PRTDSI__OE_SEL0        (* (reg8 *) Line_end__PRTDSI__OE_SEL0) 
#define Line_end_PRTDSI__OE_SEL1        (* (reg8 *) Line_end__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Line_end_PRTDSI__OUT_SEL0       (* (reg8 *) Line_end__PRTDSI__OUT_SEL0) 
#define Line_end_PRTDSI__OUT_SEL1       (* (reg8 *) Line_end__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Line_end_PRTDSI__SYNC_OUT       (* (reg8 *) Line_end__PRTDSI__SYNC_OUT) 


#if defined(Line_end__INTSTAT)  /* Interrupt Registers */

    #define Line_end_INTSTAT                (* (reg8 *) Line_end__INTSTAT)
    #define Line_end_SNAP                   (* (reg8 *) Line_end__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Line_end_H */

#endif
/* [] END OF FILE */
