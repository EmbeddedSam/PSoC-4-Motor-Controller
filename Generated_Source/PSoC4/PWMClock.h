/*******************************************************************************
* File Name: PWMClock.h
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

#if !defined(CY_CLOCK_PWMClock_H)
#define CY_CLOCK_PWMClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void PWMClock_StartEx(uint32 alignClkDiv);
#define PWMClock_Start() \
    PWMClock_StartEx(PWMClock__PA_DIV_ID)

#else

void PWMClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void PWMClock_Stop(void);

void PWMClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 PWMClock_GetDividerRegister(void);
uint8  PWMClock_GetFractionalDividerRegister(void);

#define PWMClock_Enable()                         PWMClock_Start()
#define PWMClock_Disable()                        PWMClock_Stop()
#define PWMClock_SetDividerRegister(clkDivider, reset)  \
    PWMClock_SetFractionalDividerRegister((clkDivider), 0u)
#define PWMClock_SetDivider(clkDivider)           PWMClock_SetDividerRegister((clkDivider), 1u)
#define PWMClock_SetDividerValue(clkDivider)      PWMClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define PWMClock_DIV_ID     PWMClock__DIV_ID

#define PWMClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define PWMClock_CTRL_REG   (*(reg32 *)PWMClock__CTRL_REGISTER)
#define PWMClock_DIV_REG    (*(reg32 *)PWMClock__DIV_REGISTER)

#define PWMClock_CMD_DIV_SHIFT          (0u)
#define PWMClock_CMD_PA_DIV_SHIFT       (8u)
#define PWMClock_CMD_DISABLE_SHIFT      (30u)
#define PWMClock_CMD_ENABLE_SHIFT       (31u)

#define PWMClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << PWMClock_CMD_DISABLE_SHIFT))
#define PWMClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << PWMClock_CMD_ENABLE_SHIFT))

#define PWMClock_DIV_FRAC_MASK  (0x000000F8u)
#define PWMClock_DIV_FRAC_SHIFT (3u)
#define PWMClock_DIV_INT_MASK   (0xFFFFFF00u)
#define PWMClock_DIV_INT_SHIFT  (8u)

#else 

#define PWMClock_DIV_REG        (*(reg32 *)PWMClock__REGISTER)
#define PWMClock_ENABLE_REG     PWMClock_DIV_REG
#define PWMClock_DIV_FRAC_MASK  PWMClock__FRAC_MASK
#define PWMClock_DIV_FRAC_SHIFT (16u)
#define PWMClock_DIV_INT_MASK   PWMClock__DIVIDER_MASK
#define PWMClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_PWMClock_H) */

/* [] END OF FILE */
