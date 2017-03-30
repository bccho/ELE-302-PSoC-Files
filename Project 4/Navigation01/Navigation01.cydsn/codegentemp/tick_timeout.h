/*******************************************************************************
* File Name: tick_timeout.h
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
#if !defined(__tick_timeout_INTC_H__)
#define __tick_timeout_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void tick_timeout_Start(void);
void tick_timeout_StartEx(cyisraddress address);
void tick_timeout_Stop(void) ;

CY_ISR_PROTO(tick_timeout_Interrupt);

void tick_timeout_SetVector(cyisraddress address) ;
cyisraddress tick_timeout_GetVector(void) ;

void tick_timeout_SetPriority(uint8 priority) ;
uint8 tick_timeout_GetPriority(void) ;

void tick_timeout_Enable(void) ;
uint8 tick_timeout_GetState(void) ;
void tick_timeout_Disable(void) ;

void tick_timeout_SetPending(void) ;
void tick_timeout_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the tick_timeout ISR. */
#define tick_timeout_INTC_VECTOR            ((reg32 *) tick_timeout__INTC_VECT)

/* Address of the tick_timeout ISR priority. */
#define tick_timeout_INTC_PRIOR             ((reg8 *) tick_timeout__INTC_PRIOR_REG)

/* Priority of the tick_timeout interrupt. */
#define tick_timeout_INTC_PRIOR_NUMBER      tick_timeout__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable tick_timeout interrupt. */
#define tick_timeout_INTC_SET_EN            ((reg32 *) tick_timeout__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the tick_timeout interrupt. */
#define tick_timeout_INTC_CLR_EN            ((reg32 *) tick_timeout__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the tick_timeout interrupt state to pending. */
#define tick_timeout_INTC_SET_PD            ((reg32 *) tick_timeout__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the tick_timeout interrupt. */
#define tick_timeout_INTC_CLR_PD            ((reg32 *) tick_timeout__INTC_CLR_PD_REG)



/* __tick_timeout_INTC_H__ */
#endif
