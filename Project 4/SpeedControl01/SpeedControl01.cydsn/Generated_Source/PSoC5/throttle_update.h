/*******************************************************************************
* File Name: throttle_update.h
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
#if !defined(__throttle_update_INTC_H__)
#define __throttle_update_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void throttle_update_Start(void);
void throttle_update_StartEx(cyisraddress address);
void throttle_update_Stop(void) ;

CY_ISR_PROTO(throttle_update_Interrupt);

void throttle_update_SetVector(cyisraddress address) ;
cyisraddress throttle_update_GetVector(void) ;

void throttle_update_SetPriority(uint8 priority) ;
uint8 throttle_update_GetPriority(void) ;

void throttle_update_Enable(void) ;
uint8 throttle_update_GetState(void) ;
void throttle_update_Disable(void) ;

void throttle_update_SetPending(void) ;
void throttle_update_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the throttle_update ISR. */
#define throttle_update_INTC_VECTOR            ((reg32 *) throttle_update__INTC_VECT)

/* Address of the throttle_update ISR priority. */
#define throttle_update_INTC_PRIOR             ((reg8 *) throttle_update__INTC_PRIOR_REG)

/* Priority of the throttle_update interrupt. */
#define throttle_update_INTC_PRIOR_NUMBER      throttle_update__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable throttle_update interrupt. */
#define throttle_update_INTC_SET_EN            ((reg32 *) throttle_update__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the throttle_update interrupt. */
#define throttle_update_INTC_CLR_EN            ((reg32 *) throttle_update__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the throttle_update interrupt state to pending. */
#define throttle_update_INTC_SET_PD            ((reg32 *) throttle_update__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the throttle_update interrupt. */
#define throttle_update_INTC_CLR_PD            ((reg32 *) throttle_update__INTC_CLR_PD_REG)



/* __throttle_update_INTC_H__ */
#endif
