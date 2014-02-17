/*******************************************************************************
* File Name: ModbusUART.h
* Version 1.10
*
* Description:
*  This file provides constants and parameter values for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_ModbusUART_H)
#define CY_SCB_ModbusUART_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"


/***************************************
*  Conditional Compilation Parameters
****************************************/

#define ModbusUART_SCB_MODE                     (4u)

/* SCB modes enum */
#define ModbusUART_SCB_MODE_I2C                 (0x01u)
#define ModbusUART_SCB_MODE_SPI                 (0x02u)
#define ModbusUART_SCB_MODE_UART                (0x04u)
#define ModbusUART_SCB_MODE_EZI2C               (0x08u)
#define ModbusUART_SCB_MODE_UNCONFIG            (0xFFu)

/* Define run time operation mode */
#define ModbusUART_SCB_MODE_I2C_RUNTM_CFG       (ModbusUART_SCB_MODE_I2C       == ModbusUART_scbMode)
#define ModbusUART_SCB_MODE_SPI_RUNTM_CFG       (ModbusUART_SCB_MODE_SPI       == ModbusUART_scbMode)
#define ModbusUART_SCB_MODE_UART_RUNTM_CFG      (ModbusUART_SCB_MODE_UART      == ModbusUART_scbMode)
#define ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG     (ModbusUART_SCB_MODE_EZI2C     == ModbusUART_scbMode)
#define ModbusUART_SCB_MODE_UNCONFIG_RUNTM_CFG  (ModbusUART_SCB_MODE_UNCONFIG  == ModbusUART_scbMode)

/* Condition compilation depends on operation mode: unconfigured implies apply to all modes */
#define ModbusUART_SCB_MODE_I2C_CONST_CFG       (ModbusUART_SCB_MODE_I2C       == ModbusUART_SCB_MODE)
#define ModbusUART_SCB_MODE_SPI_CONST_CFG       (ModbusUART_SCB_MODE_SPI       == ModbusUART_SCB_MODE)
#define ModbusUART_SCB_MODE_UART_CONST_CFG      (ModbusUART_SCB_MODE_UART      == ModbusUART_SCB_MODE)
#define ModbusUART_SCB_MODE_EZI2C_CONST_CFG     (ModbusUART_SCB_MODE_EZI2C     == ModbusUART_SCB_MODE)
#define ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG  (ModbusUART_SCB_MODE_UNCONFIG  == ModbusUART_SCB_MODE)

/* Condition compilation for includes */
#define ModbusUART_SCB_MODE_I2C_INC       (0u !=(ModbusUART_SCB_MODE_I2C       & ModbusUART_SCB_MODE))
#define ModbusUART_SCB_MODE_SPI_INC       (0u !=(ModbusUART_SCB_MODE_SPI       & ModbusUART_SCB_MODE))
#define ModbusUART_SCB_MODE_UART_INC      (0u !=(ModbusUART_SCB_MODE_UART      & ModbusUART_SCB_MODE))
#define ModbusUART_SCB_MODE_EZI2C_INC     (0u !=(ModbusUART_SCB_MODE_EZI2C     & ModbusUART_SCB_MODE))

/* Interrupts remove options */
#define ModbusUART_REMOVE_SCB_IRQ             (1u)
#define ModbusUART_SCB_IRQ_INTERNAL           (0u == ModbusUART_REMOVE_SCB_IRQ)

#define ModbusUART_REMOVE_UART_RX_WAKEUP_IRQ  (1u)
#define ModbusUART_UART_RX_WAKEUP_IRQ         (0u == ModbusUART_REMOVE_UART_RX_WAKEUP_IRQ)

/* SCB interrupt enum */
#define ModbusUART_SCB_INTR_MODE_NONE     (0u)
#define ModbusUART_SCB_INTR_MODE_INTERNAL (1u)
#define ModbusUART_SCB_INTR_MODE_EXTERNAL (2u)

/* Bootloader communication interface enable */
#define ModbusUART_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusUART) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))


/***************************************
*       Includes
****************************************/

#include "ModbusUART_PINS.h"

#if(ModbusUART_SCB_IRQ_INTERNAL)
    #include "ModbusUART_SCB_IRQ.h"
#endif /* (ModbusUART_SCB_IRQ_INTERNAL) */

#if(ModbusUART_UART_RX_WAKEUP_IRQ)
    #include "ModbusUART_RX_WAKEUP_IRQ.h"
#endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */


/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint8 enableState;
} ModbusUART_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* Start and Stop APIs */
void ModbusUART_Init(void);
void ModbusUART_Enable(void);
void ModbusUART_Start(void);
void ModbusUART_Stop(void);

/* Sleep and Wakeup APis */
void ModbusUART_Sleep(void);
void ModbusUART_Wakeup(void);

/* Customer interrupt handler */
void ModbusUART_SetCustomInterruptHandler(cyisraddress func);

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_BTLDR_COMM_ENABLED)

    /* Bootloader Physical layer functions */
    void ModbusUART_CyBtldrCommStart(void);
    void ModbusUART_CyBtldrCommStop (void);
    void ModbusUART_CyBtldrCommReset(void);
    cystatus ModbusUART_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ModbusUART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    #if(CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusUART)
        #define CyBtldrCommStart    ModbusUART_CyBtldrCommStart
        #define CyBtldrCommStop     ModbusUART_CyBtldrCommStop
        #define CyBtldrCommReset    ModbusUART_CyBtldrCommReset
        #define CyBtldrCommWrite    ModbusUART_CyBtldrCommWrite
        #define CyBtldrCommRead     ModbusUART_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusUART) */

