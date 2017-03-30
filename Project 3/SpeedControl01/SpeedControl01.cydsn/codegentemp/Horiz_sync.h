/*******************************************************************************
* File Name: Horiz_sync.h  
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

#if !defined(CY_PINS_Horiz_sync_H) /* Pins Horiz_sync_H */
#define CY_PINS_Horiz_sync_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Horiz_sync_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Horiz_sync__PORT == 15 && (Horiz_sync__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    Horiz_sync_Write(uint8 value) ;
void    Horiz_sync_SetDriveMode(uint8 mode) ;
uint8   Horiz_sync_ReadDataReg(void) ;
uint8   Horiz_sync_Read(void) ;
uint8   Horiz_sync_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Horiz_sync_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Horiz_sync_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Horiz_sync_DM_RES_UP          PIN_DM_RES_UP
#define Horiz_sync_DM_RES_DWN         PIN_DM_RES_DWN
#define Horiz_sync_DM_OD_LO           PIN_DM_OD_LO
#define Horiz_sync_DM_OD_HI           PIN_DM_OD_HI
#define Horiz_sync_DM_STRONG          PIN_DM_STRONG
#define Horiz_sync_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Horiz_sync_MASK               Horiz_sync__MASK
#define Horiz_sync_SHIFT              Horiz_sync__SHIFT
#define Horiz_sync_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Horiz_sync_PS                     (* (reg8 *) Horiz_sync__PS)
/* Data Register */
#define Horiz_sync_DR                     (* (reg8 *) Horiz_sync__DR)
/* Port Number */
#define Horiz_sync_PRT_NUM                (* (reg8 *) Horiz_sync__PRT) 
/* Connect to Analog Globals */                                                  
#define Horiz_sync_AG                     (* (reg8 *) Horiz_sync__AG)                       
/* Analog MUX bux enable */
#define Horiz_sync_AMUX                   (* (reg8 *) Horiz_sync__AMUX) 
/* Bidirectional Enable */                                                        
#define Horiz_sync_BIE                    (* (reg8 *) Horiz_sync__BIE)
/* Bit-mask for Aliased Register Access */
#define Horiz_sync_BIT_MASK               (* (reg8 *) Horiz_sync__BIT_MASK)
/* Bypass Enable */
#define Horiz_sync_BYP                    (* (reg8 *) Horiz_sync__BYP)
/* Port wide control signals */                                                   
#define Horiz_sync_CTL                    (* (reg8 *) Horiz_sync__CTL)
/* Drive Modes */
#define Horiz_sync_DM0                    (* (reg8 *) Horiz_sync__DM0) 
#define Horiz_sync_DM1                    (* (reg8 *) Horiz_sync__DM1)
#define Horiz_sync_DM2                    (* (reg8 *) Horiz_sync__DM2) 
/* Input Buffer Disable Override */
#define Horiz_sync_INP_DIS                (* (reg8 *) Horiz_sync__INP_DIS)
/* LCD Common or Segment Drive */
#define Horiz_sync_LCD_COM_SEG            (* (reg8 *) Horiz_sync__LCD_COM_SEG)
/* Enable Segment LCD */
#define Horiz_sync_LCD_EN                 (* (reg8 *) Horiz_sync__LCD_EN)
/* Slew Rate Control */
#define Horiz_sync_SLW                    (* (reg8 *) Horiz_sync__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Horiz_sync_PRTDSI__CAPS_SEL       (* (reg8 *) Horiz_sync__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Horiz_sync_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Horiz_sync__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Horiz_sync_PRTDSI__OE_SEL0        (* (reg8 *) Horiz_sync__PRTDSI__OE_SEL0) 
#define Horiz_sync_PRTDSI__OE_SEL1        (* (reg8 *) Horiz_sync__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Horiz_sync_PRTDSI__OUT_SEL0       (* (reg8 *) Horiz_sync__PRTDSI__OUT_SEL0) 
#define Horiz_sync_PRTDSI__OUT_SEL1       (* (reg8 *) Horiz_sync__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Horiz_sync_PRTDSI__SYNC_OUT       (* (reg8 *) Horiz_sync__PRTDSI__SYNC_OUT) 


#if defined(Horiz_sync__INTSTAT)  /* Interrupt Registers */

    #define Horiz_sync_INTSTAT                (* (reg8 *) Horiz_sync__INTSTAT)
    #define Horiz_sync_SNAP                   (* (reg8 *) Horiz_sync__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Horiz_sync_H */

#endif
/* [] END OF FILE */
