/*******************************************************************************
* File Name: wheel_tick.h
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
#if !defined(__wheel_tick_INTC_H__)
#define __wheel_tick_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void wheel_tick_Start(void);
void wheel_tick_StartEx(cyisraddress address);
void wheel_tick_Stop(void) ;

CY_ISR_PROTO(wheel_tick_Interrupt);

void wheel_tick_SetVector(cyisraddress address) ;
cyisraddress wheel_tick_GetVector(void) ;

void wheel_tick_SetPriority(uint8 priority) ;
uint8 wheel_tick_GetPriority(void) ;

void wheel_tick_Enable(void) ;
uint8 wheel_tick_GetState(void) ;
void wheel_tick_Disable(void) ;

void wheel_tick_SetPending(void) ;
void wheel_tick_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the wheel_tick ISR. */
#define wheel_tick_INTC_VECTOR            ((reg32 *) wheel_tick__INTC_VECT)

/* Address of the wheel_tick ISR priority. */
#define wheel_tick_INTC_PRIOR             ((reg8 *) wheel_tick__INTC_PRIOR_REG)

/* Priority of the wheel_tick interrupt. */
#define wheel_tick_INTC_PRIOR_NUMBER      wheel_tick__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable wheel_tick interrupt. */
#define wheel_tick_INTC_SET_EN            ((reg32 *) wheel_tick__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the wheel_tick interrupt. */
#define wheel_tick_INTC_CLR_EN            ((reg32 *) wheel_tick__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the wheel_tick interrupt state to pending. */
#define wheel_tick_INTC_SET_PD            ((reg32 *) wheel_tick__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the wheel_tick interrupt. */
#define wheel_tick_INTC_CLR_PD            ((reg32 *) wheel_tick__INTC_CLR_PD_REG)



/* __wheel_tick_INTC_H__ */
#endif
