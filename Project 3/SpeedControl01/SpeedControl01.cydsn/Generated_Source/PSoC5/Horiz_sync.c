/*******************************************************************************
* File Name: Horiz_sync.c  
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
#include "Horiz_sync.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Horiz_sync__PORT == 15 && (Horiz_sync__MASK & 0xC0))

/*******************************************************************************
* Function Name: Horiz_sync_Write
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
void Horiz_sync_Write(uint8 value) 
{
    uint8 staticBits = Horiz_sync_DR & ~Horiz_sync_MASK;
    Horiz_sync_DR = staticBits | ((value << Horiz_sync_SHIFT) & Horiz_sync_MASK);
}


/*******************************************************************************
* Function Name: Horiz_sync_SetDriveMode
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
void Horiz_sync_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Horiz_sync_0, mode);
}


/*******************************************************************************
* Function Name: Horiz_sync_Read
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
*  Macro Horiz_sync_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Horiz_sync_Read(void) 
{
    return (Horiz_sync_PS & Horiz_sync_MASK) >> Horiz_sync_SHIFT;
}


/*******************************************************************************
* Function Name: Horiz_sync_ReadDataReg
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
uint8 Horiz_sync_ReadDataReg(void) 
{
    return (Horiz_sync_DR & Horiz_sync_MASK) >> Horiz_sync_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Horiz_sync_INTSTAT) 

    /*******************************************************************************
    * Function Name: Horiz_sync_ClearInterrupt
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
    uint8 Horiz_sync_ClearInterrupt(void) 
    {
        return (Horiz_sync_INTSTAT & Horiz_sync_MASK) >> Horiz_sync_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
