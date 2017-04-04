/*******************************************************************************
* File Name: Line_begin.c  
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
#include "Line_begin.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Line_begin__PORT == 15 && (Line_begin__MASK & 0xC0))

/*******************************************************************************
* Function Name: Line_begin_Write
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
void Line_begin_Write(uint8 value) 
{
    uint8 staticBits = Line_begin_DR & ~Line_begin_MASK;
    Line_begin_DR = staticBits | ((value << Line_begin_SHIFT) & Line_begin_MASK);
}


/*******************************************************************************
* Function Name: Line_begin_SetDriveMode
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
void Line_begin_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Line_begin_0, mode);
}


/*******************************************************************************
* Function Name: Line_begin_Read
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
*  Macro Line_begin_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Line_begin_Read(void) 
{
    return (Line_begin_PS & Line_begin_MASK) >> Line_begin_SHIFT;
}


/*******************************************************************************
* Function Name: Line_begin_ReadDataReg
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
uint8 Line_begin_ReadDataReg(void) 
{
    return (Line_begin_DR & Line_begin_MASK) >> Line_begin_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Line_begin_INTSTAT) 

    /*******************************************************************************
    * Function Name: Line_begin_ClearInterrupt
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
    uint8 Line_begin_ClearInterrupt(void) 
    {
        return (Line_begin_INTSTAT & Line_begin_MASK) >> Line_begin_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
