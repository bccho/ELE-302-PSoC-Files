/*******************************************************************************
* File Name: camera_frame_start.c  
* Version 1.60
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include <CYDEVICE.H>
#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <camera_frame_start.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START camera_frame_start_intc` */

/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE	16
#endif
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);

/*******************************************************************************
* Function Name: camera_frame_start_Start
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void camera_frame_start_Start(void)
{
    /* For all we know the interrupt is active. */
    camera_frame_start_Disable();

    /* Set the ISR to point to the camera_frame_start Interrupt. */
    camera_frame_start_SetVector(camera_frame_start_Interrupt);

    /* Set the priority. */
    camera_frame_start_SetPriority(camera_frame_start_INTC_PRIOR_NUMBER);

    /* Enable it. */
    camera_frame_start_Enable();
}

/*******************************************************************************
* Function Name: camera_frame_start_StartEx
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*******************************************************************************/
void camera_frame_start_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    camera_frame_start_Disable();

    /* Set the ISR to point to the camera_frame_start Interrupt. */
    camera_frame_start_SetVector(address);

    /* Set the priority. */
    camera_frame_start_SetPriority(camera_frame_start_INTC_PRIOR_NUMBER);

    /* Enable it. */
    camera_frame_start_Enable();
}

/*******************************************************************************
* Function Name: camera_frame_start_Stop
********************************************************************************
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
void camera_frame_start_Stop(void) 
{
    /* Disable this interrupt. */
    camera_frame_start_Disable();

    /* Set the ISR to point to the passive one. */
    camera_frame_start_SetVector(IntDefaultHandler);
}

/*******************************************************************************
* Function Name: camera_frame_start_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for camera_frame_start.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
*
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
CY_ISR(camera_frame_start_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START camera_frame_start_Interrupt` */

    /* `#END` */
}

/*******************************************************************************
* Function Name: camera_frame_start_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling camera_frame_start_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use camera_frame_start_StartEx instead.
*
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void camera_frame_start_SetVector(cyisraddress address) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + camera_frame_start__INTC_NUMBER] = address;
}

/*******************************************************************************
* Function Name: camera_frame_start_GetVector
********************************************************************************
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*
*******************************************************************************/
cyisraddress camera_frame_start_GetVector(void) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + camera_frame_start__INTC_NUMBER];
}

/*******************************************************************************
* Function Name: camera_frame_start_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling camera_frame_start_Start
*   or camera_frame_start_StartEx will override any effect this method would have had. 
*	This method should only be called after camera_frame_start_Start or 
*	camera_frame_start_StartEx has been called. To set the initial
*	priority for the component use the cydwr file in the tool.
*
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void camera_frame_start_SetPriority(uint8 priority) 
{
    *camera_frame_start_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: camera_frame_start_GetPriority
********************************************************************************
* Summary:
*   Gets the Priority of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
*******************************************************************************/
uint8 camera_frame_start_GetPriority(void) 
{
    uint8 priority;


    priority = *camera_frame_start_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: camera_frame_start_Enable
********************************************************************************
* Summary:
*   Enables the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void camera_frame_start_Enable(void) 
{
    /* Enable the general interrupt. */
    *camera_frame_start_INTC_SET_EN = camera_frame_start__INTC_MASK;
}

/*******************************************************************************
* Function Name: camera_frame_start_GetState
********************************************************************************
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   1 if enabled, 0 if disabled.
*
*
*******************************************************************************/
uint8 camera_frame_start_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*camera_frame_start_INTC_SET_EN & camera_frame_start__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: camera_frame_start_Disable
********************************************************************************
* Summary:
*   Disables the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void camera_frame_start_Disable(void) 
{
    /* Disable the general interrupt. */
    *camera_frame_start_INTC_CLR_EN = camera_frame_start__INTC_MASK;
}

/*******************************************************************************
* Function Name: camera_frame_start_SetPending
********************************************************************************
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void camera_frame_start_SetPending(void) 
{
    *camera_frame_start_INTC_SET_PD = camera_frame_start__INTC_MASK;
}

/*******************************************************************************
* Function Name: camera_frame_start_ClearPending
********************************************************************************
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void camera_frame_start_ClearPending(void) 
{
    *camera_frame_start_INTC_CLR_PD = camera_frame_start__INTC_MASK;
}