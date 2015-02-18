/*******************************************************************************
* File Name: MotorCurrentADC_intClock.h
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

#if !defined(CY_CLOCK_MotorCurrentADC_intClock_H)
#define CY_CLOCK_MotorCurrentADC_intClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void MotorCurrentADC_intClock_StartEx(uint32 alignClkDiv);
#define MotorCurrentADC_intClock_Start() \
    MotorCurrentADC_intClock_StartEx(MotorCurrentADC_intClock__PA_DIV_ID)

#else

void MotorCurrentADC_intClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void MotorCurrentADC_intClock_Stop(void);

void MotorCurrentADC_intClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 MotorCurrentADC_intClock_GetDividerRegister(void);
uint8  MotorCurrentADC_intClock_GetFractionalDividerRegister(void);

#define MotorCurrentADC_intClock_Enable()                         MotorCurrentADC_intClock_Start()
#define MotorCurrentADC_intClock_Disable()                        MotorCurrentADC_intClock_Stop()
#define MotorCurrentADC_intClock_SetDividerRegister(clkDivider, reset)  \
    MotorCurrentADC_intClock_SetFractionalDividerRegister((clkDivider), 0u)
#define MotorCurrentADC_intClock_SetDivider(clkDivider)           MotorCurrentADC_intClock_SetDividerRegister((clkDivider), 1u)
#define MotorCurrentADC_intClock_SetDividerValue(clkDivider)      MotorCurrentADC_intClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define MotorCurrentADC_intClock_DIV_ID     MotorCurrentADC_intClock__DIV_ID

#define MotorCurrentADC_intClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define MotorCurrentADC_intClock_CTRL_REG   (*(reg32 *)MotorCurrentADC_intClock__CTRL_REGISTER)
#define MotorCurrentADC_intClock_DIV_REG    (*(reg32 *)MotorCurrentADC_intClock__DIV_REGISTER)

#define MotorCurrentADC_intClock_CMD_DIV_SHIFT          (0u)
#define MotorCurrentADC_intClock_CMD_PA_DIV_SHIFT       (8u)
#define MotorCurrentADC_intClock_CMD_DISABLE_SHIFT      (30u)
#define MotorCurrentADC_intClock_CMD_ENABLE_SHIFT       (31u)

#define MotorCurrentADC_intClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << MotorCurrentADC_intClock_CMD_DISABLE_SHIFT))
#define MotorCurrentADC_intClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << MotorCurrentADC_intClock_CMD_ENABLE_SHIFT))

#define MotorCurrentADC_intClock_DIV_FRAC_MASK  (0x000000F8u)
#define MotorCurrentADC_intClock_DIV_FRAC_SHIFT (3u)
#define MotorCurrentADC_intClock_DIV_INT_MASK   (0xFFFFFF00u)
#define MotorCurrentADC_intClock_DIV_INT_SHIFT  (8u)

#else 

#define MotorCurrentADC_intClock_DIV_REG        (*(reg32 *)MotorCurrentADC_intClock__REGISTER)
#define MotorCurrentADC_intClock_ENABLE_REG     MotorCurrentADC_intClock_DIV_REG
#define MotorCurrentADC_intClock_DIV_FRAC_MASK  MotorCurrentADC_intClock__FRAC_MASK
#define MotorCurrentADC_intClock_DIV_FRAC_SHIFT (16u)
#define MotorCurrentADC_intClock_DIV_INT_MASK   MotorCurrentADC_intClock__DIVIDER_MASK
#define MotorCurrentADC_intClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_MotorCurrentADC_intClock_H) */

/* [] END OF FILE */
