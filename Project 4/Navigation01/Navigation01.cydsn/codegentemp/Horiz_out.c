/*******************************************************************************
* File Name: Horiz_out.c  
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
#include "Horiz_out.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Horiz_out__PORT == 15 && (Horiz_out__MASK & 0xC0))

/*******************************************************************************
* Function Name: Horiz_out_Write
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
void Horiz_out_Write(uint8 value) 
{
    uint8 staticBits = Horiz_out_DR & ~Horiz_out_MASK;
    Horiz_out_DR = staticBits | ((value << Horiz_out_SHIFT) & Horiz_out_MASK);
}


/*******************************************************************************
* Function Name: Horiz_out_SetDriveMode
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
void Horiz_out_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Horiz_out_0, mode);
}


/*******************************************************************************
* Function Name: Horiz_out_Read
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
*  Macro Horiz_out_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Horiz_out_Read(void) 
{
    return (Horiz_out_PS & Horiz_out_MASK) >> Horiz_out_SHIFT;
}


/*******************************************************************************
* Function Name: Horiz_out_ReadDataReg
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
uint8 Horiz_out_ReadDataReg(void) 
{
    return (Horiz_out_DR & Horiz_out_MASK) >> Horiz_out_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Horiz_out_INTSTAT) 

    /*******************************************************************************
    * Function Name: Horiz_out_ClearInterrupt
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
    uint8 Horiz_out_ClearInterrupt(void) 
    {
        return (Horiz_out_INTSTAT & Horiz_out_MASK) >> Horiz_out_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
