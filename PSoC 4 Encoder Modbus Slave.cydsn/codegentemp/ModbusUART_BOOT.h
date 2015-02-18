/*******************************************************************************
* File Name: ModbusUART_BOOT.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the bootloader
*  communication interface of SCB component.
*
* Note:
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_ModbusUART_H)
#define CY_SCB_BOOT_ModbusUART_H

#include "ModbusUART_PVT.h"

#if (ModbusUART_SCB_MODE_I2C_INC)
    #include "ModbusUART_I2C.h"
#endif /* (ModbusUART_SCB_MODE_I2C_INC) */

#if (ModbusUART_SCB_MODE_EZI2C_INC)
    #include "ModbusUART_EZI2C.h"
#endif /* (ModbusUART_SCB_MODE_EZI2C_INC) */

#if (ModbusUART_SCB_MODE_SPI_INC || ModbusUART_SCB_MODE_UART_INC)
    #include "ModbusUART_SPI_UART.h"
#endif /* (ModbusUART_SCB_MODE_SPI_INC || ModbusUART_SCB_MODE_UART_INC) */


/***************************************
*        Function Prototypes
***************************************/

/* Bootloader communication interface enable */
#define ModbusUART_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusUART) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

#if (ModbusUART_SCB_MODE_I2C_INC)

    #define ModbusUART_I2C_BTLDR_COMM_ENABLED     (ModbusUART_BTLDR_COMM_ENABLED && \
                                                            (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             ModbusUART_I2C_SLAVE_CONST))

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_I2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void ModbusUART_I2CCyBtldrCommStart(void);
    void ModbusUART_I2CCyBtldrCommStop (void);
    void ModbusUART_I2CCyBtldrCommReset(void);
    cystatus ModbusUART_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ModbusUART_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Size of Read/Write buffers for I2C bootloader  */
    #define ModbusUART_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
    #define ModbusUART_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)
    #define ModbusUART_I2C_MIN_UINT16(a, b)           ( ((uint16)(a) < (uint16) (b)) ? \
                                                                    ((uint32) (a)) : ((uint32) (b)) )
    #define ModbusUART_WAIT_1_MS                      (1u)
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_I2C_BTLDR_COMM_ENABLED) */

#endif /* (ModbusUART_SCB_MODE_I2C_INC) */


#if (ModbusUART_SCB_MODE_EZI2C_INC)

    /* Provide EMPTY bootloader communication functions. EZI2C is NOT supported yet */
    #define ModbusUART_EZI2C_BTLDR_COMM_ENABLED   (ModbusUART_BTLDR_COMM_ENABLED && \
                                                         ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void ModbusUART_EzI2CCyBtldrCommStart(void);
    void ModbusUART_EzI2CCyBtldrCommStop (void);
    void ModbusUART_EzI2CCyBtldrCommReset(void);
    cystatus ModbusUART_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ModbusUART_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_EZI2C_BTLDR_COMM_ENABLED) */

#endif /* (ModbusUART_SCB_MODE_EZI2C_INC) */

#if (ModbusUART_SCB_MODE_SPI_INC || ModbusUART_SCB_MODE_UART_INC)
    /* Provide EMPTY bootloader communication functions. SPI and UART is NOT supported yet */
    #define ModbusUART_SPI_BTLDR_COMM_ENABLED     (ModbusUART_BTLDR_COMM_ENABLED && \
                                                        ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)

    #define ModbusUART_UART_BTLDR_COMM_ENABLED    (ModbusUART_BTLDR_COMM_ENABLED && \
                                                        ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void ModbusUART_SpiCyBtldrCommStart(void);
    void ModbusUART_SpiCyBtldrCommStop (void);
    void ModbusUART_SpiCyBtldrCommReset(void);
    cystatus ModbusUART_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ModbusUART_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void ModbusUART_UartCyBtldrCommStart(void);
    void ModbusUART_UartCyBtldrCommStop (void);
    void ModbusUART_UartCyBtldrCommReset(void);
    cystatus ModbusUART_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ModbusUART_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_UART_BTLDR_COMM_ENABLED) */

#endif /* (ModbusUART_SCB_MODE_SPI_INC || ModbusUART_SCB_MODE_UART_INC) */

#if !defined (ModbusUART_I2C_BTLDR_COMM_ENABLED)
    #define ModbusUART_I2C_BTLDR_COMM_ENABLED     (0u)
#endif /* (ModbusUART_I2C_BTLDR_COMM_ENABLED) */

#if !defined (ModbusUART_EZI2C_BTLDR_COMM_ENABLED)
    #define ModbusUART_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (ModbusUART_EZI2C_BTLDR_COMM_ENABLED) */

#if !defined (ModbusUART_SPI_BTLDR_COMM_ENABLED)
    #define ModbusUART_SPI_BTLDR_COMM_ENABLED     (0u)
#endif /* (ModbusUART_SPI_BTLDR_COMM_ENABLED) */

#if !defined (ModbusUART_UART_BTLDR_COMM_ENABLED)
    #define ModbusUART_UART_BTLDR_COMM_ENABLED    (0u)
#endif /* (ModbusUART_UART_BTLDR_COMM_ENABLED) */

/* Bootloader enabled condition for each mode */
#define ModbusUART_BTLDR_COMM_MODE_ENABLED    (ModbusUART_I2C_BTLDR_COMM_ENABLED   || \
                                                     ModbusUART_EZI2C_BTLDR_COMM_ENABLED || \
                                                     ModbusUART_SPI_BTLDR_COMM_ENABLED   || \
                                                     ModbusUART_UART_BTLDR_COMM_ENABLED)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_BTLDR_COMM_ENABLED)
    #if (ModbusUART_BTLDR_COMM_MODE_ENABLED)
        /* Bootloader physical layer functions */
        void ModbusUART_CyBtldrCommStart(void);
        void ModbusUART_CyBtldrCommStop (void);
        void ModbusUART_CyBtldrCommReset(void);
        cystatus ModbusUART_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus ModbusUART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (ModbusUART_BTLDR_COMM_MODE_ENABLED) */

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusUART)
        #define CyBtldrCommStart    ModbusUART_CyBtldrCommStart
        #define CyBtldrCommStop     ModbusUART_CyBtldrCommStop
        #define CyBtldrCommReset    ModbusUART_CyBtldrCommReset
        #define CyBtldrCommWrite    ModbusUART_CyBtldrCommWrite
        #define CyBtldrCommRead     ModbusUART_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusUART) */
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_BTLDR_COMM_ENABLED) */

#endif /* (CY_SCB_BOOT_ModbusUART_H) */

/* [] END OF FILE */
