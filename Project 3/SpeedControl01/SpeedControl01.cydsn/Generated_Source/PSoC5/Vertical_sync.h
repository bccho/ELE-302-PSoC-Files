/*******************************************************************************
* File Name: Vertical_sync.h  
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

#if !defined(CY_PINS_Vertical_sync_H) /* Pins Vertical_sync_H */
#define CY_PINS_Vertical_sync_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vertical_sync_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vertical_sync__PORT == 15 && (Vertical_sync__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    Vertical_sync_Write(uint8 value) ;
void    Vertical_sync_SetDriveMode(uint8 mode) ;
uint8   Vertical_sync_ReadDataReg(void) ;
uint8   Vertical_sync_Read(void) ;
uint8   Vertical_sync_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Vertical_sync_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Vertical_sync_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Vertical_sync_DM_RES_UP          PIN_DM_RES_UP
#define Vertical_sync_DM_RES_DWN         PIN_DM_RES_DWN
#define Vertical_sync_DM_OD_LO           PIN_DM_OD_LO
#define Vertical_sync_DM_OD_HI           PIN_DM_OD_HI
#define Vertical_sync_DM_STRONG          PIN_DM_STRONG
#define Vertical_sync_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Vertical_sync_MASK               Vertical_sync__MASK
#define Vertical_sync_SHIFT              Vertical_sync__SHIFT
#define Vertical_sync_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vertical_sync_PS                     (* (reg8 *) Vertical_sync__PS)
/* Data Register */
#define Vertical_sync_DR                     (* (reg8 *) Vertical_sync__DR)
/* Port Number */
#define Vertical_sync_PRT_NUM                (* (reg8 *) Vertical_sync__PRT) 
/* Connect to Analog Globals */                                                  
#define Vertical_sync_AG                     (* (reg8 *) Vertical_sync__AG)                       
/* Analog MUX bux enable */
#define Vertical_sync_AMUX                   (* (reg8 *) Vertical_sync__AMUX) 
/* Bidirectional Enable */                                                        
#define Vertical_sync_BIE                    (* (reg8 *) Vertical_sync__BIE)
/* Bit-mask for Aliased Register Access */
#define Vertical_sync_BIT_MASK               (* (reg8 *) Vertical_sync__BIT_MASK)
/* Bypass Enable */
#define Vertical_sync_BYP                    (* (reg8 *) Vertical_sync__BYP)
/* Port wide control signals */                                                   
#define Vertical_sync_CTL                    (* (reg8 *) Vertical_sync__CTL)
/* Drive Modes */
#define Vertical_sync_DM0                    (* (reg8 *) Vertical_sync__DM0) 
#define Vertical_sync_DM1                    (* (reg8 *) Vertical_sync__DM1)
#define Vertical_sync_DM2                    (* (reg8 *) Vertical_sync__DM2) 
/* Input Buffer Disable Override */
#define Vertical_sync_INP_DIS                (* (reg8 *) Vertical_sync__INP_DIS)
/* LCD Common or Segment Drive */
#define Vertical_sync_LCD_COM_SEG            (* (reg8 *) Vertical_sync__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vertical_sync_LCD_EN                 (* (reg8 *) Vertical_sync__LCD_EN)
/* Slew Rate Control */
#define Vertical_sync_SLW                    (* (reg8 *) Vertical_sync__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vertical_sync_PRTDSI__CAPS_SEL       (* (reg8 *) Vertical_sync__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vertical_sync_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vertical_sync__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vertical_sync_PRTDSI__OE_SEL0        (* (reg8 *) Vertical_sync__PRTDSI__OE_SEL0) 
#define Vertical_sync_PRTDSI__OE_SEL1        (* (reg8 *) Vertical_sync__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vertical_sync_PRTDSI__OUT_SEL0       (* (reg8 *) Vertical_sync__PRTDSI__OUT_SEL0) 
#define Vertical_sync_PRTDSI__OUT_SEL1       (* (reg8 *) Vertical_sync__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vertical_sync_PRTDSI__SYNC_OUT       (* (reg8 *) Vertical_sync__PRTDSI__SYNC_OUT) 


#if defined(Vertical_sync__INTSTAT)  /* Interrupt Registers */

    #define Vertical_sync_INTSTAT                (* (reg8 *) Vertical_sync__INTSTAT)
    #define Vertical_sync_SNAP                   (* (reg8 *) Vertical_sync__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Vertical_sync_H */

#endif
/* [] END OF FILE */
