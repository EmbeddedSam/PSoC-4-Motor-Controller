/*******************************************************************************
* File Name: EncoderInterruptPin.c  
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
#include "EncoderInterruptPin.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        EncoderInterruptPin_PC =   (EncoderInterruptPin_PC & \
                                (uint32)(~(uint32)(EncoderInterruptPin_DRIVE_MODE_IND_MASK << (EncoderInterruptPin_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (EncoderInterruptPin_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: EncoderInterruptPin_Write
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
void EncoderInterruptPin_Write(uint8 value) 
{
    uint8 drVal = (uint8)(EncoderInterruptPin_DR & (uint8)(~EncoderInterruptPin_MASK));
    drVal = (drVal | ((uint8)(value << EncoderInterruptPin_SHIFT) & EncoderInterruptPin_MASK));
    EncoderInterruptPin_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: EncoderInterruptPin_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  EncoderInterruptPin_DM_STRONG     Strong Drive 
*  EncoderInterruptPin_DM_OD_HI      Open Drain, Drives High 
*  EncoderInterruptPin_DM_OD_LO      Open Drain, Drives Low 
*  EncoderInterruptPin_DM_RES_UP     Resistive Pull Up 
*  EncoderInterruptPin_DM_RES_DWN    Resistive Pull Down 
*  EncoderInterruptPin_DM_RES_UPDWN  Resistive Pull Up/Down 
*  EncoderInterruptPin_DM_DIG_HIZ    High Impedance Digital 
*  EncoderInterruptPin_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void EncoderInterruptPin_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(EncoderInterruptPin__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: EncoderInterruptPin_Read
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
*  Macro EncoderInterruptPin_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 EncoderInterruptPin_Read(void) 
{
    return (uint8)((EncoderInterruptPin_PS & EncoderInterruptPin_MASK) >> EncoderInterruptPin_SHIFT);
}


/*******************************************************************************
* Function Name: EncoderInterruptPin_ReadDataReg
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
uint8 EncoderInterruptPin_ReadDataReg(void) 
{
    return (uint8)((EncoderInterruptPin_DR & EncoderInterruptPin_MASK) >> EncoderInterruptPin_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(EncoderInterruptPin_INTSTAT) 

    /*******************************************************************************
    * Function Name: EncoderInterruptPin_ClearInterrupt
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
    uint8 EncoderInterruptPin_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(EncoderInterruptPin_INTSTAT & EncoderInterruptPin_MASK);
		EncoderInterruptPin_INTSTAT = maskedStatus;
        return maskedStatus >> EncoderInterruptPin_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
