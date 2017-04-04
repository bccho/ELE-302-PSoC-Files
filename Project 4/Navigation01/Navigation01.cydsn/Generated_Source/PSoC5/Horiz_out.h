/*******************************************************************************
* File Name: Horiz_out.h  
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

#if !defined(CY_PINS_Horiz_out_H) /* Pins Horiz_out_H */
#define CY_PINS_Horiz_out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Horiz_out_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Horiz_out__PORT == 15 && (Horiz_out__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    Horiz_out_Write(uint8 value) ;
void    Horiz_out_SetDriveMode(uint8 mode) ;
uint8   Horiz_out_ReadDataReg(void) ;
uint8   Horiz_out_Read(void) ;
uint8   Horiz_out_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Horiz_out_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Horiz_out_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Horiz_out_DM_RES_UP          PIN_DM_RES_UP
#define Horiz_out_DM_RES_DWN         PIN_DM_RES_DWN
#define Horiz_out_DM_OD_LO           PIN_DM_OD_LO
#define Horiz_out_DM_OD_HI           PIN_DM_OD_HI
#define Horiz_out_DM_STRONG          PIN_DM_STRONG
#define Horiz_out_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Horiz_out_MASK               Horiz_out__MASK
#define Horiz_out_SHIFT              Horiz_out__SHIFT
#define Horiz_out_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Horiz_out_PS                     (* (reg8 *) Horiz_out__PS)
/* Data Register */
#define Horiz_out_DR                     (* (reg8 *) Horiz_out__DR)
/* Port Number */
#define Horiz_out_PRT_NUM                (* (reg8 *) Horiz_out__PRT) 
/* Connect to Analog Globals */                                                  
#define Horiz_out_AG                     (* (reg8 *) Horiz_out__AG)                       
/* Analog MUX bux enable */
#define Horiz_out_AMUX                   (* (reg8 *) Horiz_out__AMUX) 
/* Bidirectional Enable */                                                        
#define Horiz_out_BIE                    (* (reg8 *) Horiz_out__BIE)
/* Bit-mask for Aliased Register Access */
#define Horiz_out_BIT_MASK               (* (reg8 *) Horiz_out__BIT_MASK)
/* Bypass Enable */
#define Horiz_out_BYP                    (* (reg8 *) Horiz_out__BYP)
/* Port wide control signals */                                                   
#define Horiz_out_CTL                    (* (reg8 *) Horiz_out__CTL)
/* Drive Modes */
#define Horiz_out_DM0                    (* (reg8 *) Horiz_out__DM0) 
#define Horiz_out_DM1                    (* (reg8 *) Horiz_out__DM1)
#define Horiz_out_DM2                    (* (reg8 *) Horiz_out__DM2) 
/* Input Buffer Disable Override */
#define Horiz_out_INP_DIS                (* (reg8 *) Horiz_out__INP_DIS)
/* LCD Common or Segment Drive */
#define Horiz_out_LCD_COM_SEG            (* (reg8 *) Horiz_out__LCD_COM_SEG)
/* Enable Segment LCD */
#define Horiz_out_LCD_EN                 (* (reg8 *) Horiz_out__LCD_EN)
/* Slew Rate Control */
#define Horiz_out_SLW                    (* (reg8 *) Horiz_out__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Horiz_out_PRTDSI__CAPS_SEL       (* (reg8 *) Horiz_out__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Horiz_out_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Horiz_out__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Horiz_out_PRTDSI__OE_SEL0        (* (reg8 *) Horiz_out__PRTDSI__OE_SEL0) 
#define Horiz_out_PRTDSI__OE_SEL1        (* (reg8 *) Horiz_out__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Horiz_out_PRTDSI__OUT_SEL0       (* (reg8 *) Horiz_out__PRTDSI__OUT_SEL0) 
#define Horiz_out_PRTDSI__OUT_SEL1       (* (reg8 *) Horiz_out__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Horiz_out_PRTDSI__SYNC_OUT       (* (reg8 *) Horiz_out__PRTDSI__SYNC_OUT) 


#if defined(Horiz_out__INTSTAT)  /* Interrupt Registers */

    #define Horiz_out_INTSTAT                (* (reg8 *) Horiz_out__INTSTAT)
    #define Horiz_out_SNAP                   (* (reg8 *) Horiz_out__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Horiz_out_H */

#endif
/* [] END OF FILE */
