/*******************************************************************************
* File Name: ModbusUART_SPI_UART.h
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

#if !defined(CY_SCB_SPI_UART_ModbusUART_H)
#define CY_SCB_SPI_UART_ModbusUART_H

#include "ModbusUART.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define ModbusUART_SPI_MODE                   (0u)
#define ModbusUART_SPI_SUB_MODE               (0u)
#define ModbusUART_SPI_CLOCK_MODE             (0u)
#define ModbusUART_SPI_OVS_FACTOR             (16u)
#define ModbusUART_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define ModbusUART_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define ModbusUART_SPI_RX_DATA_BITS_NUM       (8u)
#define ModbusUART_SPI_TX_DATA_BITS_NUM       (8u)
#define ModbusUART_SPI_WAKE_ENABLE            (0u)
#define ModbusUART_SPI_BITS_ORDER             (1u)
#define ModbusUART_SPI_TRANSFER_SEPARATION    (1u)
#define ModbusUART_SPI_NUMBER_OF_SS_LINES     (1u)
#define ModbusUART_SPI_RX_BUFFER_SIZE         (8u)
#define ModbusUART_SPI_TX_BUFFER_SIZE         (8u)

#define ModbusUART_SPI_INTERRUPT_MODE         (0u)

#define ModbusUART_SPI_INTR_RX_MASK           (0u)
#define ModbusUART_SPI_INTR_TX_MASK           (0u)

#define ModbusUART_SPI_RX_TRIGGER_LEVEL       (7u)
#define ModbusUART_SPI_TX_TRIGGER_LEVEL       (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define ModbusUART_UART_SUB_MODE              (0u)
#define ModbusUART_UART_DIRECTION             (3u)
#define ModbusUART_UART_DATA_BITS_NUM         (8u)
#define ModbusUART_UART_PARITY_TYPE           (2u)
#define ModbusUART_UART_STOP_BITS_NUM         (2u)
#define ModbusUART_UART_OVS_FACTOR            (12u)
#define ModbusUART_UART_IRDA_LOW_POWER        (0u)
#define ModbusUART_UART_MEDIAN_FILTER_ENABLE  (0u)
#define ModbusUART_UART_RETRY_ON_NACK         (0u)
#define ModbusUART_UART_IRDA_POLARITY         (0u)
#define ModbusUART_UART_DROP_ON_FRAME_ERR     (0u)
#define ModbusUART_UART_DROP_ON_PARITY_ERR    (0u)
#define ModbusUART_UART_WAKE_ENABLE           (0u)
#define ModbusUART_UART_RX_BUFFER_SIZE        (8u)
#define ModbusUART_UART_TX_BUFFER_SIZE        (8u)
#define ModbusUART_UART_MP_MODE_ENABLE        (0u)
#define ModbusUART_UART_MP_ACCEPT_ADDRESS     (0u)
#define ModbusUART_UART_MP_RX_ADDRESS         (2u)
#define ModbusUART_UART_MP_RX_ADDRESS_MASK    (255u)

#define ModbusUART_UART_INTERRUPT_MODE        (2u)

#define ModbusUART_UART_INTR_RX_MASK          (4u)
#define ModbusUART_UART_INTR_TX_MASK          (0u)

#define ModbusUART_UART_RX_TRIGGER_LEVEL      (7u)
#define ModbusUART_UART_TX_TRIGGER_LEVEL      (0u)

/* Sources of RX errors */
#define ModbusUART_INTR_RX_ERR        (ModbusUART_INTR_RX_OVERFLOW    | \
                                             ModbusUART_INTR_RX_UNDERFLOW   | \
                                             ModbusUART_INTR_RX_FRAME_ERROR | \
                                             ModbusUART_INTR_RX_PARITY_ERROR)

