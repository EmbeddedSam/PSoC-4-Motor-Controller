/*******************************************************************************
* File Name: ModbusUART_BOOT.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the bootloader
*  communication support in the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ModbusUART_BOOT.h"


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_BTLDR_COMM_MODE_ENABLED)

/*******************************************************************************
* Function Name: ModbusUART_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStart function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_CyBtldrCommStart(void)
{
    #if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
        {
            ModbusUART_I2CCyBtldrCommStart();
        }
        else if(ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
        {
            ModbusUART_SpiCyBtldrCommStart();
        }
        else if(ModbusUART_SCB_MODE_UART_RUNTM_CFG)
        {
            ModbusUART_UartCyBtldrCommStart();
        }
        else if(ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
             ModbusUART_EzI2CCyBtldrCommStart();
        }
        else
        {
            /* Unknown mode */
        }
    #elif(ModbusUART_SCB_MODE_I2C_CONST_CFG)
        ModbusUART_I2CCyBtldrCommStart();

    #elif(ModbusUART_SCB_MODE_SPI_CONST_CFG)
        ModbusUART_SpiCyBtldrCommStart();

    #elif(ModbusUART_SCB_MODE_UART_CONST_CFG)
        ModbusUART_UartCyBtldrCommStart();

    #elif(ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
        ModbusUART_EzI2CCyBtldrCommStart();

    #else
        /* Unknown mode */

    #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStop function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_CyBtldrCommStop(void)
{
    #if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
        {
            ModbusUART_I2CCyBtldrCommStop();
        }
        else if(ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
        {
            ModbusUART_SpiCyBtldrCommStop();
        }
        else if(ModbusUART_SCB_MODE_UART_RUNTM_CFG)
        {
            ModbusUART_UartCyBtldrCommStop();
        }
        else if(ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            ModbusUART_EzI2CCyBtldrCommStop();
        }
        else
        {
            /* Unknown mode */
        }
    #elif(ModbusUART_SCB_MODE_I2C_CONST_CFG)
        ModbusUART_I2CCyBtldrCommStop();

    #elif(ModbusUART_SCB_MODE_SPI_CONST_CFG)
        ModbusUART_SpiCyBtldrCommStop();

    #elif(ModbusUART_SCB_MODE_UART_CONST_CFG)
        ModbusUART_UartCyBtldrCommStop();

    #elif(ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
        ModbusUART_EzI2CCyBtldrCommStop();

    #else
        /* Unknown mode */

    #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommReset function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_CyBtldrCommReset(void)
{
    #if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
        {
            ModbusUART_I2CCyBtldrCommReset();
        }
        else if(ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
        {
            ModbusUART_SpiCyBtldrCommReset();
        }
        else if(ModbusUART_SCB_MODE_UART_RUNTM_CFG)
        {
            ModbusUART_UartCyBtldrCommReset();
        }
        else if(ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            ModbusUART_EzI2CCyBtldrCommReset();
        }
        else
        {
            /* Unknown mode */
        }
    #elif(ModbusUART_SCB_MODE_I2C_CONST_CFG)
        ModbusUART_I2CCyBtldrCommReset();

    #elif(ModbusUART_SCB_MODE_SPI_CONST_CFG)
        ModbusUART_SpiCyBtldrCommReset();

    #elif(ModbusUART_SCB_MODE_UART_CONST_CFG)
        ModbusUART_UartCyBtldrCommReset();

    #elif(ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
        ModbusUART_EzI2CCyBtldrCommReset();

    #else
        /* Unknown mode */

    #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommRead function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus ModbusUART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = ModbusUART_I2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = ModbusUART_SpiCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(ModbusUART_SCB_MODE_UART_RUNTM_CFG)
        {
            status = ModbusUART_UartCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = ModbusUART_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }

    #elif(ModbusUART_SCB_MODE_I2C_CONST_CFG)
        status = ModbusUART_I2CCyBtldrCommRead(pData, size, count, timeOut);

    #elif(ModbusUART_SCB_MODE_SPI_CONST_CFG)
        status = ModbusUART_SpiCyBtldrCommRead(pData, size, count, timeOut);

    #elif(ModbusUART_SCB_MODE_UART_CONST_CFG)
        status = ModbusUART_UartCyBtldrCommRead(pData, size, count, timeOut);

    #elif(ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
        status = ModbusUART_EzI2CCyBtldrCommRead(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}


/*******************************************************************************
* Function Name: ModbusUART_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommWrite  function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus ModbusUART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = ModbusUART_I2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = ModbusUART_SpiCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(ModbusUART_SCB_MODE_UART_RUNTM_CFG)
        {
            status = ModbusUART_UartCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = ModbusUART_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode */
        }
    #elif(ModbusUART_SCB_MODE_I2C_CONST_CFG)
        status = ModbusUART_I2CCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(ModbusUART_SCB_MODE_SPI_CONST_CFG)
        status = ModbusUART_SpiCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(ModbusUART_SCB_MODE_UART_CONST_CFG)
        status = ModbusUART_UartCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
        status = ModbusUART_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode */

    #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */
