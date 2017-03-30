/*******************************************************************************
* File Name: tick_timeout.c  
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
#include <tick_timeout.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START tick_timeout_intc` */

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
* Function Name: tick_timeout_Start
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
void tick_timeout_Start(void)
{
    /* For all we know the interrupt is active. */
    tick_timeout_Disable();

    /* Set the ISR to point to the tick_timeout Interrupt. */
    tick_timeout_SetVector(tick_timeout_Interrupt);

    /* Set the priority. */
    tick_timeout_SetPriority(tick_timeout_INTC_PRIOR_NUMBER);

    /* Enable it. */
    tick_timeout_Enable();
}

/*******************************************************************************
* Function Name: tick_timeout_StartEx
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
void tick_timeout_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    tick_timeout_Disable();

    /* Set the ISR to point to the tick_timeout Interrupt. */
    tick_timeout_SetVector(address);

    /* Set the priority. */
    tick_timeout_SetPriority(tick_timeout_INTC_PRIOR_NUMBER);

    /* Enable it. */
    tick_timeout_Enable();
}

/*******************************************************************************
* Function Name: tick_timeout_Stop
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
void tick_timeout_Stop(void) 
{
    /* Disable this interrupt. */
    tick_timeout_Disable();

    /* Set the ISR to point to the passive one. */
    tick_timeout_SetVector(IntDefaultHandler);
}

/*******************************************************************************
* Function Name: tick_timeout_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for tick_timeout.
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
CY_ISR(tick_timeout_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START tick_timeout_Interrupt` */

    /* `#END` */
}

/*******************************************************************************
* Function Name: tick_timeout_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling tick_timeout_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use tick_timeout_StartEx instead.
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
void tick_timeout_SetVector(cyisraddress address) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + tick_timeout__INTC_NUMBER] = address;
}

/*******************************************************************************
* Function Name: tick_timeout_GetVector
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
cyisraddress tick_timeout_GetVector(void) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + tick_timeout__INTC_NUMBER];
}

/*******************************************************************************
* Function Name: tick_timeout_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling tick_timeout_Start
*   or tick_timeout_StartEx will override any effect this method would have had. 
*	This method should only be called after tick_timeout_Start or 
*	tick_timeout_StartEx has been called. To set the initial
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
void tick_timeout_SetPriority(uint8 priority) 
{
    *tick_timeout_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: tick_timeout_GetPriority
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
uint8 tick_timeout_GetPriority(void) 
{
    uint8 priority;


    priority = *tick_timeout_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: tick_timeout_Enable
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
void tick_timeout_Enable(void) 
{
    /* Enable the general interrupt. */
    *tick_timeout_INTC_SET_EN = tick_timeout__INTC_MASK;
}

/*******************************************************************************
* Function Name: tick_timeout_GetState
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
uint8 tick_timeout_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*tick_timeout_INTC_SET_EN & tick_timeout__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: tick_timeout_Disable
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
void tick_timeout_Disable(void) 
{
    /* Disable the general interrupt. */
    *tick_timeout_INTC_CLR_EN = tick_timeout__INTC_MASK;
}

/*******************************************************************************
* Function Name: tick_timeout_SetPending
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
void tick_timeout_SetPending(void) 
{
    *tick_timeout_INTC_SET_PD = tick_timeout__INTC_MASK;
}

/*******************************************************************************
* Function Name: tick_timeout_ClearPending
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
void tick_timeout_ClearPending(void) 
{
    *tick_timeout_INTC_CLR_PD = tick_timeout__INTC_MASK;
}
