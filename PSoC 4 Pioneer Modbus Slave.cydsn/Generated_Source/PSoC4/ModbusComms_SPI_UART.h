/*******************************************************************************
* File Name: ModbusComms_SPI_UART.h
* Version 1.10
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_ModbusComms_H)
#define CY_SCB_SPI_UART_ModbusComms_H

#include "ModbusComms.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define ModbusComms_SPI_MODE                   (0u)
#define ModbusComms_SPI_SUB_MODE               (0u)
#define ModbusComms_SPI_CLOCK_MODE             (0u)
#define ModbusComms_SPI_OVS_FACTOR             (16u)
#define ModbusComms_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define ModbusComms_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define ModbusComms_SPI_RX_DATA_BITS_NUM       (8u)
#define ModbusComms_SPI_TX_DATA_BITS_NUM       (8u)
#define ModbusComms_SPI_WAKE_ENABLE            (0u)
#define ModbusComms_SPI_BITS_ORDER             (1u)
#define ModbusComms_SPI_TRANSFER_SEPARATION    (1u)
#define ModbusComms_SPI_NUMBER_OF_SS_LINES     (1u)
#define ModbusComms_SPI_RX_BUFFER_SIZE         (8u)
#define ModbusComms_SPI_TX_BUFFER_SIZE         (8u)

#define ModbusComms_SPI_INTERRUPT_MODE         (0u)

#define ModbusComms_SPI_INTR_RX_MASK           (0u)
#define ModbusComms_SPI_INTR_TX_MASK           (0u)

#define ModbusComms_SPI_RX_TRIGGER_LEVEL       (7u)
#define ModbusComms_SPI_TX_TRIGGER_LEVEL       (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define ModbusComms_UART_SUB_MODE              (0u)
#define ModbusComms_UART_DIRECTION             (3u)
#define ModbusComms_UART_DATA_BITS_NUM         (8u)
#define ModbusComms_UART_PARITY_TYPE           (2u)
#define ModbusComms_UART_STOP_BITS_NUM         (2u)
#define ModbusComms_UART_OVS_FACTOR            (12u)
#define ModbusComms_UART_IRDA_LOW_POWER        (0u)
#define ModbusComms_UART_MEDIAN_FILTER_ENABLE  (0u)
#define ModbusComms_UART_RETRY_ON_NACK         (0u)
#define ModbusComms_UART_IRDA_POLARITY         (0u)
#define ModbusComms_UART_DROP_ON_FRAME_ERR     (0u)
#define ModbusComms_UART_DROP_ON_PARITY_ERR    (0u)
#define ModbusComms_UART_WAKE_ENABLE           (0u)
#define ModbusComms_UART_RX_BUFFER_SIZE        (8u)
#define ModbusComms_UART_TX_BUFFER_SIZE        (8u)
#define ModbusComms_UART_MP_MODE_ENABLE        (0u)
#define ModbusComms_UART_MP_ACCEPT_ADDRESS     (0u)
#define ModbusComms_UART_MP_RX_ADDRESS         (2u)
#define ModbusComms_UART_MP_RX_ADDRESS_MASK    (255u)

#define ModbusComms_UART_INTERRUPT_MODE        (2u)

#define ModbusComms_UART_INTR_RX_MASK          (4u)
#define ModbusComms_UART_INTR_TX_MASK          (0u)

#define ModbusComms_UART_RX_TRIGGER_LEVEL      (7u)
#define ModbusComms_UART_TX_TRIGGER_LEVEL      (0u)

/* Sources of RX errors */
#define ModbusComms_INTR_RX_ERR        (ModbusComms_INTR_RX_OVERFLOW    | \
                                             ModbusComms_INTR_RX_UNDERFLOW   | \
                                             ModbusComms_INTR_RX_FRAME_ERROR | \
                                             ModbusComms_INTR_RX_PARITY_ERROR)

