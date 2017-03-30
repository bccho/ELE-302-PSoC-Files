/*******************************************************************************
* File Name: camera_row_start.h
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
#if !defined(__camera_row_start_INTC_H__)
#define __camera_row_start_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void camera_row_start_Start(void);
void camera_row_start_StartEx(cyisraddress address);
void camera_row_start_Stop(void) ;

CY_ISR_PROTO(camera_row_start_Interrupt);

void camera_row_start_SetVector(cyisraddress address) ;
cyisraddress camera_row_start_GetVector(void) ;

void camera_row_start_SetPriority(uint8 priority) ;
uint8 camera_row_start_GetPriority(void) ;

void camera_row_start_Enable(void) ;
uint8 camera_row_start_GetState(void) ;
void camera_row_start_Disable(void) ;

void camera_row_start_SetPending(void) ;
void camera_row_start_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the camera_row_start ISR. */
#define camera_row_start_INTC_VECTOR            ((reg32 *) camera_row_start__INTC_VECT)

/* Address of the camera_row_start ISR priority. */
#define camera_row_start_INTC_PRIOR             ((reg8 *) camera_row_start__INTC_PRIOR_REG)

/* Priority of the camera_row_start interrupt. */
#define camera_row_start_INTC_PRIOR_NUMBER      camera_row_start__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable camera_row_start interrupt. */
#define camera_row_start_INTC_SET_EN            ((reg32 *) camera_row_start__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the camera_row_start interrupt. */
#define camera_row_start_INTC_CLR_EN            ((reg32 *) camera_row_start__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the camera_row_start interrupt state to pending. */
#define camera_row_start_INTC_SET_PD            ((reg32 *) camera_row_start__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the camera_row_start interrupt. */
#define camera_row_start_INTC_CLR_PD            ((reg32 *) camera_row_start__INTC_CLR_PD_REG)



/* __camera_row_start_INTC_H__ */
#endif
