/*******************************************************************************
* File Name: ModbusComms_UART.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
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


#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Config Structure Initialization
    ***************************************/

    const ModbusComms_UART_INIT_STRUCT ModbusComms_configUart =
    {
        ModbusComms_UART_SUB_MODE,
        ModbusComms_UART_DIRECTION,
        ModbusComms_UART_DATA_BITS_NUM,
        ModbusComms_UART_PARITY_TYPE,
        ModbusComms_UART_STOP_BITS_NUM,
        ModbusComms_UART_OVS_FACTOR,
        ModbusComms_UART_IRDA_LOW_POWER,
        ModbusComms_UART_MEDIAN_FILTER_ENABLE,
        ModbusComms_UART_RETRY_ON_NACK,
        ModbusComms_UART_IRDA_POLARITY,
        ModbusComms_UART_DROP_ON_PARITY_ERR,
        ModbusComms_UART_DROP_ON_FRAME_ERR,
        ModbusComms_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        ModbusComms_UART_MP_MODE_ENABLE,
        ModbusComms_UART_MP_ACCEPT_ADDRESS,
        ModbusComms_UART_MP_RX_ADDRESS,
        ModbusComms_UART_MP_RX_ADDRESS_MASK,
        ModbusComms_SCB_IRQ_INTERNAL,
        ModbusComms_UART_INTR_RX_MASK,
        ModbusComms_UART_RX_TRIGGER_LEVEL,
        ModbusComms_UART_INTR_TX_MASK,
        ModbusComms_UART_TX_TRIGGER_LEVEL
    };


    /*******************************************************************************
    * Function Name: ModbusComms_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for SPI operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusComms_UartInit(const ModbusComms_UART_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due bad fucntion parameter */
        }
        else
        {
            /* Configure pins */
            ModbusComms_SetPins(ModbusComms_SCB_MODE_UART, config->mode, config->direction);

            /* Store internal configuration */
            ModbusComms_scbMode       = (uint8) ModbusComms_SCB_MODE_UART;
            ModbusComms_scbEnableWake = (uint8) config->enableWake;
            ModbusComms_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            ModbusComms_rxBuffer      =         config->rxBuffer;
            ModbusComms_rxDataBits    = (uint8) config->dataBits;
            ModbusComms_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            ModbusComms_txBuffer      =         config->txBuffer;
            ModbusComms_txDataBits    = (uint8) config->dataBits;
            ModbusComms_txBufferSize  = (uint8) config->txBufferSize;


            /* Configure UART interface */
            if(ModbusComms_UART_MODE_IRDA == config->mode)
            {
                /* OVS settigns: IrDA */
                ModbusComms_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (ModbusComms_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (ModbusComms_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settigns: UART and SmartCard */
                ModbusComms_CTRL_REG  = ModbusComms_GET_CTRL_OVS(config->oversample);
            }

            ModbusComms_CTRL_REG     |= ModbusComms_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             ModbusComms_CTRL_UART;

            /* Confiuure submode: UART, SmartCard or IrDA */
            ModbusComms_UART_CTRL_REG = ModbusComms_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            ModbusComms_UART_RX_CTRL_REG = ModbusComms_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        ModbusComms_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        ModbusComms_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        ModbusComms_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        ModbusComms_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(ModbusComms_UART_PARITY_NONE != config->parity)
            {
               ModbusComms_UART_RX_CTRL_REG |= ModbusComms_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    ModbusComms_UART_RX_CTRL_PARITY_ENABLED;
            }

            ModbusComms_RX_CTRL_REG      = ModbusComms_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                ModbusComms_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                ModbusComms_GET_UART_RX_CTRL_ENABLED(config->direction);

            ModbusComms_RX_FIFO_CTRL_REG = ModbusComms_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            ModbusComms_RX_MATCH_REG     = ModbusComms_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                ModbusComms_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            ModbusComms_UART_TX_CTRL_REG = ModbusComms_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                ModbusComms_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(ModbusComms_UART_PARITY_NONE != config->parity)
            {
               ModbusComms_UART_TX_CTRL_REG |= ModbusComms_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    ModbusComms_UART_TX_CTRL_PARITY_ENABLED;
            }

            ModbusComms_TX_CTRL_REG      = ModbusComms_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                ModbusComms_GET_UART_TX_CTRL_ENABLED(config->direction);

            ModbusComms_TX_FIFO_CTRL_REG = ModbusComms_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);


            /* Configure WAKE interrupt */
            #if(ModbusComms_UART_RX_WAKEUP_IRQ)
                ModbusComms_RX_WAKEUP_IRQ_StartEx(&ModbusComms_UART_WAKEUP_ISR);
                ModbusComms_RX_WAKEUP_IRQ_Disable();
            #endif /* (ModbusComms_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt with UART handler */
            ModbusComms_SCB_IRQ_Disable();
            ModbusComms_SCB_IRQ_SetVector(&ModbusComms_SPI_UART_ISR);
            ModbusComms_SCB_IRQ_SetPriority((uint8)ModbusComms_SCB_IRQ_INTC_PRIOR_NUMBER);

            /* Configure interrupt sources */
            ModbusComms_INTR_I2C_EC_MASK_REG = ModbusComms_NO_INTR_SOURCES;
            ModbusComms_INTR_SPI_EC_MASK_REG = ModbusComms_NO_INTR_SOURCES;
            ModbusComms_INTR_SLAVE_MASK_REG  = ModbusComms_NO_INTR_SOURCES;
            ModbusComms_INTR_MASTER_MASK_REG = ModbusComms_NO_INTR_SOURCES;
            ModbusComms_INTR_RX_MASK_REG     = config->rxInterruptMask;
            ModbusComms_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            ModbusComms_rxBufferHead     = 0u;
            ModbusComms_rxBufferTail     = 0u;
            ModbusComms_rxBufferOverflow = 0u;

            /* Clrea TX buffer indexes */
            ModbusComms_txBufferHead = 0u;
            ModbusComms_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: ModbusComms_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for SPI operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusComms_UartInit(void)
    {
        /* Configure UART interface */
        ModbusComms_CTRL_REG = ModbusComms_UART_DEFAULT_CTRL;

        /* Confiuure submode: UART, SmartCard or IrDA */
        ModbusComms_UART_CTRL_REG = ModbusComms_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        ModbusComms_UART_RX_CTRL_REG = ModbusComms_UART_DEFAULT_UART_RX_CTRL;
        ModbusComms_RX_CTRL_REG      = ModbusComms_UART_DEFAULT_RX_CTRL;
        ModbusComms_RX_FIFO_CTRL_REG = ModbusComms_UART_DEFAULT_RX_FIFO_CTRL;
        ModbusComms_RX_MATCH_REG     = ModbusComms_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        ModbusComms_UART_TX_CTRL_REG = ModbusComms_UART_DEFAULT_UART_TX_CTRL;
        ModbusComms_TX_CTRL_REG      = ModbusComms_UART_DEFAULT_TX_CTRL;
        ModbusComms_TX_FIFO_CTRL_REG = ModbusComms_UART_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with UART handler */
        #if(ModbusComms_SCB_IRQ_INTERNAL)
            ModbusComms_SCB_IRQ_Disable();
            ModbusComms_SCB_IRQ_SetVector(&ModbusComms_SPI_UART_ISR);
            ModbusComms_SCB_IRQ_SetPriority((uint8)ModbusComms_SCB_IRQ_INTC_PRIOR_NUMBER);
        #endif /* (ModbusComms_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
        #if(ModbusComms_UART_RX_WAKEUP_IRQ)
            ModbusComms_RX_WAKEUP_IRQ_StartEx(&ModbusComms_UART_WAKEUP_ISR);
            ModbusComms_RX_WAKEUP_IRQ_Disable();
        #endif /* (ModbusComms_UART_RX_WAKEUP_IRQ) */
        
        /* Configure interrupt sources */
        ModbusComms_INTR_I2C_EC_MASK_REG = ModbusComms_UART_DEFAULT_INTR_I2C_EC_MASK;
        ModbusComms_INTR_SPI_EC_MASK_REG = ModbusComms_UART_DEFAULT_INTR_SPI_EC_MASK;
        ModbusComms_INTR_SLAVE_MASK_REG  = ModbusComms_UART_DEFAULT_INTR_SLAVE_MASK;
        ModbusComms_INTR_MASTER_MASK_REG = ModbusComms_UART_DEFAULT_INTR_MASTER_MASK;
        ModbusComms_INTR_RX_MASK_REG     = ModbusComms_UART_DEFAULT_INTR_RX_MASK;
        ModbusComms_INTR_TX_MASK_REG     = ModbusComms_UART_DEFAULT_INTR_TX_MASK;

        #if(ModbusComms_INTERNAL_RX_SW_BUFFER_CONST)
            ModbusComms_rxBufferHead     = 0u;
            ModbusComms_rxBufferTail     = 0u;
            ModbusComms_rxBufferOverflow = 0u;
        #endif /* (ModbusComms_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(ModbusComms_INTERNAL_TX_SW_BUFFER_CONST)
            ModbusComms_txBufferHead = 0u;
            ModbusComms_txBufferTail = 0u;
        #endif /* (ModbusComms_INTERNAL_TX_SW_BUFFER_CONST) */
    }

#endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: ModbusComms_UartSetRxAddress
********************************************************************************
*
* Summary:
*  Sets the hardware detectable receiver address for the UART in Multiprocessor
*  mode.
*
* Parameters:
*  address: Address for hardware address detection.
*
* Return:
*  None
*
*******************************************************************************/
void ModbusComms_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = ModbusComms_RX_MATCH_REG;

    matchReg &= ((uint32) ~ModbusComms_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & ModbusComms_RX_MATCH_ADDR_MASK)); /* Set address  */

    ModbusComms_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: ModbusComms_UartSetRxAddressMask
********************************************************************************
*
* Summary:
*  Sets the hardware address mask for the UART in Multiprocessor mode.
*
* Parameters:
*  addressMask: Address mask.
*   0 - address bit does not care while comparison.
*   1 - address bit is significant while comparison.
*
* Return:
*  None
*
*******************************************************************************/
void ModbusComms_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = ModbusComms_RX_MATCH_REG;

    matchReg &= ((uint32) ~ModbusComms_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << ModbusComms_RX_MATCH_MASK_POS));

    ModbusComms_RX_MATCH_REG = matchReg;
}


