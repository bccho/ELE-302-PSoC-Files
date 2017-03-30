/*******************************************************************************
* File Name: inter_1.h
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
#if !defined(__inter_1_INTC_H__)
#define __inter_1_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void inter_1_Start(void);
void inter_1_StartEx(cyisraddress address);
void inter_1_Stop(void) ;

CY_ISR_PROTO(inter_1_Interrupt);

void inter_1_SetVector(cyisraddress address) ;
cyisraddress inter_1_GetVector(void) ;

void inter_1_SetPriority(uint8 priority) ;
uint8 inter_1_GetPriority(void) ;

void inter_1_Enable(void) ;
uint8 inter_1_GetState(void) ;
void inter_1_Disable(void) ;

void inter_1_SetPending(void) ;
void inter_1_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the inter_1 ISR. */
#define inter_1_INTC_VECTOR            ((reg32 *) inter_1__INTC_VECT)

/* Address of the inter_1 ISR priority. */
#define inter_1_INTC_PRIOR             ((reg8 *) inter_1__INTC_PRIOR_REG)

/* Priority of the inter_1 interrupt. */
#define inter_1_INTC_PRIOR_NUMBER      inter_1__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable inter_1 interrupt. */
#define inter_1_INTC_SET_EN            ((reg32 *) inter_1__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the inter_1 interrupt. */
#define inter_1_INTC_CLR_EN            ((reg32 *) inter_1__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the inter_1 interrupt state to pending. */
#define inter_1_INTC_SET_PD            ((reg32 *) inter_1__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the inter_1 interrupt. */
#define inter_1_INTC_CLR_PD            ((reg32 *) inter_1__INTC_CLR_PD_REG)



/* __inter_1_INTC_H__ */
#endif