/* UART direction enum */
#define ModbusComms_UART_RX    (1u)
#define ModbusComms_UART_TX    (2u)
#define ModbusComms_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Direction */
    #define ModbusComms_RX_DIRECTION           (1u)
    #define ModbusComms_TX_DIRECTION           (1u)
    #define ModbusComms_UART_RX_DIRECTION      (1u)
    #define ModbusComms_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for uncofigured mode */
    #define ModbusComms_INTERNAL_RX_SW_BUFFER   (0u)
    #define ModbusComms_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define ModbusComms_RX_BUFFER_SIZE (ModbusComms_rxBufferSize)
    #define ModbusComms_TX_BUFFER_SIZE (ModbusComms_txBufferSize)

    /* Return true if buffer is provided */
    #define ModbusComms_CHECK_RX_SW_BUFFER (NULL != ModbusComms_rxBuffer)
    #define ModbusComms_CHECK_TX_SW_BUFFER (NULL != ModbusComms_txBuffer)

    /* Alwasy provde global variables to support RX and TX buffers */
    #define ModbusComms_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define ModbusComms_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define ModbusComms_SPI_WAKE_ENABLE_CONST  (1u)
    #define ModbusComms_CHECK_SPI_WAKE_ENABLE  (0u != ModbusComms_scbEnableWake)
    #define ModbusComms_UART_WAKE_ENABLE_CONST (1u)

