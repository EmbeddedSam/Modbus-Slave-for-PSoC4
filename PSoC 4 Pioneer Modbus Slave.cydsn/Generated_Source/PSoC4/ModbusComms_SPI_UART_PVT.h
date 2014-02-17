/*******************************************************************************
* File Name: ModbusComms_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_ModbusComms_H)
#define CY_SCB_SPI_UART_PVT_ModbusComms_H

#include "ModbusComms_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if(ModbusComms_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  ModbusComms_rxBufferHead;
    extern volatile uint32  ModbusComms_rxBufferTail;
    extern volatile uint8   ModbusComms_rxBufferOverflow;
#endif /* (ModbusComms_INTERNAL_RX_SW_BUFFER_CONST) */

#if(ModbusComms_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  ModbusComms_txBufferHead;
    extern volatile uint32  ModbusComms_txBufferTail;
#endif /* (ModbusComms_INTERNAL_TX_SW_BUFFER_CONST) */

#if(ModbusComms_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 ModbusComms_rxBufferInternal[ModbusComms_RX_BUFFER_SIZE];
#endif /* (ModbusComms_INTERNAL_RX_SW_BUFFER) */

#if(ModbusComms_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 ModbusComms_txBufferInternal[ModbusComms_TX_BUFFER_SIZE];
#endif /* (ModbusComms_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(ModbusComms_SCB_MODE_SPI_CONST_CFG)
    void ModbusComms_SpiInit(void);
#endif /* (ModbusComms_SCB_MODE_SPI_CONST_CFG) */

#if(ModbusComms_SPI_WAKE_ENABLE_CONST)
    void ModbusComms_SpiSaveConfig(void);
    void ModbusComms_SpiRestoreConfig(void);
#endif /* (ModbusComms_SPI_WAKE_ENABLE_CONST) */

#if(ModbusComms_SCB_MODE_UART_CONST_CFG)
    void ModbusComms_UartInit(void);
#endif /* (ModbusComms_SCB_MODE_UART_CONST_CFG) */

#if(ModbusComms_UART_WAKE_ENABLE_CONST)
    void ModbusComms_UartSaveConfig(void);
    void ModbusComms_UartRestoreConfig(void);
#endif /* (ModbusComms_UART_WAKE_ENABLE_CONST) */

/* Interrupt processing */
#define ModbusComms_SpiUartEnableIntRx(intSourceMask)  ModbusComms_SetRxInterruptMode(intSourceMask)
#define ModbusComms_SpiUartEnableIntTx(intSourceMask)  ModbusComms_SetTxInterruptMode(intSourceMask)
uint32 ModbusComms_SpiUartDisableIntRx(void);
uint32 ModbusComms_SpiUartDisableIntTx(void);

#endif /* (CY_SCB_SPI_UART_PVT_ModbusComms_H) */


/* [] END OF FILE */
