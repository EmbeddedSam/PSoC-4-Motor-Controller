/*******************************************************************************
* File Name: Direction.c  
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
#include "Direction.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Direction_PC =   (Direction_PC & \
                                (uint32)(~(uint32)(Direction_DRIVE_MODE_IND_MASK << (Direction_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Direction_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Direction_Write
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
void Direction_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Direction_DR & (uint8)(~Direction_MASK));
    drVal = (drVal | ((uint8)(value << Direction_SHIFT) & Direction_MASK));
    Direction_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Direction_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Direction_DM_STRONG     Strong Drive 
*  Direction_DM_OD_HI      Open Drain, Drives High 
*  Direction_DM_OD_LO      Open Drain, Drives Low 
*  Direction_DM_RES_UP     Resistive Pull Up 
*  Direction_DM_RES_DWN    Resistive Pull Down 
*  Direction_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Direction_DM_DIG_HIZ    High Impedance Digital 
*  Direction_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Direction_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Direction__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Direction_Read
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
*  Macro Direction_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Direction_Read(void) 
{
    return (uint8)((Direction_PS & Direction_MASK) >> Direction_SHIFT);
}


/*******************************************************************************
* Function Name: Direction_ReadDataReg
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
uint8 Direction_ReadDataReg(void) 
{
    return (uint8)((Direction_DR & Direction_MASK) >> Direction_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Direction_INTSTAT) 

    /*******************************************************************************
    * Function Name: Direction_ClearInterrupt
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
    uint8 Direction_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Direction_INTSTAT & Direction_MASK);
		Direction_INTSTAT = maskedStatus;
        return maskedStatus >> Direction_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
