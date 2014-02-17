/*******************************************************************************
* File Name: ModbusComms_SPI_UART_INT.c
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

#include "ModbusComms_PVT.h"
#include "ModbusComms_SPI_UART_PVT.h"


/*******************************************************************************
* Function Name: ModbusComms_SPI_UART_ISR
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
CY_ISR(ModbusComms_SPI_UART_ISR)
{
    #if(ModbusComms_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
        uint32 dataRx;
    #endif /* (ModbusComms_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(ModbusComms_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (ModbusComms_INTERNAL_TX_SW_BUFFER_CONST) */

    if(NULL != ModbusComms_customIntrHandler)
    {
        ModbusComms_customIntrHandler(); /* Call customer routine if needed */
    }

    #if(ModbusComms_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        ModbusComms_ClearSpiExtClkInterruptSource(ModbusComms_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if(ModbusComms_CHECK_RX_SW_BUFFER)
    {
        /* Get data from RX FIFO */
        if(ModbusComms_CHECK_INTR_RX_MASKED(ModbusComms_INTR_RX_NOT_EMPTY))
        {
            while(0u != ModbusComms_GET_RX_FIFO_ENTRIES)
            {
                /* Get data from RX FIFO */
                dataRx = ModbusComms_RX_FIFO_RD_REG;

                /* Move local head index */
                locHead = (ModbusComms_rxBufferHead + 1u);

                /* Adjust local head index */
                if(ModbusComms_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if(locHead == ModbusComms_rxBufferTail)
                {
                    /* Overflow: through away new data */
                    ModbusComms_rxBufferOverflow = (uint8) ModbusComms_INTR_RX_OVERFLOW;
                }
                else
                {
                    /* Store received data */
                    ModbusComms_PutWordInRxBuffer(locHead, dataRx);

                    /* Move head index */
                    ModbusComms_rxBufferHead = locHead;
                }
            }

            ModbusComms_ClearRxInterruptSource(ModbusComms_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if(ModbusComms_CHECK_TX_SW_BUFFER)
    {
        if(ModbusComms_CHECK_INTR_TX_MASKED(ModbusComms_INTR_TX_NOT_FULL))
        {
            /* Put data into TX FIFO */
            while(ModbusComms_FIFO_SIZE != ModbusComms_GET_TX_FIFO_ENTRIES)
            {
                /* There is a data in TX software buffer */
                if(ModbusComms_txBufferHead != ModbusComms_txBufferTail)
                {
                    /* Mode local tail index */
                    locTail = (ModbusComms_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if(ModbusComms_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    ModbusComms_TX_FIFO_WR_REG = ModbusComms_GetWordFromTxBuffer(locTail);

                    /* Mode tail index */
                    ModbusComms_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is EMPTY: end of transmitting */
                    ModbusComms_DISABLE_INTR_TX(ModbusComms_INTR_TX_NOT_FULL);
                    break;
                }
            }

            ModbusComms_ClearTxInterruptSource(ModbusComms_INTR_TX_NOT_FULL);
        }
    }
    #endif
}


/* [] END OF FILE */
