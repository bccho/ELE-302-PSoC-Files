/*******************************************************************************
* File Name: Hall_sensor.h  
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

#if !defined(CY_PINS_Hall_sensor_H) /* Pins Hall_sensor_H */
#define CY_PINS_Hall_sensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Hall_sensor_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Hall_sensor__PORT == 15 && (Hall_sensor__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    Hall_sensor_Write(uint8 value) ;
void    Hall_sensor_SetDriveMode(uint8 mode) ;
uint8   Hall_sensor_ReadDataReg(void) ;
uint8   Hall_sensor_Read(void) ;
uint8   Hall_sensor_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Hall_sensor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Hall_sensor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Hall_sensor_DM_RES_UP          PIN_DM_RES_UP
#define Hall_sensor_DM_RES_DWN         PIN_DM_RES_DWN
#define Hall_sensor_DM_OD_LO           PIN_DM_OD_LO
#define Hall_sensor_DM_OD_HI           PIN_DM_OD_HI
#define Hall_sensor_DM_STRONG          PIN_DM_STRONG
#define Hall_sensor_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Hall_sensor_MASK               Hall_sensor__MASK
#define Hall_sensor_SHIFT              Hall_sensor__SHIFT
#define Hall_sensor_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Hall_sensor_PS                     (* (reg8 *) Hall_sensor__PS)
/* Data Register */
#define Hall_sensor_DR                     (* (reg8 *) Hall_sensor__DR)
/* Port Number */
#define Hall_sensor_PRT_NUM                (* (reg8 *) Hall_sensor__PRT) 
/* Connect to Analog Globals */                                                  
#define Hall_sensor_AG                     (* (reg8 *) Hall_sensor__AG)                       
/* Analog MUX bux enable */
#define Hall_sensor_AMUX                   (* (reg8 *) Hall_sensor__AMUX) 
/* Bidirectional Enable */                                                        
#define Hall_sensor_BIE                    (* (reg8 *) Hall_sensor__BIE)
/* Bit-mask for Aliased Register Access */
#define Hall_sensor_BIT_MASK               (* (reg8 *) Hall_sensor__BIT_MASK)
/* Bypass Enable */
#define Hall_sensor_BYP                    (* (reg8 *) Hall_sensor__BYP)
/* Port wide control signals */                                                   
#define Hall_sensor_CTL                    (* (reg8 *) Hall_sensor__CTL)
/* Drive Modes */
#define Hall_sensor_DM0                    (* (reg8 *) Hall_sensor__DM0) 
#define Hall_sensor_DM1                    (* (reg8 *) Hall_sensor__DM1)
#define Hall_sensor_DM2                    (* (reg8 *) Hall_sensor__DM2) 
/* Input Buffer Disable Override */
#define Hall_sensor_INP_DIS                (* (reg8 *) Hall_sensor__INP_DIS)
/* LCD Common or Segment Drive */
#define Hall_sensor_LCD_COM_SEG            (* (reg8 *) Hall_sensor__LCD_COM_SEG)
/* Enable Segment LCD */
#define Hall_sensor_LCD_EN                 (* (reg8 *) Hall_sensor__LCD_EN)
/* Slew Rate Control */
#define Hall_sensor_SLW                    (* (reg8 *) Hall_sensor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Hall_sensor_PRTDSI__CAPS_SEL       (* (reg8 *) Hall_sensor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Hall_sensor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Hall_sensor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Hall_sensor_PRTDSI__OE_SEL0        (* (reg8 *) Hall_sensor__PRTDSI__OE_SEL0) 
#define Hall_sensor_PRTDSI__OE_SEL1        (* (reg8 *) Hall_sensor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Hall_sensor_PRTDSI__OUT_SEL0       (* (reg8 *) Hall_sensor__PRTDSI__OUT_SEL0) 
#define Hall_sensor_PRTDSI__OUT_SEL1       (* (reg8 *) Hall_sensor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Hall_sensor_PRTDSI__SYNC_OUT       (* (reg8 *) Hall_sensor__PRTDSI__SYNC_OUT) 


#if defined(Hall_sensor__INTSTAT)  /* Interrupt Registers */

    #define Hall_sensor_INTSTAT                (* (reg8 *) Hall_sensor__INTSTAT)
    #define Hall_sensor_SNAP                   (* (reg8 *) Hall_sensor__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Hall_sensor_H */

#endif
/* [] END OF FILE */
