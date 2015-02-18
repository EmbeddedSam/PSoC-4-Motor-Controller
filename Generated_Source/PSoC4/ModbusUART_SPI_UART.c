/*******************************************************************************
* File Name: ModbusUART_SPI_UART.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
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

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(ModbusUART_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 ModbusUART_rxBufferHead;
    volatile uint32 ModbusUART_rxBufferTail;
    volatile uint8  ModbusUART_rxBufferOverflow;
#endif /* (ModbusUART_INTERNAL_RX_SW_BUFFER_CONST) */

#if(ModbusUART_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 ModbusUART_txBufferHead;
    volatile uint32 ModbusUART_txBufferTail;
#endif /* (ModbusUART_INTERNAL_TX_SW_BUFFER_CONST) */

#if(ModbusUART_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 ModbusUART_rxBufferInternal[ModbusUART_RX_BUFFER_SIZE];
#endif /* (ModbusUART_INTERNAL_RX_SW_BUFFER) */

#if(ModbusUART_INTERNAL_TX_SW_BUFFER)
    volatile uint8 ModbusUART_txBufferInternal[ModbusUART_TX_BUFFER_SIZE];
#endif /* (ModbusUART_INTERNAL_TX_SW_BUFFER) */


#if(ModbusUART_RX_DIRECTION)

    /*******************************************************************************
    * Function Name: ModbusUART_SpiUartReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Next data element from the receive buffer.
    *
    * Global Variables:
    *  Look into ModbusUART_SpiInit for description.
    *
    *******************************************************************************/
    uint32 ModbusUART_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

        #if(ModbusUART_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 locTail;
        #endif /* (ModbusUART_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(ModbusUART_CHECK_RX_SW_BUFFER)
        {
            if(ModbusUART_rxBufferHead != ModbusUART_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (ModbusUART_rxBufferTail + 1u);

                if(ModbusUART_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = ModbusUART_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                ModbusUART_rxBufferTail = locTail;
            }
        }
        #else
        {
            rxData = ModbusUART_RX_FIFO_RD_REG; /* Read data from RX FIFO */
        }
        #endif

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: ModbusUART_SpiUartGetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of received data elements
    *
    *******************************************************************************/
    uint32 ModbusUART_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
        #if(ModbusUART_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 locHead;
        #endif /* (ModbusUART_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(ModbusUART_CHECK_RX_SW_BUFFER)
        {
            locHead = ModbusUART_rxBufferHead;

            if(locHead >= ModbusUART_rxBufferTail)
            {
                size = (locHead - ModbusUART_rxBufferTail);
            }
            else
            {
                size = (locHead + (ModbusUART_RX_BUFFER_SIZE - ModbusUART_rxBufferTail));
            }
        }
        #else
        {
            size = ModbusUART_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return(size);
    }


    /*******************************************************************************
    * Function Name: ModbusUART_SpiUartClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receive buffer and RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusUART_SpiUartClearRxBuffer(void)
    {
        #if(ModbusUART_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 intSourceMask;
        #endif /* (ModbusUART_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(ModbusUART_CHECK_RX_SW_BUFFER)
        {
            intSourceMask = ModbusUART_SpiUartDisableIntRx();

            ModbusUART_CLEAR_RX_FIFO;

            /* Flush RX software buffer */
            ModbusUART_rxBufferHead     = ModbusUART_rxBufferTail;
            ModbusUART_rxBufferOverflow = 0u;

            /* End RX transfer */
            ModbusUART_ClearRxInterruptSource(ModbusUART_INTR_RX_ALL);

            ModbusUART_SpiUartEnableIntRx(intSourceMask);
        }
        #else
        {
            ModbusUART_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (ModbusUART_RX_DIRECTION) */


#if(ModbusUART_TX_DIRECTION)

    /*******************************************************************************
    * Function Name: ModbusUART_SpiUartWriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    * Parameters:
    *  txDataByte: the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusUART_SpiUartWriteTxData(uint32 txData)
    {
        #if(ModbusUART_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 locHead;
            uint32 intSourceMask;
        #endif /* (ModbusUART_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(ModbusUART_CHECK_TX_SW_BUFFER)
        {
            /* Head index to put data */
            locHead = (ModbusUART_txBufferHead + 1u);

            /* Adjust TX software buffer index */
            if(ModbusUART_TX_BUFFER_SIZE == locHead)
            {
                locHead = 0u;
            }

            while(locHead == ModbusUART_txBufferTail)
            {
                /* Wait for space in TX software buffer */
            }

            /* TX software buffer has at least one room */

            if((ModbusUART_txBufferHead == ModbusUART_txBufferTail) &&
               (ModbusUART_SPI_UART_FIFO_SIZE != ModbusUART_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                ModbusUART_TX_FIFO_WR_REG = txData;
            }
            /* Put data in TX software buffer */
            else
            {
                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                ModbusUART_ClearTxInterruptSource(ModbusUART_INTR_TX_NOT_FULL);

                ModbusUART_PutWordInTxBuffer(locHead, txData);

                ModbusUART_txBufferHead = locHead;

                /* Enable interrupt to transmit */
                intSourceMask  = ModbusUART_INTR_TX_NOT_FULL;
                intSourceMask |= ModbusUART_GetTxInterruptMode();
                ModbusUART_SpiUartEnableIntTx(intSourceMask);
            }
        }
        #else
        {
            while(ModbusUART_SPI_UART_FIFO_SIZE == ModbusUART_GET_TX_FIFO_ENTRIES)
            {
                /* Block while TX FIFO is FULL */
            }

            ModbusUART_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: ModbusUART_SpiUartPutArray
    ********************************************************************************
    *
    * Summary:
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * Parameters:
    *  wrBuf:  pointer to an array with data to be placed in transmit buffer.
    *  count:  number of data elements to be placed in the transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusUART_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for(i=0u; i < count; i++)
        {
            ModbusUART_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: ModbusUART_SpiUartGetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    * Returns the number of elements currently in the transmit buffer.
    *  - TX software buffer is disabled: returns the number of used entries in
    *    TX FIFO.
    *  - TX software buffer is enabled: returns the number of elements currently
    *    used in the transmit buffer. This number does not include used entries in
    *    the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *    not full.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of data elements ready to transmit.
    *
    *******************************************************************************/
    uint32 ModbusUART_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
        #if(ModbusUART_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 locTail;
        #endif /* (ModbusUART_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(ModbusUART_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = ModbusUART_txBufferTail;

            if(ModbusUART_txBufferHead >= locTail)
            {
                size = (ModbusUART_txBufferHead - locTail);
            }
            else
            {
                size = (ModbusUART_txBufferHead + (ModbusUART_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = ModbusUART_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return(size);
    }


    /*******************************************************************************
    * Function Name: ModbusUART_SpiUartClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the transmit buffer and TX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusUART_SpiUartClearTxBuffer(void)
    {
        #if(ModbusUART_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 intSourceMask;
        #endif /* (ModbusUART_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(ModbusUART_CHECK_TX_SW_BUFFER)
        {
            intSourceMask = ModbusUART_SpiUartDisableIntTx();

            ModbusUART_CLEAR_TX_FIFO;

            /* Flush TX software buffer */
            ModbusUART_txBufferHead = ModbusUART_txBufferTail;

            /* End TX transfer if it is in progress */
            intSourceMask &= (uint32) ~ModbusUART_INTR_TX_NOT_FULL;

            ModbusUART_SpiUartEnableIntTx(intSourceMask);
        }
        #else
        {
            ModbusUART_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (ModbusUART_TX_DIRECTION) */


/*******************************************************************************
* Function Name: ModbusUART_SpiUartDisableIntRx
********************************************************************************
*
* Summary:
*  Disables the RX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 ModbusUART_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = ModbusUART_GetRxInterruptMode();

    ModbusUART_SetRxInterruptMode(ModbusUART_NO_INTR_SOURCES);

    return(intSource);
}


/*******************************************************************************
* Function Name: ModbusUART_SpiUartDisableIntTx
********************************************************************************
*
* Summary:
*  Disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 ModbusUART_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = ModbusUART_GetTxInterruptMode();

    ModbusUART_SetTxInterruptMode(ModbusUART_NO_INTR_SOURCES);

    return(intSourceMask);
}


#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: ModbusUART_PutWordInRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  index:      index to store data byte/word in the RX buffer.
    *  rxDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusUART_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if(ModbusUART_ONE_BYTE_WIDTH == ModbusUART_rxDataBits)
        {
            ModbusUART_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            ModbusUART_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            ModbusUART_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: ModbusUART_GetWordFromRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 ModbusUART_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if(ModbusUART_ONE_BYTE_WIDTH == ModbusUART_rxDataBits)
        {
            value = ModbusUART_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) ModbusUART_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)ModbusUART_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return(value);
    }


    /*******************************************************************************
    * Function Name: ModbusUART_PutWordInTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx:        index to store data byte/word in the TX buffer.
    *  txDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusUART_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if(ModbusUART_ONE_BYTE_WIDTH == ModbusUART_txDataBits)
        {
            ModbusUART_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            ModbusUART_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            ModbusUART_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: ModbusUART_GetWordFromTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx: index to get data byte/word from the TX buffer.
    *
    * Return:
    *  Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 ModbusUART_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if(ModbusUART_ONE_BYTE_WIDTH == ModbusUART_txDataBits)
        {
            value = (uint32) ModbusUART_txBuffer[idx];
        }
        else
        {
            value  = (uint32) ModbusUART_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) ModbusUART_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return(value);
    }

#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
