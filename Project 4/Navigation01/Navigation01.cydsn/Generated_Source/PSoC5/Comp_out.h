/*******************************************************************************
* File Name: Comp_out.h  
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

#if !defined(CY_PINS_Comp_out_H) /* Pins Comp_out_H */
#define CY_PINS_Comp_out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Comp_out_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Comp_out__PORT == 15 && (Comp_out__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    Comp_out_Write(uint8 value) ;
void    Comp_out_SetDriveMode(uint8 mode) ;
uint8   Comp_out_ReadDataReg(void) ;
uint8   Comp_out_Read(void) ;
uint8   Comp_out_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Comp_out_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Comp_out_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Comp_out_DM_RES_UP          PIN_DM_RES_UP
#define Comp_out_DM_RES_DWN         PIN_DM_RES_DWN
#define Comp_out_DM_OD_LO           PIN_DM_OD_LO
#define Comp_out_DM_OD_HI           PIN_DM_OD_HI
#define Comp_out_DM_STRONG          PIN_DM_STRONG
#define Comp_out_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Comp_out_MASK               Comp_out__MASK
#define Comp_out_SHIFT              Comp_out__SHIFT
#define Comp_out_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Comp_out_PS                     (* (reg8 *) Comp_out__PS)
/* Data Register */
#define Comp_out_DR                     (* (reg8 *) Comp_out__DR)
/* Port Number */
#define Comp_out_PRT_NUM                (* (reg8 *) Comp_out__PRT) 
/* Connect to Analog Globals */                                                  
#define Comp_out_AG                     (* (reg8 *) Comp_out__AG)                       
/* Analog MUX bux enable */
#define Comp_out_AMUX                   (* (reg8 *) Comp_out__AMUX) 
/* Bidirectional Enable */                                                        
#define Comp_out_BIE                    (* (reg8 *) Comp_out__BIE)
/* Bit-mask for Aliased Register Access */
#define Comp_out_BIT_MASK               (* (reg8 *) Comp_out__BIT_MASK)
/* Bypass Enable */
#define Comp_out_BYP                    (* (reg8 *) Comp_out__BYP)
/* Port wide control signals */                                                   
#define Comp_out_CTL                    (* (reg8 *) Comp_out__CTL)
/* Drive Modes */
#define Comp_out_DM0                    (* (reg8 *) Comp_out__DM0) 
#define Comp_out_DM1                    (* (reg8 *) Comp_out__DM1)
#define Comp_out_DM2                    (* (reg8 *) Comp_out__DM2) 
/* Input Buffer Disable Override */
#define Comp_out_INP_DIS                (* (reg8 *) Comp_out__INP_DIS)
/* LCD Common or Segment Drive */
#define Comp_out_LCD_COM_SEG            (* (reg8 *) Comp_out__LCD_COM_SEG)
/* Enable Segment LCD */
#define Comp_out_LCD_EN                 (* (reg8 *) Comp_out__LCD_EN)
/* Slew Rate Control */
#define Comp_out_SLW                    (* (reg8 *) Comp_out__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Comp_out_PRTDSI__CAPS_SEL       (* (reg8 *) Comp_out__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Comp_out_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Comp_out__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Comp_out_PRTDSI__OE_SEL0        (* (reg8 *) Comp_out__PRTDSI__OE_SEL0) 
#define Comp_out_PRTDSI__OE_SEL1        (* (reg8 *) Comp_out__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Comp_out_PRTDSI__OUT_SEL0       (* (reg8 *) Comp_out__PRTDSI__OUT_SEL0) 
#define Comp_out_PRTDSI__OUT_SEL1       (* (reg8 *) Comp_out__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Comp_out_PRTDSI__SYNC_OUT       (* (reg8 *) Comp_out__PRTDSI__SYNC_OUT) 


#if defined(Comp_out__INTSTAT)  /* Interrupt Registers */

    #define Comp_out_INTSTAT                (* (reg8 *) Comp_out__INTSTAT)
    #define Comp_out_SNAP                   (* (reg8 *) Comp_out__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Comp_out_H */

#endif
/* [] END OF FILE */
