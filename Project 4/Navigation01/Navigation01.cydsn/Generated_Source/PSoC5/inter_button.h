/*******************************************************************************
* File Name: inter_button.h
* Version 1.60
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#if !defined(__inter_button_INTC_H__)
#define __inter_button_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void inter_button_Start(void);
void inter_button_StartEx(cyisraddress address);
void inter_button_Stop(void) ;

CY_ISR_PROTO(inter_button_Interrupt);

void inter_button_SetVector(cyisraddress address) ;
cyisraddress inter_button_GetVector(void) ;

void inter_button_SetPriority(uint8 priority) ;
uint8 inter_button_GetPriority(void) ;

void inter_button_Enable(void) ;
uint8 inter_button_GetState(void) ;
void inter_button_Disable(void) ;

void inter_button_SetPending(void) ;
void inter_button_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the inter_button ISR. */
#define inter_button_INTC_VECTOR            ((reg32 *) inter_button__INTC_VECT)

/* Address of the inter_button ISR priority. */
#define inter_button_INTC_PRIOR             ((reg8 *) inter_button__INTC_PRIOR_REG)

/* Priority of the inter_button interrupt. */
#define inter_button_INTC_PRIOR_NUMBER      inter_button__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable inter_button interrupt. */
#define inter_button_INTC_SET_EN            ((reg32 *) inter_button__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the inter_button interrupt. */
#define inter_button_INTC_CLR_EN            ((reg32 *) inter_button__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the inter_button interrupt state to pending. */
#define inter_button_INTC_SET_PD            ((reg32 *) inter_button__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the inter_button interrupt. */
#define inter_button_INTC_CLR_PD            ((reg32 *) inter_button__INTC_CLR_PD_REG)



/* __inter_button_INTC_H__ */
#endif