#endif /*defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusUART) || \
                                                     (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */

/* Interface to internal interrupt component */
#if(ModbusUART_SCB_IRQ_INTERNAL)
    #define ModbusUART_EnableInt()    ModbusUART_SCB_IRQ_Enable()
    #define ModbusUART_DisableInt()   ModbusUART_SCB_IRQ_Disable()
#endif /* (ModbusUART_SCB_IRQ_INTERNAL) */

/* Get interrupt cause */
#define ModbusUART_GetInterruptCause()    (ModbusUART_INTR_CAUSE_REG)

/* APIs to service INTR_RX register */
#define ModbusUART_SetRxInterruptMode(interruptMask)     ModbusUART_WRITE_INTR_RX_MASK(interruptMask)
#define ModbusUART_ClearRxInterruptSource(interruptMask) ModbusUART_CLEAR_INTR_RX(interruptMask)
#define ModbusUART_SetRxInterrupt(interruptMask)         ModbusUART_SET_INTR_RX(interruptMask)
#define ModbusUART_GetRxInterruptSource()                (ModbusUART_INTR_RX_REG)
#define ModbusUART_GetRxInterruptMode()                  (ModbusUART_INTR_RX_MASK_REG)
#define ModbusUART_GetRxInterruptSourceMasked()          (ModbusUART_INTR_RX_MASKED_REG)

/* APIs to service INTR_TX register */
#define ModbusUART_SetTxInterruptMode(interruptMask)     ModbusUART_WRITE_INTR_TX_MASK(interruptMask)
#define ModbusUART_ClearTxInterruptSource(interruptMask) ModbusUART_CLEAR_INTR_TX(interruptMask)
#define ModbusUART_SetTxInterrupt(interruptMask)         ModbusUART_SET_INTR_TX(interruptMask)
#define ModbusUART_GetTxInterruptSource()                (ModbusUART_INTR_TX_REG)
#define ModbusUART_GetTxInterruptMode()                  (ModbusUART_INTR_TX_MASK_REG)
#define ModbusUART_GetTxInterruptSourceMasked()          (ModbusUART_INTR_TX_MASKED_REG)

/* APIs to service INTR_MASTER register */
#define ModbusUART_SetMasterInterruptMode(interruptMask)    ModbusUART_WRITE_INTR_MASTER_MASK(interruptMask)
#define ModbusUART_ClearMasterInterruptSource(interruptMask) ModbusUART_CLEAR_INTR_MASTER(interruptMask)
#define ModbusUART_SetMasterInterrupt(interruptMask)         ModbusUART_SET_INTR_MASTER(interruptMask)
#define ModbusUART_GetMasterInterruptSource()                (ModbusUART_INTR_MASTER_REG)
#define ModbusUART_GetMasterInterruptMode()                  (ModbusUART_INTR_MASTER_MASK_REG)
#define ModbusUART_GetMasterInterruptSourceMasked()          (ModbusUART_INTR_MASTER_MASKED_REG)

/* APIs to service INTR_SLAVE register */
#define ModbusUART_SetSlaveInterruptMode(interruptMask)     ModbusUART_WRITE_INTR_SLAVE_MASK(interruptMask)
#define ModbusUART_ClearSlaveInterruptSource(interruptMask) ModbusUART_CLEAR_INTR_SLAVE(interruptMask)
#define ModbusUART_SetSlaveInterrupt(interruptMask)         ModbusUART_SET_INTR_SLAVE(interruptMask)
#define ModbusUART_GetSlaveInterruptSource()                (ModbusUART_INTR_SLAVE_REG)
#define ModbusUART_GetSlaveInterruptMode()                  (ModbusUART_INTR_SLAVE_MASK_REG)
#define ModbusUART_GetSlaveInterruptSourceMasked()          (ModbusUART_INTR_SLAVE_MASKED_REG)


/**********************************
*     Vars with External Linkage
**********************************/

extern uint8 ModbusUART_initVar;


/***************************************
*              Registers
***************************************/

#define ModbusUART_CTRL_REG               (*(reg32 *) ModbusUART_SCB__CTRL)
#define ModbusUART_CTRL_PTR               ( (reg32 *) ModbusUART_SCB__CTRL)

#define ModbusUART_STATUS_REG             (*(reg32 *) ModbusUART_SCB__STATUS)
#define ModbusUART_STATUS_PTR             ( (reg32 *) ModbusUART_SCB__STATUS)

#define ModbusUART_SPI_CTRL_REG           (*(reg32 *) ModbusUART_SCB__SPI_CTRL)
#define ModbusUART_SPI_CTRL_PTR           ( (reg32 *) ModbusUART_SCB__SPI_CTRL)

#define ModbusUART_SPI_STATUS_REG         (*(reg32 *) ModbusUART_SCB__SPI_STATUS)
#define ModbusUART_SPI_STATUS_PTR         ( (reg32 *) ModbusUART_SCB__SPI_STATUS)

#define ModbusUART_UART_CTRL_REG          (*(reg32 *) ModbusUART_SCB__UART_CTRL)
#define ModbusUART_UART_CTRL_PTR          ( (reg32 *) ModbusUART_SCB__UART_CTRL)

#define ModbusUART_UART_TX_CTRL_REG       (*(reg32 *) ModbusUART_SCB__UART_TX_CTRL)
#define ModbusUART_UART_TX_CTRL_PTR       ( (reg32 *) ModbusUART_SCB__UART_RX_CTRL)

#define ModbusUART_UART_RX_CTRL_REG       (*(reg32 *) ModbusUART_SCB__UART_RX_CTRL)
#define ModbusUART_UART_RX_CTRL_PTR       ( (reg32 *) ModbusUART_SCB__UART_RX_CTRL)

#define ModbusUART_UART_RX_STATUS_REG     (*(reg32 *) ModbusUART_SCB__UART_RX_STATUS)
#define ModbusUART_UART_RX_STATUS_PTR     ( (reg32 *) ModbusUART_SCB__UART_RX_STATUS)

#define ModbusUART_I2C_CTRL_REG           (*(reg32 *) ModbusUART_SCB__I2C_CTRL)
#define ModbusUART_I2C_CTRL_PTR           ( (reg32 *) ModbusUART_SCB__I2C_CTRL)

#define ModbusUART_I2C_STATUS_REG         (*(reg32 *) ModbusUART_SCB__I2C_STATUS)
#define ModbusUART_I2C_STATUS_PTR         ( (reg32 *) ModbusUART_SCB__I2C_STATUS)

#define ModbusUART_I2C_MASTER_CMD_REG     (*(reg32 *) ModbusUART_SCB__I2C_M_CMD)
#define ModbusUART_I2C_MASTER_CMD_PTR     ( (reg32 *) ModbusUART_SCB__I2C_M_CMD)

#define ModbusUART_I2C_SLAVE_CMD_REG      (*(reg32 *) ModbusUART_SCB__I2C_S_CMD)
#define ModbusUART_I2C_SLAVE_CMD_PTR      ( (reg32 *) ModbusUART_SCB__I2C_S_CMD)

#define ModbusUART_I2C_CFG_REG            (*(reg32 *) ModbusUART_SCB__I2C_CFG)
#define ModbusUART_I2C_CFG_PTR            ( (reg32 *) ModbusUART_SCB__I2C_CFG)

#define ModbusUART_TX_CTRL_REG            (*(reg32 *) ModbusUART_SCB__TX_CTRL)
#define ModbusUART_TX_CTRL_PTR            ( (reg32 *) ModbusUART_SCB__TX_CTRL)

#define ModbusUART_TX_FIFO_CTRL_REG       (*(reg32 *) ModbusUART_SCB__TX_FIFO_CTRL)
#define ModbusUART_TX_FIFO_CTRL_PTR       ( (reg32 *) ModbusUART_SCB__TX_FIFO_CTRL)

#define ModbusUART_TX_FIFO_STATUS_REG     (*(reg32 *) ModbusUART_SCB__TX_FIFO_STATUS)
#define ModbusUART_TX_FIFO_STATUS_PTR     ( (reg32 *) ModbusUART_SCB__TX_FIFO_STATUS)

#define ModbusUART_TX_FIFO_WR_REG         (*(reg32 *) ModbusUART_SCB__TX_FIFO_WR)
#define ModbusUART_TX_FIFO_WR_PTR         ( (reg32 *) ModbusUART_SCB__TX_FIFO_WR)

#define ModbusUART_RX_CTRL_REG            (*(reg32 *) ModbusUART_SCB__RX_CTRL)
#define ModbusUART_RX_CTRL_PTR            ( (reg32 *) ModbusUART_SCB__RX_CTRL)

#define ModbusUART_RX_FIFO_CTRL_REG       (*(reg32 *) ModbusUART_SCB__RX_FIFO_CTRL)
#define ModbusUART_RX_FIFO_CTRL_PTR       ( (reg32 *) ModbusUART_SCB__RX_FIFO_CTRL)

#define ModbusUART_RX_FIFO_STATUS_REG     (*(reg32 *) ModbusUART_SCB__RX_FIFO_STATUS)
#define ModbusUART_RX_FIFO_STATUS_PTR     ( (reg32 *) ModbusUART_SCB__RX_FIFO_STATUS)

#define ModbusUART_RX_MATCH_REG           (*(reg32 *) ModbusUART_SCB__RX_MATCH)
#define ModbusUART_RX_MATCH_PTR           ( (reg32 *) ModbusUART_SCB__RX_MATCH)

#define ModbusUART_RX_FIFO_RD_REG         (*(reg32 *) ModbusUART_SCB__RX_FIFO_RD)
#define ModbusUART_RX_FIFO_RD_PTR         ( (reg32 *) ModbusUART_SCB__RX_FIFO_RD)

#define ModbusUART_RX_FIFO_RD_SILENT_REG  (*(reg32 *) ModbusUART_SCB__RX_FIFO_RD_SILENT)
#define ModbusUART_RX_FIFO_RD_SILENT_PTR  ( (reg32 *) ModbusUART_SCB__RX_FIFO_RD_SILENT)

#define ModbusUART_EZBUF_DATA00_REG       (*(reg32 *) ModbusUART_SCB__EZ_DATA00)
#define ModbusUART_EZBUF_DATA00_PTR       ( (reg32 *) ModbusUART_SCB__EZ_DATA00)

#define ModbusUART_INTR_CAUSE_REG         (*(reg32 *) ModbusUART_SCB__INTR_CAUSE)
#define ModbusUART_INTR_CAUSE_PTR         ( (reg32 *) ModbusUART_SCB__INTR_CAUSE)

#define ModbusUART_INTR_I2C_EC_REG        (*(reg32 *) ModbusUART_SCB__INTR_I2C_EC)
#define ModbusUART_INTR_I2C_EC_PTR        ( (reg32 *) ModbusUART_SCB__INTR_I2C_EC)

#define ModbusUART_INTR_I2C_EC_MASK_REG   (*(reg32 *) ModbusUART_SCB__INTR_I2C_EC_MASK)
#define ModbusUART_INTR_I2C_EC_MASK_PTR   ( (reg32 *) ModbusUART_SCB__INTR_I2C_EC_MASK)

#define ModbusUART_INTR_I2C_EC_MASKED_REG (*(reg32 *) ModbusUART_SCB__INTR_I2C_EC_MASKED)
#define ModbusUART_INTR_I2C_EC_MASKED_PTR ( (reg32 *) ModbusUART_SCB__INTR_I2C_EC_MASKED)

#define ModbusUART_INTR_SPI_EC_REG        (*(reg32 *) ModbusUART_SCB__INTR_SPI_EC)
#define ModbusUART_INTR_SPI_EC_PTR        ( (reg32 *) ModbusUART_SCB__INTR_SPI_EC)

#define ModbusUART_INTR_SPI_EC_MASK_REG   (*(reg32 *) ModbusUART_SCB__INTR_SPI_EC_MASK)
#define ModbusUART_INTR_SPI_EC_MASK_PTR   ( (reg32 *) ModbusUART_SCB__INTR_SPI_EC_MASK)

#define ModbusUART_INTR_SPI_EC_MASKED_REG (*(reg32 *) ModbusUART_SCB__INTR_SPI_EC_MASKED)
#define ModbusUART_INTR_SPI_EC_MASKED_PTR ( (reg32 *) ModbusUART_SCB__INTR_SPI_EC_MASKED)

#define ModbusUART_INTR_MASTER_REG        (*(reg32 *) ModbusUART_SCB__INTR_M)
#define ModbusUART_INTR_MASTER_PTR        ( (reg32 *) ModbusUART_SCB__INTR_M)

#define ModbusUART_INTR_MASTER_SET_REG    (*(reg32 *) ModbusUART_SCB__INTR_M_SET)
#define ModbusUART_INTR_MASTER_SET_PTR    ( (reg32 *) ModbusUART_SCB__INTR_M_SET)

#define ModbusUART_INTR_MASTER_MASK_REG   (*(reg32 *) ModbusUART_SCB__INTR_M_MASK)
#define ModbusUART_INTR_MASTER_MASK_PTR   ( (reg32 *) ModbusUART_SCB__INTR_M_MASK)

#define ModbusUART_INTR_MASTER_MASKED_REG (*(reg32 *) ModbusUART_SCB__INTR_M_MASKED)
#define ModbusUART_INTR_MASTER_MASKED_PTR ( (reg32 *) ModbusUART_SCB__INTR_M_MASKED)

#define ModbusUART_INTR_SLAVE_REG         (*(reg32 *) ModbusUART_SCB__INTR_S)
#define ModbusUART_INTR_SLAVE_PTR         ( (reg32 *) ModbusUART_SCB__INTR_S)

#define ModbusUART_INTR_SLAVE_SET_REG     (*(reg32 *) ModbusUART_SCB__INTR_S_SET)
#define ModbusUART_INTR_SLAVE_SET_PTR     ( (reg32 *) ModbusUART_SCB__INTR_S_SET)

#define ModbusUART_INTR_SLAVE_MASK_REG    (*(reg32 *) ModbusUART_SCB__INTR_S_MASK)
#define ModbusUART_INTR_SLAVE_MASK_PTR    ( (reg32 *) ModbusUART_SCB__INTR_S_MASK)

#define ModbusUART_INTR_SLAVE_MASKED_REG  (*(reg32 *) ModbusUART_SCB__INTR_S_MASKED)
#define ModbusUART_INTR_SLAVE_MASKED_PTR  ( (reg32 *) ModbusUART_SCB__INTR_S_MASKED)

#define ModbusUART_INTR_TX_REG            (*(reg32 *) ModbusUART_SCB__INTR_TX)
#define ModbusUART_INTR_TX_PTR            ( (reg32 *) ModbusUART_SCB__INTR_TX)

#define ModbusUART_INTR_TX_SET_REG        (*(reg32 *) ModbusUART_SCB__INTR_TX_SET)
#define ModbusUART_INTR_TX_SET_PTR        ( (reg32 *) ModbusUART_SCB__INTR_TX_SET)

#define ModbusUART_INTR_TX_MASK_REG       (*(reg32 *) ModbusUART_SCB__INTR_TX_MASK)
#define ModbusUART_INTR_TX_MASK_PTR       ( (reg32 *) ModbusUART_SCB__INTR_TX_MASK)

#define ModbusUART_INTR_TX_MASKED_REG     (*(reg32 *) ModbusUART_SCB__INTR_TX_MASKED)
#define ModbusUART_INTR_TX_MASKED_PTR     ( (reg32 *) ModbusUART_SCB__INTR_TX_MASKED)

#define ModbusUART_INTR_RX_REG            (*(reg32 *) ModbusUART_SCB__INTR_RX)
#define ModbusUART_INTR_RX_PTR            ( (reg32 *) ModbusUART_SCB__INTR_RX)

#define ModbusUART_INTR_RX_SET_REG        (*(reg32 *) ModbusUART_SCB__INTR_RX_SET)
#define ModbusUART_INTR_RX_SET_PTR        ( (reg32 *) ModbusUART_SCB__INTR_RX_SET)

#define ModbusUART_INTR_RX_MASK_REG       (*(reg32 *) ModbusUART_SCB__INTR_RX_MASK)
#define ModbusUART_INTR_RX_MASK_PTR       ( (reg32 *) ModbusUART_SCB__INTR_RX_MASK)

#define ModbusUART_INTR_RX_MASKED_REG     (*(reg32 *) ModbusUART_SCB__INTR_RX_MASKED)
#define ModbusUART_INTR_RX_MASKED_PTR     ( (reg32 *) ModbusUART_SCB__INTR_RX_MASKED)


/***************************************
*        Registers Constants
***************************************/

/* ModbusUART_CTRL */
#define ModbusUART_CTRL_OVS_POS           (0u)  /* [3:0]   Oversampling factor                 */
#define ModbusUART_CTRL_EC_AM_MODE_POS    (8u)  /* [8]     Externally clocked address match    */
#define ModbusUART_CTRL_EC_OP_MODE_POS    (9u)  /* [9]     Externally clocked operation mode   */
#define ModbusUART_CTRL_EZBUF_MODE_POS    (10u) /* [10]    EZ buffer is enabled                */
#define ModbusUART_CTRL_ADDR_ACCEPT_POS   (16u) /* [16]    Put matched address in RX FIFO      */
#define ModbusUART_CTRL_BLOCK_POS         (17u) /* [17]    Ext and Int logic to resolve colide */
#define ModbusUART_CTRL_MODE_POS          (24u) /* [25:24] Operation mode                      */
#define ModbusUART_CTRL_ENABLED_POS       (31u) /* [31]    Enable SCB block                    */
#define ModbusUART_CTRL_OVS_MASK          ((uint32) 0x0Fu)
#define ModbusUART_CTRL_EC_AM_MODE        ((uint32) ((uint32) 0x01u << ModbusUART_CTRL_EC_AM_MODE_POS))
#define ModbusUART_CTRL_EC_OP_MODE        ((uint32) ((uint32) 0x01u << ModbusUART_CTRL_EC_OP_MODE_POS))
#define ModbusUART_CTRL_EZBUF_MODE        ((uint32) ((uint32) 0x01u << ModbusUART_CTRL_EZBUF_MODE_POS))
#define ModbusUART_CTRL_ADDR_ACCEPT       ((uint32) ((uint32) 0x01u << ModbusUART_CTRL_ADDR_ACCEPT_POS))
#define ModbusUART_CTRL_BLOCK             ((uint32) ((uint32) 0x01u << ModbusUART_CTRL_BLOCK_POS))
#define ModbusUART_CTRL_MODE_MASK         ((uint32) ((uint32) 0x03u << ModbusUART_CTRL_MODE_POS))
#define ModbusUART_CTRL_MODE_I2C          ((uint32)  0x00u)
#define ModbusUART_CTRL_MODE_SPI          ((uint32) ((uint32) 0x01u << ModbusUART_CTRL_MODE_POS))
#define ModbusUART_CTRL_MODE_UART         ((uint32) ((uint32) 0x02u << ModbusUART_CTRL_MODE_POS))
#define ModbusUART_CTRL_ENABLED           ((uint32) ((uint32) 0x01u << ModbusUART_CTRL_ENABLED_POS))


/* ModbusUART_STATUS_REG */
#define ModbusUART_STATUS_EC_BUSY_POS     (0u)  /* [0] Bus busy. Externaly clocked loigc access to EZ memory */
#define ModbusUART_STATUS_EC_BUSY         ((uint32) 0x0Fu)


/* ModbusUART_SPI_CTRL_REG  */
#define ModbusUART_SPI_CTRL_CONTINUOUS_POS        (0u)  /* [0]     Continuous or Separated SPI data transfers */
#define ModbusUART_SPI_CTRL_SELECT_PRECEDE_POS    (1u)  /* [1]     Precedes or coincides start of data frame  */
#define ModbusUART_SPI_CTRL_CPHA_POS              (2u)  /* [2]     SCLK phase                                 */
#define ModbusUART_SPI_CTRL_CPOL_POS              (3u)  /* [3]     SCLK polarity                              */
#define ModbusUART_SPI_CTRL_LATE_MISO_SAMPLE_POS  (4u)  /* [4]     Late MISO sample enabled                   */
#define ModbusUART_SPI_CTRL_LOOPBACK_POS          (16u) /* [16]    Local loopback control enabled             */
#define ModbusUART_SPI_CTRL_MODE_POS              (24u) /* [25:24] Submode of SPI operation                   */
#define ModbusUART_SPI_CTRL_SLAVE_SELECT_POS      (26u) /* [27:26] Selects SPI SS signal                      */
#define ModbusUART_SPI_CTRL_MASTER_MODE_POS       (31u) /* [31]    Master mode enabled                        */
#define ModbusUART_SPI_CTRL_CONTINUOUS            ((uint32) 0x01u)
#define ModbusUART_SPI_CTRL_SELECT_PRECEDE        ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_SPI_CTRL_SELECT_PRECEDE_POS))
#define ModbusUART_SPI_CTRL_SCLK_MODE_MASK        ((uint32) ((uint32) 0x03u << \
                                                                    ModbusUART_SPI_CTRL_CPHA_POS))
