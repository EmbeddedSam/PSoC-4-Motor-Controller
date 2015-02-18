/*******************************************************************************
* File Name: writeEnable.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "writeEnable.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        writeEnable_PC =   (writeEnable_PC & \
                                (uint32)(~(uint32)(writeEnable_DRIVE_MODE_IND_MASK << (writeEnable_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (writeEnable_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: writeEnable_Write
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
void writeEnable_Write(uint8 value) 
{
    uint8 drVal = (uint8)(writeEnable_DR & (uint8)(~writeEnable_MASK));
    drVal = (drVal | ((uint8)(value << writeEnable_SHIFT) & writeEnable_MASK));
    writeEnable_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: writeEnable_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  writeEnable_DM_STRONG     Strong Drive 
*  writeEnable_DM_OD_HI      Open Drain, Drives High 
*  writeEnable_DM_OD_LO      Open Drain, Drives Low 
*  writeEnable_DM_RES_UP     Resistive Pull Up 
*  writeEnable_DM_RES_DWN    Resistive Pull Down 
*  writeEnable_DM_RES_UPDWN  Resistive Pull Up/Down 
*  writeEnable_DM_DIG_HIZ    High Impedance Digital 
*  writeEnable_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void writeEnable_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(writeEnable__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: writeEnable_Read
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
*  Macro writeEnable_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 writeEnable_Read(void) 
{
    return (uint8)((writeEnable_PS & writeEnable_MASK) >> writeEnable_SHIFT);
}


/*******************************************************************************
* Function Name: writeEnable_ReadDataReg
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
uint8 writeEnable_ReadDataReg(void) 
{
    return (uint8)((writeEnable_DR & writeEnable_MASK) >> writeEnable_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(writeEnable_INTSTAT) 

    /*******************************************************************************
    * Function Name: writeEnable_ClearInterrupt
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
    uint8 writeEnable_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(writeEnable_INTSTAT & writeEnable_MASK);
		writeEnable_INTSTAT = maskedStatus;
        return maskedStatus >> writeEnable_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
