/*******************************************************************************
* File Name: ModbusUART.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the SCB Component.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

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
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 ModbusUART_scbMode = ModbusUART_SCB_MODE_UNCONFIG;
    uint8 ModbusUART_scbEnableWake;
    uint8 ModbusUART_scbEnableIntr;

    /* I2C configuration variables */
    uint8 ModbusUART_mode;
    uint8 ModbusUART_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * ModbusUART_rxBuffer;
    uint8  ModbusUART_rxDataBits;
    uint32 ModbusUART_rxBufferSize;

    volatile uint8 * ModbusUART_txBuffer;
    uint8  ModbusUART_txDataBits;
    uint32 ModbusUART_txBufferSize;

    /* EZI2C configuration variables */
    uint8 ModbusUART_numberOfAddr;
    uint8 ModbusUART_subAddrSize;
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 ModbusUART_initVar = 0u;

#if !defined (CY_REMOVE_ModbusUART_CUSTOM_INTR_HANDLER)
    cyisraddress ModbusUART_customIntrHandler = NULL;
#endif /* !defined (CY_REMOVE_ModbusUART_CUSTOM_INTR_HANDLER) */


/***************************************
*    Private Function Prototypes
***************************************/

static void ModbusUART_ScbEnableIntr(void);
static void ModbusUART_ScbModeStop(void);


/*******************************************************************************
* Function Name: ModbusUART_Init
********************************************************************************
*
* Summary:
*  Initializes the SCB component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SCB_I2CInit, SCB_SpiInit, SCB_UartInit or SCB_EzI2CInit.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_Init(void)
{
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    if(ModbusUART_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        ModbusUART_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif(ModbusUART_SCB_MODE_I2C_CONST_CFG)
    ModbusUART_I2CInit();

#elif(ModbusUART_SCB_MODE_SPI_CONST_CFG)
    ModbusUART_SpiInit();

#elif(ModbusUART_SCB_MODE_UART_CONST_CFG)
    ModbusUART_UartInit();

#elif(ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
    ModbusUART_EzI2CInit();

#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_Enable
********************************************************************************
*
* Summary:
*  Enables the SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_Enable(void)
{
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if(!ModbusUART_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        ModbusUART_CTRL_REG |= ModbusUART_CTRL_ENABLED;

        ModbusUART_ScbEnableIntr();
    }
#else
    ModbusUART_CTRL_REG |= ModbusUART_CTRL_ENABLED;

    ModbusUART_ScbEnableIntr();
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZ I2C. Otherwise this function does not enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ModbusUART_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void ModbusUART_Start(void)
{
    if(0u == ModbusUART_initVar)
    {
        ModbusUART_Init();
        ModbusUART_initVar = 1u; /* Component was initialized */
    }

    ModbusUART_Enable();
}


/*******************************************************************************
* Function Name: ModbusUART_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component and its interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_Stop(void)
{
#if(ModbusUART_SCB_IRQ_INTERNAL)
    ModbusUART_DisableInt();
#endif /* (ModbusUART_SCB_IRQ_INTERNAL) */

    ModbusUART_CTRL_REG &= (uint32) ~ModbusUART_CTRL_ENABLED;  /* Disable scb IP */

#if(ModbusUART_SCB_IRQ_INTERNAL)
    ModbusUART_ClearPendingInt();
#endif /* (ModbusUART_SCB_IRQ_INTERNAL) */

    ModbusUART_ScbModeStop(); /* Calls scbMode specific Stop function */
}


