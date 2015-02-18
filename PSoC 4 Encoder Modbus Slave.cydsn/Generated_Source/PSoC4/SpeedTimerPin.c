/*******************************************************************************
* File Name: SpeedTimerPin.c  
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
#include "SpeedTimerPin.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        SpeedTimerPin_PC =   (SpeedTimerPin_PC & \
                                (uint32)(~(uint32)(SpeedTimerPin_DRIVE_MODE_IND_MASK << (SpeedTimerPin_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (SpeedTimerPin_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: SpeedTimerPin_Write
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
void SpeedTimerPin_Write(uint8 value) 
{
    uint8 drVal = (uint8)(SpeedTimerPin_DR & (uint8)(~SpeedTimerPin_MASK));
    drVal = (drVal | ((uint8)(value << SpeedTimerPin_SHIFT) & SpeedTimerPin_MASK));
    SpeedTimerPin_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: SpeedTimerPin_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  SpeedTimerPin_DM_STRONG     Strong Drive 
*  SpeedTimerPin_DM_OD_HI      Open Drain, Drives High 
*  SpeedTimerPin_DM_OD_LO      Open Drain, Drives Low 
*  SpeedTimerPin_DM_RES_UP     Resistive Pull Up 
*  SpeedTimerPin_DM_RES_DWN    Resistive Pull Down 
*  SpeedTimerPin_DM_RES_UPDWN  Resistive Pull Up/Down 
*  SpeedTimerPin_DM_DIG_HIZ    High Impedance Digital 
*  SpeedTimerPin_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void SpeedTimerPin_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(SpeedTimerPin__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: SpeedTimerPin_Read
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
*  Macro SpeedTimerPin_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SpeedTimerPin_Read(void) 
{
    return (uint8)((SpeedTimerPin_PS & SpeedTimerPin_MASK) >> SpeedTimerPin_SHIFT);
}


/*******************************************************************************
* Function Name: SpeedTimerPin_ReadDataReg
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
uint8 SpeedTimerPin_ReadDataReg(void) 
{
    return (uint8)((SpeedTimerPin_DR & SpeedTimerPin_MASK) >> SpeedTimerPin_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SpeedTimerPin_INTSTAT) 

    /*******************************************************************************
    * Function Name: SpeedTimerPin_ClearInterrupt
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
    uint8 SpeedTimerPin_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(SpeedTimerPin_INTSTAT & SpeedTimerPin_MASK);
		SpeedTimerPin_INTSTAT = maskedStatus;
        return maskedStatus >> SpeedTimerPin_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
