/*******************************************************************************
* File Name: ChannelA.c  
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
#include "ChannelA.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        ChannelA_PC =   (ChannelA_PC & \
                                (uint32)(~(uint32)(ChannelA_DRIVE_MODE_IND_MASK << (ChannelA_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (ChannelA_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: ChannelA_Write
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
void ChannelA_Write(uint8 value) 
{
    uint8 drVal = (uint8)(ChannelA_DR & (uint8)(~ChannelA_MASK));
    drVal = (drVal | ((uint8)(value << ChannelA_SHIFT) & ChannelA_MASK));
    ChannelA_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: ChannelA_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  ChannelA_DM_STRONG     Strong Drive 
*  ChannelA_DM_OD_HI      Open Drain, Drives High 
*  ChannelA_DM_OD_LO      Open Drain, Drives Low 
*  ChannelA_DM_RES_UP     Resistive Pull Up 
*  ChannelA_DM_RES_DWN    Resistive Pull Down 
*  ChannelA_DM_RES_UPDWN  Resistive Pull Up/Down 
*  ChannelA_DM_DIG_HIZ    High Impedance Digital 
*  ChannelA_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void ChannelA_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(ChannelA__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: ChannelA_Read
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
*  Macro ChannelA_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ChannelA_Read(void) 
{
    return (uint8)((ChannelA_PS & ChannelA_MASK) >> ChannelA_SHIFT);
}


/*******************************************************************************
* Function Name: ChannelA_ReadDataReg
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
uint8 ChannelA_ReadDataReg(void) 
{
    return (uint8)((ChannelA_DR & ChannelA_MASK) >> ChannelA_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ChannelA_INTSTAT) 

    /*******************************************************************************
    * Function Name: ChannelA_ClearInterrupt
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
    uint8 ChannelA_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(ChannelA_INTSTAT & ChannelA_MASK);
		ChannelA_INTSTAT = maskedStatus;
        return maskedStatus >> ChannelA_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
