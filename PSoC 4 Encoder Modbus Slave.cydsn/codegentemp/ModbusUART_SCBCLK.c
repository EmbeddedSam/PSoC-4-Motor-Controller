/*******************************************************************************
* File Name: ModbusUART_SCBCLK.c
* Version 2.20
*
*  Description:
*   Provides system API for the clocking, interrupts and watchdog timer.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <cydevice_trm.h>
#include "ModbusUART_SCBCLK.h"

#if defined CYREG_PERI_DIV_CMD

/*******************************************************************************
* Function Name: ModbusUART_SCBCLK_StartEx
********************************************************************************
*
* Summary:
*  Starts the clock, aligned to the specified running clock.
*
* Parameters:
*  alignClkDiv:  The divider to which phase alignment is performed when the
*    clock is started.
*
* Returns:
*  None
*
*******************************************************************************/
void ModbusUART_SCBCLK_StartEx(uint32 alignClkDiv)
{
    /* Make sure any previous start command has finished. */
    while((ModbusUART_SCBCLK_CMD_REG & ModbusUART_SCBCLK_CMD_ENABLE_MASK) != 0u)
    {
    }
    
    /* Specify the target divider and it's alignment divider, and enable. */
    ModbusUART_SCBCLK_CMD_REG =
        ((uint32)ModbusUART_SCBCLK__DIV_ID << ModbusUART_SCBCLK_CMD_DIV_SHIFT)|
        (alignClkDiv << ModbusUART_SCBCLK_CMD_PA_DIV_SHIFT) |
        (uint32)ModbusUART_SCBCLK_CMD_ENABLE_MASK;
}

#else

/*******************************************************************************
* Function Name: ModbusUART_SCBCLK_Start
********************************************************************************
*
* Summary:
*  Starts the clock.
*
* Parameters:
*  None
*
* Returns:
*  None
*
*******************************************************************************/

void ModbusUART_SCBCLK_Start(void)
{
    /* Set the bit to enable the clock. */
    ModbusUART_SCBCLK_ENABLE_REG |= ModbusUART_SCBCLK__ENABLE_MASK;
}

#endif /* CYREG_PERI_DIV_CMD */


/*******************************************************************************
* Function Name: ModbusUART_SCBCLK_Stop
********************************************************************************
*
* Summary:
*  Stops the clock and returns immediately. This API does not require the
*  source clock to be running but may return before the hardware is actually
*  disabled.
*
* Parameters:
*  None
*
* Returns:
*  None
*
*******************************************************************************/
void ModbusUART_SCBCLK_Stop(void)
{
#if defined CYREG_PERI_DIV_CMD

    /* Make sure any previous start command has finished. */
    while((ModbusUART_SCBCLK_CMD_REG & ModbusUART_SCBCLK_CMD_ENABLE_MASK) != 0u)
    {
    }
    
    /* Specify the target divider and it's alignment divider, and disable. */
    ModbusUART_SCBCLK_CMD_REG =
        ((uint32)ModbusUART_SCBCLK__DIV_ID << ModbusUART_SCBCLK_CMD_DIV_SHIFT)|
        ((uint32)ModbusUART_SCBCLK_CMD_DISABLE_MASK);

#else

    /* Clear the bit to disable the clock. */
    ModbusUART_SCBCLK_ENABLE_REG &= (uint32)(~ModbusUART_SCBCLK__ENABLE_MASK);
    
#endif /* CYREG_PERI_DIV_CMD */
}


/*******************************************************************************
* Function Name: ModbusUART_SCBCLK_SetFractionalDividerRegister
********************************************************************************
*
* Summary:
*  Modifies the clock divider and the fractional divider.
*
* Parameters:
*  clkDivider:  Divider register value (0-65535). This value is NOT the
*    divider; the clock hardware divides by clkDivider plus one. For example,
*    to divide the clock by 2, this parameter should be set to 1.
*  fracDivider:  Fractional Divider register value (0-31).
* Returns:
*  None
*
*******************************************************************************/
void ModbusUART_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional)
{
    uint32 maskVal;
    uint32 regVal;
    
#if defined (ModbusUART_SCBCLK__FRAC_MASK) || defined (CYREG_PERI_DIV_CMD)
    
	/* get all but divider bits */
    maskVal = ModbusUART_SCBCLK_DIV_REG & 
                    (uint32)(~(uint32)(ModbusUART_SCBCLK_DIV_INT_MASK | ModbusUART_SCBCLK_DIV_FRAC_MASK)); 
	/* combine mask and new divider vals into 32-bit value */
    regVal = maskVal |
        ((uint32)((uint32)clkDivider <<  ModbusUART_SCBCLK_DIV_INT_SHIFT) & ModbusUART_SCBCLK_DIV_INT_MASK) |
        ((uint32)((uint32)clkFractional << ModbusUART_SCBCLK_DIV_FRAC_SHIFT) & ModbusUART_SCBCLK_DIV_FRAC_MASK);
    
#else
    /* get all but integer divider bits */
    maskVal = ModbusUART_SCBCLK_DIV_REG & (uint32)(~(uint32)ModbusUART_SCBCLK__DIVIDER_MASK);
    /* combine mask and new divider val into 32-bit value */
    regVal = clkDivider | maskVal;
    
#endif /* ModbusUART_SCBCLK__FRAC_MASK || CYREG_PERI_DIV_CMD */

    ModbusUART_SCBCLK_DIV_REG = regVal;
}


/*******************************************************************************
* Function Name: ModbusUART_SCBCLK_GetDividerRegister
********************************************************************************
*
* Summary:
*  Gets the clock divider register value.
*
* Parameters:
*  None
*
* Returns:
*  Divide value of the clock minus 1. For example, if the clock is set to
*  divide by 2, the return value will be 1.
*
*******************************************************************************/
uint16 ModbusUART_SCBCLK_GetDividerRegister(void)
{
    return (uint16)((ModbusUART_SCBCLK_DIV_REG & ModbusUART_SCBCLK_DIV_INT_MASK)
        >> ModbusUART_SCBCLK_DIV_INT_SHIFT);
}


/*******************************************************************************
* Function Name: ModbusUART_SCBCLK_GetFractionalDividerRegister
********************************************************************************
*
* Summary:
*  Gets the clock fractional divider register value.
*
* Parameters:
*  None
*
* Returns:
*  Fractional Divide value of the clock
*  0 if the fractional divider is not in use.
*
*******************************************************************************/
uint8 ModbusUART_SCBCLK_GetFractionalDividerRegister(void)
{
#if defined (ModbusUART_SCBCLK__FRAC_MASK)
    /* return fractional divider bits */
    return (uint8)((ModbusUART_SCBCLK_DIV_REG & ModbusUART_SCBCLK_DIV_FRAC_MASK)
        >> ModbusUART_SCBCLK_DIV_FRAC_SHIFT);
#else
    return 0u;
#endif /* ModbusUART_SCBCLK__FRAC_MASK */
}


/* [] END OF FILE */
