/*******************************************************************************
* File Name: Pin_button.h  
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

#if !defined(CY_PINS_Pin_button_H) /* Pins Pin_button_H */
#define CY_PINS_Pin_button_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_button_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin_button__PORT == 15 && (Pin_button__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_button_Write(uint8 value) ;
void    Pin_button_SetDriveMode(uint8 mode) ;
uint8   Pin_button_ReadDataReg(void) ;
uint8   Pin_button_Read(void) ;
uint8   Pin_button_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_button_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin_button_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin_button_DM_RES_UP          PIN_DM_RES_UP
#define Pin_button_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin_button_DM_OD_LO           PIN_DM_OD_LO
#define Pin_button_DM_OD_HI           PIN_DM_OD_HI
#define Pin_button_DM_STRONG          PIN_DM_STRONG
#define Pin_button_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin_button_MASK               Pin_button__MASK
#define Pin_button_SHIFT              Pin_button__SHIFT
#define Pin_button_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_button_PS                     (* (reg8 *) Pin_button__PS)
/* Data Register */
#define Pin_button_DR                     (* (reg8 *) Pin_button__DR)
/* Port Number */
#define Pin_button_PRT_NUM                (* (reg8 *) Pin_button__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_button_AG                     (* (reg8 *) Pin_button__AG)                       
/* Analog MUX bux enable */
#define Pin_button_AMUX                   (* (reg8 *) Pin_button__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_button_BIE                    (* (reg8 *) Pin_button__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_button_BIT_MASK               (* (reg8 *) Pin_button__BIT_MASK)
/* Bypass Enable */
#define Pin_button_BYP                    (* (reg8 *) Pin_button__BYP)
/* Port wide control signals */                                                   
#define Pin_button_CTL                    (* (reg8 *) Pin_button__CTL)
/* Drive Modes */
#define Pin_button_DM0                    (* (reg8 *) Pin_button__DM0) 
#define Pin_button_DM1                    (* (reg8 *) Pin_button__DM1)
#define Pin_button_DM2                    (* (reg8 *) Pin_button__DM2) 
/* Input Buffer Disable Override */
#define Pin_button_INP_DIS                (* (reg8 *) Pin_button__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_button_LCD_COM_SEG            (* (reg8 *) Pin_button__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_button_LCD_EN                 (* (reg8 *) Pin_button__LCD_EN)
/* Slew Rate Control */
#define Pin_button_SLW                    (* (reg8 *) Pin_button__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_button_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_button__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_button_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_button__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_button_PRTDSI__OE_SEL0        (* (reg8 *) Pin_button__PRTDSI__OE_SEL0) 
#define Pin_button_PRTDSI__OE_SEL1        (* (reg8 *) Pin_button__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_button_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_button__PRTDSI__OUT_SEL0) 
#define Pin_button_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_button__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_button_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_button__PRTDSI__SYNC_OUT) 


#if defined(Pin_button__INTSTAT)  /* Interrupt Registers */

    #define Pin_button_INTSTAT                (* (reg8 *) Pin_button__INTSTAT)
    #define Pin_button_SNAP                   (* (reg8 *) Pin_button__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Pin_button_H */

#endif
/* [] END OF FILE */
