/*******************************************************************************
* File Name: camera_comp_fall.h
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
#if !defined(__camera_comp_fall_INTC_H__)
#define __camera_comp_fall_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void camera_comp_fall_Start(void);
void camera_comp_fall_StartEx(cyisraddress address);
void camera_comp_fall_Stop(void) ;

CY_ISR_PROTO(camera_comp_fall_Interrupt);

void camera_comp_fall_SetVector(cyisraddress address) ;
cyisraddress camera_comp_fall_GetVector(void) ;

void camera_comp_fall_SetPriority(uint8 priority) ;
uint8 camera_comp_fall_GetPriority(void) ;

void camera_comp_fall_Enable(void) ;
uint8 camera_comp_fall_GetState(void) ;
void camera_comp_fall_Disable(void) ;

void camera_comp_fall_SetPending(void) ;
void camera_comp_fall_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the camera_comp_fall ISR. */
#define camera_comp_fall_INTC_VECTOR            ((reg32 *) camera_comp_fall__INTC_VECT)

/* Address of the camera_comp_fall ISR priority. */
#define camera_comp_fall_INTC_PRIOR             ((reg8 *) camera_comp_fall__INTC_PRIOR_REG)

/* Priority of the camera_comp_fall interrupt. */
#define camera_comp_fall_INTC_PRIOR_NUMBER      camera_comp_fall__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable camera_comp_fall interrupt. */
#define camera_comp_fall_INTC_SET_EN            ((reg32 *) camera_comp_fall__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the camera_comp_fall interrupt. */
#define camera_comp_fall_INTC_CLR_EN            ((reg32 *) camera_comp_fall__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the camera_comp_fall interrupt state to pending. */
#define camera_comp_fall_INTC_SET_PD            ((reg32 *) camera_comp_fall__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the camera_comp_fall interrupt. */
#define camera_comp_fall_INTC_CLR_PD            ((reg32 *) camera_comp_fall__INTC_CLR_PD_REG)



/* __camera_comp_fall_INTC_H__ */
#endif
