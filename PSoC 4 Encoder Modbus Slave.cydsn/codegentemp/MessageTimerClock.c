/*******************************************************************************
* File Name: MessageTimerClock.c
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
#include "MessageTimerClock.h"

#if defined CYREG_PERI_DIV_CMD

/*******************************************************************************
* Function Name: MessageTimerClock_StartEx
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
void MessageTimerClock_StartEx(uint32 alignClkDiv)
{
    /* Make sure any previous start command has finished. */
    while((MessageTimerClock_CMD_REG & MessageTimerClock_CMD_ENABLE_MASK) != 0u)
    {
    }
    
    /* Specify the target divider and it's alignment divider, and enable. */
    MessageTimerClock_CMD_REG =
        ((uint32)MessageTimerClock__DIV_ID << MessageTimerClock_CMD_DIV_SHIFT)|
        (alignClkDiv << MessageTimerClock_CMD_PA_DIV_SHIFT) |
        (uint32)MessageTimerClock_CMD_ENABLE_MASK;
}

#else

/*******************************************************************************
* Function Name: MessageTimerClock_Start
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

void MessageTimerClock_Start(void)
{
    /* Set the bit to enable the clock. */
    MessageTimerClock_ENABLE_REG |= MessageTimerClock__ENABLE_MASK;
}

#endif /* CYREG_PERI_DIV_CMD */


/*******************************************************************************
* Function Name: MessageTimerClock_Stop
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
void MessageTimerClock_Stop(void)
{
#if defined CYREG_PERI_DIV_CMD

    /* Make sure any previous start command has finished. */
    while((MessageTimerClock_CMD_REG & MessageTimerClock_CMD_ENABLE_MASK) != 0u)
    {
    }
    
    /* Specify the target divider and it's alignment divider, and disable. */
    MessageTimerClock_CMD_REG =
        ((uint32)MessageTimerClock__DIV_ID << MessageTimerClock_CMD_DIV_SHIFT)|
        ((uint32)MessageTimerClock_CMD_DISABLE_MASK);

#else

    /* Clear the bit to disable the clock. */
    MessageTimerClock_ENABLE_REG &= (uint32)(~MessageTimerClock__ENABLE_MASK);
    
#endif /* CYREG_PERI_DIV_CMD */
}


/*******************************************************************************
* Function Name: MessageTimerClock_SetFractionalDividerRegister
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
void MessageTimerClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional)
{
    uint32 maskVal;
    uint32 regVal;
    
#if defined (MessageTimerClock__FRAC_MASK) || defined (CYREG_PERI_DIV_CMD)
    
	/* get all but divider bits */
    maskVal = MessageTimerClock_DIV_REG & 
                    (uint32)(~(uint32)(MessageTimerClock_DIV_INT_MASK | MessageTimerClock_DIV_FRAC_MASK)); 
	/* combine mask and new divider vals into 32-bit value */
    regVal = maskVal |
        ((uint32)((uint32)clkDivider <<  MessageTimerClock_DIV_INT_SHIFT) & MessageTimerClock_DIV_INT_MASK) |
        ((uint32)((uint32)clkFractional << MessageTimerClock_DIV_FRAC_SHIFT) & MessageTimerClock_DIV_FRAC_MASK);
    
#else
    /* get all but integer divider bits */
    maskVal = MessageTimerClock_DIV_REG & (uint32)(~(uint32)MessageTimerClock__DIVIDER_MASK);
    /* combine mask and new divider val into 32-bit value */
    regVal = clkDivider | maskVal;
    
#endif /* MessageTimerClock__FRAC_MASK || CYREG_PERI_DIV_CMD */

    MessageTimerClock_DIV_REG = regVal;
}


/*******************************************************************************
* Function Name: MessageTimerClock_GetDividerRegister
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
uint16 MessageTimerClock_GetDividerRegister(void)
{
    return (uint16)((MessageTimerClock_DIV_REG & MessageTimerClock_DIV_INT_MASK)
        >> MessageTimerClock_DIV_INT_SHIFT);
}


/*******************************************************************************
* Function Name: MessageTimerClock_GetFractionalDividerRegister
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
uint8 MessageTimerClock_GetFractionalDividerRegister(void)
{
#if defined (MessageTimerClock__FRAC_MASK)
    /* return fractional divider bits */
    return (uint8)((MessageTimerClock_DIV_REG & MessageTimerClock_DIV_FRAC_MASK)
        >> MessageTimerClock_DIV_FRAC_SHIFT);
#else
    return 0u;
#endif /* MessageTimerClock__FRAC_MASK */
}


/* [] END OF FILE */