#else

    /* SPI internal RX and TX buffers */
    #define ModbusComms_INTERNAL_SPI_RX_SW_BUFFER  (ModbusComms_SPI_RX_BUFFER_SIZE > \
                                                                                            ModbusComms_FIFO_SIZE)
    #define ModbusComms_INTERNAL_SPI_TX_SW_BUFFER  (ModbusComms_SPI_TX_BUFFER_SIZE > \
                                                                                            ModbusComms_FIFO_SIZE)

    /* UART internal RX and TX buffers */
    #define ModbusComms_INTERNAL_UART_RX_SW_BUFFER  (ModbusComms_UART_RX_BUFFER_SIZE > \
                                                                                            ModbusComms_FIFO_SIZE)
    #define ModbusComms_INTERNAL_UART_TX_SW_BUFFER  (ModbusComms_UART_TX_BUFFER_SIZE > \
                                                                                            ModbusComms_FIFO_SIZE)

    /* SPI Direction */
    #define ModbusComms_SPI_RX_DIRECTION (1u)
    #define ModbusComms_SPI_TX_DIRECTION (1u)

    /* UART Direction */
    #define ModbusComms_UART_RX_DIRECTION (0u != (ModbusComms_UART_DIRECTION & ModbusComms_UART_RX))
    #define ModbusComms_UART_TX_DIRECTION (0u != (ModbusComms_UART_DIRECTION & ModbusComms_UART_TX))

    /* Direction */
    #define ModbusComms_RX_DIRECTION ((ModbusComms_SCB_MODE_SPI_CONST_CFG) ? \
                                            (ModbusComms_SPI_RX_DIRECTION) : (ModbusComms_UART_RX_DIRECTION))

    #define ModbusComms_TX_DIRECTION ((ModbusComms_SCB_MODE_SPI_CONST_CFG) ? \
                                            (ModbusComms_SPI_TX_DIRECTION) : (ModbusComms_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART */
    #if(ModbusComms_SCB_MODE_SPI_CONST_CFG)

        /* Internal SPI RX and TX buffer */
        #define ModbusComms_INTERNAL_RX_SW_BUFFER  (ModbusComms_INTERNAL_SPI_RX_SW_BUFFER)
        #define ModbusComms_INTERNAL_TX_SW_BUFFER  (ModbusComms_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define ModbusComms_RX_BUFFER_SIZE         (ModbusComms_SPI_RX_BUFFER_SIZE + 1u)
        #define ModbusComms_TX_BUFFER_SIZE         (ModbusComms_SPI_TX_BUFFER_SIZE)
        
        /* Get wakeup enable option */
        #define ModbusComms_SPI_WAKE_ENABLE_CONST  (0u != ModbusComms_SPI_WAKE_ENABLE)
        #define ModbusComms_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* Internal UART RX and TX buffer */
        #define ModbusComms_INTERNAL_RX_SW_BUFFER  (ModbusComms_INTERNAL_UART_RX_SW_BUFFER)
        #define ModbusComms_INTERNAL_TX_SW_BUFFER  (ModbusComms_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define ModbusComms_RX_BUFFER_SIZE         (ModbusComms_UART_RX_BUFFER_SIZE + 1u)
        #define ModbusComms_TX_BUFFER_SIZE         (ModbusComms_UART_TX_BUFFER_SIZE)
        
        /* Get wakeup enable option */
        #define ModbusComms_SPI_WAKE_ENABLE_CONST  (0u)
        #define ModbusComms_UART_WAKE_ENABLE_CONST (0u != ModbusComms_UART_WAKE_ENABLE)
    #endif /* (ModbusComms_SCB_MODE_SPI_CONST_CFG) */

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define ModbusComms_CHECK_RX_SW_BUFFER (ModbusComms_INTERNAL_RX_SW_BUFFER)
    #define ModbusComms_CHECK_TX_SW_BUFFER (ModbusComms_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define ModbusComms_INTERNAL_RX_SW_BUFFER_CONST    (ModbusComms_INTERNAL_RX_SW_BUFFER)
    #define ModbusComms_INTERNAL_TX_SW_BUFFER_CONST    (ModbusComms_INTERNAL_TX_SW_BUFFER)
    
    /* Wakeup for SPI */
    #define ModbusComms_CHECK_SPI_WAKE_ENABLE  (ModbusComms_SPI_WAKE_ENABLE_CONST)

#endif /* End (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Bootloader communication interface enable: NOT supported yet */
#define ModbusComms_SPI_BTLDR_COMM_ENABLED   ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusComms) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

#define ModbusComms_UART_BTLDR_COMM_ENABLED   ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusComms) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))


/***************************************
*       Type Definitions
***************************************/

/* ModbusComms_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
} ModbusComms_SPI_INIT_STRUCT;

/* ModbusComms_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
} ModbusComms_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
    void ModbusComms_SpiInit(const ModbusComms_SPI_INIT_STRUCT *config);
#endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(ModbusComms_SCB_MODE_SPI_INC)
    void ModbusComms_SpiSetActiveSlaveSelect(uint32 activeSelect);
#endif /* (ModbusComms_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
    void ModbusComms_UartInit(const ModbusComms_UART_INIT_STRUCT *config);
#endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(ModbusComms_SCB_MODE_UART_INC)
    void ModbusComms_UartSetRxAddress(uint32 address);
    void ModbusComms_UartSetRxAddressMask(uint32 addressMask);
#endif /* (ModbusComms_SCB_MODE_UART_INC) */

/* UART RX direction APIs */
#if(ModbusComms_UART_RX_DIRECTION)
    uint32 ModbusComms_UartGetChar(void);
    uint32 ModbusComms_UartGetByte(void);
#endif /* (ModbusComms_UART_RX_DIRECTION) */

/* UART TX direction APIs */
#if(ModbusComms_UART_TX_DIRECTION)
    #define ModbusComms_UartPutChar(ch)    ModbusComms_SpiUartWriteTxData((uint32)(ch))
    void ModbusComms_UartPutString(const char8 string[]);
    void ModbusComms_UartPutCRLF(uint32 txDataByte);
#endif /* (ModbusComms_UART_TX_DIRECTION) */

/* Common APIs Rx direction */
#if(ModbusComms_RX_DIRECTION)
    uint32 ModbusComms_SpiUartReadRxData(void);
    uint32 ModbusComms_SpiUartGetRxBufferSize(void);
    void   ModbusComms_SpiUartClearRxBuffer(void);
#endif /* (ModbusComms_RX_DIRECTION) */

/* Common APIs Tx direction */
#if(ModbusComms_TX_DIRECTION)
    void   ModbusComms_SpiUartWriteTxData(uint32 txDataByte);
    void   ModbusComms_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    void   ModbusComms_SpiUartClearTxBuffer(void);
    uint32 ModbusComms_SpiUartGetTxBufferSize(void);
#endif /* (ModbusComms_TX_DIRECTION) */

CY_ISR_PROTO(ModbusComms_SPI_UART_ISR);

#if(ModbusComms_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(ModbusComms_UART_WAKEUP_ISR);
#endif /* (ModbusComms_UART_RX_WAKEUP_IRQ) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusComms_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void ModbusComms_SpiCyBtldrCommStart(void);
    void ModbusComms_SpiCyBtldrCommStop (void);
    void ModbusComms_SpiCyBtldrCommReset(void);
    cystatus ModbusComms_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ModbusComms_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusComms_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusComms_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void ModbusComms_UartCyBtldrCommStart(void);
    void ModbusComms_UartCyBtldrCommStop (void);
    void ModbusComms_UartCyBtldrCommReset(void);
    cystatus ModbusComms_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ModbusComms_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusComms_UART_BTLDR_COMM_ENABLED) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   ModbusComms_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 ModbusComms_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   ModbusComms_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 ModbusComms_GetWordFromTxBuffer(uint32 idx);