#define ModbusUART_SPI_CTRL_CPHA                  ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_SPI_CTRL_CPHA_POS))
#define ModbusUART_SPI_CTRL_CPOL                  ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_SPI_CTRL_CPOL_POS))
#define ModbusUART_SPI_CTRL_LATE_MISO_SAMPLE      ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_SPI_CTRL_LATE_MISO_SAMPLE_POS))
#define ModbusUART_SPI_CTRL_LOOPBACK              ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_SPI_CTRL_LOOPBACK_POS))
#define ModbusUART_SPI_CTRL_MODE_MASK             ((uint32) ((uint32) 0x03u << \
                                                                    ModbusUART_SPI_CTRL_MODE_POS))
#define ModbusUART_SPI_CTRL_MODE_MOTOROLA         ((uint32) 0x00u)
#define ModbusUART_SPI_CTRL_MODE_TI               ((uint32) ((uint32) 0x01u << ModbusUART_CTRL_MODE_POS))
#define ModbusUART_SPI_CTRL_MODE_NS               ((uint32) ((uint32) 0x02u << ModbusUART_CTRL_MODE_POS))
#define ModbusUART_SPI_CTRL_SLAVE_SELECT_MASK     ((uint32) ((uint32) 0x03u << \
                                                                    ModbusUART_SPI_CTRL_SLAVE_SELECT_POS))
#define ModbusUART_SPI_CTRL_SLAVE_SELECT0         ((uint32) 0x00u)
#define ModbusUART_SPI_CTRL_SLAVE_SELECT1         ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_SPI_CTRL_SLAVE_SELECT_POS))
#define ModbusUART_SPI_CTRL_SLAVE_SELECT2         ((uint32) ((uint32) 0x02u << \
                                                                    ModbusUART_SPI_CTRL_SLAVE_SELECT_POS))
#define ModbusUART_SPI_CTRL_SLAVE_SELECT3         ((uint32) ((uint32) 0x03u << \
                                                                    ModbusUART_SPI_CTRL_SLAVE_SELECT_POS))
#define ModbusUART_SPI_CTRL_MASTER                ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_SPI_CTRL_MASTER_MODE_POS))
#define ModbusUART_SPI_CTRL_SLAVE                 ((uint32) 0x00u)


/* ModbusUART_SPI_STATUS_REG  */
#define ModbusUART_SPI_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy - slave selected */
#define ModbusUART_SPI_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EzAddress                 */
#define ModbusUART_SPI_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define ModbusUART_SPI_STATUS_EZBUF_ADDR_MASK    ((uint32) ((uint32) 0xFFu << \
                                                                    ModbusUART_I2C_STATUS_EZBUF_ADDR_POS))


/* ModbusUART_UART_CTRL */
#define ModbusUART_UART_CTRL_LOOPBACK_POS         (16u) /* [16] Loopback     */
#define ModbusUART_UART_CTRL_MODE_POS             (24u) /* [24] UART subMode */
#define ModbusUART_UART_CTRL_LOOPBACK             ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_UART_CTRL_LOOPBACK_POS))
#define ModbusUART_UART_CTRL_MODE_UART_STD        ((uint32) 0x00u)
#define ModbusUART_UART_CTRL_MODE_UART_SMARTCARD  ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_UART_CTRL_MODE_POS))
#define ModbusUART_UART_CTRL_MODE_UART_IRDA       ((uint32) ((uint32) 0x02u << \
                                                                        ModbusUART_UART_CTRL_MODE_POS))
#define ModbusUART_UART_CTRL_MODE_MASK            ((uint32) ((uint32) 0x03u << \
                                                                        ModbusUART_UART_CTRL_MODE_POS))


/* ModbusUART_UART_TX_CTRL */
#define ModbusUART_UART_TX_CTRL_STOP_BITS_POS         (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period */
#define ModbusUART_UART_TX_CTRL_PARITY_POS            (4u)  /* [4]   Parity bit                              */
#define ModbusUART_UART_TX_CTRL_PARITY_ENABLED_POS    (5u)  /* [5]   Parity enable                           */
#define ModbusUART_UART_TX_CTRL_RETRY_ON_NACK_POS     (8u)  /* [8]   Smart Card: re-send frame on NACK       */
#define ModbusUART_UART_TX_CTRL_ONE_STOP_BIT          ((uint32) 0x01u)
#define ModbusUART_UART_TX_CTRL_ONE_HALF_STOP_BITS    ((uint32) 0x02u)
#define ModbusUART_UART_TX_CTRL_TWO_STOP_BITS         ((uint32) 0x03u)
#define ModbusUART_UART_TX_CTRL_STOP_BITS_MASK        ((uint32) 0x07u)
#define ModbusUART_UART_TX_CTRL_PARITY                ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_UART_TX_CTRL_PARITY_POS))
#define ModbusUART_UART_TX_CTRL_PARITY_ENABLED        ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_UART_TX_CTRL_PARITY_ENABLED_POS))
#define ModbusUART_UART_TX_CTRL_RETRY_ON_NACK         ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_UART_TX_CTRL_RETRY_ON_NACK_POS))


/* ModbusUART_UART_RX_CTRL */
#define ModbusUART_UART_RX_CTRL_STOP_BITS_POS             (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 prd   */
#define ModbusUART_UART_RX_CTRL_PARITY_POS                (4u)  /* [4]   Parity bit                             */
#define ModbusUART_UART_RX_CTRL_PARITY_ENABLED_POS        (5u)  /* [5]   Parity enable                          */
#define ModbusUART_UART_RX_CTRL_POLARITY_POS              (6u)  /* [6]   IrDA: inverts polarity of RX signal    */
#define ModbusUART_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS    (8u)  /* [8]   Drop and lost RX FIFO on parity error  */
#define ModbusUART_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS     (9u)  /* [9]   Drop and lost RX FIFO on frame error   */
#define ModbusUART_UART_RX_CTRL_MP_MODE_POS               (10u) /* [10]  Multi-processor mode                   */
#define ModbusUART_UART_RX_CTRL_LIN_MODE_POS              (12u) /* [12]  Lin mode: applicable for UART Standart */
#define ModbusUART_UART_RX_CTRL_SKIP_START_POS            (13u) /* [13]  Skip start not: only for UART Standart */
#define ModbusUART_UART_RX_CTRL_BREAK_WIDTH_POS           (16u) /* [19:16]  Break width: (Break width + 1)      */
#define ModbusUART_UART_TX_CTRL_ONE_STOP_BIT              ((uint32) 0x01u)
#define ModbusUART_UART_TX_CTRL_ONE_HALF_STOP_BITS        ((uint32) 0x02u)
#define ModbusUART_UART_TX_CTRL_TWO_STOP_BITS             ((uint32) 0x03u)
#define ModbusUART_UART_RX_CTRL_STOP_BITS_MASK            ((uint32) 0x07u)
#define ModbusUART_UART_RX_CTRL_PARITY                    ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_UART_RX_CTRL_PARITY_POS))
#define ModbusUART_UART_RX_CTRL_PARITY_ENABLED            ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_UART_RX_CTRL_PARITY_ENABLED_POS))
#define ModbusUART_UART_RX_CTRL_POLARITY                  ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_UART_RX_CTRL_POLARITY_POS))
#define ModbusUART_UART_RX_CTRL_DROP_ON_PARITY_ERR        ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS))
#define ModbusUART_UART_RX_CTRL_DROP_ON_FRAME_ERR         ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS))
#define ModbusUART_UART_RX_CTRL_MP_MODE                   ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_UART_RX_CTRL_MP_MODE_POS))
#define ModbusUART_UART_RX_CTRL_LIN_MODE                  ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_UART_RX_CTRL_LIN_MODE_POS))
#define ModbusUART_UART_RX_CTRL_SKIP_START                ((uint32) ((uint32) 0x01u << \
                                                                  ModbusUART_UART_RX_CTRL_SKIP_START_POS))
#define ModbusUART_UART_RX_CTRL_BREAK_WIDTH_MASK          ((uint32) ((uint32) 0x0Fu << \
                                                                  ModbusUART_UART_RX_CTRL_BREAK_WIDTH_POS))

/* ModbusUART_UART_RX_STATUS_REG */
#define ModbusUART_UART_RX_STATUS_BR_COUNTER_POS     (0u)  /* [11:0] Baute Rate counter */
#define ModbusUART_UART_RX_STATUS_BR_COUNTER_MASK    ((uint32) 0xFFFu)


