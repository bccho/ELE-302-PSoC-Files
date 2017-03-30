/*******************************************************************************
* File Name: Comparator.c  
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
#include "Comparator.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Comparator__PORT == 15 && (Comparator__MASK & 0xC0))

/*******************************************************************************
* Function Name: Comparator_Write
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
void Comparator_Write(uint8 value) 
{
    uint8 staticBits = Comparator_DR & ~Comparator_MASK;
    Comparator_DR = staticBits | ((value << Comparator_SHIFT) & Comparator_MASK);
}


/*******************************************************************************
* Function Name: Comparator_SetDriveMode
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
void Comparator_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Comparator_0, mode);
}


/*******************************************************************************
* Function Name: Comparator_Read
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
*  Macro Comparator_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Comparator_Read(void) 
{
    return (Comparator_PS & Comparator_MASK) >> Comparator_SHIFT;
}


/*******************************************************************************
* Function Name: Comparator_ReadDataReg
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
uint8 Comparator_ReadDataReg(void) 
{
    return (Comparator_DR & Comparator_MASK) >> Comparator_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Comparator_INTSTAT) 

    /*******************************************************************************
    * Function Name: Comparator_ClearInterrupt
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
    uint8 Comparator_ClearInterrupt(void) 
    {
        return (Comparator_INTSTAT & Comparator_MASK) >> Comparator_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
