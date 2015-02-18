/*******************************************************************************
* File Name: ChannelB.c  
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
#include "ChannelB.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        ChannelB_PC =   (ChannelB_PC & \
                                (uint32)(~(uint32)(ChannelB_DRIVE_MODE_IND_MASK << (ChannelB_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (ChannelB_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: ChannelB_Write
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
void ChannelB_Write(uint8 value) 
{
    uint8 drVal = (uint8)(ChannelB_DR & (uint8)(~ChannelB_MASK));
    drVal = (drVal | ((uint8)(value << ChannelB_SHIFT) & ChannelB_MASK));
    ChannelB_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: ChannelB_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  ChannelB_DM_STRONG     Strong Drive 
*  ChannelB_DM_OD_HI      Open Drain, Drives High 
*  ChannelB_DM_OD_LO      Open Drain, Drives Low 
*  ChannelB_DM_RES_UP     Resistive Pull Up 
*  ChannelB_DM_RES_DWN    Resistive Pull Down 
*  ChannelB_DM_RES_UPDWN  Resistive Pull Up/Down 
*  ChannelB_DM_DIG_HIZ    High Impedance Digital 
*  ChannelB_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void ChannelB_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(ChannelB__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: ChannelB_Read
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
*  Macro ChannelB_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ChannelB_Read(void) 
{
    return (uint8)((ChannelB_PS & ChannelB_MASK) >> ChannelB_SHIFT);
}


/*******************************************************************************
* Function Name: ChannelB_ReadDataReg
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
uint8 ChannelB_ReadDataReg(void) 
{
    return (uint8)((ChannelB_DR & ChannelB_MASK) >> ChannelB_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ChannelB_INTSTAT) 

    /*******************************************************************************
    * Function Name: ChannelB_ClearInterrupt
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
    uint8 ChannelB_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(ChannelB_INTSTAT & ChannelB_MASK);
		ChannelB_INTSTAT = maskedStatus;
        return maskedStatus >> ChannelB_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