/* ModbusUART_I2C_CTRL */
#define ModbusUART_I2C_CTRL_HIGH_PHASE_OVS_POS           (0u)   /* [3:0] Oversampling factor high: masrer only */
#define ModbusUART_I2C_CTRL_LOW_PHASE_OVS_POS            (4u)   /* [7:4] Oversampling factor low:  masrer only */
#define ModbusUART_I2C_CTRL_M_READY_DATA_ACK_POS         (8u)   /* [8]   Master ACKs data wgile RX FIFO != FULL*/
#define ModbusUART_I2C_CTRL_M_NOT_READY_DATA_NACK_POS    (9u)   /* [9]   Master NACKs data if RX FIFO ==  FULL */
#define ModbusUART_I2C_CTRL_S_GENERAL_IGNORE_POS         (11u)  /* [11]  Slave ignores General call            */
#define ModbusUART_I2C_CTRL_S_READY_ADDR_ACK_POS         (12u)  /* [12]  Slave ACKs Address if RX FIFO != FULL */
#define ModbusUART_I2C_CTRL_S_READY_DATA_ACK_POS         (13u)  /* [13]  Slave ACKs data while RX FIFO == FULL */
#define ModbusUART_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS    (14u)  /* [14]  Slave NACKs address if RX FIFO == FULL*/
#define ModbusUART_I2C_CTRL_S_NOT_READY_DATA_NACK_POS    (15u)  /* [15]  Slave NACKs data if RX FIFO is  FULL  */
#define ModbusUART_I2C_CTRL_LOOPBACK_POS                 (16u)  /* [16]  Loopback                              */
#define ModbusUART_I2C_CTRL_SLAVE_MODE_POS               (30u)  /* [30]  Slave mode enabled                    */
#define ModbusUART_I2C_CTRL_MASTER_MODE_POS              (31u)  /* [31]  Master mode enabled                   */
#define ModbusUART_I2C_CTRL_HIGH_PHASE_OVS_MASK  ((uint32) 0x0Fu)
#define ModbusUART_I2C_CTRL_LOW_PHASE_OVS_MASK   ((uint32) ((uint32) 0x0Fu << \
                                                                ModbusUART_I2C_CTRL_LOW_PHASE_OVS_POS))
#define ModbusUART_I2C_CTRL_M_READY_DATA_ACK      ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_CTRL_M_READY_DATA_ACK_POS))
#define ModbusUART_I2C_CTRL_M_NOT_READY_DATA_NACK ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_CTRL_M_NOT_READY_DATA_NACK_POS))
#define ModbusUART_I2C_CTRL_S_GENERAL_IGNORE      ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_CTRL_S_GENERAL_IGNORE_POS))
#define ModbusUART_I2C_CTRL_S_READY_ADDR_ACK      ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_CTRL_S_READY_ADDR_ACK_POS))
#define ModbusUART_I2C_CTRL_S_READY_DATA_ACK      ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_CTRL_S_READY_DATA_ACK_POS))
#define ModbusUART_I2C_CTRL_S_NOT_READY_ADDR_NACK ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS))
#define ModbusUART_I2C_CTRL_S_NOT_READY_DATA_NACK ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_CTRL_S_NOT_READY_DATA_NACK_POS))
#define ModbusUART_I2C_CTRL_LOOPBACK              ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_CTRL_LOOPBACK_POS))
#define ModbusUART_I2C_CTRL_SLAVE_MODE            ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_CTRL_SLAVE_MODE_POS))
#define ModbusUART_I2C_CTRL_MASTER_MODE           ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_CTRL_MASTER_MODE_POS))
#define ModbusUART_I2C_CTRL_SLAVE_MASTER_MODE_MASK    ((uint32) ((uint32) 0x03u << \
                                                                ModbusUART_I2C_CTRL_SLAVE_MODE_POS))


/* ModbusUART_I2C_STATUS_REG  */
#define ModbusUART_I2C_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy: internally clocked */
#define ModbusUART_I2C_STATUS_S_READ_POS      (4u)  /* [4]    Slave is read by master      */
#define ModbusUART_I2C_STATUS_M_READ_POS      (5u)  /* [5]    Master reads Slave           */
#define ModbusUART_I2C_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EZAddress                    */
#define ModbusUART_I2C_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define ModbusUART_I2C_STATUS_S_READ          ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_I2C_STATUS_S_READ_POS))
#define ModbusUART_I2C_STATUS_M_READ          ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_I2C_STATUS_M_READ_POS))
#define ModbusUART_I2C_STATUS_EZBUF_ADDR_MASK ((uint32) ((uint32) 0xFFu << \
                                                                    ModbusUART_I2C_STATUS_EZBUF_ADDR_POS))


/* ModbusUART_I2C_MASTER_CMD_REG */
#define ModbusUART_I2C_MASTER_CMD_M_START_POS             (0u)  /* [0] Master generate Start                */
#define ModbusUART_I2C_MASTER_CMD_M_START_ON_IDLE_POS     (1u)  /* [1] Master generate Start if bus is free */
#define ModbusUART_I2C_MASTER_CMD_M_ACK_POS               (2u)  /* [2] Master generate ACK                  */
#define ModbusUART_I2C_MASTER_CMD_M_NACK_POS              (3u)  /* [3] Master generate NACK                 */
#define ModbusUART_I2C_MASTER_CMD_M_STOP_POS              (4u)  /* [4] Master generate Stop                 */
#define ModbusUART_I2C_MASTER_CMD_M_START         ((uint32) 0x01u)
#define ModbusUART_I2C_MASTER_CMD_M_START_ON_IDLE ((uint32) ((uint32) 0x01u << \
                                                                   ModbusUART_I2C_MASTER_CMD_M_START_ON_IDLE_POS))
#define ModbusUART_I2C_MASTER_CMD_M_ACK           ((uint32) ((uint32) 0x01u << \
                                                                   ModbusUART_I2C_MASTER_CMD_M_ACK_POS))
#define ModbusUART_I2C_MASTER_CMD_M_NACK          ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_I2C_MASTER_CMD_M_NACK_POS))
#define ModbusUART_I2C_MASTER_CMD_M_STOP          ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_I2C_MASTER_CMD_M_STOP_POS))


/* ModbusUART_I2C_SLAVE_CMD_REG  */
#define ModbusUART_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define ModbusUART_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define ModbusUART_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define ModbusUART_I2C_SLAVE_CMD_S_NACK       ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_SLAVE_CMD_S_NACK_POS))

#define ModbusUART_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define ModbusUART_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define ModbusUART_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define ModbusUART_I2C_SLAVE_CMD_S_NACK       ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_SLAVE_CMD_S_NACK_POS))
/* ModbusUART_I2C_CFG  */
#define ModbusUART_I2C_CFG_SDA_FILT_HYS_POS           (0u)  /* [1:0]   Trim bits for the I2C SDA filter         */
#define ModbusUART_I2C_CFG_SDA_FILT_TRIM_POS          (2u)  /* [3:2]   Trim bits for the I2C SDA filter         */
#define ModbusUART_I2C_CFG_SCL_FILT_HYS_POS           (4u)  /* [5:4]   Trim bits for the I2C SCL filter         */
#define ModbusUART_I2C_CFG_SCL_FILT_TRIM_POS          (6u)  /* [7:6]   Trim bits for the I2C SCL filter         */
#define ModbusUART_I2C_CFG_SDA_FILT_OUT_HYS_POS       (8u)  /* [9:8]   Trim bits for I2C SDA filter output path */
#define ModbusUART_I2C_CFG_SDA_FILT_OUT_TRIM_POS      (10u) /* [11:10] Trim bits for I2C SDA filter output path */
#define ModbusUART_I2C_CFG_SDA_FILT_HS_POS            (16u) /* [16]    '0': 50 ns filter, '1': 10 ns filter     */
#define ModbusUART_I2C_CFG_SDA_FILT_ENABLED_POS       (17u) /* [17]    I2C SDA filter enabled                   */
#define ModbusUART_I2C_CFG_SCL_FILT_HS_POS            (24u) /* [24]    '0': 50 ns filter, '1': 10 ns filter     */
#define ModbusUART_I2C_CFG_SCL_FILT_ENABLED_POS       (25u) /* [25]    I2C SCL filter enabled                   */
#define ModbusUART_I2C_CFG_SDA_FILT_OUT_HS_POS        (26u) /* [26]    '0': 50ns filter, '1': 10 ns filter      */
#define ModbusUART_I2C_CFG_SDA_FILT_OUT_ENABLED_POS   (27u) /* [27]    I2C SDA output delay filter enabled      */
#define ModbusUART_I2C_CFG_SDA_FILT_HYS_MASK          ((uint32) 0x00u)
#define ModbusUART_I2C_CFG_SDA_FILT_TRIM_MASK         ((uint32) ((uint32) 0x03u << \
                                                                ModbusUART_I2C_CFG_SDA_FILT_TRIM_POS))
#define ModbusUART_I2C_CFG_SCL_FILT_HYS_MASK          ((uint32) ((uint32) 0x03u << \
                                                                ModbusUART_I2C_CFG_SCL_FILT_HYS_POS))
#define ModbusUART_I2C_CFG_SCL_FILT_TRIM_MASK         ((uint32) ((uint32) 0x03u << \
                                                                ModbusUART_I2C_CFG_SCL_FILT_TRIM_POS))
#define ModbusUART_I2C_CFG_SDA_FILT_OUT_HYS_MASK      ((uint32) ((uint32) 0x03u << \
                                                                ModbusUART_I2C_CFG_SDA_FILT_OUT_HYS_POS))
#define ModbusUART_I2C_CFG_SDA_FILT_OUT_TRIM_MASK     ((uint32) ((uint32) 0x03u << \
                                                                ModbusUART_I2C_CFG_SDA_FILT_OUT_TRIM_POS))
#define ModbusUART_I2C_CFG_SDA_FILT_HS                ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_CFG_SDA_FILT_HS_POS))
#define ModbusUART_I2C_CFG_SDA_FILT_ENABLED           ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_CFG_SDA_FILT_ENABLED_POS))
#define ModbusUART_I2C_CFG_SCL_FILT_HS                ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_CFG_SCL_FILT_HS_POS))
#define ModbusUART_I2C_CFG_SCL_FILT_ENABLED           ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_CFG_SCL_FILT_ENABLED_POS))
#define ModbusUART_I2C_CFG_SDA_FILT_OUT_HS            ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_CFG_SDA_FILT_OUT_HS_POS))
#define ModbusUART_I2C_CFG_SDA_FILT_OUT_ENABLED       ((uint32) ((uint32) 0x01u << \
                                                                ModbusUART_I2C_CFG_SDA_FILT_OUT_ENABLED_POS))


/* ModbusUART_TX_CTRL_REG */
#define ModbusUART_TX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Dataframe width: (Data width - 1) */
#define ModbusUART_TX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define ModbusUART_TX_CTRL_ENABLED_POS        (31u) /* [31]  Transmitter enabled               */
#define ModbusUART_TX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define ModbusUART_TX_CTRL_MSB_FIRST          ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_TX_CTRL_MSB_FIRST_POS))
#define ModbusUART_TX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define ModbusUART_TX_CTRL_ENABLED            ((uint32) ((uint32) 0x01u << ModbusUART_TX_CTRL_ENABLED_POS))


/* ModbusUART_TX_CTRL_FIFO_REG */
#define ModbusUART_TX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)  /* [2:0] Trigger level                              */
#define ModbusUART_TX_FIFO_CTRL_CLEAR_POS             (16u) /* [16]  Clear TX FIFO: claared after set           */
#define ModbusUART_TX_FIFO_CTRL_FREEZE_POS            (17u) /* [17]  Freeze TX FIFO: HW do not inc read pointer */
#define ModbusUART_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) 0x07u)
#define ModbusUART_TX_FIFO_CTRL_CLEAR                 ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_TX_FIFO_CTRL_CLEAR_POS))
#define ModbusUART_TX_FIFO_CTRL_FREEZE                ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_TX_FIFO_CTRL_FREEZE_POS))


/* ModbusUART_TX_FIFO_STATUS_REG */
#define ModbusUART_TX_FIFO_STATUS_USED_POS    (0u)  /* [3:0]   Amount of entries in TX FIFO */
#define ModbusUART_TX_FIFO_SR_VALID_POS       (15u) /* [15]    Shifter status of TX FIFO    */
#define ModbusUART_TX_FIFO_STATUS_RD_PTR_POS  (16u) /* [18:16] TX FIFO read pointer         */
#define ModbusUART_TX_FIFO_STATUS_WR_PTR_POS  (24u) /* [26:24] TX FIFO write pointer        */
#define ModbusUART_TX_FIFO_STATUS_USED_MASK   ((uint32) 0x0Fu)
#define ModbusUART_TX_FIFO_SR_VALID           ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_TX_FIFO_SR_VALID_POS))
#define ModbusUART_TX_FIFO_STATUS_RD_PTR_MASK ((uint32) ((uint32) 0x07u << \
                                                                    ModbusUART_TX_FIFO_STATUS_RD_PTR_POS))
