/*******************************************************************************
* File Name: ModbusUART_SPI_UART_INT.c
* Version 1.10
*
* Description:
*  This file provides the source code to the Interrupt Servive Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ModbusUART_PVT.h"
#include "ModbusUART_SPI_UART_PVT.h"


/*******************************************************************************
* Function Name: ModbusUART_SPI_UART_ISR
********************************************************************************
*
* Summary:
*  Handles Interrupt Service Routine for SCB SPI or UART modes.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(ModbusUART_SPI_UART_ISR)
{
    #if(ModbusUART_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
        uint32 dataRx;
    #endif /* (ModbusUART_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(ModbusUART_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (ModbusUART_INTERNAL_TX_SW_BUFFER_CONST) */

    if(NULL != ModbusUART_customIntrHandler)
    {
        ModbusUART_customIntrHandler(); /* Call customer routine if needed */
    }

    #if(ModbusUART_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        ModbusUART_ClearSpiExtClkInterruptSource(ModbusUART_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if(ModbusUART_CHECK_RX_SW_BUFFER)
    {
        /* Get data from RX FIFO */
        if(ModbusUART_CHECK_INTR_RX_MASKED(ModbusUART_INTR_RX_NOT_EMPTY))
        {
            while(0u != ModbusUART_GET_RX_FIFO_ENTRIES)
            {
                /* Get data from RX FIFO */
                dataRx = ModbusUART_RX_FIFO_RD_REG;

                /* Move local head index */
                locHead = (ModbusUART_rxBufferHead + 1u);

                /* Adjust local head index */
                if(ModbusUART_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if(locHead == ModbusUART_rxBufferTail)
                {
                    /* Overflow: through away new data */
                    ModbusUART_rxBufferOverflow = (uint8) ModbusUART_INTR_RX_OVERFLOW;
                }
                else
                {
                    /* Store received data */
                    ModbusUART_PutWordInRxBuffer(locHead, dataRx);

                    /* Move head index */
                    ModbusUART_rxBufferHead = locHead;
                }
            }

            ModbusUART_ClearRxInterruptSource(ModbusUART_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if(ModbusUART_CHECK_TX_SW_BUFFER)
    {
        if(ModbusUART_CHECK_INTR_TX_MASKED(ModbusUART_INTR_TX_NOT_FULL))
        {
            /* Put data into TX FIFO */
            while(ModbusUART_FIFO_SIZE != ModbusUART_GET_TX_FIFO_ENTRIES)
            {
                /* There is a data in TX software buffer */
                if(ModbusUART_txBufferHead != ModbusUART_txBufferTail)
                {
                    /* Mode local tail index */
                    locTail = (ModbusUART_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if(ModbusUART_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    ModbusUART_TX_FIFO_WR_REG = ModbusUART_GetWordFromTxBuffer(locTail);

                    /* Mode tail index */
                    ModbusUART_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is EMPTY: end of transmitting */
                    ModbusUART_DISABLE_INTR_TX(ModbusUART_INTR_TX_NOT_FULL);
                    break;
                }
            }

            ModbusUART_ClearTxInterruptSource(ModbusUART_INTR_TX_NOT_FULL);
        }
    }
    #endif
}


/* [] END OF FILE */