/* UART direction enum */
#define ModbusUART_UART_RX    (1u)
#define ModbusUART_UART_TX    (2u)
#define ModbusUART_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Direction */
    #define ModbusUART_RX_DIRECTION           (1u)
    #define ModbusUART_TX_DIRECTION           (1u)
    #define ModbusUART_UART_RX_DIRECTION      (1u)
    #define ModbusUART_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for uncofigured mode */
    #define ModbusUART_INTERNAL_RX_SW_BUFFER   (0u)
    #define ModbusUART_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define ModbusUART_RX_BUFFER_SIZE (ModbusUART_rxBufferSize)
    #define ModbusUART_TX_BUFFER_SIZE (ModbusUART_txBufferSize)

    /* Return true if buffer is provided */
    #define ModbusUART_CHECK_RX_SW_BUFFER (NULL != ModbusUART_rxBuffer)
    #define ModbusUART_CHECK_TX_SW_BUFFER (NULL != ModbusUART_txBuffer)

    /* Alwasy provde global variables to support RX and TX buffers */
    #define ModbusUART_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define ModbusUART_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define ModbusUART_SPI_WAKE_ENABLE_CONST  (1u)
    #define ModbusUART_CHECK_SPI_WAKE_ENABLE  (0u != ModbusUART_scbEnableWake)
    #define ModbusUART_UART_WAKE_ENABLE_CONST (1u)

#else

    /* SPI internal RX and TX buffers */
    #define ModbusUART_INTERNAL_SPI_RX_SW_BUFFER  (ModbusUART_SPI_RX_BUFFER_SIZE > \
                                                                                            ModbusUART_FIFO_SIZE)
    #define ModbusUART_INTERNAL_SPI_TX_SW_BUFFER  (ModbusUART_SPI_TX_BUFFER_SIZE > \
                                                                                            ModbusUART_FIFO_SIZE)

    /* UART internal RX and TX buffers */
    #define ModbusUART_INTERNAL_UART_RX_SW_BUFFER  (ModbusUART_UART_RX_BUFFER_SIZE > \
                                                                                            ModbusUART_FIFO_SIZE)
    #define ModbusUART_INTERNAL_UART_TX_SW_BUFFER  (ModbusUART_UART_TX_BUFFER_SIZE > \
                                                                                            ModbusUART_FIFO_SIZE)

    /* SPI Direction */
    #define ModbusUART_SPI_RX_DIRECTION (1u)
    #define ModbusUART_SPI_TX_DIRECTION (1u)

    /* UART Direction */
    #define ModbusUART_UART_RX_DIRECTION (0u != (ModbusUART_UART_DIRECTION & ModbusUART_UART_RX))
    #define ModbusUART_UART_TX_DIRECTION (0u != (ModbusUART_UART_DIRECTION & ModbusUART_UART_TX))

    /* Direction */
    #define ModbusUART_RX_DIRECTION ((ModbusUART_SCB_MODE_SPI_CONST_CFG) ? \
                                            (ModbusUART_SPI_RX_DIRECTION) : (ModbusUART_UART_RX_DIRECTION))

    #define ModbusUART_TX_DIRECTION ((ModbusUART_SCB_MODE_SPI_CONST_CFG) ? \
                                            (ModbusUART_SPI_TX_DIRECTION) : (ModbusUART_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART */
    #if(ModbusUART_SCB_MODE_SPI_CONST_CFG)

        /* Internal SPI RX and TX buffer */
        #define ModbusUART_INTERNAL_RX_SW_BUFFER  (ModbusUART_INTERNAL_SPI_RX_SW_BUFFER)
        #define ModbusUART_INTERNAL_TX_SW_BUFFER  (ModbusUART_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define ModbusUART_RX_BUFFER_SIZE         (ModbusUART_SPI_RX_BUFFER_SIZE + 1u)
        #define ModbusUART_TX_BUFFER_SIZE         (ModbusUART_SPI_TX_BUFFER_SIZE)
        
        /* Get wakeup enable option */
        #define ModbusUART_SPI_WAKE_ENABLE_CONST  (0u != ModbusUART_SPI_WAKE_ENABLE)
        #define ModbusUART_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* Internal UART RX and TX buffer */
        #define ModbusUART_INTERNAL_RX_SW_BUFFER  (ModbusUART_INTERNAL_UART_RX_SW_BUFFER)
        #define ModbusUART_INTERNAL_TX_SW_BUFFER  (ModbusUART_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define ModbusUART_RX_BUFFER_SIZE         (ModbusUART_UART_RX_BUFFER_SIZE + 1u)
        #define ModbusUART_TX_BUFFER_SIZE         (ModbusUART_UART_TX_BUFFER_SIZE)
        
        /* Get wakeup enable option */
        #define ModbusUART_SPI_WAKE_ENABLE_CONST  (0u)
        #define ModbusUART_UART_WAKE_ENABLE_CONST (0u != ModbusUART_UART_WAKE_ENABLE)
    #endif /* (ModbusUART_SCB_MODE_SPI_CONST_CFG) */

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define ModbusUART_CHECK_RX_SW_BUFFER (ModbusUART_INTERNAL_RX_SW_BUFFER)
    #define ModbusUART_CHECK_TX_SW_BUFFER (ModbusUART_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define ModbusUART_INTERNAL_RX_SW_BUFFER_CONST    (ModbusUART_INTERNAL_RX_SW_BUFFER)
    #define ModbusUART_INTERNAL_TX_SW_BUFFER_CONST    (ModbusUART_INTERNAL_TX_SW_BUFFER)
    
    /* Wakeup for SPI */
    #define ModbusUART_CHECK_SPI_WAKE_ENABLE  (ModbusUART_SPI_WAKE_ENABLE_CONST)

#endif /* End (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Bootloader communication interface enable: NOT supported yet */
#define ModbusUART_SPI_BTLDR_COMM_ENABLED   ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusUART) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

#define ModbusUART_UART_BTLDR_COMM_ENABLED   ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusUART) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))


/***************************************
*       Type Definitions
***************************************/

/* ModbusUART_SPI_INIT_STRUCT */
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
} ModbusUART_SPI_INIT_STRUCT;