#define ModbusUART_TX_FIFO_STATUS_WR_PTR_MASK ((uint32) ((uint32) 0x07u << \
                                                                    ModbusUART_TX_FIFO_STATUS_WR_PTR_POS))


/* ModbusUART_TX_FIFO_WR_REG */
#define ModbusUART_TX_FIFO_WR_POS    (0u)  /* [15:0] Data written into TX FIFO */
#define ModbusUART_TX_FIFO_WR_MASK   ((uint32) 0xFFu)


/* ModbusUART_RX_CTRL_REG */
#define ModbusUART_RX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Dataframe width: (Data width - 1) */
#define ModbusUART_RX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define ModbusUART_RX_CTRL_MEDIAN_POS         (9u)  /* [9]   Median filter                     */
#define ModbusUART_RX_CTRL_ENABLED_POS        (31u) /* [31]  Receiver enabled                  */
#define ModbusUART_RX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define ModbusUART_RX_CTRL_MSB_FIRST          ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_RX_CTRL_MSB_FIRST_POS))
#define ModbusUART_RX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define ModbusUART_RX_CTRL_MEDIAN             ((uint32) ((uint32) 0x01u << ModbusUART_RX_CTRL_MEDIAN_POS))
#define ModbusUART_RX_CTRL_ENABLED            ((uint32) ((uint32) 0x01u << ModbusUART_RX_CTRL_ENABLED_POS))


/* ModbusUART_RX_FIFO_CTRL_REG */
#define ModbusUART_RX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)   /* [2:0] Trigger level                            */
#define ModbusUART_RX_FIFO_CTRL_CLEAR_POS             (16u)  /* [16]  Clear RX FIFO: claar after set           */
#define ModbusUART_RX_FIFO_CTRL_FREEZE_POS            (17u)  /* [17]  Freeze RX FIFO: HW writes has not effect */
#define ModbusUART_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) 0x07u)
#define ModbusUART_RX_FIFO_CTRL_CLEAR                 ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_RX_FIFO_CTRL_CLEAR_POS))
#define ModbusUART_RX_FIFO_CTRL_FREEZE                ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_RX_FIFO_CTRL_FREEZE_POS))


/* ModbusUART_RX_FIFO_STATUS_REG */
#define ModbusUART_RX_FIFO_STATUS_USED_POS    (0u)   /* [3:0]   Amount of entries in RX FIFO */
#define ModbusUART_RX_FIFO_SR_VALID_POS       (15u)  /* [15]    Shifter status of RX FIFO    */
#define ModbusUART_RX_FIFO_STATUS_RD_PTR_POS  (16u)  /* [18:16] RX FIFO read pointer         */
#define ModbusUART_RX_FIFO_STATUS_WR_PTR_POS  (24u)  /* [26:24] RX FIFO write pointer        */
#define ModbusUART_RX_FIFO_STATUS_USED_MASK   ((uint32) 0x0Fu)
#define ModbusUART_RX_FIFO_SR_VALID           ((uint32) ((uint32) 0x01u << \
                                                                  ModbusUART_RX_FIFO_SR_VALID_POS))
#define ModbusUART_RX_FIFO_STATUS_RD_PTR_MASK ((uint32) ((uint32) 0x07u << \
                                                                  ModbusUART_RX_FIFO_STATUS_RD_PTR_POS))
#define ModbusUART_RX_FIFO_STATUS_WR_PTR_MASK ((uint32) ((uint32) 0x07u << \
                                                                  ModbusUART_RX_FIFO_STATUS_WR_PTR_POS))


/* ModbusUART_RX_MATCH_REG */
#define ModbusUART_RX_MATCH_ADDR_POS     (0u)  /* [7:0]   Slave address                        */
#define ModbusUART_RX_MATCH_MASK_POS     (16u) /* [23:16] Slave address mask: 0 - doesn't care */
#define ModbusUART_RX_MATCH_ADDR_MASK    ((uint32) 0xFFu)
#define ModbusUART_RX_MATCH_MASK_MASK    ((uint32) ((uint32) 0xFFu << ModbusUART_RX_MATCH_MASK_POS))


/* ModbusUART_RX_FIFO_WR_REG */
#define ModbusUART_RX_FIFO_RD_POS    (0u)  /* [15:0] Data read from RX FIFO */
#define ModbusUART_RX_FIFO_RD_MASK   ((uint32) 0xFFu)


/* ModbusUART_RX_FIFO_RD_SILENT_REG */
#define ModbusUART_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define ModbusUART_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* ModbusUART_RX_FIFO_RD_SILENT_REG */
#define ModbusUART_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define ModbusUART_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* ModbusUART_EZBUF_DATA_REG */
#define ModbusUART_EZBUF_DATA_POS   (0u)  /* [7:0] Data from Ez Memory */
#define ModbusUART_EZBUF_DATA_MASK  ((uint32) 0xFFu)

/*  ModbusUART_INTR_CAUSE_REG */
#define ModbusUART_INTR_CAUSE_MASTER_POS  (0u)  /* [0] Master interrupt active                 */
#define ModbusUART_INTR_CAUSE_SLAVE_POS   (1u)  /* [1] Slave interrupt active                  */
#define ModbusUART_INTR_CAUSE_TX_POS      (2u)  /* [2] Transmitter interrupt active            */
#define ModbusUART_INTR_CAUSE_RX_POS      (3u)  /* [3] Receiver interrupt active               */
#define ModbusUART_INTR_CAUSE_I2C_EC_POS  (4u)  /* [4] Externally clock I2C interrupt active   */
#define ModbusUART_INTR_CAUSE_SPI_EC_POS  (5u)  /* [5] Externally clocked SPI interrupt active */
#define ModbusUART_INTR_CAUSE_MASTER      ((uint32) 0x01u)
#define ModbusUART_INTR_CAUSE_SLAVE       ((uint32) ((uint32) 0x01u << ModbusUART_INTR_CAUSE_SLAVE_POS))
#define ModbusUART_INTR_CAUSE_TX          ((uint32) ((uint32) 0x01u << ModbusUART_INTR_CAUSE_TX_POS))
#define ModbusUART_INTR_CAUSE_RX          ((uint32) ((uint32) 0x01u << ModbusUART_INTR_CAUSE_RX_POS))
#define ModbusUART_INTR_CAUSE_I2C_EC      ((uint32) ((uint32) 0x01u << ModbusUART_INTR_CAUSE_I2C_EC_POS))
#define ModbusUART_INTR_CAUSE_SPI_EC      ((uint32) ((uint32) 0x01u << ModbusUART_INTR_CAUSE_SPI_EC_POS))


/* ModbusUART_INTR_SPI_EC_REG, ModbusUART_INTR_SPI_EC_MASK_REG, ModbusUART_INTR_SPI_EC_MASKED_REG */
#define ModbusUART_INTR_SPI_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define ModbusUART_INTR_SPI_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define ModbusUART_INTR_SPI_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define ModbusUART_INTR_SPI_EC_WAKE_UP              ((uint32) 0x01u)
#define ModbusUART_INTR_SPI_EC_EZBUF_STOP           ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_SPI_EC_EZBUF_STOP_POS))
#define ModbusUART_INTR_SPI_EC_EZBUF_WRITE_STOP     ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_SPI_EC_EZBUF_WRITE_STOP_POS))


/* ModbusUART_INTR_I2C_EC, ModbusUART_INTR_I2C_EC_MASK, ModbusUART_INTR_I2C_EC_MASKED */
#define ModbusUART_INTR_I2C_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define ModbusUART_INTR_I2C_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define ModbusUART_INTR_I2C_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define ModbusUART_INTR_I2C_EC_WAKE_UP              ((uint32) 0x01u)
#define ModbusUART_INTR_I2C_EC_EZBUF_STOP           ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_I2C_EC_EZBUF_STOP_POS))
#define ModbusUART_INTR_I2C_EC_EZBUF_WRITE_STOP     ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_I2C_EC_EZBUF_WRITE_STOP_POS))


/* ModbusUART_INTR_MASTER, ModbusUART_INTR_MASTER_SET,
   ModbusUART_INTR_MASTER_MASK, ModbusUART_INTR_MASTER_MASKED */
#define ModbusUART_INTR_MASTER_I2C_ARB_LOST_POS   (0u)  /* [0] Master lost arbitration                          */
#define ModbusUART_INTR_MASTER_I2C_NACK_POS       (1u)  /* [1] Master receives NACK: address or write to slave  */
#define ModbusUART_INTR_MASTER_I2C_ACK_POS        (2u)  /* [2] Master receives NACK: address or write to slave  */
#define ModbusUART_INTR_MASTER_I2C_STOP_POS       (4u)  /* [4] Master detects the Stop: only self generated Stop*/
#define ModbusUART_INTR_MASTER_I2C_BUS_ERROR_POS  (8u)  /* [8] Master detects bus error: misplaced Start or Stop*/
#define ModbusUART_INTR_MASTER_SPI_DONE_POS       (9u)  /* [9] Master complete trasfer: Only for SPI            */
#define ModbusUART_INTR_MASTER_I2C_ARB_LOST       ((uint32) 0x01u)
#define ModbusUART_INTR_MASTER_I2C_NACK           ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_MASTER_I2C_NACK_POS))
#define ModbusUART_INTR_MASTER_I2C_ACK            ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_MASTER_I2C_ACK_POS))
#define ModbusUART_INTR_MASTER_I2C_STOP           ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_MASTER_I2C_STOP_POS))
#define ModbusUART_INTR_MASTER_I2C_BUS_ERROR      ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_MASTER_I2C_BUS_ERROR_POS))
#define ModbusUART_INTR_MASTER_SPI_DONE           ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_MASTER_SPI_DONE_POS))

/*
* ModbusUART_INTR_SLAVE, ModbusUART_INTR_SLAVE_SET,
* ModbusUART_INTR_SLAVE_MASK, ModbusUART_INTR_SLAVE_MASKED
*/
#define ModbusUART_INTR_SLAVE_I2C_ARB_LOST_POS         (0u)  /* [0]  Slave lost arbitration                   */
#define ModbusUART_INTR_SLAVE_I2C_NACK_POS             (1u)  /* [1]  Slave receives NACK: master reads data   */
#define ModbusUART_INTR_SLAVE_I2C_ACK_POS              (2u)  /* [2]  Slave receives ACK: master reads data    */
#define ModbusUART_INTR_SLAVE_I2C_WRITE_STOP_POS       (3u)  /* [3]  Slave detects end of write transaction   */
#define ModbusUART_INTR_SLAVE_I2C_STOP_POS             (4u)  /* [4]  Slave detects end of transaction intened */
#define ModbusUART_INTR_SLAVE_I2C_START_POS            (5u)  /* [5]  Slave detects Start                      */
#define ModbusUART_INTR_SLAVE_I2C_ADDR_MATCH_POS       (6u)  /* [6]  Slave address matches                    */
#define ModbusUART_INTR_SLAVE_I2C_GENERAL_POS          (7u)  /* [7]  General call received                    */
#define ModbusUART_INTR_SLAVE_I2C_BUS_ERROR_POS        (8u)  /* [8]  Slave detects bus error                  */
#define ModbusUART_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS (9u)  /* [9]  Slave write complete: Only for SPI       */
#define ModbusUART_INTR_SLAVE_SPI_EZBUF_STOP_POS       (10u) /* [10] Slave end of transaciton: Only for SPI   */
#define ModbusUART_INTR_SLAVE_SPI_BUS_ERROR_POS        (11u) /* [11] Slave detects bus error: Only for SPI    */
#define ModbusUART_INTR_SLAVE_I2C_ARB_LOST             ((uint32) 0x01u)
#define ModbusUART_INTR_SLAVE_I2C_NACK                 ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_SLAVE_I2C_NACK_POS))
#define ModbusUART_INTR_SLAVE_I2C_ACK                  ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_SLAVE_I2C_ACK_POS))
#define ModbusUART_INTR_SLAVE_I2C_WRITE_STOP           ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_SLAVE_I2C_WRITE_STOP_POS))
#define ModbusUART_INTR_SLAVE_I2C_STOP                 ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_SLAVE_I2C_STOP_POS))
#define ModbusUART_INTR_SLAVE_I2C_START                ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_SLAVE_I2C_START_POS))
#define ModbusUART_INTR_SLAVE_I2C_ADDR_MATCH           ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_SLAVE_I2C_ADDR_MATCH_POS))
#define ModbusUART_INTR_SLAVE_I2C_GENERAL              ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_SLAVE_I2C_GENERAL_POS))
#define ModbusUART_INTR_SLAVE_I2C_BUS_ERROR            ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_SLAVE_I2C_BUS_ERROR_POS))
#define ModbusUART_INTR_SLAVE_SPI_EZBUF_WRITE_STOP     ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS))
#define ModbusUART_INTR_SLAVE_SPI_EZBUF_STOP           ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_SLAVE_SPI_EZBUF_STOP_POS))
#define ModbusUART_INTR_SLAVE_SPI_BUS_ERROR           ((uint32) ((uint32) 0x01u << \
                                                                    ModbusUART_INTR_SLAVE_SPI_BUS_ERROR_POS))


