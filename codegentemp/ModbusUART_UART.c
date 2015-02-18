/*******************************************************************************
* File Name: ModbusUART_UART.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
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
#include "ModbusUART_SPI_UART_PVT.h"


#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const ModbusUART_UART_INIT_STRUCT ModbusUART_configUart =
    {
        ModbusUART_UART_SUB_MODE,
        ModbusUART_UART_DIRECTION,
        ModbusUART_UART_DATA_BITS_NUM,
        ModbusUART_UART_PARITY_TYPE,
        ModbusUART_UART_STOP_BITS_NUM,
        ModbusUART_UART_OVS_FACTOR,
        ModbusUART_UART_IRDA_LOW_POWER,
        ModbusUART_UART_MEDIAN_FILTER_ENABLE,
        ModbusUART_UART_RETRY_ON_NACK,
        ModbusUART_UART_IRDA_POLARITY,
        ModbusUART_UART_DROP_ON_PARITY_ERR,
        ModbusUART_UART_DROP_ON_FRAME_ERR,
        ModbusUART_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        ModbusUART_UART_MP_MODE_ENABLE,
        ModbusUART_UART_MP_ACCEPT_ADDRESS,
        ModbusUART_UART_MP_RX_ADDRESS,
        ModbusUART_UART_MP_RX_ADDRESS_MASK,
        (uint32) ModbusUART_SCB_IRQ_INTERNAL,
        ModbusUART_UART_INTR_RX_MASK,
        ModbusUART_UART_RX_TRIGGER_LEVEL,
        ModbusUART_UART_INTR_TX_MASK,
        ModbusUART_UART_TX_TRIGGER_LEVEL,
        (uint8) ModbusUART_UART_BYTE_MODE_ENABLE,
        (uint8) ModbusUART_UART_CTS_ENABLE,
        (uint8) ModbusUART_UART_CTS_POLARITY,
        (uint8) ModbusUART_UART_RTS_POLARITY,
        (uint8) ModbusUART_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: ModbusUART_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusUART_UartInit(const ModbusUART_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (ModbusUART_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)         ? (ModbusUART_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */

            /* Configure pins */
            ModbusUART_SetPins(ModbusUART_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            ModbusUART_scbMode       = (uint8) ModbusUART_SCB_MODE_UART;
            ModbusUART_scbEnableWake = (uint8) config->enableWake;
            ModbusUART_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            ModbusUART_rxBuffer      =         config->rxBuffer;
            ModbusUART_rxDataBits    = (uint8) config->dataBits;
            ModbusUART_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            ModbusUART_txBuffer      =         config->txBuffer;
            ModbusUART_txDataBits    = (uint8) config->dataBits;
            ModbusUART_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(ModbusUART_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                ModbusUART_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (ModbusUART_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (ModbusUART_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                ModbusUART_CTRL_REG  = ModbusUART_GET_CTRL_OVS(config->oversample);
            }

            ModbusUART_CTRL_REG     |= ModbusUART_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             ModbusUART_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             ModbusUART_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            ModbusUART_UART_CTRL_REG = ModbusUART_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            ModbusUART_UART_RX_CTRL_REG = ModbusUART_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        ModbusUART_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        ModbusUART_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        ModbusUART_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        ModbusUART_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(ModbusUART_UART_PARITY_NONE != config->parity)
            {
               ModbusUART_UART_RX_CTRL_REG |= ModbusUART_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    ModbusUART_UART_RX_CTRL_PARITY_ENABLED;
            }

            ModbusUART_RX_CTRL_REG      = ModbusUART_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                ModbusUART_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                ModbusUART_GET_UART_RX_CTRL_ENABLED(config->direction);

            ModbusUART_RX_FIFO_CTRL_REG = ModbusUART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            ModbusUART_RX_MATCH_REG     = ModbusUART_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                ModbusUART_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            ModbusUART_UART_TX_CTRL_REG = ModbusUART_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                ModbusUART_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(ModbusUART_UART_PARITY_NONE != config->parity)
            {
               ModbusUART_UART_TX_CTRL_REG |= ModbusUART_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    ModbusUART_UART_TX_CTRL_PARITY_ENABLED;
            }

            ModbusUART_TX_CTRL_REG      = ModbusUART_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                ModbusUART_GET_UART_TX_CTRL_ENABLED(config->direction);

            ModbusUART_TX_FIFO_CTRL_REG = ModbusUART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
            ModbusUART_UART_FLOW_CTRL_REG = ModbusUART_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            ModbusUART_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            ModbusUART_GET_UART_FLOW_CTRL_RTS_POLARITY(config->rtsPolarity)   | \
                                            ModbusUART_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (ModbusUART_ISR_NUMBER);
            CyIntSetPriority(ModbusUART_ISR_NUMBER, ModbusUART_ISR_PRIORITY);
            (void) CyIntSetVector(ModbusUART_ISR_NUMBER, &ModbusUART_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(ModbusUART_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (ModbusUART_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(ModbusUART_RX_WAKE_ISR_NUMBER, ModbusUART_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(ModbusUART_RX_WAKE_ISR_NUMBER, &ModbusUART_UART_WAKEUP_ISR);
        #endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            ModbusUART_INTR_I2C_EC_MASK_REG = ModbusUART_NO_INTR_SOURCES;
            ModbusUART_INTR_SPI_EC_MASK_REG = ModbusUART_NO_INTR_SOURCES;
            ModbusUART_INTR_SLAVE_MASK_REG  = ModbusUART_NO_INTR_SOURCES;
            ModbusUART_INTR_MASTER_MASK_REG = ModbusUART_NO_INTR_SOURCES;
            ModbusUART_INTR_RX_MASK_REG     = config->rxInterruptMask;
            ModbusUART_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            ModbusUART_rxBufferHead     = 0u;
            ModbusUART_rxBufferTail     = 0u;
            ModbusUART_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            ModbusUART_txBufferHead = 0u;
            ModbusUART_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: ModbusUART_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusUART_UartInit(void)
    {
        /* Configure UART interface */
        ModbusUART_CTRL_REG = ModbusUART_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        ModbusUART_UART_CTRL_REG = ModbusUART_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        ModbusUART_UART_RX_CTRL_REG = ModbusUART_UART_DEFAULT_UART_RX_CTRL;
        ModbusUART_RX_CTRL_REG      = ModbusUART_UART_DEFAULT_RX_CTRL;
        ModbusUART_RX_FIFO_CTRL_REG = ModbusUART_UART_DEFAULT_RX_FIFO_CTRL;
        ModbusUART_RX_MATCH_REG     = ModbusUART_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        ModbusUART_UART_TX_CTRL_REG = ModbusUART_UART_DEFAULT_UART_TX_CTRL;
        ModbusUART_TX_CTRL_REG      = ModbusUART_UART_DEFAULT_TX_CTRL;
        ModbusUART_TX_FIFO_CTRL_REG = ModbusUART_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
        ModbusUART_UART_FLOW_CTRL_REG = ModbusUART_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(ModbusUART_SCB_IRQ_INTERNAL)
        CyIntDisable    (ModbusUART_ISR_NUMBER);
        CyIntSetPriority(ModbusUART_ISR_NUMBER, ModbusUART_ISR_PRIORITY);
        (void) CyIntSetVector(ModbusUART_ISR_NUMBER, &ModbusUART_SPI_UART_ISR);
    #endif /* (ModbusUART_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(ModbusUART_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (ModbusUART_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(ModbusUART_RX_WAKE_ISR_NUMBER, ModbusUART_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(ModbusUART_RX_WAKE_ISR_NUMBER, &ModbusUART_UART_WAKEUP_ISR);
    #endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        ModbusUART_INTR_I2C_EC_MASK_REG = ModbusUART_UART_DEFAULT_INTR_I2C_EC_MASK;
        ModbusUART_INTR_SPI_EC_MASK_REG = ModbusUART_UART_DEFAULT_INTR_SPI_EC_MASK;
        ModbusUART_INTR_SLAVE_MASK_REG  = ModbusUART_UART_DEFAULT_INTR_SLAVE_MASK;
        ModbusUART_INTR_MASTER_MASK_REG = ModbusUART_UART_DEFAULT_INTR_MASTER_MASK;
        ModbusUART_INTR_RX_MASK_REG     = ModbusUART_UART_DEFAULT_INTR_RX_MASK;
        ModbusUART_INTR_TX_MASK_REG     = ModbusUART_UART_DEFAULT_INTR_TX_MASK;

    #if(ModbusUART_INTERNAL_RX_SW_BUFFER_CONST)
        ModbusUART_rxBufferHead     = 0u;
        ModbusUART_rxBufferTail     = 0u;
        ModbusUART_rxBufferOverflow = 0u;
    #endif /* (ModbusUART_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(ModbusUART_INTERNAL_TX_SW_BUFFER_CONST)
        ModbusUART_txBufferHead = 0u;
        ModbusUART_txBufferTail = 0u;
    #endif /* (ModbusUART_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: ModbusUART_UartSetRxAddress
********************************************************************************
*
* Summary:
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
* Parameters:
*  address: Address for hardware address detection.
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = ModbusUART_RX_MATCH_REG;

    matchReg &= ((uint32) ~ModbusUART_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & ModbusUART_RX_MATCH_ADDR_MASK)); /* Set address  */

    ModbusUART_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: ModbusUART_UartSetRxAddressMask
********************************************************************************
*
* Summary:
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
* Parameters:
*  addressMask: Address mask.
*   0 - address bit does not care while comparison.
*   1 - address bit is significant while comparison.
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = ModbusUART_RX_MATCH_REG;

    matchReg &= ((uint32) ~ModbusUART_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << ModbusUART_RX_MATCH_MASK_POS));

    ModbusUART_RX_MATCH_REG = matchReg;
}


#if(ModbusUART_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: ModbusUART_UartGetChar
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *  This function is designed for ASCII characters and returns a char
    *  where 1 to 255 are valid characters and 0 indicates an error occurred or
    *  no data present.
    *  - The RX software buffer is disabled: returns the data element
    *    retrieved from the RX FIFO.
    *    Undefined data will be returned if the RX FIFO is empty.
    *  - The RX software buffer is enabled: returns the data element from
    *    the software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The next data element from the receive buffer.
    *  ASCII character values from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is enabled: The internal software buffer overflow
    *  does not treat as an error condition.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 ModbusUART_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if(0u != ModbusUART_SpiUartGetRxBufferSize())
        {
            rxData = ModbusUART_SpiUartReadRxData();
        }

        if(ModbusUART_CHECK_INTR_RX(ModbusUART_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            ModbusUART_ClearRxInterruptSource(ModbusUART_INTR_RX_ERR);
        }

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: ModbusUART_UartGetByte
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Bits 7-0 contain the next data element from the receive buffer and
    *  other bits contain the error condition.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is disabled: The internal software buffer overflow
    *  is not returned as status by this function.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 ModbusUART_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;
        uint32 intSourceMask;

        intSourceMask = ModbusUART_SpiUartDisableIntRx();

        if(0u != ModbusUART_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            ModbusUART_SpiUartEnableIntRx(intSourceMask);

            /* Get received byte */
            rxData = ModbusUART_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the case
            * of empty. Otherwise the first received byte will be read.
            */
            rxData = ModbusUART_RX_FIFO_RD_REG;

            /* Enables interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by the interrupt routine
            * in case the byte was received and read by code above.
            */
            ModbusUART_SpiUartEnableIntRx(intSourceMask);
        }

        /* Get and clear RX error mask */
        tmpStatus = (ModbusUART_GetRxInterruptSource() & ModbusUART_INTR_RX_ERR);
        ModbusUART_ClearRxInterruptSource(ModbusUART_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return(rxData);
    }


    #if !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: ModbusUART_UartSetRtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of RTS output signal.
        *
        * Parameters:
        *  polarity: Active polarity of RTS output signal.
        *   ModbusUART_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   ModbusUART_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void ModbusUART_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                ModbusUART_UART_FLOW_CTRL_REG |= (uint32)  ModbusUART_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                ModbusUART_UART_FLOW_CTRL_REG &= (uint32) ~ModbusUART_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: ModbusUART_UartSetRtsFifoLevel
        ********************************************************************************
        *
        * Summary:
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *
        * Parameters:
        *  level: Level in the RX FIFO for RTS signal activation.
        *         The range of valid level values is between 0 and RX FIFO depth - 1.
        *         Setting level value to 0 disables RTS signal activation.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void ModbusUART_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = ModbusUART_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~ModbusUART_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (ModbusUART_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            ModbusUART_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */

#endif /* (ModbusUART_UART_RX_DIRECTION) */


#if(ModbusUART_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: ModbusUART_UartPutString
    ********************************************************************************
    *
    * Summary:
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  string: pointer to the null terminated string array to be placed in the
    *          transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusUART_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            ModbusUART_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: ModbusUART_UartPutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data followed by a carriage return (0x0D) and
    *  line feed (0x0A) into the transmit buffer.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  txDataByte : the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusUART_UartPutCRLF(uint32 txDataByte)
    {
        ModbusUART_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        ModbusUART_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        ModbusUART_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: ModbusUARTSCB_UartEnableCts
        ********************************************************************************
        *
        * Summary:
        *  Enables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void ModbusUART_UartEnableCts(void)
        {
            ModbusUART_UART_FLOW_CTRL_REG |= (uint32)  ModbusUART_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: ModbusUART_UartDisableCts
        ********************************************************************************
        *
        * Summary:
        *  Disables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void ModbusUART_UartDisableCts(void)
        {
            ModbusUART_UART_FLOW_CTRL_REG &= (uint32) ~ModbusUART_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: ModbusUART_UartSetCtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of CTS input signal.
        *
        * Parameters:
        *  polarity: Active polarity of CTS output signal.
        *   ModbusUART_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   ModbusUART_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void ModbusUART_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                ModbusUART_UART_FLOW_CTRL_REG |= (uint32)  ModbusUART_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                ModbusUART_UART_FLOW_CTRL_REG &= (uint32) ~ModbusUART_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */

#endif /* (ModbusUART_UART_TX_DIRECTION) */


#if(ModbusUART_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: ModbusUART_UartSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clears and enables interrupt on a falling edge of the Rx input. The GPIO
    *  event wakes up the device and SKIP_START feature allows the UART continue
    *  receiving data bytes properly. The GPIO interrupt does not track in the
    *  active mode therefore requires to be cleared by this API.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusUART_UartSaveConfig(void)
    {
        /* Clear interrupt activity:
        *  - set skip start and disable RX. At GPIO wakeup RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers during normal operation.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        ModbusUART_UART_RX_CTRL_REG |= ModbusUART_UART_RX_CTRL_SKIP_START;

    #if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(ModbusUART_MOSI_SCL_RX_WAKE_PIN)
            (void) ModbusUART_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
        #endif /* (ModbusUART_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(ModbusUART_UART_RX_WAKE_PIN)
            (void) ModbusUART_rx_wake_ClearInterrupt();
        #endif /* (ModbusUART_UART_RX_WAKE_PIN) */
    #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */

    #if(ModbusUART_UART_RX_WAKEUP_IRQ)
        ModbusUART_RxWakeClearPendingInt();
        ModbusUART_RxWakeEnableInt();
    #endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: ModbusUART_UartRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusUART_UartRestoreConfig(void)
    {
    /* Disable RX GPIO interrupt: no more triggers in active mode */
    #if(ModbusUART_UART_RX_WAKEUP_IRQ)
        ModbusUART_RxWakeDisableInt();
    #endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (ModbusUART_UART_WAKE_ENABLE_CONST) */


#if(ModbusUART_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: ModbusUART_UART_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
    *  event. This event is configured to trigger on a falling edge of the RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR(ModbusUART_UART_WAKEUP_ISR)
    {
        /* Clear interrupt source: the event becomes multi triggered and is
        * only disabled by ModbusUART_UartRestoreConfig() call.
        */
    #if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(ModbusUART_MOSI_SCL_RX_WAKE_PIN)
            (void) ModbusUART_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
        #endif /* (ModbusUART_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(ModbusUART_UART_RX_WAKE_PIN)
            (void) ModbusUART_rx_wake_ClearInterrupt();
        #endif /* (ModbusUART_UART_RX_WAKE_PIN) */
    #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
    }
#endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
