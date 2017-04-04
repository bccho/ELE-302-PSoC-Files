/*******************************************************************************
* File Name: Vert_out.c  
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
#include "Vert_out.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vert_out__PORT == 15 && (Vert_out__MASK & 0xC0))

/*******************************************************************************
* Function Name: Vert_out_Write
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
void Vert_out_Write(uint8 value) 
{
    uint8 staticBits = Vert_out_DR & ~Vert_out_MASK;
    Vert_out_DR = staticBits | ((value << Vert_out_SHIFT) & Vert_out_MASK);
}


/*******************************************************************************
* Function Name: Vert_out_SetDriveMode
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
void Vert_out_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Vert_out_0, mode);
}


/*******************************************************************************
* Function Name: Vert_out_Read
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
*  Macro Vert_out_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Vert_out_Read(void) 
{
    return (Vert_out_PS & Vert_out_MASK) >> Vert_out_SHIFT;
}


/*******************************************************************************
* Function Name: Vert_out_ReadDataReg
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
uint8 Vert_out_ReadDataReg(void) 
{
    return (Vert_out_DR & Vert_out_MASK) >> Vert_out_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Vert_out_INTSTAT) 

    /*******************************************************************************
    * Function Name: Vert_out_ClearInterrupt
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
    uint8 Vert_out_ClearInterrupt(void) 
    {
        return (Vert_out_INTSTAT & Vert_out_MASK) >> Vert_out_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