#if(ModbusComms_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: ModbusComms_UartGetChar
    ********************************************************************************
    *
    * Summary:
    *  Retrieves next data element from receive buffer.
    *  This function is designed for ASCII characters and returns a char
    *  where 1 to 255 is valid characters and 0 indicates an error occurred or
    *  no data is present.
    *  RX software buffer disabled: returns data element retrieved from RX FIFO.
    *  Undefined data will be returned if the RX FIFO is empty.
    *  RX software buffer enabled: Returns data element from the software receive
    *  buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Next data element from the receive buffer.
    *  ASCII character values from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    *******************************************************************************/
    uint32 ModbusComms_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Read data only if there is data to read */
        if(0u != ModbusComms_SpiUartGetRxBufferSize())
        {
            rxData = ModbusComms_SpiUartReadRxData();
        }

        if(ModbusComms_CHECK_INTR_RX(ModbusComms_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occured: return zero */
            ModbusComms_ClearRxInterruptSource(ModbusComms_INTR_RX_ERR);
        }

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: ModbusComms_UartGetByte
    ********************************************************************************
    *
    * Summary:
    *  Retrieves next data element from the receive buffer, returns received byte
    *  and error condition.
    *  RX software buffer disabled: Returns data element retrieved from RX FIFO.
    *  Undefined data will be returned if the RX FIFO is empty.
    *  RX software buffer enabled: Returns data element from the software receive
    *  buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Bits 15-8 contains status and bits 7-0 contains the next data element from
    *  receive buffer. If the bits 15-8 are nonzero, an error has occurred.
    *
    *******************************************************************************/
    uint32 ModbusComms_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;
        uint32 intSourceMask;

        intSourceMask = ModbusComms_SpiUartDisableIntRx();

        if(0u != ModbusComms_SpiUartGetRxBufferSize())
        {
             /*
             * Enable interrupt to receive more bytes: at least one byte is in
             * buffer.
             */
            ModbusComms_SpiUartEnableIntRx(intSourceMask);

            /* Get received byte */
            rxData = ModbusComms_SpiUartReadRxData();
        }
        else
        {
            /*
            * Read byte directly from RX FIFO: the underflow is raised in case
            * of empty. In other case the first received byte will be read.
            */
            rxData = ModbusComms_RX_FIFO_RD_REG;

            /*
            * Enable interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by interrupt routine in case
            * byte was received and read above.
            */
            ModbusComms_SpiUartEnableIntRx(intSourceMask);
        }

        /* Get and clear RX error mask */
        tmpStatus = (ModbusComms_GetRxInterruptSource() & ModbusComms_INTR_RX_ERR);
        ModbusComms_ClearRxInterruptSource(ModbusComms_INTR_RX_ERR);

        /*
        * Put together data and error status:
        * MP mode and accept address: the 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return(rxData);
    }

#endif /* (ModbusComms_UART_RX_DIRECTION) */


#if(ModbusComms_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: ModbusComms_UartPutString
    ********************************************************************************
    *
    * Summary:
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is a space available to put
    *  all requested data in transmit buffer.
    *
    * Parameters:
    *  string: pointer to the null terminated string array to be placed in the
    *          transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusComms_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data will be sent */
        while(string[bufIndex] != ((char8) 0))
        {
            ModbusComms_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: ModbusComms_UartPutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Places byte of data followed by a carriage return (0x0D) and line feed (0x0A)
    *  to the transmit buffer.
    *  This function is blocking and waits until there is a space available to put
    *  all requested data in transmit buffer.
    *
    * Parameters:
    *  txDataByte : the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusComms_UartPutCRLF(uint32 txDataByte)
    {
        ModbusComms_UartPutChar(txDataByte);  /* Blocks the control flow until all data will be sent */
        ModbusComms_UartPutChar(0x0Du);       /* Blocks the control flow until all data will be sent */
        ModbusComms_UartPutChar(0x0Au);       /* Blocks the control flow until all data will be sent */
    }
#endif /* (ModbusComms_UART_TX_DIRECTION) */


#if(ModbusComms_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: ModbusComms_UartSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Wakeup disabled: does nothing.
    *  Wakeup enabled: clears SCB_backup.enableStateto keep component enabled while
    *  DeepSleep. Clears and enables interrupt on falling edge of rx input. The GPIO
    *  event wakes up the device and SKIP_START feature allows UART continue
    *  receiving data bytes properly. The GPIO interrupt does not track in active mode
    *  therefore requires to be cleared by this API. It makes uart wakeup single
    *  triggered event.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusComms_UartSaveConfig(void)
    {
        /* Clear interrupt activy:
        *  - set skip start and disable RX. On GPIO wakeup the RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers while normal operations.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        ModbusComms_UART_RX_CTRL_REG |= ModbusComms_UART_RX_CTRL_SKIP_START;

        #if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
            #if(ModbusComms_MOSI_SCL_RX_WAKE_PIN)
                (void) ModbusComms_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
            #endif /* (ModbusComms_MOSI_SCL_RX_WAKE_PIN) */
        #else
            #if(ModbusComms_UART_RX_WAKE_PIN)
                (void) ModbusComms_rx_wake_ClearInterrupt();
            #endif /* (ModbusComms_UART_RX_WAKE_PIN) */
        #endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */

        #if(ModbusComms_UART_RX_WAKEUP_IRQ)
            ModbusComms_RX_WAKEUP_IRQ_ClearPending();
            ModbusComms_RX_WAKEUP_IRQ_Enable();
        #endif /* (ModbusComms_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: ModbusComms_UartRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Does nothing.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusComms_UartRestoreConfig(void)
    {
        /* Disable RX GPIO interrupt: no more triggers in active mode */
        #if(ModbusComms_UART_RX_WAKEUP_IRQ)
            ModbusComms_RX_WAKEUP_IRQ_Disable();
        #endif /* (ModbusComms_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (ModbusComms_UART_WAKE_ENABLE_CONST) */


#if(ModbusComms_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: ModbusComms_UART_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles Interrupt Service Routine for SCB UART mode GPIO wakeup event.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR(ModbusComms_UART_WAKEUP_ISR)
    {
        /* Clear interrupt source: the event becomes multi triggerred and only disabled
        * by ModbusComms_UartRestoreConfig() call.
        */
        #if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
            #if(ModbusComms_MOSI_SCL_RX_WAKE_PIN)
                (void) ModbusComms_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
            #endif /* (ModbusComms_MOSI_SCL_RX_WAKE_PIN) */
        #else
            #if(ModbusComms_UART_RX_WAKE_PIN)
                (void) ModbusComms_rx_wake_ClearInterrupt();
            #endif /* (ModbusComms_UART_RX_WAKE_PIN) */
        #endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */
    }
#endif /* (ModbusComms_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
