/*******************************************************************************
* File Name: ModbusUART_PM.c
* Version 2.0
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ModbusUART.h"
#include "ModbusUART_PVT.h"

#if(ModbusUART_SCB_MODE_I2C_INC)
    #include "ModbusUART_I2C_PVT.h"
#endif /* (ModbusUART_SCB_MODE_I2C_INC) */

#if(ModbusUART_SCB_MODE_EZI2C_INC)
    #include "ModbusUART_EZI2C_PVT.h"
#endif /* (ModbusUART_SCB_MODE_EZI2C_INC) */

#if(ModbusUART_SCB_MODE_SPI_INC || ModbusUART_SCB_MODE_UART_INC)
    #include "ModbusUART_SPI_UART_PVT.h"
#endif /* (ModbusUART_SCB_MODE_SPI_INC || ModbusUART_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG || \
   (ModbusUART_SCB_MODE_I2C_CONST_CFG   && (!ModbusUART_I2C_WAKE_ENABLE_CONST))   || \
   (ModbusUART_SCB_MODE_EZI2C_CONST_CFG && (!ModbusUART_EZI2C_WAKE_ENABLE_CONST)) || \
   (ModbusUART_SCB_MODE_SPI_CONST_CFG   && (!ModbusUART_SPI_WAKE_ENABLE_CONST))   || \
   (ModbusUART_SCB_MODE_UART_CONST_CFG  && (!ModbusUART_UART_WAKE_ENABLE_CONST)))

    ModbusUART_BACKUP_STRUCT ModbusUART_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: ModbusUART_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component to enter Deep Sleep.
*  The "Enable wakeup from Sleep Mode" selection has an influence on
*  this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_Sleep(void)
{
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)

    if(ModbusUART_SCB_WAKE_ENABLE_CHECK)
    {
        if(ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
        {
            ModbusUART_I2CSaveConfig();
        }
        else if(ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            ModbusUART_EzI2CSaveConfig();
        }
    #if(!ModbusUART_CY_SCBIP_V1)
        else if(ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
        {
            ModbusUART_SpiSaveConfig();
        }
        else if(ModbusUART_SCB_MODE_UART_RUNTM_CFG)
        {
            ModbusUART_UartSaveConfig();
        }
    #endif /* (!ModbusUART_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        ModbusUART_backup.enableState = (uint8) ModbusUART_GET_CTRL_ENABLED;

        if(0u != ModbusUART_backup.enableState)
        {
            ModbusUART_Stop();
        }
    }

#else

    #if (ModbusUART_SCB_MODE_I2C_CONST_CFG && ModbusUART_I2C_WAKE_ENABLE_CONST)
        ModbusUART_I2CSaveConfig();

    #elif (ModbusUART_SCB_MODE_EZI2C_CONST_CFG && ModbusUART_EZI2C_WAKE_ENABLE_CONST)
        ModbusUART_EzI2CSaveConfig();

    #elif (ModbusUART_SCB_MODE_SPI_CONST_CFG && ModbusUART_SPI_WAKE_ENABLE_CONST)
        ModbusUART_SpiSaveConfig();

    #elif (ModbusUART_SCB_MODE_UART_CONST_CFG && ModbusUART_UART_WAKE_ENABLE_CONST)
        ModbusUART_UartSaveConfig();

    #else

        ModbusUART_backup.enableState = (uint8) ModbusUART_GET_CTRL_ENABLED;

        if(0u != ModbusUART_backup.enableState)
        {
            ModbusUART_Stop();
        }

    #endif /* defined (ModbusUART_SCB_MODE_I2C_CONST_CFG) && (ModbusUART_I2C_WAKE_ENABLE_CONST) */

#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_Wakeup
********************************************************************************
*
* Summary:
*  Prepares the component for the Active mode operation after exiting
*  Deep Sleep. The "Enable wakeup from Sleep Mode" option has an influence
*  on this function implementation.
*  This function should not be called after exiting Sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_Wakeup(void)
{
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)

    if(ModbusUART_SCB_WAKE_ENABLE_CHECK)
    {
        if(ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
        {
            ModbusUART_I2CRestoreConfig();
        }
        else if(ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            ModbusUART_EzI2CRestoreConfig();
        }
    #if(!ModbusUART_CY_SCBIP_V1)
        else if(ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
        {
            ModbusUART_SpiRestoreConfig();
        }
        else if(ModbusUART_SCB_MODE_UART_RUNTM_CFG)
        {
            ModbusUART_UartRestoreConfig();
        }
    #endif /* (!ModbusUART_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != ModbusUART_backup.enableState)
        {
            ModbusUART_Enable();
        }
    }

#else

    #if (ModbusUART_SCB_MODE_I2C_CONST_CFG  && ModbusUART_I2C_WAKE_ENABLE_CONST)
        ModbusUART_I2CRestoreConfig();

    #elif (ModbusUART_SCB_MODE_EZI2C_CONST_CFG && ModbusUART_EZI2C_WAKE_ENABLE_CONST)
        ModbusUART_EzI2CRestoreConfig();

    #elif (ModbusUART_SCB_MODE_SPI_CONST_CFG && ModbusUART_SPI_WAKE_ENABLE_CONST)
        ModbusUART_SpiRestoreConfig();

    #elif (ModbusUART_SCB_MODE_UART_CONST_CFG && ModbusUART_UART_WAKE_ENABLE_CONST)
        ModbusUART_UartRestoreConfig();

    #else

        if(0u != ModbusUART_backup.enableState)
        {
            ModbusUART_Enable();
        }

    #endif /* (ModbusUART_I2C_WAKE_ENABLE_CONST) */

#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