/*
* ModbusUART_INTR_TX, ModbusUART_INTR_TX_SET,
* ModbusUART_INTR_TX_MASK, ModbusUART_INTR_TX_MASKED
*/
#define ModbusUART_INTR_TX_TRIGGER_POS        (0u)  /* [0]  Trigger on TX FIFO entires                       */
#define ModbusUART_INTR_TX_NOT_FULL_POS       (1u)  /* [1]  TX FIFO is not full                              */
#define ModbusUART_INTR_TX_EMPTY_POS          (4u)  /* [4]  TX FIFO is empty                                 */
#define ModbusUART_INTR_TX_OVERFLOW_POS       (5u)  /* [5]  Attempt to write to a full TX FIFO               */
#define ModbusUART_INTR_TX_UNDERFLOW_POS      (6u)  /* [6]  Attempt to read from an empty TX FIFO            */
#define ModbusUART_INTR_TX_BLOCKED_POS        (7u)  /* [7]  No access to the EZ memory                       */
#define ModbusUART_INTR_TX_UART_NACK_POS      (8u)  /* [8]  UART transmitter received a NACK: SmartCard mode */
#define ModbusUART_INTR_TX_UART_DONE_POS      (9u)  /* [9]  UART transmitter done even                       */
#define ModbusUART_INTR_TX_UART_ARB_LOST_POS  (10u) /* [10] UART lost arbitration: LIN or SmartCard          */
#define ModbusUART_INTR_TX_TRIGGER            ((uint32) 0x01u)
#define ModbusUART_INTR_TX_NOT_FULL           ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_TX_NOT_FULL_POS))
#define ModbusUART_INTR_TX_EMPTY              ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_TX_EMPTY_POS))
#define ModbusUART_INTR_TX_OVERFLOW           ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_TX_OVERFLOW_POS))
#define ModbusUART_INTR_TX_UNDERFLOW          ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_TX_UNDERFLOW_POS))
#define ModbusUART_INTR_TX_BLOCKED            ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_TX_BLOCKED_POS))
#define ModbusUART_INTR_TX_UART_NACK          ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_TX_UART_NACK_POS))
#define ModbusUART_INTR_TX_UART_DONE          ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_TX_UART_DONE_POS))
#define ModbusUART_INTR_TX_UART_ARB_LOST      ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_TX_UART_ARB_LOST_POS))


/*
* ModbusUART_INTR_RX, ModbusUART_INTR_RX_SET,
* ModbusUART_INTR_RX_MASK, ModbusUART_INTR_RX_MASKED
*/
#define ModbusUART_INTR_RX_TRIGGER_POS        (0u)   /* [0]  Trigger on RX FIFO entires            */
#define ModbusUART_INTR_RX_NOT_EMPTY_POS      (2u)   /* [2]  RX FIFO is not empty                  */
#define ModbusUART_INTR_RX_FULL_POS           (3u)   /* [3]  RX FIFO is full                       */
#define ModbusUART_INTR_RX_OVERFLOW_POS       (5u)   /* [5]  Attempt to write to a full RX FIFO    */
#define ModbusUART_INTR_RX_UNDERFLOW_POS      (6u)   /* [6]  Attempt to read from an empty RX FIFO */
#define ModbusUART_INTR_RX_BLOCKED_POS        (7u)   /* [7]  No access to the EZ memory            */
#define ModbusUART_INTR_RX_FRAME_ERROR_POS    (8u)   /* [8]  Frame error in received data frame    */
#define ModbusUART_INTR_RX_PARITY_ERROR_POS   (9u)   /* [9]  Parity error in received data frame   */
#define ModbusUART_INTR_RX_BAUD_DETECT_POS    (10u)  /* [10] LIN baudrate detection is completed   */
#define ModbusUART_INTR_RX_BREAK_DETECT_POS   (11u)  /* [11] Break detection is successful         */
#define ModbusUART_INTR_RX_TRIGGER            ((uint32) 0x01u)
#define ModbusUART_INTR_RX_NOT_EMPTY          ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_RX_NOT_EMPTY_POS))
#define ModbusUART_INTR_RX_FULL               ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_RX_FULL_POS))
#define ModbusUART_INTR_RX_OVERFLOW           ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_RX_OVERFLOW_POS))
#define ModbusUART_INTR_RX_UNDERFLOW          ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_RX_UNDERFLOW_POS))
#define ModbusUART_INTR_RX_BLOCKED            ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_RX_BLOCKED_POS))
#define ModbusUART_INTR_RX_FRAME_ERROR        ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_RX_FRAME_ERROR_POS))
#define ModbusUART_INTR_RX_PARITY_ERROR       ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_RX_PARITY_ERROR_POS))
#define ModbusUART_INTR_RX_BAUD_DETECT        ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_RX_BAUD_DETECT_POS))
#define ModbusUART_INTR_RX_BREAK_DETECT       ((uint32) ((uint32) 0x01u << \
                                                                        ModbusUART_INTR_RX_BREAK_DETECT_POS))


/* Define all interupt soureces */
#define ModbusUART_INTR_I2C_EC_ALL    (ModbusUART_INTR_I2C_EC_WAKE_UP    | \
                                             ModbusUART_INTR_I2C_EC_EZBUF_STOP | \
                                             ModbusUART_INTR_I2C_EC_EZBUF_WRITE_STOP)

#define ModbusUART_INTR_SPI_EC_ALL    (ModbusUART_INTR_SPI_EC_WAKE_UP    | \
                                             ModbusUART_INTR_SPI_EC_EZBUF_STOP | \
                                             ModbusUART_INTR_SPI_EC_EZBUF_WRITE_STOP)

#define ModbusUART_INTR_MASTER_ALL    (ModbusUART_INTR_MASTER_I2C_ARB_LOST  | \
                                             ModbusUART_INTR_MASTER_I2C_NACK      | \
                                             ModbusUART_INTR_MASTER_I2C_ACK       | \
                                             ModbusUART_INTR_MASTER_I2C_STOP      | \
                                             ModbusUART_INTR_MASTER_I2C_BUS_ERROR | \
                                             ModbusUART_INTR_MASTER_SPI_DONE )

#define ModbusUART_INTR_SLAVE_ALL     (ModbusUART_INTR_SLAVE_I2C_ARB_LOST      | \
                                             ModbusUART_INTR_SLAVE_I2C_NACK          | \
                                             ModbusUART_INTR_SLAVE_I2C_ACK           | \
                                             ModbusUART_INTR_SLAVE_I2C_WRITE_STOP    | \
                                             ModbusUART_INTR_SLAVE_I2C_STOP          | \
                                             ModbusUART_INTR_SLAVE_I2C_START         | \
                                             ModbusUART_INTR_SLAVE_I2C_ADDR_MATCH    | \
                                             ModbusUART_INTR_SLAVE_I2C_GENERAL       | \
                                             ModbusUART_INTR_SLAVE_I2C_BUS_ERROR     | \
                                             ModbusUART_INTR_SLAVE_SPI_EZBUF_WRITE_STOP | \
                                             ModbusUART_INTR_SLAVE_SPI_EZBUF_STOP       | \
                                             ModbusUART_INTR_SLAVE_SPI_BUS_ERROR)

#define ModbusUART_INTR_TX_ALL        (ModbusUART_INTR_TX_TRIGGER   | \
                                             ModbusUART_INTR_TX_NOT_FULL  | \
                                             ModbusUART_INTR_TX_EMPTY     | \
                                             ModbusUART_INTR_TX_OVERFLOW  | \
                                             ModbusUART_INTR_TX_UNDERFLOW | \
                                             ModbusUART_INTR_TX_BLOCKED   | \
                                             ModbusUART_INTR_TX_UART_NACK | \
                                             ModbusUART_INTR_TX_UART_DONE | \
                                             ModbusUART_INTR_TX_UART_ARB_LOST)

#define ModbusUART_INTR_RX_ALL        (ModbusUART_INTR_RX_TRIGGER      | \
                                             ModbusUART_INTR_RX_NOT_EMPTY    | \
                                             ModbusUART_INTR_RX_FULL         | \
                                             ModbusUART_INTR_RX_OVERFLOW     | \
                                             ModbusUART_INTR_RX_UNDERFLOW    | \
                                             ModbusUART_INTR_RX_BLOCKED      | \
                                             ModbusUART_INTR_RX_FRAME_ERROR  | \
                                             ModbusUART_INTR_RX_PARITY_ERROR | \
                                             ModbusUART_INTR_RX_BAUD_DETECT  | \
                                             ModbusUART_INTR_RX_BREAK_DETECT)

/* General usage HW definitions */
#define ModbusUART_ONE_BYTE_WIDTH (8u)   /* Number of bits in one byte           */
#define ModbusUART_FIFO_SIZE      (8u)   /* Size of TX or RX FIFO: defined by HW */
#define ModbusUART_EZBUFFER_SIZE  (32u)  /* EZ Buffer size: defined by HW        */

/* I2C and EZI2C slave address defines */
#define ModbusUART_I2C_SLAVE_ADDR_POS    (0x01u)    /* 7-bit address shift */
#define ModbusUART_I2C_SLAVE_ADDR_MASK   (0xFEu)    /* 8-bit address mask */

/* OVS constants for IrDA Low Power operation */
#define ModbusUART_CTRL_OVS_IRDA_LP_OVS16     (0x00u)
#define ModbusUART_CTRL_OVS_IRDA_LP_OVS32     (0x01u)
#define ModbusUART_CTRL_OVS_IRDA_LP_OVS48     (0x02u)
#define ModbusUART_CTRL_OVS_IRDA_LP_OVS96     (0x03u)
#define ModbusUART_CTRL_OVS_IRDA_LP_OVS192    (0x04u)
#define ModbusUART_CTRL_OVS_IRDA_LP_OVS768    (0x05u)
#define ModbusUART_CTRL_OVS_IRDA_LP_OVS1536   (0x06u)

/* OVS constant for IrDA */
#define ModbusUART_CTRL_OVS_IRDA_OVS16        (ModbusUART_UART_IRDA_LP_OVS16)


/***************************************
*    SCB Common Macro Definitions
***************************************/

/*
* Re-enables SCB IP: this cause partial reset of IP: state, status, TX and RX FIFOs.
* The triggered interrupts remains set.
*/
#define ModbusUART_SCB_SW_RESET \
                        do{ \
                            ModbusUART_CTRL_REG &= ((uint32) ~ModbusUART_CTRL_ENABLED ); \
                            ModbusUART_CTRL_REG |= ((uint32)  ModbusUART_CTRL_ENABLED ); \
                        }while(0)

