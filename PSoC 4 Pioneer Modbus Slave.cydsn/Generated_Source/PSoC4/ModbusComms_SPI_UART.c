/*******************************************************************************
* File Name: ModbusComms_SPI_UART.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ModbusComms_PVT.h"
#include "ModbusComms_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(ModbusComms_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 ModbusComms_rxBufferHead;
    volatile uint32 ModbusComms_rxBufferTail;
    volatile uint8  ModbusComms_rxBufferOverflow;
#endif /* (ModbusComms_INTERNAL_RX_SW_BUFFER_CONST) */

#if(ModbusComms_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 ModbusComms_txBufferHead;
    volatile uint32 ModbusComms_txBufferTail;
#endif /* (ModbusComms_INTERNAL_TX_SW_BUFFER_CONST) */

#if(ModbusComms_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 ModbusComms_rxBufferInternal[ModbusComms_RX_BUFFER_SIZE];
#endif /* (ModbusComms_INTERNAL_RX_SW_BUFFER) */

#if(ModbusComms_INTERNAL_TX_SW_BUFFER)
    volatile uint8 ModbusComms_txBufferInternal[ModbusComms_TX_BUFFER_SIZE];
#endif /* (ModbusComms_INTERNAL_TX_SW_BUFFER) */


#if(ModbusComms_RX_DIRECTION)

    /*******************************************************************************
    * Function Name: ModbusComms_SpiUartReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer. Undefined data will
    *  be returned if the RX buffer is empty.
    *  Call ModbusComms_SpiUartGetRxBufferSize() to return buffer size.
    *   - RX software buffer disabled: Returns data element retrieved from RX FIFO.
    *   - RX software buffer enabled: Returns data element from the software
    *     receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Next data element from the receive buffer.
    *
    * Global Variables:
    *  Look into ModbusComms_SpiInit for description.
    *
    *******************************************************************************/
    uint32 ModbusComms_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

        #if(ModbusComms_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 locTail;
        #endif /* (ModbusComms_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(ModbusComms_CHECK_RX_SW_BUFFER)
        {
            if(ModbusComms_rxBufferHead != ModbusComms_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (ModbusComms_rxBufferTail + 1u);

                if(ModbusComms_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data fron RX software buffer */
                rxData = ModbusComms_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                ModbusComms_rxBufferTail = locTail;
            }
        }
        #else
        {
            rxData = ModbusComms_RX_FIFO_RD_REG; /* Read data from RX FIFO */
        }
        #endif

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: ModbusComms_SpiUartGetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of received data elements
    *
    *******************************************************************************/
    uint32 ModbusComms_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
        #if(ModbusComms_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 locHead;
        #endif /* (ModbusComms_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(ModbusComms_CHECK_RX_SW_BUFFER)
        {
            locHead = ModbusComms_rxBufferHead;

            if(locHead >= ModbusComms_rxBufferTail)
            {
                size = (locHead - ModbusComms_rxBufferTail);
            }
            else
            {
                size = (locHead + (ModbusComms_RX_BUFFER_SIZE - ModbusComms_rxBufferTail));
            }
        }
        #else
        {
            size = ModbusComms_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return(size);
    }


    /*******************************************************************************
    * Function Name: ModbusComms_SpiUartClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clear the receive buffer and RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusComms_SpiUartClearRxBuffer(void)
    {
        #if(ModbusComms_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 intSourceMask;
        #endif /* (ModbusComms_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(ModbusComms_CHECK_RX_SW_BUFFER)
        {
            intSourceMask = ModbusComms_SpiUartDisableIntRx();

            ModbusComms_CLEAR_RX_FIFO;

            /* Flush RX software buffer */
            ModbusComms_rxBufferHead     = ModbusComms_rxBufferTail;
            ModbusComms_rxBufferOverflow = 0u;

            /* End RX transfer */
            ModbusComms_ClearRxInterruptSource(ModbusComms_INTR_RX_ALL);

            ModbusComms_SpiUartEnableIntRx(intSourceMask);
        }
        #else
        {
            ModbusComms_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (ModbusComms_RX_DIRECTION) */


#if(ModbusComms_TX_DIRECTION)

    /*******************************************************************************
    * Function Name: ModbusComms_SpiUartWriteTxData
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
    void ModbusComms_SpiUartWriteTxData(uint32 txDataByte)
    {
        #if(ModbusComms_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 locHead;
            uint32 intSourceMask;
        #endif /* (ModbusComms_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(ModbusComms_CHECK_TX_SW_BUFFER)
        {
            /* Head index to put data */
            locHead = (ModbusComms_txBufferHead + 1u);

            /* Adjust TX software buffer index */
            if(ModbusComms_TX_BUFFER_SIZE == locHead)
            {
                locHead = 0u;
            }

            while(locHead == ModbusComms_txBufferTail)
            {
                /* Wait for space in the TX software buffer */
            }

            /* The TX software buffer has at least one room */

            if((ModbusComms_txBufferHead == ModbusComms_txBufferTail) &&
               (ModbusComms_FIFO_SIZE != ModbusComms_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                ModbusComms_TX_FIFO_WR_REG = txDataByte;
            }
            /* Put data in the TX software buffer */
            else
            {
                /* Clear old status of INTR_TX_EMPTY. It sets at the end of transfer: TX FIFO empty. */
                ModbusComms_ClearTxInterruptSource(ModbusComms_INTR_TX_NOT_FULL);

                ModbusComms_PutWordInTxBuffer(locHead, txDataByte);

                ModbusComms_txBufferHead = locHead;

                /* Enable interrupt to transmit */
                intSourceMask  = ModbusComms_INTR_TX_NOT_FULL;
                intSourceMask |= ModbusComms_GetTxInterruptMode();
                ModbusComms_SpiUartEnableIntTx(intSourceMask);
            }
        }
        #else
        {
            while(ModbusComms_FIFO_SIZE == ModbusComms_GET_TX_FIFO_ENTRIES)
            {
                /* Block while TX FIFO is FULL */
            }

            ModbusComms_TX_FIFO_WR_REG = txDataByte;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: ModbusComms_SpiUartPutArray
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
    void ModbusComms_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for(i=0u; i < count; i++)
        {
            ModbusComms_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: ModbusComms_SpiUartGetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of elements currently in the transmit buffer.
    *  TX software buffer disabled: returns the number of used entries in TX FIFO.
    *  TX software buffer enabled: returns the number of elements currently used
    *  in the transmit buffer. This number does not include used entries in the
    *  TX FIFO. The transmit buffer size is zero until the TX FIFO is full.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of data elements ready to transmit.
    *
    *******************************************************************************/
    uint32 ModbusComms_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
        #if(ModbusComms_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 locTail;
        #endif /* (ModbusComms_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(ModbusComms_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = ModbusComms_txBufferTail;

            if(ModbusComms_txBufferHead >= locTail)
            {
                size = (ModbusComms_txBufferHead - locTail);
            }
            else
            {
                size = (ModbusComms_txBufferHead + (ModbusComms_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = ModbusComms_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return(size);
    }


    /*******************************************************************************
    * Function Name: ModbusComms_SpiUartClearTxBuffer
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
    void ModbusComms_SpiUartClearTxBuffer(void)
    {
        #if(ModbusComms_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 intSourceMask;
        #endif /* (ModbusComms_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(ModbusComms_CHECK_TX_SW_BUFFER)
        {
            intSourceMask = ModbusComms_SpiUartDisableIntTx();

            ModbusComms_CLEAR_TX_FIFO;

            /* Flush TX software buffer */
            ModbusComms_txBufferHead = ModbusComms_txBufferTail;

            /* End TX transfer if it is in progress */
            intSourceMask &= (uint32) ~ModbusComms_INTR_TX_NOT_FULL;

            ModbusComms_SpiUartEnableIntTx(intSourceMask);
        }
        #else
        {
            ModbusComms_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (ModbusComms_TX_DIRECTION) */


/*******************************************************************************
* Function Name: ModbusComms_SpiUartDisableIntRx
********************************************************************************
*
* Summary:
*  Disables RX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns RX interrupt soureces enabled before function call.
*
*******************************************************************************/
uint32 ModbusComms_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = ModbusComms_GetRxInterruptMode();

    ModbusComms_SetRxInterruptMode(ModbusComms_NO_INTR_SOURCES);

    return(intSource);
}


/*******************************************************************************
* Function Name: ModbusComms_SpiUartDisableIntTx
********************************************************************************
*
* Summary:
*  Disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns TX interrupt soureces enabled before function call.
*
*******************************************************************************/
uint32 ModbusComms_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = ModbusComms_GetTxInterruptMode();

    ModbusComms_SetTxInterruptMode(ModbusComms_NO_INTR_SOURCES);

    return(intSourceMask);
}


#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)

    /*******************************************************************************
    * Function Name: ModbusComms_PutWordInRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the RX buffer.
    *  Only available in Unconfigured operation mode.
    *
    * Parameters:
    *  index:      index to store data byte/word in the RX buffer.
    *  rxDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusComms_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in the buffer */
        if(ModbusComms_ONE_BYTE_WIDTH == ModbusComms_rxDataBits)
        {
            ModbusComms_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            ModbusComms_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            ModbusComms_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: ModbusComms_GetWordFromRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from RX buffer.
    *  Only available in Unconfigured operation mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 ModbusComms_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if(ModbusComms_ONE_BYTE_WIDTH == ModbusComms_rxDataBits)
        {
            value = ModbusComms_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) ModbusComms_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)ModbusComms_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return(value);
    }


    /*******************************************************************************
    * Function Name: ModbusComms_PutWordInTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the TX buffer.
    * Only available in Unconfigured operation mode.
    *
    * Parameters:
    *  idx:        index to store data byte/word in the TX buffer.
    *  txDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusComms_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in the buffer */
        if(ModbusComms_ONE_BYTE_WIDTH == ModbusComms_txDataBits)
        {
            ModbusComms_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            ModbusComms_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            ModbusComms_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: ModbusComms_GetWordFromTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from TX buffer.
    *  Only available in Unconfigured operation mode.
    *
    * Parameters:
    *  idx: index to get data byte/word from the TX buffer.
    *
    * Return:
    *  Returns byte/word read from TX buffer.
    *
    *******************************************************************************/
    uint32 ModbusComms_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if(ModbusComms_ONE_BYTE_WIDTH == ModbusComms_txDataBits)
        {
            value = (uint32) ModbusComms_txBuffer[idx];
        }
        else
        {
            value  = (uint32) ModbusComms_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) ModbusComms_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return(value);
    }

#endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
