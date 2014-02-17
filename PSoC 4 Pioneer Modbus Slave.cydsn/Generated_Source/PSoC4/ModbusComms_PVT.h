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

#if !defined(CY_SCB_PVT_ModbusComms_H)
#define CY_SCB_PVT_ModbusComms_H

#include "ModbusComms.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define ModbusComms_SetI2CExtClkInterruptMode(interruptMask) ModbusComms_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define ModbusComms_ClearI2CExtClkInterruptSource(interruptMask) ModbusComms_CLEAR_INTR_I2C_EC(interruptMask)
#define ModbusComms_GetI2CExtClkInterruptSource()                (ModbusComms_INTR_I2C_EC_REG)
#define ModbusComms_GetI2CExtClkInterruptMode()                  (ModbusComms_INTR_I2C_EC_MASK_REG)
#define ModbusComms_GetI2CExtClkInterruptSourceMasked()          (ModbusComms_INTR_I2C_EC_MASKED_REG)

/* APIs to service INTR_SPI_EC register */
#define ModbusComms_SetSpiExtClkInterruptMode(interruptMask) ModbusComms_WRITE_INTR_SPI_EC_MASK(interruptMask)
#define ModbusComms_ClearSpiExtClkInterruptSource(interruptMask) ModbusComms_CLEAR_INTR_SPI_EC(interruptMask)
#define ModbusComms_GetExtSpiClkInterruptSource()                 (ModbusComms_INTR_SPI_EC_REG)
#define ModbusComms_GetExtSpiClkInterruptMode()                   (ModbusComms_INTR_SPI_EC_MASK_REG)
#define ModbusComms_GetExtSpiClkInterruptSourceMasked()           (ModbusComms_INTR_SPI_EC_MASKED_REG)

#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void ModbusComms_SetPins(uint32 mode, uint32 subMode, uint32 uartTxRx);
#endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */

void ModbusComms_DisableTxPinsInputBuffer(void);
void ModbusComms_EnableTxPinsInputBuffer(void);


/**********************************
*     Vars with External Linkage
**********************************/

extern cyisraddress ModbusComms_customIntrHandler;
extern ModbusComms_BACKUP_STRUCT ModbusComms_backup;

#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common config vars */
    extern uint8 ModbusComms_scbMode;
    extern uint8 ModbusComms_scbEnableWake;
    extern uint8 ModbusComms_scbEnableIntr;

    /* I2C config vars */
    extern uint8 ModbusComms_mode;
    extern uint8 ModbusComms_acceptAddr;

    /* SPI/UART config vars */
    extern volatile uint8 * ModbusComms_rxBuffer;
    extern uint8   ModbusComms_rxDataBits;
    extern uint32  ModbusComms_rxBufferSize;

    extern volatile uint8 * ModbusComms_txBuffer;
    extern uint8   ModbusComms_txDataBits;
    extern uint32  ModbusComms_txBufferSize;

    /* EZI2C config vars */
    extern uint8 ModbusComms_numberOfAddr;
    extern uint8 ModbusComms_subAddrSize;
#endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */

#endif /* (CY_SCB_PVT_ModbusComms_H) */


/* [] END OF FILE */
