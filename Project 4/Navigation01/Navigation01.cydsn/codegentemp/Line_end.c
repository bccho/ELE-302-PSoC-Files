/*******************************************************************************
* File Name: Line_end.c  
* Version 1.70
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "Line_end.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Line_end__PORT == 15 && (Line_end__MASK & 0xC0))

/*******************************************************************************
* Function Name: Line_end_Write
********************************************************************************
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  void 
*  
*******************************************************************************/
void Line_end_Write(uint8 value) 
{
    uint8 staticBits = Line_end_DR & ~Line_end_MASK;
    Line_end_DR = staticBits | ((value << Line_end_SHIFT) & Line_end_MASK);
}


/*******************************************************************************
* Function Name: Line_end_SetDriveMode
********************************************************************************
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  void
*
*******************************************************************************/
void Line_end_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Line_end_0, mode);
}


/*******************************************************************************
* Function Name: Line_end_Read
********************************************************************************
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Line_end_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Line_end_Read(void) 
{
    return (Line_end_PS & Line_end_MASK) >> Line_end_SHIFT;
}


/*******************************************************************************
* Function Name: Line_end_ReadDataReg
********************************************************************************
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Line_end_ReadDataReg(void) 
{
    return (Line_end_DR & Line_end_MASK) >> Line_end_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Line_end_INTSTAT) 

    /*******************************************************************************
    * Function Name: Line_end_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  void 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Line_end_ClearInterrupt(void) 
    {
        return (Line_end_INTSTAT & Line_end_MASK) >> Line_end_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