/*******************************************************************************
* Function Name: ModbusUART_SetRxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the RX FIFO to generate RX level interrupt.
*         The range of valid level values is between 0 and RX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = ModbusUART_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~ModbusUART_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (ModbusUART_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    ModbusUART_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: ModbusUART_SetTxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has more entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the TX FIFO to generate TX level interrupt.
*         The range of valid level values is between 0 and TX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = ModbusUART_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~ModbusUART_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (ModbusUART_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    ModbusUART_TX_FIFO_CTRL_REG = txFifoCtrl;
}


/*******************************************************************************
* Function Name: ModbusUART_SetCustomInterruptHandler
********************************************************************************
*
* Summary:
*  Registers a function to be called by the internal interrupt handler.
*  First the function that is registered is called, then the internal interrupt
*  handler performs any operation such as software buffer management functions
*  before the interrupt returns.  It is the user's responsibility not to break
*  the software buffer operations. Only one custom handler is supported, which
*  is the function provided by the most recent call.
*  At the initialization time no custom handler is registered.
*
* Parameters:
*  func: Pointer to the function to register.
*        The value NULL indicates to remove the current custom interrupt
*        handler.
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_SetCustomInterruptHandler(cyisraddress func)
{
#if !defined (CY_REMOVE_ModbusUART_CUSTOM_INTR_HANDLER)
    ModbusUART_customIntrHandler = func; /* Register interrupt handler */
#else
    if(NULL != func)
    {
        /* Suppress compiler warning */
    }
#endif /* !defined (CY_REMOVE_ModbusUART_CUSTOM_INTR_HANDLER) */
}


/*******************************************************************************
* Function Name: ModbusUART_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables an interrupt for a specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void ModbusUART_ScbEnableIntr(void)
{
#if(ModbusUART_SCB_IRQ_INTERNAL)
    #if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Enable interrupt in NVIC */
        if(0u != ModbusUART_scbEnableIntr)
        {
            ModbusUART_EnableInt();
        }
    #else
        ModbusUART_EnableInt();

    #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (ModbusUART_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: ModbusUART_ScbModeStop
