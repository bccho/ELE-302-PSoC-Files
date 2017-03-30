/*******************************************************************************
* File Name: throttle_update.c  
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
#include <throttle_update.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START throttle_update_intc` */

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
* Function Name: throttle_update_Start
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
void throttle_update_Start(void)
{
    /* For all we know the interrupt is active. */
    throttle_update_Disable();

    /* Set the ISR to point to the throttle_update Interrupt. */
    throttle_update_SetVector(throttle_update_Interrupt);

    /* Set the priority. */
    throttle_update_SetPriority(throttle_update_INTC_PRIOR_NUMBER);

    /* Enable it. */
    throttle_update_Enable();
}

/*******************************************************************************
* Function Name: throttle_update_StartEx
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
void throttle_update_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    throttle_update_Disable();

    /* Set the ISR to point to the throttle_update Interrupt. */
    throttle_update_SetVector(address);

    /* Set the priority. */
    throttle_update_SetPriority(throttle_update_INTC_PRIOR_NUMBER);

    /* Enable it. */
    throttle_update_Enable();
}

/*******************************************************************************
* Function Name: throttle_update_Stop
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
void throttle_update_Stop(void) 
{
    /* Disable this interrupt. */
    throttle_update_Disable();

    /* Set the ISR to point to the passive one. */
    throttle_update_SetVector(IntDefaultHandler);
}

/*******************************************************************************
* Function Name: throttle_update_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for throttle_update.
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
CY_ISR(throttle_update_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START throttle_update_Interrupt` */

    /* `#END` */
}

/*******************************************************************************
* Function Name: throttle_update_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling throttle_update_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use throttle_update_StartEx instead.
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
void throttle_update_SetVector(cyisraddress address) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + throttle_update__INTC_NUMBER] = address;
}

/*******************************************************************************
* Function Name: throttle_update_GetVector
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
cyisraddress throttle_update_GetVector(void) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + throttle_update__INTC_NUMBER];
}

/*******************************************************************************
* Function Name: throttle_update_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling throttle_update_Start
*   or throttle_update_StartEx will override any effect this method would have had. 
*	This method should only be called after throttle_update_Start or 
*	throttle_update_StartEx has been called. To set the initial
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
void throttle_update_SetPriority(uint8 priority) 
{
    *throttle_update_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: throttle_update_GetPriority
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
uint8 throttle_update_GetPriority(void) 
{
    uint8 priority;


    priority = *throttle_update_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: throttle_update_Enable
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
void throttle_update_Enable(void) 
{
    /* Enable the general interrupt. */
    *throttle_update_INTC_SET_EN = throttle_update__INTC_MASK;
}

/*******************************************************************************
* Function Name: throttle_update_GetState
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
uint8 throttle_update_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*throttle_update_INTC_SET_EN & throttle_update__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: throttle_update_Disable
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
void throttle_update_Disable(void) 
{
    /* Disable the general interrupt. */
    *throttle_update_INTC_CLR_EN = throttle_update__INTC_MASK;
}

/*******************************************************************************
* Function Name: throttle_update_SetPending
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
void throttle_update_SetPending(void) 
{
    *throttle_update_INTC_SET_PD = throttle_update__INTC_MASK;
}

/*******************************************************************************
* Function Name: throttle_update_ClearPending
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
void throttle_update_ClearPending(void) 
{
    *throttle_update_INTC_CLR_PD = throttle_update__INTC_MASK;
}
