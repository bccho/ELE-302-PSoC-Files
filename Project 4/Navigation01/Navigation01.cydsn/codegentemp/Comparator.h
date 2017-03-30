/*******************************************************************************
* File Name: Comparator.h  
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

#if !defined(CY_PINS_Comparator_H) /* Pins Comparator_H */
#define CY_PINS_Comparator_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Comparator_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Comparator__PORT == 15 && (Comparator__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    Comparator_Write(uint8 value) ;
void    Comparator_SetDriveMode(uint8 mode) ;
uint8   Comparator_ReadDataReg(void) ;
uint8   Comparator_Read(void) ;
uint8   Comparator_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Comparator_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Comparator_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Comparator_DM_RES_UP          PIN_DM_RES_UP
#define Comparator_DM_RES_DWN         PIN_DM_RES_DWN
#define Comparator_DM_OD_LO           PIN_DM_OD_LO
#define Comparator_DM_OD_HI           PIN_DM_OD_HI
#define Comparator_DM_STRONG          PIN_DM_STRONG
#define Comparator_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Comparator_MASK               Comparator__MASK
#define Comparator_SHIFT              Comparator__SHIFT
#define Comparator_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Comparator_PS                     (* (reg8 *) Comparator__PS)
/* Data Register */
#define Comparator_DR                     (* (reg8 *) Comparator__DR)
/* Port Number */
#define Comparator_PRT_NUM                (* (reg8 *) Comparator__PRT) 
/* Connect to Analog Globals */                                                  
#define Comparator_AG                     (* (reg8 *) Comparator__AG)                       
/* Analog MUX bux enable */
#define Comparator_AMUX                   (* (reg8 *) Comparator__AMUX) 
/* Bidirectional Enable */                                                        
#define Comparator_BIE                    (* (reg8 *) Comparator__BIE)
/* Bit-mask for Aliased Register Access */
#define Comparator_BIT_MASK               (* (reg8 *) Comparator__BIT_MASK)
/* Bypass Enable */
#define Comparator_BYP                    (* (reg8 *) Comparator__BYP)
/* Port wide control signals */                                                   
#define Comparator_CTL                    (* (reg8 *) Comparator__CTL)
/* Drive Modes */
#define Comparator_DM0                    (* (reg8 *) Comparator__DM0) 
#define Comparator_DM1                    (* (reg8 *) Comparator__DM1)
#define Comparator_DM2                    (* (reg8 *) Comparator__DM2) 
/* Input Buffer Disable Override */
#define Comparator_INP_DIS                (* (reg8 *) Comparator__INP_DIS)
/* LCD Common or Segment Drive */
#define Comparator_LCD_COM_SEG            (* (reg8 *) Comparator__LCD_COM_SEG)
/* Enable Segment LCD */
#define Comparator_LCD_EN                 (* (reg8 *) Comparator__LCD_EN)
/* Slew Rate Control */
#define Comparator_SLW                    (* (reg8 *) Comparator__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Comparator_PRTDSI__CAPS_SEL       (* (reg8 *) Comparator__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Comparator_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Comparator__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Comparator_PRTDSI__OE_SEL0        (* (reg8 *) Comparator__PRTDSI__OE_SEL0) 
#define Comparator_PRTDSI__OE_SEL1        (* (reg8 *) Comparator__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Comparator_PRTDSI__OUT_SEL0       (* (reg8 *) Comparator__PRTDSI__OUT_SEL0) 
#define Comparator_PRTDSI__OUT_SEL1       (* (reg8 *) Comparator__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Comparator_PRTDSI__SYNC_OUT       (* (reg8 *) Comparator__PRTDSI__SYNC_OUT) 


#if defined(Comparator__INTSTAT)  /* Interrupt Registers */

    #define Comparator_INTSTAT                (* (reg8 *) Comparator__INTSTAT)
    #define Comparator_SNAP                   (* (reg8 *) Comparator__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Comparator_H */

#endif
/* [] END OF FILE */
