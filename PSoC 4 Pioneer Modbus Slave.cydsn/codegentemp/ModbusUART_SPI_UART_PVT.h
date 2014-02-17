/*******************************************************************************
* File Name: ModbusUART_SPI_UART_PVT.h
* Version 1.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_ModbusUART_H)
#define CY_SCB_SPI_UART_PVT_ModbusUART_H

#include "ModbusUART_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if(ModbusUART_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  ModbusUART_rxBufferHead;
    extern volatile uint32  ModbusUART_rxBufferTail;
    extern volatile uint8   ModbusUART_rxBufferOverflow;
#endif /* (ModbusUART_INTERNAL_RX_SW_BUFFER_CONST) */

#if(ModbusUART_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  ModbusUART_txBufferHead;
    extern volatile uint32  ModbusUART_txBufferTail;
#endif /* (ModbusUART_INTERNAL_TX_SW_BUFFER_CONST) */

#if(ModbusUART_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 ModbusUART_rxBufferInternal[ModbusUART_RX_BUFFER_SIZE];
#endif /* (ModbusUART_INTERNAL_RX_SW_BUFFER) */

#if(ModbusUART_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 ModbusUART_txBufferInternal[ModbusUART_TX_BUFFER_SIZE];
#endif /* (ModbusUART_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(ModbusUART_SCB_MODE_SPI_CONST_CFG)
    void ModbusUART_SpiInit(void);
#endif /* (ModbusUART_SCB_MODE_SPI_CONST_CFG) */

#if(ModbusUART_SPI_WAKE_ENABLE_CONST)
    void ModbusUART_SpiSaveConfig(void);
    void ModbusUART_SpiRestoreConfig(void);
#endif /* (ModbusUART_SPI_WAKE_ENABLE_CONST) */

#if(ModbusUART_SCB_MODE_UART_CONST_CFG)
    void ModbusUART_UartInit(void);
#endif /* (ModbusUART_SCB_MODE_UART_CONST_CFG) */

#if(ModbusUART_UART_WAKE_ENABLE_CONST)
    void ModbusUART_UartSaveConfig(void);
    void ModbusUART_UartRestoreConfig(void);
#endif /* (ModbusUART_UART_WAKE_ENABLE_CONST) */

/* Interrupt processing */
#define ModbusUART_SpiUartEnableIntRx(intSourceMask)  ModbusUART_SetRxInterruptMode(intSourceMask)
#define ModbusUART_SpiUartEnableIntTx(intSourceMask)  ModbusUART_SetTxInterruptMode(intSourceMask)
uint32 ModbusUART_SpiUartDisableIntRx(void);
uint32 ModbusUART_SpiUartDisableIntTx(void);

#endif /* (CY_SCB_SPI_UART_PVT_ModbusUART_H) */


/* [] END OF FILE */
