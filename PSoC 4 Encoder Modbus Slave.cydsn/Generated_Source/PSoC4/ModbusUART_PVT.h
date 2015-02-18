/*******************************************************************************
* File Name: .h
* Version 2.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_ModbusUART_H)
#define CY_SCB_PVT_ModbusUART_H

#include "ModbusUART.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define ModbusUART_SetI2CExtClkInterruptMode(interruptMask) ModbusUART_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define ModbusUART_ClearI2CExtClkInterruptSource(interruptMask) ModbusUART_CLEAR_INTR_I2C_EC(interruptMask)
#define ModbusUART_GetI2CExtClkInterruptSource()                (ModbusUART_INTR_I2C_EC_REG)
#define ModbusUART_GetI2CExtClkInterruptMode()                  (ModbusUART_INTR_I2C_EC_MASK_REG)
#define ModbusUART_GetI2CExtClkInterruptSourceMasked()          (ModbusUART_INTR_I2C_EC_MASKED_REG)

#if (!ModbusUART_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define ModbusUART_SetSpiExtClkInterruptMode(interruptMask) \
                                                                ModbusUART_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define ModbusUART_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                ModbusUART_CLEAR_INTR_SPI_EC(interruptMask)
    #define ModbusUART_GetExtSpiClkInterruptSource()                 (ModbusUART_INTR_SPI_EC_REG)
    #define ModbusUART_GetExtSpiClkInterruptMode()                   (ModbusUART_INTR_SPI_EC_MASK_REG)
    #define ModbusUART_GetExtSpiClkInterruptSourceMasked()           (ModbusUART_INTR_SPI_EC_MASKED_REG)
#endif /* (!ModbusUART_CY_SCBIP_V1) */

#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void ModbusUART_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if !defined (CY_REMOVE_ModbusUART_CUSTOM_INTR_HANDLER)
    extern cyisraddress ModbusUART_customIntrHandler;
#endif /* !defined (CY_REMOVE_ModbusUART_CUSTOM_INTR_HANDLER) */

extern ModbusUART_BACKUP_STRUCT ModbusUART_backup;

#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 ModbusUART_scbMode;
    extern uint8 ModbusUART_scbEnableWake;
    extern uint8 ModbusUART_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 ModbusUART_mode;
    extern uint8 ModbusUART_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * ModbusUART_rxBuffer;
    extern uint8   ModbusUART_rxDataBits;
    extern uint32  ModbusUART_rxBufferSize;

    extern volatile uint8 * ModbusUART_txBuffer;
    extern uint8   ModbusUART_txDataBits;
    extern uint32  ModbusUART_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 ModbusUART_numberOfAddr;
    extern uint8 ModbusUART_subAddrSize;
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define ModbusUART_SCB_MODE_I2C_RUNTM_CFG     (ModbusUART_SCB_MODE_I2C      == ModbusUART_scbMode)
    #define ModbusUART_SCB_MODE_SPI_RUNTM_CFG     (ModbusUART_SCB_MODE_SPI      == ModbusUART_scbMode)
    #define ModbusUART_SCB_MODE_UART_RUNTM_CFG    (ModbusUART_SCB_MODE_UART     == ModbusUART_scbMode)
    #define ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG   (ModbusUART_SCB_MODE_EZI2C    == ModbusUART_scbMode)
    #define ModbusUART_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (ModbusUART_SCB_MODE_UNCONFIG == ModbusUART_scbMode)

    /* Defines wakeup enable */
    #define ModbusUART_SCB_WAKE_ENABLE_CHECK       (0u != ModbusUART_scbEnableWake)
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!ModbusUART_CY_SCBIP_V1)
    #define ModbusUART_SCB_PINS_NUMBER    (7u)
#else
    #define ModbusUART_SCB_PINS_NUMBER    (2u)
#endif /* (!ModbusUART_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_ModbusUART_H) */


/* [] END OF FILE */