#else

    /* RX direction */
    #if(ModbusComms_INTERNAL_RX_SW_BUFFER_CONST)
        #define ModbusComms_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    ModbusComms_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define ModbusComms_GetWordFromRxBuffer(idx) ModbusComms_rxBufferInternal[(idx)]

    #endif /* (ModbusComms_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(ModbusComms_INTERNAL_TX_SW_BUFFER_CONST)
        #define ModbusComms_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        ModbusComms_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define ModbusComms_GetWordFromTxBuffer(idx) ModbusComms_txBufferInternal[(idx)]

    #endif /* (ModbusComms_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (ModbusComms_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI mode enum */
#define ModbusComms_SPI_SLAVE  (0u)
#define ModbusComms_SPI_MASTER (1u)

/* SPI sub mode enum */
#define ModbusComms_SPI_MODE_MOTOROLA      (0x00u)
#define ModbusComms_SPI_MODE_TI_COINCIDES  (0x01u)
#define ModbusComms_SPI_MODE_TI_PRECEDES   (0x11u)
#define ModbusComms_SPI_MODE_NATIONAL      (0x02u)
#define ModbusComms_SPI_MODE_MASK          (0x03u)
#define ModbusComms_SPI_MODE_TI_PRECEDES_MASK  (0x10u)

/* SPI phase and polarity mode enum */
#define ModbusComms_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define ModbusComms_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define ModbusComms_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define ModbusComms_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define ModbusComms_BITS_ORDER_LSB_FIRST   (0u)
#define ModbusComms_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define ModbusComms_SPI_TRANSFER_SEPARATED     (0u)
#define ModbusComms_SPI_TRANSFER_CONTINUOUS    (1u)

/* "activeSS" constants for SpiSetActiveSlaveSelect() function */
#define ModbusComms_SPIM_ACTIVE_SS0    (0x00u)
#define ModbusComms_SPIM_ACTIVE_SS1    (0x01u)
#define ModbusComms_SPIM_ACTIVE_SS2    (0x02u)
#define ModbusComms_SPIM_ACTIVE_SS3    (0x03u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define ModbusComms_UART_MODE_STD          (0u)
#define ModbusComms_UART_MODE_SMARTCARD    (1u)
#define ModbusComms_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define ModbusComms_UART_RX    (1u)
#define ModbusComms_UART_TX    (2u)
#define ModbusComms_UART_TX_RX (3u)

/* UART parity enum */
#define ModbusComms_UART_PARITY_EVEN   (0u)
#define ModbusComms_UART_PARITY_ODD    (1u)
#define ModbusComms_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define ModbusComms_UART_STOP_BITS_1   (1u)
#define ModbusComms_UART_STOP_BITS_1_5 (2u)
#define ModbusComms_UART_STOP_BITS_2   (3u)

/* UART IrDA low power OVS enum */
#define ModbusComms_UART_IRDA_LP_OVS16     (16u)
#define ModbusComms_UART_IRDA_LP_OVS32     (32u)
#define ModbusComms_UART_IRDA_LP_OVS48     (48u)
#define ModbusComms_UART_IRDA_LP_OVS96     (96u)
#define ModbusComms_UART_IRDA_LP_OVS192    (192u)
#define ModbusComms_UART_IRDA_LP_OVS768    (768u)
#define ModbusComms_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define ModbusComms_UART_MP_MARK       (0x100u)
#define ModbusComms_UART_MP_SPACE      (0x000u)


