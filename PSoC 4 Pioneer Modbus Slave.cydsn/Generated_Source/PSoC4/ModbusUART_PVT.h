/*******************************************************************************
* File Name: .h
* Version 1.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in I2C mode.
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

#if !defined(CY_SCB_PVT_ModbusUART_H)
#define CY_SCB_PVT_ModbusUART_H

#include "ModbusUART.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define ModbusUART_SetI2CExtClkInterruptMode(interruptMask) ModbusUART_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define ModbusUART_ClearI2CExtClkInterruptSource(interruptMask) ModbusUART_CLEAR_INTR_I2C_EC(interruptMask)
#define ModbusUART_GetI2CExtClkInterruptSource()                (ModbusUART_INTR_I2C_EC_REG)
#define ModbusUART_GetI2CExtClkInterruptMode()                  (ModbusUART_INTR_I2C_EC_MASK_REG)
#define ModbusUART_GetI2CExtClkInterruptSourceMasked()          (ModbusUART_INTR_I2C_EC_MASKED_REG)

/* APIs to service INTR_SPI_EC register */
#define ModbusUART_SetSpiExtClkInterruptMode(interruptMask) ModbusUART_WRITE_INTR_SPI_EC_MASK(interruptMask)
#define ModbusUART_ClearSpiExtClkInterruptSource(interruptMask) ModbusUART_CLEAR_INTR_SPI_EC(interruptMask)
#define ModbusUART_GetExtSpiClkInterruptSource()                 (ModbusUART_INTR_SPI_EC_REG)
#define ModbusUART_GetExtSpiClkInterruptMode()                   (ModbusUART_INTR_SPI_EC_MASK_REG)
#define ModbusUART_GetExtSpiClkInterruptSourceMasked()           (ModbusUART_INTR_SPI_EC_MASKED_REG)

#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void ModbusUART_SetPins(uint32 mode, uint32 subMode, uint32 uartTxRx);
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */

void ModbusUART_DisableTxPinsInputBuffer(void);
void ModbusUART_EnableTxPinsInputBuffer(void);


/**********************************
*     Vars with External Linkage
**********************************/

extern cyisraddress ModbusUART_customIntrHandler;
extern ModbusUART_BACKUP_STRUCT ModbusUART_backup;

#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common config vars */
    extern uint8 ModbusUART_scbMode;
    extern uint8 ModbusUART_scbEnableWake;
    extern uint8 ModbusUART_scbEnableIntr;

    /* I2C config vars */
    extern uint8 ModbusUART_mode;
    extern uint8 ModbusUART_acceptAddr;

    /* SPI/UART config vars */
    extern volatile uint8 * ModbusUART_rxBuffer;
    extern uint8   ModbusUART_rxDataBits;
    extern uint32  ModbusUART_rxBufferSize;

    extern volatile uint8 * ModbusUART_txBuffer;
    extern uint8   ModbusUART_txDataBits;
    extern uint32  ModbusUART_txBufferSize;

    /* EZI2C config vars */
    extern uint8 ModbusUART_numberOfAddr;
    extern uint8 ModbusUART_subAddrSize;
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */

#endif /* (CY_SCB_PVT_ModbusUART_H) */


/* [] END OF FILE */