/* TX FIFO macro */
#define ModbusUART_CLEAR_TX_FIFO \
                            do{        \
                                ModbusUART_TX_FIFO_CTRL_REG |= ((uint32)  ModbusUART_TX_FIFO_CTRL_CLEAR); \
                                ModbusUART_TX_FIFO_CTRL_REG &= ((uint32) ~ModbusUART_TX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define ModbusUART_GET_TX_FIFO_ENTRIES    (ModbusUART_TX_FIFO_STATUS_REG & \
                                                 ModbusUART_TX_FIFO_STATUS_USED_MASK)

#define ModbusUART_GET_TX_FIFO_SR_VALID   ((0u != (ModbusUART_TX_FIFO_STATUS_REG & \
                                                         ModbusUART_TX_FIFO_SR_VALID)) ? (1u) : (0u))

/* RX FIFO macro */
#define ModbusUART_CLEAR_RX_FIFO \
                            do{        \
                                ModbusUART_RX_FIFO_CTRL_REG |= ((uint32)  ModbusUART_RX_FIFO_CTRL_CLEAR); \
                                ModbusUART_RX_FIFO_CTRL_REG &= ((uint32) ~ModbusUART_RX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define ModbusUART_GET_RX_FIFO_ENTRIES    (ModbusUART_RX_FIFO_STATUS_REG & \
                                                    ModbusUART_RX_FIFO_STATUS_USED_MASK)

#define ModbusUART_GET_RX_FIFO_SR_VALID   ((0u != (ModbusUART_RX_FIFO_STATUS_REG & \
                                                         ModbusUART_RX_FIFO_SR_VALID)) ? (1u) : (0u))

/* Writes interrupt source: set sourceMask bits in ModbusUART_INTR_X_MASK_REG */
#define ModbusUART_WRITE_INTR_I2C_EC_MASK(sourceMask) \
                                                do{         \
                                                    ModbusUART_INTR_I2C_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_WRITE_INTR_SPI_EC_MASK(sourceMask) \
                                                do{         \
                                                    ModbusUART_INTR_SPI_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_WRITE_INTR_MASTER_MASK(sourceMask) \
                                                do{         \
                                                    ModbusUART_INTR_MASTER_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_WRITE_INTR_SLAVE_MASK(sourceMask)  \
                                                do{         \
                                                    ModbusUART_INTR_SLAVE_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_WRITE_INTR_TX_MASK(sourceMask)     \
                                                do{         \
                                                    ModbusUART_INTR_TX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_WRITE_INTR_RX_MASK(sourceMask)     \
                                                do{         \
                                                    ModbusUART_INTR_RX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Enables interrupt source: set sourceMask bits in ModbusUART_INTR_X_MASK_REG */
#define ModbusUART_ENABLE_INTR_I2C_EC(sourceMask) \
                                                do{     \
                                                    ModbusUART_INTR_I2C_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_ENABLE_INTR_SPI_EC(sourceMask) \
                                                do{     \
                                                    ModbusUART_INTR_SPI_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_ENABLE_INTR_MASTER(sourceMask) \
                                                do{     \
                                                    ModbusUART_INTR_MASTER_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_ENABLE_INTR_SLAVE(sourceMask)  \
                                                do{     \
                                                    ModbusUART_INTR_SLAVE_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_ENABLE_INTR_TX(sourceMask)     \
                                                do{     \
                                                    ModbusUART_INTR_TX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_ENABLE_INTR_RX(sourceMask)     \
                                                do{     \
                                                    ModbusUART_INTR_RX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

/* Disables interrupt source: clear sourceMask bits in ModbusUART_INTR_X_MASK_REG */
#define ModbusUART_DISABLE_INTR_I2C_EC(sourceMask) \
                                do{                      \
                                    ModbusUART_INTR_I2C_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define ModbusUART_DISABLE_INTR_SPI_EC(sourceMask) \
                                do{                      \
                                    ModbusUART_INTR_SPI_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)

#define ModbusUART_DISABLE_INTR_MASTER(sourceMask) \
                                do{                      \
                                ModbusUART_INTR_MASTER_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define ModbusUART_DISABLE_INTR_SLAVE(sourceMask) \
                                do{                     \
                                    ModbusUART_INTR_SLAVE_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define ModbusUART_DISABLE_INTR_TX(sourceMask)    \
                                do{                     \
                                    ModbusUART_INTR_TX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)

#define ModbusUART_DISABLE_INTR_RX(sourceMask)    \
                                do{                     \
                                    ModbusUART_INTR_RX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

/* Sets interrupt sources: write sourceMask bits in ModbusUART_INTR_X_SET_REG */
#define ModbusUART_SET_INTR_MASTER(sourceMask)    \
                                                do{     \
                                                    ModbusUART_INTR_MASTER_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_SET_INTR_SLAVE(sourceMask) \
                                                do{ \
                                                    ModbusUART_INTR_SLAVE_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_SET_INTR_TX(sourceMask)    \
                                                do{ \
                                                    ModbusUART_INTR_TX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_SET_INTR_RX(sourceMask)    \
                                                do{ \
                                                    ModbusUART_INTR_RX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Clears interrupt sources: write sourceMask bits in ModbusUART_INTR_X_REG */
#define ModbusUART_CLEAR_INTR_I2C_EC(sourceMask)  \
                                                do{     \
                                                    ModbusUART_INTR_I2C_EC_REG = (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_CLEAR_INTR_SPI_EC(sourceMask)  \
                                                do{     \
                                                    ModbusUART_INTR_SPI_EC_REG = (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_CLEAR_INTR_MASTER(sourceMask)  \
                                                do{     \
                                                    ModbusUART_INTR_MASTER_REG = (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_CLEAR_INTR_SLAVE(sourceMask)   \
                                                do{     \
                                                    ModbusUART_INTR_SLAVE_REG  = (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_CLEAR_INTR_TX(sourceMask)      \
                                                do{     \
                                                    ModbusUART_INTR_TX_REG     = (uint32) (sourceMask); \
                                                }while(0)

#define ModbusUART_CLEAR_INTR_RX(sourceMask)      \
                                                do{     \
                                                    ModbusUART_INTR_RX_REG     = (uint32) (sourceMask); \
                                                }while(0)

/* Return true if sourceMask is set in ModbusUART_INTR_CAUSE_REG */
#define ModbusUART_CHECK_CAUSE_INTR(sourceMask)    (0u != (ModbusUART_INTR_CAUSE_REG & (sourceMask)))

/* Return true if sourceMask is set in  INTR_X_MASKED_REG */
#define ModbusUART_CHECK_INTR_EC_I2C(sourceMask)  (0u != (ModbusUART_INTR_I2C_EC_REG & (sourceMask)))
#define ModbusUART_CHECK_INTR_EC_SPI(sourceMask)  (0u != (ModbusUART_INTR_SPI_EC_REG & (sourceMask)))
#define ModbusUART_CHECK_INTR_MASTER(sourceMask)  (0u != (ModbusUART_INTR_MASTER_REG & (sourceMask)))
#define ModbusUART_CHECK_INTR_SLAVE(sourceMask)   (0u != (ModbusUART_INTR_SLAVE_REG  & (sourceMask)))
#define ModbusUART_CHECK_INTR_TX(sourceMask)      (0u != (ModbusUART_INTR_TX_REG     & (sourceMask)))
#define ModbusUART_CHECK_INTR_RX(sourceMask)      (0u != (ModbusUART_INTR_RX_REG     & (sourceMask)))

/* Return true if sourceMask is set in ModbusUART_INTR_X_MASKED_REG */
#define ModbusUART_CHECK_INTR_I2C_EC_MASKED(sourceMask)   (0u != (ModbusUART_INTR_I2C_EC_MASKED_REG & \
                                                                       (sourceMask)))
#define ModbusUART_CHECK_INTR_SPI_EC_MASKED(sourceMask)   (0u != (ModbusUART_INTR_SPI_EC_MASKED_REG & \
                                                                       (sourceMask)))
#define ModbusUART_CHECK_INTR_MASTER_MASKED(sourceMask)   (0u != (ModbusUART_INTR_MASTER_MASKED_REG & \
                                                                       (sourceMask)))
#define ModbusUART_CHECK_INTR_SLAVE_MASKED(sourceMask)    (0u != (ModbusUART_INTR_SLAVE_MASKED_REG  & \
                                                                       (sourceMask)))
#define ModbusUART_CHECK_INTR_TX_MASKED(sourceMask)       (0u != (ModbusUART_INTR_TX_MASKED_REG     & \
                                                                       (sourceMask)))
#define ModbusUART_CHECK_INTR_RX_MASKED(sourceMask)       (0u != (ModbusUART_INTR_RX_MASKED_REG     & \
                                                                       (sourceMask)))

/* Return true if sourceMask is set in ModbusUART_CTRL_REG: generaly is used to check enable bit */
#define ModbusUART_GET_CTRL_ENABLED    (0u != (ModbusUART_CTRL_REG & ModbusUART_CTRL_ENABLED))

#define ModbusUART_CHECK_SLAVE_AUTO_ADDR_NACK     (0u != (ModbusUART_I2C_CTRL_REG & \
                                                                ModbusUART_I2C_CTRL_S_NOT_READY_DATA_NACK))


/***************************************
*      I2C Macro Definitions
***************************************/

/* Enable auto ACK/NACK */
#define ModbusUART_ENABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                      \
                                ModbusUART_I2C_CTRL_REG |= ModbusUART_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define ModbusUART_ENABLE_SLAVE_AUTO_DATA_ACK \
                            do{                     \
                                ModbusUART_I2C_CTRL_REG |= ModbusUART_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define ModbusUART_ENABLE_SLAVE_AUTO_DATA_NACK \
                            do{                      \
                                ModbusUART_I2C_CTRL_REG |= ModbusUART_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define ModbusUART_ENABLE_MASTER_AUTO_DATA_ACK \
                            do{                      \
                                ModbusUART_I2C_CTRL_REG |= ModbusUART_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define ModbusUART_ENABLE_MASTER_AUTO_DATA_NACK \
                            do{                       \
                                ModbusUART_I2C_CTRL_REG |= ModbusUART_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Disable auto ACK/NACK */
#define ModbusUART_DISABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                       \
                                ModbusUART_I2C_CTRL_REG &= ~ModbusUART_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define ModbusUART_DISABLE_SLAVE_AUTO_DATA_ACK \
                            do{                      \
                                ModbusUART_I2C_CTRL_REG &= ~ModbusUART_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define ModbusUART_DISABLE_SLAVE_AUTO_DATA_NACK \
                            do{                       \
                                ModbusUART_I2C_CTRL_REG &= ~ModbusUART_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define ModbusUART_DISABLE_MASTER_AUTO_DATA_ACK \
                            do{                       \
                                ModbusUART_I2C_CTRL_REG &= ~ModbusUART_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define ModbusUART_DISABLE_MASTER_AUTO_DATA_NACK \
                            do{                        \
                                ModbusUART_I2C_CTRL_REG &= ~ModbusUART_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Enable Slave autoACK/NACK Data */
#define ModbusUART_ENABLE_SLAVE_AUTO_DATA \
                            do{                 \
                                ModbusUART_I2C_CTRL_REG |= (ModbusUART_I2C_CTRL_S_READY_DATA_ACK |      \
                                                                  ModbusUART_I2C_CTRL_S_NOT_READY_DATA_NACK); \
                            }while(0)

/* Disable Slave autoACK/NACK Data */
#define ModbusUART_DISABLE_SLAVE_AUTO_DATA \
                            do{                  \
                                ModbusUART_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(ModbusUART_I2C_CTRL_S_READY_DATA_ACK |       \
                                                                    ModbusUART_I2C_CTRL_S_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Disable Master autoACK/NACK Data */
#define ModbusUART_DISABLE_MASTER_AUTO_DATA \
                            do{                   \
                                ModbusUART_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(ModbusUART_I2C_CTRL_M_READY_DATA_ACK |       \
                                                                    ModbusUART_I2C_CTRL_M_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Master commands */
#define ModbusUART_I2C_MASTER_GENERATE_START \
                            do{                    \
                                ModbusUART_I2C_MASTER_CMD_REG = ModbusUART_I2C_MASTER_CMD_M_START_ON_IDLE; \
                            }while(0)

#define ModbusUART_I2C_MASTER_CLEAR_START \
                            do{                 \
                                ModbusUART_I2C_MASTER_CMD_REG =  ((uint32) 0u); \
                            }while(0)

#define ModbusUART_I2C_MASTER_GENERATE_RESTART ModbusUART_I2CReStartGeneration()

#define ModbusUART_I2C_MASTER_GENERATE_STOP \
                            do{                   \
                                ModbusUART_I2C_MASTER_CMD_REG =                                            \
                                    (ModbusUART_I2C_MASTER_CMD_M_STOP |                                    \
                                        (ModbusUART_CHECK_I2C_STATUS(ModbusUART_I2C_STATUS_M_READ) ? \
                                            (ModbusUART_I2C_MASTER_CMD_M_NACK) : (0u)));                   \
                            }while(0)

#define ModbusUART_I2C_MASTER_GENERATE_ACK \
                            do{                  \
                                ModbusUART_I2C_MASTER_CMD_REG = ModbusUART_I2C_MASTER_CMD_M_ACK; \
                            }while(0)

#define ModbusUART_I2C_MASTER_GENERATE_NACK \
                            do{                   \
                                ModbusUART_I2C_MASTER_CMD_REG = ModbusUART_I2C_MASTER_CMD_M_NACK; \
                            }while(0)

/* Slave comamnds */
#define ModbusUART_I2C_SLAVE_GENERATE_ACK \
                            do{                 \
                                ModbusUART_I2C_SLAVE_CMD_REG = ModbusUART_I2C_SLAVE_CMD_S_ACK; \
                            }while(0)

#define ModbusUART_I2C_SLAVE_GENERATE_NACK \
                            do{                  \
                                ModbusUART_I2C_SLAVE_CMD_REG = ModbusUART_I2C_SLAVE_CMD_S_NACK; \
                            }while(0)


/* Return 8-bit address. The input address should be 7-bits */
#define ModbusUART_GET_I2C_8BIT_ADDRESS(addr) (((uint32) ((uint32) (addr) << \
                                                                    ModbusUART_I2C_SLAVE_ADDR_POS)) & \
                                                                        ModbusUART_I2C_SLAVE_ADDR_MASK)

#define ModbusUART_GET_I2C_7BIT_ADDRESS(addr) ((uint32) (addr) >> ModbusUART_I2C_SLAVE_ADDR_POS)


/* Adjust SDA filter Trim settings */
#define ModbusUART_DEFAULT_I2C_CFG_SDA_FILT_TRIM  (0x02u)
#define ModbusUART_EC_AM_I2C_CFG_SDA_FILT_TRIM    (0x03u)

#define ModbusUART_SET_I2C_CFG_SDA_FILT_TRIM(sdaTrim) \
        do{                                                 \
            ModbusUART_I2C_CFG_REG =                  \
                            ((ModbusUART_I2C_CFG_REG & (uint32) ~ModbusUART_I2C_CFG_SDA_FILT_TRIM_MASK) | \
                             ((uint32) ((uint32) (sdaTrim) <<ModbusUART_I2C_CFG_SDA_FILT_TRIM_POS)));           \
        }while(0)

/* Returns slave select number in SPI_CTRL */
#define ModbusUART_GET_SPI_CTRL_SS(activeSelect) (((uint32) ((uint32) (activeSelect) << \
                                                                    ModbusUART_SPI_CTRL_SLAVE_SELECT_POS)) & \
                                                                        ModbusUART_SPI_CTRL_SLAVE_SELECT_MASK)

/* Returns true if bit is set in ModbusUART_I2C_STATUS_REG */
#define ModbusUART_CHECK_I2C_STATUS(sourceMask)   (0u != (ModbusUART_I2C_STATUS_REG & (sourceMask)))

/* Returns true if bit is set in ModbusUART_SPI_STATUS_REG */
#define ModbusUART_CHECK_SPI_STATUS(sourceMask)   (0u != (ModbusUART_SPI_STATUS_REG & (sourceMask)))


/***************************************
*       SCB Init Macros Definitions
***************************************/

/* ModbusUART_CTRL */
#define ModbusUART_GET_CTRL_OVS(oversample)   ((((uint32) (oversample)) - 1u) & ModbusUART_CTRL_OVS_MASK)

#define ModbusUART_GET_CTRL_EC_OP_MODE(opMode)        ((0u != (opMode)) ? \
                                                                (ModbusUART_CTRL_EC_OP_MODE)  : (0u))

#define ModbusUART_GET_CTRL_EC_AM_MODE(amMode)        ((0u != (amMode)) ? \
                                                                (ModbusUART_CTRL_EC_AM_MODE)  : (0u))

#define ModbusUART_GET_CTRL_BLOCK(block)              ((0u != (block))  ? \
                                                                (ModbusUART_CTRL_BLOCK)       : (0u))

#define ModbusUART_GET_CTRL_ADDR_ACCEPT(acceptAddr)   ((0u != (acceptAddr)) ? \
                                                                (ModbusUART_CTRL_ADDR_ACCEPT) : (0u))

/* ModbusUART_I2C_CTRL */
#define ModbusUART_GET_I2C_CTRL_HIGH_PHASE_OVS(oversampleHigh) (((uint32) (oversampleHigh) - 1u) & \
                                                                        ModbusUART_I2C_CTRL_HIGH_PHASE_OVS_MASK)

#define ModbusUART_GET_I2C_CTRL_LOW_PHASE_OVS(oversampleLow)   (((uint32) (((uint32) (oversampleLow) - 1u) << \
                                                                    ModbusUART_I2C_CTRL_LOW_PHASE_OVS_POS)) &  \
                                                                    ModbusUART_I2C_CTRL_LOW_PHASE_OVS_MASK)

#define ModbusUART_GET_I2C_CTRL_S_NOT_READY_ADDR_NACK(wakeNack) ((0u != (wakeNack)) ? \
                                                            (ModbusUART_I2C_CTRL_S_NOT_READY_ADDR_NACK) : (0u))

#define ModbusUART_GET_I2C_CTRL_SL_MSTR_MODE(mode)    ((uint32) ((uint32)(mode) << \
                                                                    ModbusUART_I2C_CTRL_SLAVE_MODE_POS))

/* ModbusUART_SPI_CTRL */
#define ModbusUART_GET_SPI_CTRL_CONTINUOUS(separate)  ((0u != (separate)) ? \
                                                                (ModbusUART_SPI_CTRL_CONTINUOUS) : (0u))

#define ModbusUART_GET_SPI_CTRL_SELECT_PRECEDE(mode)  ((0u != (mode)) ? \
                                                                      (ModbusUART_SPI_CTRL_SELECT_PRECEDE) : (0u))

#define ModbusUART_GET_SPI_CTRL_SCLK_MODE(mode)       (((uint32) ((uint32) (mode) << \
                                                                        ModbusUART_SPI_CTRL_CPHA_POS)) & \
                                                                        ModbusUART_SPI_CTRL_SCLK_MODE_MASK)

#define ModbusUART_GET_SPI_CTRL_LATE_MISO_SAMPLE(lateMiso) ((0u != (lateMiso)) ? \
                                                                    (ModbusUART_SPI_CTRL_LATE_MISO_SAMPLE) : (0u))

#define ModbusUART_GET_SPI_CTRL_SUB_MODE(mode)        (((uint32) (((uint32) (mode)) << \
                                                                        ModbusUART_SPI_CTRL_MODE_POS)) & \
                                                                        ModbusUART_SPI_CTRL_MODE_MASK)