/***************************************
*     Vars with External Linkage
***************************************/

#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const ModbusComms_SPI_INIT_STRUCT  ModbusComms_configSpi;
    extern const ModbusComms_UART_INIT_STRUCT ModbusComms_configUart;
#endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define ModbusComms_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & ModbusComms_INTR_SLAVE_SPI_BUS_ERROR)
#define ModbusComms_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & ModbusComms_INTR_MASTER_SPI_DONE)
#define ModbusComms_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~ModbusComms_INTR_SLAVE_SPI_BUS_ERROR)

#define ModbusComms_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~ModbusComms_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define ModbusComms_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((ModbusComms_UART_IRDA_LP_OVS16   == (oversample)) ? ModbusComms_CTRL_OVS_IRDA_LP_OVS16 : \
         ((ModbusComms_UART_IRDA_LP_OVS32   == (oversample)) ? ModbusComms_CTRL_OVS_IRDA_LP_OVS32 : \
          ((ModbusComms_UART_IRDA_LP_OVS48   == (oversample)) ? ModbusComms_CTRL_OVS_IRDA_LP_OVS48 : \
           ((ModbusComms_UART_IRDA_LP_OVS96   == (oversample)) ? ModbusComms_CTRL_OVS_IRDA_LP_OVS96 : \
            ((ModbusComms_UART_IRDA_LP_OVS192  == (oversample)) ? ModbusComms_CTRL_OVS_IRDA_LP_OVS192 : \
             ((ModbusComms_UART_IRDA_LP_OVS768  == (oversample)) ? ModbusComms_CTRL_OVS_IRDA_LP_OVS768 : \
              ((ModbusComms_UART_IRDA_LP_OVS1536 == (oversample)) ? ModbusComms_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          ModbusComms_CTRL_OVS_IRDA_LP_OVS16)))))))

#define ModbusComms_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (ModbusComms_UART_RX & (direction))) ? \
                                                                    (ModbusComms_RX_CTRL_ENABLED) : (0u))

