/*******************************************************************************
* File Name: MessageTimerClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_MessageTimerClock_H)
#define CY_CLOCK_MessageTimerClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void MessageTimerClock_StartEx(uint32 alignClkDiv);
#define MessageTimerClock_Start() \
    MessageTimerClock_StartEx(MessageTimerClock__PA_DIV_ID)

#else

void MessageTimerClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void MessageTimerClock_Stop(void);

void MessageTimerClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 MessageTimerClock_GetDividerRegister(void);
uint8  MessageTimerClock_GetFractionalDividerRegister(void);

#define MessageTimerClock_Enable()                         MessageTimerClock_Start()
#define MessageTimerClock_Disable()                        MessageTimerClock_Stop()
#define MessageTimerClock_SetDividerRegister(clkDivider, reset)  \
    MessageTimerClock_SetFractionalDividerRegister((clkDivider), 0u)
#define MessageTimerClock_SetDivider(clkDivider)           MessageTimerClock_SetDividerRegister((clkDivider), 1u)
#define MessageTimerClock_SetDividerValue(clkDivider)      MessageTimerClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define MessageTimerClock_DIV_ID     MessageTimerClock__DIV_ID

#define MessageTimerClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define MessageTimerClock_CTRL_REG   (*(reg32 *)MessageTimerClock__CTRL_REGISTER)
#define MessageTimerClock_DIV_REG    (*(reg32 *)MessageTimerClock__DIV_REGISTER)

#define MessageTimerClock_CMD_DIV_SHIFT          (0u)
#define MessageTimerClock_CMD_PA_DIV_SHIFT       (8u)
#define MessageTimerClock_CMD_DISABLE_SHIFT      (30u)
#define MessageTimerClock_CMD_ENABLE_SHIFT       (31u)

#define MessageTimerClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << MessageTimerClock_CMD_DISABLE_SHIFT))
#define MessageTimerClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << MessageTimerClock_CMD_ENABLE_SHIFT))

#define MessageTimerClock_DIV_FRAC_MASK  (0x000000F8u)
#define MessageTimerClock_DIV_FRAC_SHIFT (3u)
#define MessageTimerClock_DIV_INT_MASK   (0xFFFFFF00u)
#define MessageTimerClock_DIV_INT_SHIFT  (8u)

#else 

#define MessageTimerClock_DIV_REG        (*(reg32 *)MessageTimerClock__REGISTER)
#define MessageTimerClock_ENABLE_REG     MessageTimerClock_DIV_REG
#define MessageTimerClock_DIV_FRAC_MASK  MessageTimerClock__FRAC_MASK
#define MessageTimerClock_DIV_FRAC_SHIFT (16u)
#define MessageTimerClock_DIV_INT_MASK   MessageTimerClock__DIVIDER_MASK
#define MessageTimerClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_MessageTimerClock_H) */

/* [] END OF FILE */
