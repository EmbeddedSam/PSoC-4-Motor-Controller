/*******************************************************************************
* File Name: ModbusComms_tx.c  
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
#include "ModbusComms_tx.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        ModbusComms_tx_PC =   (ModbusComms_tx_PC & \
                                (uint32)(~(uint32)(ModbusComms_tx_DRIVE_MODE_IND_MASK << (ModbusComms_tx_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (ModbusComms_tx_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: ModbusComms_tx_Write
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
void ModbusComms_tx_Write(uint8 value) 
{
    uint8 drVal = (uint8)(ModbusComms_tx_DR & (uint8)(~ModbusComms_tx_MASK));
    drVal = (drVal | ((uint8)(value << ModbusComms_tx_SHIFT) & ModbusComms_tx_MASK));
    ModbusComms_tx_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: ModbusComms_tx_SetDriveMode
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
void ModbusComms_tx_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(ModbusComms_tx__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: ModbusComms_tx_Read
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
*  Macro ModbusComms_tx_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ModbusComms_tx_Read(void) 
{
    return (uint8)((ModbusComms_tx_PS & ModbusComms_tx_MASK) >> ModbusComms_tx_SHIFT);
}


/*******************************************************************************
* Function Name: ModbusComms_tx_ReadDataReg
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
uint8 ModbusComms_tx_ReadDataReg(void) 
{
    return (uint8)((ModbusComms_tx_DR & ModbusComms_tx_MASK) >> ModbusComms_tx_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ModbusComms_tx_INTSTAT) 

    /*******************************************************************************
    * Function Name: ModbusComms_tx_ClearInterrupt
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
    uint8 ModbusComms_tx_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(ModbusComms_tx_INTSTAT & ModbusComms_tx_MASK);
		ModbusComms_tx_INTSTAT = maskedStatus;
        return maskedStatus >> ModbusComms_tx_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