/* ModbusUART_UART_INIT_STRUCT */
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
} ModbusUART_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    void ModbusUART_SpiInit(const ModbusUART_SPI_INIT_STRUCT *config);
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(ModbusUART_SCB_MODE_SPI_INC)
    void ModbusUART_SpiSetActiveSlaveSelect(uint32 activeSelect);
#endif /* (ModbusUART_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    void ModbusUART_UartInit(const ModbusUART_UART_INIT_STRUCT *config);
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(ModbusUART_SCB_MODE_UART_INC)
    void ModbusUART_UartSetRxAddress(uint32 address);
    void ModbusUART_UartSetRxAddressMask(uint32 addressMask);
#endif /* (ModbusUART_SCB_MODE_UART_INC) */

/* UART RX direction APIs */
#if(ModbusUART_UART_RX_DIRECTION)
    uint32 ModbusUART_UartGetChar(void);
    uint32 ModbusUART_UartGetByte(void);
#endif /* (ModbusUART_UART_RX_DIRECTION) */

/* UART TX direction APIs */
#if(ModbusUART_UART_TX_DIRECTION)
    #define ModbusUART_UartPutChar(ch)    ModbusUART_SpiUartWriteTxData((uint32)(ch))
    void ModbusUART_UartPutString(const char8 string[]);
    void ModbusUART_UartPutCRLF(uint32 txDataByte);
#endif /* (ModbusUART_UART_TX_DIRECTION) */

/* Common APIs Rx direction */
#if(ModbusUART_RX_DIRECTION)
    uint32 ModbusUART_SpiUartReadRxData(void);
    uint32 ModbusUART_SpiUartGetRxBufferSize(void);
    void   ModbusUART_SpiUartClearRxBuffer(void);
#endif /* (ModbusUART_RX_DIRECTION) */

/* Common APIs Tx direction */
#if(ModbusUART_TX_DIRECTION)
    void   ModbusUART_SpiUartWriteTxData(uint32 txDataByte);
    void   ModbusUART_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    void   ModbusUART_SpiUartClearTxBuffer(void);
    uint32 ModbusUART_SpiUartGetTxBufferSize(void);
#endif /* (ModbusUART_TX_DIRECTION) */

CY_ISR_PROTO(ModbusUART_SPI_UART_ISR);

