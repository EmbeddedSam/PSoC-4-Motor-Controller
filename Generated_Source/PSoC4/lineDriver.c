/*******************************************************************************
* File Name: lineDriver.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "lineDriver.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        lineDriver_PC =   (lineDriver_PC & \
                                (uint32)(~(uint32)(lineDriver_DRIVE_MODE_IND_MASK << (lineDriver_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (lineDriver_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: lineDriver_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void lineDriver_Write(uint8 value) 
{
    uint8 drVal = (uint8)(lineDriver_DR & (uint8)(~lineDriver_MASK));
    drVal = (drVal | ((uint8)(value << lineDriver_SHIFT) & lineDriver_MASK));
    lineDriver_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: lineDriver_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void lineDriver_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(lineDriver__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: lineDriver_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro lineDriver_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 lineDriver_Read(void) 
{
    return (uint8)((lineDriver_PS & lineDriver_MASK) >> lineDriver_SHIFT);
}


/*******************************************************************************
* Function Name: lineDriver_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 lineDriver_ReadDataReg(void) 
{
    return (uint8)((lineDriver_DR & lineDriver_MASK) >> lineDriver_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(lineDriver_INTSTAT) 

    /*******************************************************************************
    * Function Name: lineDriver_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 lineDriver_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(lineDriver_INTSTAT & lineDriver_MASK);
		lineDriver_INTSTAT = maskedStatus;
        return maskedStatus >> lineDriver_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
