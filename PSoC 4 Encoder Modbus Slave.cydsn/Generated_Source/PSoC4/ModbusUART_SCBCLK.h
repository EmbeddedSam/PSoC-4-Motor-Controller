/*******************************************************************************
* File Name: ModbusUART_SCBCLK.h
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

#if !defined(CY_CLOCK_ModbusUART_SCBCLK_H)
#define CY_CLOCK_ModbusUART_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void ModbusUART_SCBCLK_StartEx(uint32 alignClkDiv);
#define ModbusUART_SCBCLK_Start() \
    ModbusUART_SCBCLK_StartEx(ModbusUART_SCBCLK__PA_DIV_ID)

#else

void ModbusUART_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void ModbusUART_SCBCLK_Stop(void);

void ModbusUART_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 ModbusUART_SCBCLK_GetDividerRegister(void);
uint8  ModbusUART_SCBCLK_GetFractionalDividerRegister(void);

#define ModbusUART_SCBCLK_Enable()                         ModbusUART_SCBCLK_Start()
#define ModbusUART_SCBCLK_Disable()                        ModbusUART_SCBCLK_Stop()
#define ModbusUART_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    ModbusUART_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define ModbusUART_SCBCLK_SetDivider(clkDivider)           ModbusUART_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define ModbusUART_SCBCLK_SetDividerValue(clkDivider)      ModbusUART_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define ModbusUART_SCBCLK_DIV_ID     ModbusUART_SCBCLK__DIV_ID

#define ModbusUART_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define ModbusUART_SCBCLK_CTRL_REG   (*(reg32 *)ModbusUART_SCBCLK__CTRL_REGISTER)
#define ModbusUART_SCBCLK_DIV_REG    (*(reg32 *)ModbusUART_SCBCLK__DIV_REGISTER)

#define ModbusUART_SCBCLK_CMD_DIV_SHIFT          (0u)
#define ModbusUART_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define ModbusUART_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define ModbusUART_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define ModbusUART_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << ModbusUART_SCBCLK_CMD_DISABLE_SHIFT))
#define ModbusUART_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << ModbusUART_SCBCLK_CMD_ENABLE_SHIFT))

#define ModbusUART_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define ModbusUART_SCBCLK_DIV_FRAC_SHIFT (3u)
#define ModbusUART_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define ModbusUART_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define ModbusUART_SCBCLK_DIV_REG        (*(reg32 *)ModbusUART_SCBCLK__REGISTER)
#define ModbusUART_SCBCLK_ENABLE_REG     ModbusUART_SCBCLK_DIV_REG
#define ModbusUART_SCBCLK_DIV_FRAC_MASK  ModbusUART_SCBCLK__FRAC_MASK
#define ModbusUART_SCBCLK_DIV_FRAC_SHIFT (16u)
#define ModbusUART_SCBCLK_DIV_INT_MASK   ModbusUART_SCBCLK__DIVIDER_MASK
#define ModbusUART_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_ModbusUART_SCBCLK_H) */

/* [] END OF FILE */