#if(ModbusUART_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(ModbusUART_UART_WAKEUP_ISR);
#endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void ModbusUART_SpiCyBtldrCommStart(void);
    void ModbusUART_SpiCyBtldrCommStop (void);
    void ModbusUART_SpiCyBtldrCommReset(void);
    cystatus ModbusUART_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ModbusUART_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void ModbusUART_UartCyBtldrCommStart(void);
    void ModbusUART_UartCyBtldrCommStop (void);
    void ModbusUART_UartCyBtldrCommReset(void);
    cystatus ModbusUART_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ModbusUART_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_UART_BTLDR_COMM_ENABLED) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   ModbusUART_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 ModbusUART_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   ModbusUART_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 ModbusUART_GetWordFromTxBuffer(uint32 idx);

#else

    /* RX direction */
    #if(ModbusUART_INTERNAL_RX_SW_BUFFER_CONST)
        #define ModbusUART_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    ModbusUART_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define ModbusUART_GetWordFromRxBuffer(idx) ModbusUART_rxBufferInternal[(idx)]

    #endif /* (ModbusUART_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(ModbusUART_INTERNAL_TX_SW_BUFFER_CONST)
        #define ModbusUART_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        ModbusUART_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define ModbusUART_GetWordFromTxBuffer(idx) ModbusUART_txBufferInternal[(idx)]

    #endif /* (ModbusUART_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (ModbusUART_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI mode enum */
#define ModbusUART_SPI_SLAVE  (0u)
#define ModbusUART_SPI_MASTER (1u)

/* SPI sub mode enum */
#define ModbusUART_SPI_MODE_MOTOROLA      (0x00u)
#define ModbusUART_SPI_MODE_TI_COINCIDES  (0x01u)
#define ModbusUART_SPI_MODE_TI_PRECEDES   (0x11u)
#define ModbusUART_SPI_MODE_NATIONAL      (0x02u)
#define ModbusUART_SPI_MODE_MASK          (0x03u)
#define ModbusUART_SPI_MODE_TI_PRECEDES_MASK  (0x10u)

/* SPI phase and polarity mode enum */
#define ModbusUART_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define ModbusUART_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define ModbusUART_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define ModbusUART_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define ModbusUART_BITS_ORDER_LSB_FIRST   (0u)
#define ModbusUART_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define ModbusUART_SPI_TRANSFER_SEPARATED     (0u)
#define ModbusUART_SPI_TRANSFER_CONTINUOUS    (1u)

/* "activeSS" constants for SpiSetActiveSlaveSelect() function */
#define ModbusUART_SPIM_ACTIVE_SS0    (0x00u)
#define ModbusUART_SPIM_ACTIVE_SS1    (0x01u)
#define ModbusUART_SPIM_ACTIVE_SS2    (0x02u)
#define ModbusUART_SPIM_ACTIVE_SS3    (0x03u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define ModbusUART_UART_MODE_STD          (0u)
#define ModbusUART_UART_MODE_SMARTCARD    (1u)
#define ModbusUART_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define ModbusUART_UART_RX    (1u)
#define ModbusUART_UART_TX    (2u)
#define ModbusUART_UART_TX_RX (3u)

/* UART parity enum */
#define ModbusUART_UART_PARITY_EVEN   (0u)
#define ModbusUART_UART_PARITY_ODD    (1u)
#define ModbusUART_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define ModbusUART_UART_STOP_BITS_1   (1u)
#define ModbusUART_UART_STOP_BITS_1_5 (2u)
#define ModbusUART_UART_STOP_BITS_2   (3u)

/* UART IrDA low power OVS enum */
#define ModbusUART_UART_IRDA_LP_OVS16     (16u)
#define ModbusUART_UART_IRDA_LP_OVS32     (32u)
#define ModbusUART_UART_IRDA_LP_OVS48     (48u)
#define ModbusUART_UART_IRDA_LP_OVS96     (96u)
#define ModbusUART_UART_IRDA_LP_OVS192    (192u)
#define ModbusUART_UART_IRDA_LP_OVS768    (768u)
#define ModbusUART_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define ModbusUART_UART_MP_MARK       (0x100u)
#define ModbusUART_UART_MP_SPACE      (0x000u)