********************************************************************************
*
* Summary:
*  Calls the Stop function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void ModbusUART_ScbModeStop(void)
{
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    if(ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
    {
        ModbusUART_I2CStop();
    }
    else if (ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        ModbusUART_EzI2CStop();
    }
#if (!ModbusUART_CY_SCBIP_V1)
    else if (ModbusUART_SCB_MODE_UART_RUNTM_CFG)
    {
        ModbusUART_UartStop();
    }
#endif /* (!ModbusUART_CY_SCBIP_V1) */
    else
    {
        /* Do nothing for other modes */
    }
#elif(ModbusUART_SCB_MODE_I2C_CONST_CFG)
    ModbusUART_I2CStop();

#elif(ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
    ModbusUART_EzI2CStop();

#elif(ModbusUART_SCB_MODE_UART_CONST_CFG)
    ModbusUART_UartStop();

#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: ModbusUART_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusUART_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [ModbusUART_SCB_PINS_NUMBER];
        uint32 pinsDm   [ModbusUART_SCB_PINS_NUMBER];

    #if (!ModbusUART_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!ModbusUART_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for(i = 0u; i < ModbusUART_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = ModbusUART_HSIOM_DEF_SEL;
            pinsDm[i]    = ModbusUART_PIN_DM_ALG_HIZ;
        }

        if((ModbusUART_SCB_MODE_I2C   == mode) ||
           (ModbusUART_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[ModbusUART_MOSI_SCL_RX_PIN_INDEX] = ModbusUART_HSIOM_I2C_SEL;
            hsiomSel[ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_HSIOM_I2C_SEL;

            pinsDm[ModbusUART_MOSI_SCL_RX_PIN_INDEX] = ModbusUART_PIN_DM_OD_LO;
            pinsDm[ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_PIN_DM_OD_LO;
        }
    #if (!ModbusUART_CY_SCBIP_V1)
        else if(ModbusUART_SCB_MODE_SPI == mode)
        {
            hsiomSel[ModbusUART_MOSI_SCL_RX_PIN_INDEX] = ModbusUART_HSIOM_SPI_SEL;
            hsiomSel[ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_HSIOM_SPI_SEL;
            hsiomSel[ModbusUART_SCLK_PIN_INDEX]        = ModbusUART_HSIOM_SPI_SEL;

            if(ModbusUART_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[ModbusUART_MOSI_SCL_RX_PIN_INDEX] = ModbusUART_PIN_DM_DIG_HIZ;
                pinsDm[ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                pinsDm[ModbusUART_SCLK_PIN_INDEX]        = ModbusUART_PIN_DM_DIG_HIZ;

            #if(ModbusUART_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[ModbusUART_SS0_PIN_INDEX] = ModbusUART_HSIOM_SPI_SEL;
                pinsDm  [ModbusUART_SS0_PIN_INDEX] = ModbusUART_PIN_DM_DIG_HIZ;
            #endif /* (ModbusUART_SS1_PIN) */

            #if(ModbusUART_MISO_SDA_TX_PIN)
                /* Disable input buffer */
                 pinsInBuf |= ModbusUART_MISO_SDA_TX_PIN_MASK;
            #endif /* (ModbusUART_MISO_SDA_TX_PIN_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[ModbusUART_MOSI_SCL_RX_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                pinsDm[ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_PIN_DM_DIG_HIZ;
                pinsDm[ModbusUART_SCLK_PIN_INDEX]        = ModbusUART_PIN_DM_STRONG;

            #if(ModbusUART_SS0_PIN)
                hsiomSel [ModbusUART_SS0_PIN_INDEX] = ModbusUART_HSIOM_SPI_SEL;
                pinsDm   [ModbusUART_SS0_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                pinsInBuf                                |= ModbusUART_SS0_PIN_MASK;
            #endif /* (ModbusUART_SS0_PIN) */

            #if(ModbusUART_SS1_PIN)
                hsiomSel [ModbusUART_SS1_PIN_INDEX] = ModbusUART_HSIOM_SPI_SEL;
                pinsDm   [ModbusUART_SS1_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                pinsInBuf                                |= ModbusUART_SS1_PIN_MASK;
            #endif /* (ModbusUART_SS1_PIN) */

            #if(ModbusUART_SS2_PIN)
                hsiomSel [ModbusUART_SS2_PIN_INDEX] = ModbusUART_HSIOM_SPI_SEL;
                pinsDm   [ModbusUART_SS2_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                pinsInBuf                                |= ModbusUART_SS2_PIN_MASK;
            #endif /* (ModbusUART_SS2_PIN) */

            #if(ModbusUART_SS3_PIN)
                hsiomSel [ModbusUART_SS3_PIN_INDEX] = ModbusUART_HSIOM_SPI_SEL;
                pinsDm   [ModbusUART_SS3_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                pinsInBuf                                |= ModbusUART_SS3_PIN_MASK;
            #endif /* (ModbusUART_SS2_PIN) */

                /* Disable input buffers */
            #if(ModbusUART_MOSI_SCL_RX_PIN)
                pinsInBuf |= ModbusUART_MOSI_SCL_RX_PIN_MASK;
            #endif /* (ModbusUART_MOSI_SCL_RX_PIN) */

             #if(ModbusUART_MOSI_SCL_RX_WAKE_PIN)
                pinsInBuf |= ModbusUART_MOSI_SCL_RX_WAKE_PIN_MASK;
            #endif /* (ModbusUART_MOSI_SCL_RX_WAKE_PIN) */

            #if(ModbusUART_SCLK_PIN)
                pinsInBuf |= ModbusUART_SCLK_PIN_MASK;
            #endif /* (ModbusUART_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if(ModbusUART_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_HSIOM_UART_SEL;
                pinsDm  [ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if(0u != (ModbusUART_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[ModbusUART_MOSI_SCL_RX_PIN_INDEX] = ModbusUART_HSIOM_UART_SEL;
                    pinsDm  [ModbusUART_MOSI_SCL_RX_PIN_INDEX] = ModbusUART_PIN_DM_DIG_HIZ;
                }

                if(0u != (ModbusUART_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_HSIOM_UART_SEL;
                    pinsDm  [ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;

                #if(ModbusUART_MISO_SDA_TX_PIN)
                     pinsInBuf |= ModbusUART_MISO_SDA_TX_PIN_MASK;
                #endif /* (ModbusUART_MISO_SDA_TX_PIN_PIN) */
                }

            #if !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
                if(ModbusUART_UART_MODE_STD == subMode)
                {
                    if(0u != (ModbusUART_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[ModbusUART_SCLK_PIN_INDEX] = ModbusUART_HSIOM_UART_SEL;
                        pinsDm  [ModbusUART_SCLK_PIN_INDEX] = ModbusUART_PIN_DM_DIG_HIZ;
                    }

                    if(0u != (ModbusUART_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[ModbusUART_SS0_PIN_INDEX] = ModbusUART_HSIOM_UART_SEL;
                        pinsDm  [ModbusUART_SS0_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;

                    #if(ModbusUART_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= ModbusUART_SS0_PIN_MASK;
                    #endif /* (ModbusUART_SS0_PIN) */
                    }
                }
            #endif /* !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */
            }
        }
    #endif /* (!ModbusUART_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if(ModbusUART_MOSI_SCL_RX_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_MOSI_SCL_RX_HSIOM_REG,
                                       ModbusUART_MOSI_SCL_RX_HSIOM_MASK,
                                       ModbusUART_MOSI_SCL_RX_HSIOM_POS,
                                       hsiomSel[ModbusUART_MOSI_SCL_RX_PIN_INDEX]);

        ModbusUART_spi_mosi_i2c_scl_uart_rx_SetDriveMode((uint8) pinsDm[ModbusUART_MOSI_SCL_RX_PIN_INDEX]);

    #if (!ModbusUART_CY_SCBIP_V1)
        ModbusUART_SET_INP_DIS(ModbusUART_spi_mosi_i2c_scl_uart_rx_INP_DIS,
                                     ModbusUART_spi_mosi_i2c_scl_uart_rx_MASK,
                                     (0u != (pinsInBuf & ModbusUART_MOSI_SCL_RX_PIN_MASK)));
    #endif /* (!ModbusUART_CY_SCBIP_V1) */
    #endif /* (ModbusUART_MOSI_SCL_RX_PIN) */

    #if(ModbusUART_MOSI_SCL_RX_WAKE_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_REG,
                                       ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_MASK,
                                       ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_POS,
                                       hsiomSel[ModbusUART_MOSI_SCL_RX_WAKE_PIN_INDEX]);

        ModbusUART_spi_mosi_i2c_scl_uart_rx_wake_SetDriveMode((uint8)
                                                               pinsDm[ModbusUART_MOSI_SCL_RX_WAKE_PIN_INDEX]);

        ModbusUART_SET_INP_DIS(ModbusUART_spi_mosi_i2c_scl_uart_rx_wake_INP_DIS,
                                     ModbusUART_spi_mosi_i2c_scl_uart_rx_wake_MASK,
                                     (0u != (pinsInBuf & ModbusUART_MOSI_SCL_RX_WAKE_PIN_MASK)));

         /* Set interrupt on falling edge */
        ModbusUART_SET_INCFG_TYPE(ModbusUART_MOSI_SCL_RX_WAKE_INTCFG_REG,
                                        ModbusUART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK,
                                        ModbusUART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS,
                                        ModbusUART_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (ModbusUART_MOSI_SCL_RX_WAKE_PIN) */

    #if(ModbusUART_MISO_SDA_TX_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_MISO_SDA_TX_HSIOM_REG,
                                       ModbusUART_MISO_SDA_TX_HSIOM_MASK,
                                       ModbusUART_MISO_SDA_TX_HSIOM_POS,
                                       hsiomSel[ModbusUART_MISO_SDA_TX_PIN_INDEX]);

        ModbusUART_spi_miso_i2c_sda_uart_tx_SetDriveMode((uint8) pinsDm[ModbusUART_MISO_SDA_TX_PIN_INDEX]);

    #if (!ModbusUART_CY_SCBIP_V1)
        ModbusUART_SET_INP_DIS(ModbusUART_spi_miso_i2c_sda_uart_tx_INP_DIS,
                                     ModbusUART_spi_miso_i2c_sda_uart_tx_MASK,
                                    (0u != (pinsInBuf & ModbusUART_MISO_SDA_TX_PIN_MASK)));
    #endif /* (!ModbusUART_CY_SCBIP_V1) */
    #endif /* (ModbusUART_MOSI_SCL_RX_PIN) */

    #if(ModbusUART_SCLK_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_SCLK_HSIOM_REG, ModbusUART_SCLK_HSIOM_MASK,
                                       ModbusUART_SCLK_HSIOM_POS, hsiomSel[ModbusUART_SCLK_PIN_INDEX]);

        ModbusUART_spi_sclk_SetDriveMode((uint8) pinsDm[ModbusUART_SCLK_PIN_INDEX]);

        ModbusUART_SET_INP_DIS(ModbusUART_spi_sclk_INP_DIS,
                                     ModbusUART_spi_sclk_MASK,
                                     (0u != (pinsInBuf & ModbusUART_SCLK_PIN_MASK)));
    #endif /* (ModbusUART_SCLK_PIN) */

    #if(ModbusUART_SS0_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_SS0_HSIOM_REG, ModbusUART_SS0_HSIOM_MASK,
                                       ModbusUART_SS0_HSIOM_POS, hsiomSel[ModbusUART_SS0_PIN_INDEX]);

        ModbusUART_spi_ss0_SetDriveMode((uint8) pinsDm[ModbusUART_SS0_PIN_INDEX]);

        ModbusUART_SET_INP_DIS(ModbusUART_spi_ss0_INP_DIS,
                                     ModbusUART_spi_ss0_MASK,
                                     (0u != (pinsInBuf & ModbusUART_SS0_PIN_MASK)));
    #endif /* (ModbusUART_SS1_PIN) */

    #if(ModbusUART_SS1_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_SS1_HSIOM_REG, ModbusUART_SS1_HSIOM_MASK,
                                       ModbusUART_SS1_HSIOM_POS, hsiomSel[ModbusUART_SS1_PIN_INDEX]);

        ModbusUART_spi_ss1_SetDriveMode((uint8) pinsDm[ModbusUART_SS1_PIN_INDEX]);

        ModbusUART_SET_INP_DIS(ModbusUART_spi_ss1_INP_DIS,
                                     ModbusUART_spi_ss1_MASK,
                                     (0u != (pinsInBuf & ModbusUART_SS1_PIN_MASK)));
    #endif /* (ModbusUART_SS1_PIN) */

    #if(ModbusUART_SS2_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_SS2_HSIOM_REG, ModbusUART_SS2_HSIOM_MASK,
                                       ModbusUART_SS2_HSIOM_POS, hsiomSel[ModbusUART_SS2_PIN_INDEX]);

        ModbusUART_spi_ss2_SetDriveMode((uint8) pinsDm[ModbusUART_SS2_PIN_INDEX]);

        ModbusUART_SET_INP_DIS(ModbusUART_spi_ss2_INP_DIS,
                                     ModbusUART_spi_ss2_MASK,
                                     (0u != (pinsInBuf & ModbusUART_SS2_PIN_MASK)));
    #endif /* (ModbusUART_SS2_PIN) */

    #if(ModbusUART_SS3_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_SS3_HSIOM_REG,  ModbusUART_SS3_HSIOM_MASK,
                                       ModbusUART_SS3_HSIOM_POS, hsiomSel[ModbusUART_SS3_PIN_INDEX]);

        ModbusUART_spi_ss3_SetDriveMode((uint8) pinsDm[ModbusUART_SS3_PIN_INDEX]);

        ModbusUART_SET_INP_DIS(ModbusUART_spi_ss3_INP_DIS,
                                     ModbusUART_spi_ss3_MASK,
                                     (0u != (pinsInBuf & ModbusUART_SS3_PIN_MASK)));
    #endif /* (ModbusUART_SS3_PIN) */
    }

#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: ModbusUART_I2CSlaveNackGeneration
    ********************************************************************************
    *
    * Summary:
    *  Sets command to generate NACK to the address or data.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusUART_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (ModbusUART_CTRL_REG & ModbusUART_CTRL_EC_AM_MODE)) &&
            (0u == (ModbusUART_I2C_CTRL_REG & ModbusUART_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            ModbusUART_CTRL_REG &= ~ModbusUART_CTRL_EC_AM_MODE;
            ModbusUART_CTRL_REG |=  ModbusUART_CTRL_EC_AM_MODE;
        }

        ModbusUART_I2C_SLAVE_CMD_REG = ModbusUART_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */


/* [] END OF FILE */
