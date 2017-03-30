/*******************************************************************************
* File Name: Camera_data.h  
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

#if !defined(CY_PINS_Camera_data_H) /* Pins Camera_data_H */
#define CY_PINS_Camera_data_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Camera_data_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Camera_data__PORT == 15 && (Camera_data__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    Camera_data_Write(uint8 value) ;
void    Camera_data_SetDriveMode(uint8 mode) ;
uint8   Camera_data_ReadDataReg(void) ;
uint8   Camera_data_Read(void) ;
uint8   Camera_data_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Camera_data_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Camera_data_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Camera_data_DM_RES_UP          PIN_DM_RES_UP
#define Camera_data_DM_RES_DWN         PIN_DM_RES_DWN
#define Camera_data_DM_OD_LO           PIN_DM_OD_LO
#define Camera_data_DM_OD_HI           PIN_DM_OD_HI
#define Camera_data_DM_STRONG          PIN_DM_STRONG
#define Camera_data_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Camera_data_MASK               Camera_data__MASK
#define Camera_data_SHIFT              Camera_data__SHIFT
#define Camera_data_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Camera_data_PS                     (* (reg8 *) Camera_data__PS)
/* Data Register */
#define Camera_data_DR                     (* (reg8 *) Camera_data__DR)
/* Port Number */
#define Camera_data_PRT_NUM                (* (reg8 *) Camera_data__PRT) 
/* Connect to Analog Globals */                                                  
#define Camera_data_AG                     (* (reg8 *) Camera_data__AG)                       
/* Analog MUX bux enable */
#define Camera_data_AMUX                   (* (reg8 *) Camera_data__AMUX) 
/* Bidirectional Enable */                                                        
#define Camera_data_BIE                    (* (reg8 *) Camera_data__BIE)
/* Bit-mask for Aliased Register Access */
#define Camera_data_BIT_MASK               (* (reg8 *) Camera_data__BIT_MASK)
/* Bypass Enable */
#define Camera_data_BYP                    (* (reg8 *) Camera_data__BYP)
/* Port wide control signals */                                                   
#define Camera_data_CTL                    (* (reg8 *) Camera_data__CTL)
/* Drive Modes */
#define Camera_data_DM0                    (* (reg8 *) Camera_data__DM0) 
#define Camera_data_DM1                    (* (reg8 *) Camera_data__DM1)
#define Camera_data_DM2                    (* (reg8 *) Camera_data__DM2) 
/* Input Buffer Disable Override */
#define Camera_data_INP_DIS                (* (reg8 *) Camera_data__INP_DIS)
/* LCD Common or Segment Drive */
#define Camera_data_LCD_COM_SEG            (* (reg8 *) Camera_data__LCD_COM_SEG)
/* Enable Segment LCD */
#define Camera_data_LCD_EN                 (* (reg8 *) Camera_data__LCD_EN)
/* Slew Rate Control */
#define Camera_data_SLW                    (* (reg8 *) Camera_data__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Camera_data_PRTDSI__CAPS_SEL       (* (reg8 *) Camera_data__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Camera_data_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Camera_data__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Camera_data_PRTDSI__OE_SEL0        (* (reg8 *) Camera_data__PRTDSI__OE_SEL0) 
#define Camera_data_PRTDSI__OE_SEL1        (* (reg8 *) Camera_data__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Camera_data_PRTDSI__OUT_SEL0       (* (reg8 *) Camera_data__PRTDSI__OUT_SEL0) 
#define Camera_data_PRTDSI__OUT_SEL1       (* (reg8 *) Camera_data__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Camera_data_PRTDSI__SYNC_OUT       (* (reg8 *) Camera_data__PRTDSI__SYNC_OUT) 


#if defined(Camera_data__INTSTAT)  /* Interrupt Registers */

    #define Camera_data_INTSTAT                (* (reg8 *) Camera_data__INTSTAT)
    #define Camera_data_SNAP                   (* (reg8 *) Camera_data__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Camera_data_H */

#endif
/* [] END OF FILE */