/***************************************
*     Vars with External Linkage
***************************************/

#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const ModbusUART_SPI_INIT_STRUCT  ModbusUART_configSpi;
    extern const ModbusUART_UART_INIT_STRUCT ModbusUART_configUart;
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define ModbusUART_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & ModbusUART_INTR_SLAVE_SPI_BUS_ERROR)
#define ModbusUART_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & ModbusUART_INTR_MASTER_SPI_DONE)
#define ModbusUART_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~ModbusUART_INTR_SLAVE_SPI_BUS_ERROR)

#define ModbusUART_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~ModbusUART_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define ModbusUART_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((ModbusUART_UART_IRDA_LP_OVS16   == (oversample)) ? ModbusUART_CTRL_OVS_IRDA_LP_OVS16 : \
         ((ModbusUART_UART_IRDA_LP_OVS32   == (oversample)) ? ModbusUART_CTRL_OVS_IRDA_LP_OVS32 : \
          ((ModbusUART_UART_IRDA_LP_OVS48   == (oversample)) ? ModbusUART_CTRL_OVS_IRDA_LP_OVS48 : \
           ((ModbusUART_UART_IRDA_LP_OVS96   == (oversample)) ? ModbusUART_CTRL_OVS_IRDA_LP_OVS96 : \
            ((ModbusUART_UART_IRDA_LP_OVS192  == (oversample)) ? ModbusUART_CTRL_OVS_IRDA_LP_OVS192 : \
             ((ModbusUART_UART_IRDA_LP_OVS768  == (oversample)) ? ModbusUART_CTRL_OVS_IRDA_LP_OVS768 : \
              ((ModbusUART_UART_IRDA_LP_OVS1536 == (oversample)) ? ModbusUART_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          ModbusUART_CTRL_OVS_IRDA_LP_OVS16)))))))

#define ModbusUART_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (ModbusUART_UART_RX & (direction))) ? \
                                                                    (ModbusUART_RX_CTRL_ENABLED) : (0u))