#define ModbusComms_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (ModbusComms_UART_TX & (direction))) ? \
                                                                    (ModbusComms_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define ModbusComms_CTRL_SPI      (ModbusComms_CTRL_MODE_SPI)
#define ModbusComms_SPI_RX_CTRL   (ModbusComms_RX_CTRL_ENABLED)
#define ModbusComms_SPI_TX_CTRL   (ModbusComms_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#if(ModbusComms_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define ModbusComms_SPI_DEFAULT_CTRL \
                    (ModbusComms_GET_CTRL_OVS(ModbusComms_SPI_OVS_FACTOR)         | \
                     ModbusComms_GET_CTRL_EC_AM_MODE(ModbusComms_SPI_WAKE_ENABLE) | \
                     ModbusComms_CTRL_SPI)

    #define ModbusComms_SPI_DEFAULT_SPI_CTRL \
                    (ModbusComms_GET_SPI_CTRL_CONTINUOUS    (ModbusComms_SPI_TRANSFER_SEPARATION)       | \
                     ModbusComms_GET_SPI_CTRL_SELECT_PRECEDE(ModbusComms_SPI_SUB_MODE &                   \
                                                                  ModbusComms_SPI_MODE_TI_PRECEDES_MASK)     | \
                     ModbusComms_GET_SPI_CTRL_SCLK_MODE     (ModbusComms_SPI_CLOCK_MODE)                | \
                     ModbusComms_GET_SPI_CTRL_LATE_MISO_SAMPLE(ModbusComms_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     ModbusComms_GET_SPI_CTRL_SUB_MODE      (ModbusComms_SPI_SUB_MODE)                  | \
                     ModbusComms_GET_SPI_CTRL_MASTER_MODE   (ModbusComms_SPI_MODE))

    /* RX direction */
    #define ModbusComms_SPI_DEFAULT_RX_CTRL \
                    (ModbusComms_GET_RX_CTRL_DATA_WIDTH(ModbusComms_SPI_RX_DATA_BITS_NUM)     | \
                     ModbusComms_GET_RX_CTRL_BIT_ORDER (ModbusComms_SPI_BITS_ORDER)           | \
                     ModbusComms_GET_RX_CTRL_MEDIAN    (ModbusComms_SPI_MEDIAN_FILTER_ENABLE) | \
                     ModbusComms_SPI_RX_CTRL)

    #define ModbusComms_SPI_DEFAULT_RX_FIFO_CTRL \
                    ModbusComms_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(ModbusComms_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define ModbusComms_SPI_DEFAULT_TX_CTRL \
                    (ModbusComms_GET_TX_CTRL_DATA_WIDTH(ModbusComms_SPI_TX_DATA_BITS_NUM) | \
                     ModbusComms_GET_TX_CTRL_BIT_ORDER (ModbusComms_SPI_BITS_ORDER)       | \
                     ModbusComms_SPI_TX_CTRL)

    #define ModbusComms_SPI_DEFAULT_TX_FIFO_CTRL \
                    ModbusComms_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(ModbusComms_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define ModbusComms_SPI_DEFAULT_INTR_SPI_EC_MASK   (ModbusComms_NO_INTR_SOURCES)

    #define ModbusComms_SPI_DEFAULT_INTR_I2C_EC_MASK   (ModbusComms_NO_INTR_SOURCES)
    #define ModbusComms_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (ModbusComms_SPI_INTR_RX_MASK & ModbusComms_INTR_SLAVE_SPI_BUS_ERROR)

    #define ModbusComms_SPI_DEFAULT_INTR_MASTER_MASK \
                    (ModbusComms_SPI_INTR_TX_MASK & ModbusComms_INTR_MASTER_SPI_DONE)

    #define ModbusComms_SPI_DEFAULT_INTR_RX_MASK \
                    (ModbusComms_SPI_INTR_RX_MASK & (uint32) ~ModbusComms_INTR_SLAVE_SPI_BUS_ERROR)

    #define ModbusComms_SPI_DEFAULT_INTR_TX_MASK \
                    (ModbusComms_SPI_INTR_TX_MASK & (uint32) ~ModbusComms_INTR_MASTER_SPI_DONE)

#endif /* (ModbusComms_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define ModbusComms_CTRL_UART      (ModbusComms_CTRL_MODE_UART)
#define ModbusComms_UART_RX_CTRL   (ModbusComms_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define ModbusComms_UART_TX_CTRL   (ModbusComms_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(ModbusComms_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(ModbusComms_UART_MODE_IRDA == ModbusComms_UART_SUB_MODE)

        #define ModbusComms_DEFAULT_CTRL_OVS   ((0u != ModbusComms_UART_IRDA_LOW_POWER) ?              \
                                (ModbusComms_UART_GET_CTRL_OVS_IRDA_LP(ModbusComms_UART_OVS_FACTOR)) : \
                                (ModbusComms_CTRL_OVS_IRDA_OVS16))

    #else

        #define ModbusComms_DEFAULT_CTRL_OVS   ModbusComms_GET_CTRL_OVS(ModbusComms_UART_OVS_FACTOR)

    #endif /* (ModbusComms_UART_MODE_IRDA == ModbusComms_UART_SUB_MODE) */

    #define ModbusComms_UART_DEFAULT_CTRL \
                                (ModbusComms_GET_CTRL_ADDR_ACCEPT(ModbusComms_UART_MP_ACCEPT_ADDRESS) | \
                                 ModbusComms_DEFAULT_CTRL_OVS                                              | \
                                 ModbusComms_CTRL_UART)

    #define ModbusComms_UART_DEFAULT_UART_CTRL \
                                    (ModbusComms_GET_UART_CTRL_MODE(ModbusComms_UART_SUB_MODE))

    /* RX direction */
    #define ModbusComms_UART_DEFAULT_RX_CTRL_PARITY \
                                ((ModbusComms_UART_PARITY_NONE != ModbusComms_UART_PARITY_TYPE) ?      \
                                  (ModbusComms_GET_UART_RX_CTRL_PARITY(ModbusComms_UART_PARITY_TYPE) | \
                                   ModbusComms_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define ModbusComms_UART_DEFAULT_UART_RX_CTRL \
                    (ModbusComms_GET_UART_RX_CTRL_MODE(ModbusComms_UART_STOP_BITS_NUM)                    | \
                     ModbusComms_GET_UART_RX_CTRL_POLARITY(ModbusComms_UART_IRDA_POLARITY)                | \
                     ModbusComms_GET_UART_RX_CTRL_MP_MODE(ModbusComms_UART_MP_MODE_ENABLE)                | \
                     ModbusComms_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(ModbusComms_UART_DROP_ON_PARITY_ERR) | \
                     ModbusComms_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(ModbusComms_UART_DROP_ON_FRAME_ERR)   | \
                     ModbusComms_UART_DEFAULT_RX_CTRL_PARITY)

    #define ModbusComms_UART_DEFAULT_RX_CTRL \
                                (ModbusComms_GET_RX_CTRL_DATA_WIDTH(ModbusComms_UART_DATA_BITS_NUM)        | \
                                 ModbusComms_GET_RX_CTRL_MEDIAN    (ModbusComms_UART_MEDIAN_FILTER_ENABLE) | \
                                 ModbusComms_GET_UART_RX_CTRL_ENABLED(ModbusComms_UART_DIRECTION))

    #define ModbusComms_UART_DEFAULT_RX_FIFO_CTRL \
                                ModbusComms_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(ModbusComms_UART_RX_TRIGGER_LEVEL)

    #define ModbusComms_UART_DEFAULT_RX_MATCH_REG  ((0u != ModbusComms_UART_MP_MODE_ENABLE) ?          \
                                (ModbusComms_GET_RX_MATCH_ADDR(ModbusComms_UART_MP_RX_ADDRESS) | \
                                 ModbusComms_GET_RX_MATCH_MASK(ModbusComms_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define ModbusComms_UART_DEFAULT_TX_CTRL_PARITY (ModbusComms_UART_DEFAULT_RX_CTRL_PARITY)

    #define ModbusComms_UART_DEFAULT_UART_TX_CTRL \
                                (ModbusComms_GET_UART_TX_CTRL_MODE(ModbusComms_UART_STOP_BITS_NUM)       | \
                                 ModbusComms_GET_UART_TX_CTRL_RETRY_NACK(ModbusComms_UART_RETRY_ON_NACK) | \
                                 ModbusComms_UART_DEFAULT_TX_CTRL_PARITY)

    #define ModbusComms_UART_DEFAULT_TX_CTRL \
                                (ModbusComms_GET_TX_CTRL_DATA_WIDTH(ModbusComms_UART_DATA_BITS_NUM) | \
                                 ModbusComms_GET_UART_TX_CTRL_ENABLED(ModbusComms_UART_DIRECTION))

    #define ModbusComms_UART_DEFAULT_TX_FIFO_CTRL \
                                ModbusComms_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(ModbusComms_UART_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define ModbusComms_UART_DEFAULT_INTR_I2C_EC_MASK  (ModbusComms_NO_INTR_SOURCES)
    #define ModbusComms_UART_DEFAULT_INTR_SPI_EC_MASK  (ModbusComms_NO_INTR_SOURCES)
    #define ModbusComms_UART_DEFAULT_INTR_SLAVE_MASK   (ModbusComms_NO_INTR_SOURCES)
    #define ModbusComms_UART_DEFAULT_INTR_MASTER_MASK  (ModbusComms_NO_INTR_SOURCES)
    #define ModbusComms_UART_DEFAULT_INTR_RX_MASK      (ModbusComms_UART_INTR_RX_MASK)
    #define ModbusComms_UART_DEFAULT_INTR_TX_MASK      (ModbusComms_UART_INTR_TX_MASK)

#endif /* (ModbusComms_SCB_MODE_UART_CONST_CFG) */

#endif /* CY_SCB_SPI_UART_ModbusComms_H */


/* [] END OF FILE */