#define ModbusUART_GET_SPI_CTRL_SLAVE_SELECT(select)  (((uint32) ((uint32) (select) << \
                                                                      ModbusUART_SPI_CTRL_SLAVE_SELECT_POS)) & \
                                                                      ModbusUART_SPI_CTRL_SLAVE_SELECT_MASK)

#define ModbusUART_GET_SPI_CTRL_MASTER_MODE(mode)     ((0u != (mode)) ? \
                                                                (ModbusUART_SPI_CTRL_MASTER) : (0u))

/* ModbusUART_UART_CTRL */
#define ModbusUART_GET_UART_CTRL_MODE(mode)           (((uint32) ((uint32) (mode) << \
                                                                            ModbusUART_UART_CTRL_MODE_POS)) & \
                                                                                ModbusUART_UART_CTRL_MODE_MASK)

/* ModbusUART_UART_RX_CTRL */
#define ModbusUART_GET_UART_RX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                        ModbusUART_UART_RX_CTRL_STOP_BITS_MASK)

#define ModbusUART_GET_UART_RX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                                    (ModbusUART_UART_RX_CTRL_PARITY) : (0u))

#define ModbusUART_GET_UART_RX_CTRL_POLARITY(polarity)    ((0u != (polarity)) ? \
                                                                    (ModbusUART_UART_RX_CTRL_POLARITY) : (0u))

#define ModbusUART_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (ModbusUART_UART_RX_CTRL_DROP_ON_PARITY_ERR) : (0u))

#define ModbusUART_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (ModbusUART_UART_RX_CTRL_DROP_ON_FRAME_ERR) : (0u))

#define ModbusUART_GET_UART_RX_CTRL_MP_MODE(mpMode)   ((0u != (mpMode)) ? \
                                                        (ModbusUART_UART_RX_CTRL_MP_MODE) : (0u))

/* ModbusUART_UART_TX_CTRL */
#define ModbusUART_GET_UART_TX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                ModbusUART_UART_RX_CTRL_STOP_BITS_MASK)

#define ModbusUART_GET_UART_TX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                               (ModbusUART_UART_TX_CTRL_PARITY) : (0u))

#define ModbusUART_GET_UART_TX_CTRL_RETRY_NACK(nack)  ((0u != (nack)) ? \
                                                               (ModbusUART_UART_TX_CTRL_RETRY_ON_NACK) : (0u))

/* ModbusUART_RX_CTRL */
#define ModbusUART_GET_RX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                ModbusUART_RX_CTRL_DATA_WIDTH_MASK)

#define ModbusUART_GET_RX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (ModbusUART_RX_CTRL_MSB_FIRST) : (0u))

#define ModbusUART_GET_RX_CTRL_MEDIAN(filterEn)       ((0u != (filterEn)) ? \
                                                                (ModbusUART_RX_CTRL_MEDIAN) : (0u))

/* ModbusUART_RX_MATCH */
#define ModbusUART_GET_RX_MATCH_ADDR(addr)    ((uint32) (addr) & ModbusUART_RX_MATCH_ADDR_MASK)
#define ModbusUART_GET_RX_MATCH_MASK(mask)    (((uint32) ((uint32) (mask) << \
                                                            ModbusUART_RX_MATCH_MASK_POS)) & \
                                                            ModbusUART_RX_MATCH_MASK_MASK)

/* ModbusUART_RX_FIFO_CTRL */
#define ModbusUART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    ModbusUART_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* ModbusUART_TX_CTRL */
#define ModbusUART_GET_TX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                ModbusUART_RX_CTRL_DATA_WIDTH_MASK)

#define ModbusUART_GET_TX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (ModbusUART_TX_CTRL_MSB_FIRST) : (0u))

/* ModbusUART_TX_FIFO_CTRL */
#define ModbusUART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    ModbusUART_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* Clears register: config and interrupt mask */
#define ModbusUART_CLEAR_REG          ((uint32) (0u))
#define ModbusUART_NO_INTR_SOURCES    ((uint32) (0u))
#define ModbusUART_DUMMY_PARAM        ((uint32) (0u))
#define ModbusUART_SUBMODE_SPI_SLAVE  ((uint32) (0u))

/* Return in case I2C read error */
#define ModbusUART_I2C_INVALID_BYTE   ((uint32) 0xFFFFFFFFu)
#define ModbusUART_CHECK_VALID_BYTE   ((uint32) 0x80000000u)

#endif /* (CY_SCB_ModbusUART_H) */


/* [] END OF FILE */