#define ModbusUART_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (ModbusUART_UART_TX & (direction))) ? \
                                                                    (ModbusUART_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define ModbusUART_CTRL_SPI      (ModbusUART_CTRL_MODE_SPI)
#define ModbusUART_SPI_RX_CTRL   (ModbusUART_RX_CTRL_ENABLED)
#define ModbusUART_SPI_TX_CTRL   (ModbusUART_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#if(ModbusUART_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define ModbusUART_SPI_DEFAULT_CTRL \
                    (ModbusUART_GET_CTRL_OVS(ModbusUART_SPI_OVS_FACTOR)         | \
                     ModbusUART_GET_CTRL_EC_AM_MODE(ModbusUART_SPI_WAKE_ENABLE) | \
                     ModbusUART_CTRL_SPI)

    #define ModbusUART_SPI_DEFAULT_SPI_CTRL \
                    (ModbusUART_GET_SPI_CTRL_CONTINUOUS    (ModbusUART_SPI_TRANSFER_SEPARATION)       | \
                     ModbusUART_GET_SPI_CTRL_SELECT_PRECEDE(ModbusUART_SPI_SUB_MODE &                   \
                                                                  ModbusUART_SPI_MODE_TI_PRECEDES_MASK)     | \
                     ModbusUART_GET_SPI_CTRL_SCLK_MODE     (ModbusUART_SPI_CLOCK_MODE)                | \
                     ModbusUART_GET_SPI_CTRL_LATE_MISO_SAMPLE(ModbusUART_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     ModbusUART_GET_SPI_CTRL_SUB_MODE      (ModbusUART_SPI_SUB_MODE)                  | \
                     ModbusUART_GET_SPI_CTRL_MASTER_MODE   (ModbusUART_SPI_MODE))

    /* RX direction */
    #define ModbusUART_SPI_DEFAULT_RX_CTRL \
                    (ModbusUART_GET_RX_CTRL_DATA_WIDTH(ModbusUART_SPI_RX_DATA_BITS_NUM)     | \
                     ModbusUART_GET_RX_CTRL_BIT_ORDER (ModbusUART_SPI_BITS_ORDER)           | \
                     ModbusUART_GET_RX_CTRL_MEDIAN    (ModbusUART_SPI_MEDIAN_FILTER_ENABLE) | \
                     ModbusUART_SPI_RX_CTRL)

    #define ModbusUART_SPI_DEFAULT_RX_FIFO_CTRL \
                    ModbusUART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(ModbusUART_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define ModbusUART_SPI_DEFAULT_TX_CTRL \
                    (ModbusUART_GET_TX_CTRL_DATA_WIDTH(ModbusUART_SPI_TX_DATA_BITS_NUM) | \
                     ModbusUART_GET_TX_CTRL_BIT_ORDER (ModbusUART_SPI_BITS_ORDER)       | \
                     ModbusUART_SPI_TX_CTRL)

    #define ModbusUART_SPI_DEFAULT_TX_FIFO_CTRL \
                    ModbusUART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(ModbusUART_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define ModbusUART_SPI_DEFAULT_INTR_SPI_EC_MASK   (ModbusUART_NO_INTR_SOURCES)

    #define ModbusUART_SPI_DEFAULT_INTR_I2C_EC_MASK   (ModbusUART_NO_INTR_SOURCES)
    #define ModbusUART_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (ModbusUART_SPI_INTR_RX_MASK & ModbusUART_INTR_SLAVE_SPI_BUS_ERROR)

    #define ModbusUART_SPI_DEFAULT_INTR_MASTER_MASK \
                    (ModbusUART_SPI_INTR_TX_MASK & ModbusUART_INTR_MASTER_SPI_DONE)

    #define ModbusUART_SPI_DEFAULT_INTR_RX_MASK \
                    (ModbusUART_SPI_INTR_RX_MASK & (uint32) ~ModbusUART_INTR_SLAVE_SPI_BUS_ERROR)

    #define ModbusUART_SPI_DEFAULT_INTR_TX_MASK \
                    (ModbusUART_SPI_INTR_TX_MASK & (uint32) ~ModbusUART_INTR_MASTER_SPI_DONE)

#endif /* (ModbusUART_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define ModbusUART_CTRL_UART      (ModbusUART_CTRL_MODE_UART)
#define ModbusUART_UART_RX_CTRL   (ModbusUART_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define ModbusUART_UART_TX_CTRL   (ModbusUART_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(ModbusUART_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(ModbusUART_UART_MODE_IRDA == ModbusUART_UART_SUB_MODE)

        #define ModbusUART_DEFAULT_CTRL_OVS   ((0u != ModbusUART_UART_IRDA_LOW_POWER) ?              \
                                (ModbusUART_UART_GET_CTRL_OVS_IRDA_LP(ModbusUART_UART_OVS_FACTOR)) : \
                                (ModbusUART_CTRL_OVS_IRDA_OVS16))

    #else

        #define ModbusUART_DEFAULT_CTRL_OVS   ModbusUART_GET_CTRL_OVS(ModbusUART_UART_OVS_FACTOR)

    #endif /* (ModbusUART_UART_MODE_IRDA == ModbusUART_UART_SUB_MODE) */

    #define ModbusUART_UART_DEFAULT_CTRL \
                                (ModbusUART_GET_CTRL_ADDR_ACCEPT(ModbusUART_UART_MP_ACCEPT_ADDRESS) | \
                                 ModbusUART_DEFAULT_CTRL_OVS                                              | \
                                 ModbusUART_CTRL_UART)

    #define ModbusUART_UART_DEFAULT_UART_CTRL \
                                    (ModbusUART_GET_UART_CTRL_MODE(ModbusUART_UART_SUB_MODE))

    /* RX direction */
    #define ModbusUART_UART_DEFAULT_RX_CTRL_PARITY \
                                ((ModbusUART_UART_PARITY_NONE != ModbusUART_UART_PARITY_TYPE) ?      \
                                  (ModbusUART_GET_UART_RX_CTRL_PARITY(ModbusUART_UART_PARITY_TYPE) | \
                                   ModbusUART_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define ModbusUART_UART_DEFAULT_UART_RX_CTRL \
                    (ModbusUART_GET_UART_RX_CTRL_MODE(ModbusUART_UART_STOP_BITS_NUM)                    | \
                     ModbusUART_GET_UART_RX_CTRL_POLARITY(ModbusUART_UART_IRDA_POLARITY)                | \
                     ModbusUART_GET_UART_RX_CTRL_MP_MODE(ModbusUART_UART_MP_MODE_ENABLE)                | \
                     ModbusUART_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(ModbusUART_UART_DROP_ON_PARITY_ERR) | \
                     ModbusUART_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(ModbusUART_UART_DROP_ON_FRAME_ERR)   | \
                     ModbusUART_UART_DEFAULT_RX_CTRL_PARITY)

    #define ModbusUART_UART_DEFAULT_RX_CTRL \
                                (ModbusUART_GET_RX_CTRL_DATA_WIDTH(ModbusUART_UART_DATA_BITS_NUM)        | \
                                 ModbusUART_GET_RX_CTRL_MEDIAN    (ModbusUART_UART_MEDIAN_FILTER_ENABLE) | \
                                 ModbusUART_GET_UART_RX_CTRL_ENABLED(ModbusUART_UART_DIRECTION))

    #define ModbusUART_UART_DEFAULT_RX_FIFO_CTRL \
                                ModbusUART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(ModbusUART_UART_RX_TRIGGER_LEVEL)

    #define ModbusUART_UART_DEFAULT_RX_MATCH_REG  ((0u != ModbusUART_UART_MP_MODE_ENABLE) ?          \
                                (ModbusUART_GET_RX_MATCH_ADDR(ModbusUART_UART_MP_RX_ADDRESS) | \
                                 ModbusUART_GET_RX_MATCH_MASK(ModbusUART_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define ModbusUART_UART_DEFAULT_TX_CTRL_PARITY (ModbusUART_UART_DEFAULT_RX_CTRL_PARITY)

    #define ModbusUART_UART_DEFAULT_UART_TX_CTRL \
                                (ModbusUART_GET_UART_TX_CTRL_MODE(ModbusUART_UART_STOP_BITS_NUM)       | \
                                 ModbusUART_GET_UART_TX_CTRL_RETRY_NACK(ModbusUART_UART_RETRY_ON_NACK) | \
                                 ModbusUART_UART_DEFAULT_TX_CTRL_PARITY)

    #define ModbusUART_UART_DEFAULT_TX_CTRL \
                                (ModbusUART_GET_TX_CTRL_DATA_WIDTH(ModbusUART_UART_DATA_BITS_NUM) | \
                                 ModbusUART_GET_UART_TX_CTRL_ENABLED(ModbusUART_UART_DIRECTION))

    #define ModbusUART_UART_DEFAULT_TX_FIFO_CTRL \
                                ModbusUART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(ModbusUART_UART_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define ModbusUART_UART_DEFAULT_INTR_I2C_EC_MASK  (ModbusUART_NO_INTR_SOURCES)
    #define ModbusUART_UART_DEFAULT_INTR_SPI_EC_MASK  (ModbusUART_NO_INTR_SOURCES)
    #define ModbusUART_UART_DEFAULT_INTR_SLAVE_MASK   (ModbusUART_NO_INTR_SOURCES)
    #define ModbusUART_UART_DEFAULT_INTR_MASTER_MASK  (ModbusUART_NO_INTR_SOURCES)
    #define ModbusUART_UART_DEFAULT_INTR_RX_MASK      (ModbusUART_UART_INTR_RX_MASK)
    #define ModbusUART_UART_DEFAULT_INTR_TX_MASK      (ModbusUART_UART_INTR_TX_MASK)

#endif /* (ModbusUART_SCB_MODE_UART_CONST_CFG) */

#endif /* CY_SCB_SPI_UART_ModbusUART_H */


/* [] END OF FILE */
