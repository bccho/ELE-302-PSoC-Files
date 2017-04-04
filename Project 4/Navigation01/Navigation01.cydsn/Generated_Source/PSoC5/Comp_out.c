/*******************************************************************************
* File Name: Comp_out.c  
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
#include "Comp_out.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Comp_out__PORT == 15 && (Comp_out__MASK & 0xC0))

/*******************************************************************************
* Function Name: Comp_out_Write
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
void Comp_out_Write(uint8 value) 
{
    uint8 staticBits = Comp_out_DR & ~Comp_out_MASK;
    Comp_out_DR = staticBits | ((value << Comp_out_SHIFT) & Comp_out_MASK);
}


/*******************************************************************************
* Function Name: Comp_out_SetDriveMode
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
void Comp_out_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Comp_out_0, mode);
}


/*******************************************************************************
* Function Name: Comp_out_Read
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
*  Macro Comp_out_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Comp_out_Read(void) 
{
    return (Comp_out_PS & Comp_out_MASK) >> Comp_out_SHIFT;
}


/*******************************************************************************
* Function Name: Comp_out_ReadDataReg
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
uint8 Comp_out_ReadDataReg(void) 
{
    return (Comp_out_DR & Comp_out_MASK) >> Comp_out_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Comp_out_INTSTAT) 

    /*******************************************************************************
    * Function Name: Comp_out_ClearInterrupt
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
    uint8 Comp_out_ClearInterrupt(void) 
    {
        return (Comp_out_INTSTAT & Comp_out_MASK) >> Comp_out_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
