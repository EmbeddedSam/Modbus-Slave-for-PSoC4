/*******************************************************************************
* File Name: ModbusUART_UART.c
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

#include "ModbusUART_PVT.h"
#include "ModbusUART_SPI_UART_PVT.h"


#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Config Structure Initialization
    ***************************************/

    const ModbusUART_UART_INIT_STRUCT ModbusUART_configUart =
    {
        ModbusUART_UART_SUB_MODE,
        ModbusUART_UART_DIRECTION,
        ModbusUART_UART_DATA_BITS_NUM,
        ModbusUART_UART_PARITY_TYPE,
        ModbusUART_UART_STOP_BITS_NUM,
        ModbusUART_UART_OVS_FACTOR,
        ModbusUART_UART_IRDA_LOW_POWER,
        ModbusUART_UART_MEDIAN_FILTER_ENABLE,
        ModbusUART_UART_RETRY_ON_NACK,
        ModbusUART_UART_IRDA_POLARITY,
        ModbusUART_UART_DROP_ON_PARITY_ERR,
        ModbusUART_UART_DROP_ON_FRAME_ERR,
        ModbusUART_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        ModbusUART_UART_MP_MODE_ENABLE,
        ModbusUART_UART_MP_ACCEPT_ADDRESS,
        ModbusUART_UART_MP_RX_ADDRESS,
        ModbusUART_UART_MP_RX_ADDRESS_MASK,
        ModbusUART_SCB_IRQ_INTERNAL,
        ModbusUART_UART_INTR_RX_MASK,
        ModbusUART_UART_RX_TRIGGER_LEVEL,
        ModbusUART_UART_INTR_TX_MASK,
        ModbusUART_UART_TX_TRIGGER_LEVEL
    };


    /*******************************************************************************
    * Function Name: ModbusUART_UartInit
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
    void ModbusUART_UartInit(const ModbusUART_UART_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due bad fucntion parameter */
        }
        else
        {
            /* Configure pins */
            ModbusUART_SetPins(ModbusUART_SCB_MODE_UART, config->mode, config->direction);

            /* Store internal configuration */
            ModbusUART_scbMode       = (uint8) ModbusUART_SCB_MODE_UART;
            ModbusUART_scbEnableWake = (uint8) config->enableWake;
            ModbusUART_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            ModbusUART_rxBuffer      =         config->rxBuffer;
            ModbusUART_rxDataBits    = (uint8) config->dataBits;
            ModbusUART_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            ModbusUART_txBuffer      =         config->txBuffer;
            ModbusUART_txDataBits    = (uint8) config->dataBits;
            ModbusUART_txBufferSize  = (uint8) config->txBufferSize;


            /* Configure UART interface */
            if(ModbusUART_UART_MODE_IRDA == config->mode)
            {
                /* OVS settigns: IrDA */
                ModbusUART_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (ModbusUART_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (ModbusUART_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settigns: UART and SmartCard */
                ModbusUART_CTRL_REG  = ModbusUART_GET_CTRL_OVS(config->oversample);
            }

            ModbusUART_CTRL_REG     |= ModbusUART_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             ModbusUART_CTRL_UART;

            /* Confiuure submode: UART, SmartCard or IrDA */
            ModbusUART_UART_CTRL_REG = ModbusUART_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            ModbusUART_UART_RX_CTRL_REG = ModbusUART_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        ModbusUART_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        ModbusUART_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        ModbusUART_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        ModbusUART_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(ModbusUART_UART_PARITY_NONE != config->parity)
            {
               ModbusUART_UART_RX_CTRL_REG |= ModbusUART_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    ModbusUART_UART_RX_CTRL_PARITY_ENABLED;
            }

            ModbusUART_RX_CTRL_REG      = ModbusUART_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                ModbusUART_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                ModbusUART_GET_UART_RX_CTRL_ENABLED(config->direction);

            ModbusUART_RX_FIFO_CTRL_REG = ModbusUART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            ModbusUART_RX_MATCH_REG     = ModbusUART_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                ModbusUART_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            ModbusUART_UART_TX_CTRL_REG = ModbusUART_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                ModbusUART_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(ModbusUART_UART_PARITY_NONE != config->parity)
            {
               ModbusUART_UART_TX_CTRL_REG |= ModbusUART_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    ModbusUART_UART_TX_CTRL_PARITY_ENABLED;
            }

            ModbusUART_TX_CTRL_REG      = ModbusUART_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                ModbusUART_GET_UART_TX_CTRL_ENABLED(config->direction);

            ModbusUART_TX_FIFO_CTRL_REG = ModbusUART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);


            /* Configure WAKE interrupt */
            #if(ModbusUART_UART_RX_WAKEUP_IRQ)
                ModbusUART_RX_WAKEUP_IRQ_StartEx(&ModbusUART_UART_WAKEUP_ISR);
                ModbusUART_RX_WAKEUP_IRQ_Disable();
            #endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt with UART handler */
            ModbusUART_SCB_IRQ_Disable();
            ModbusUART_SCB_IRQ_SetVector(&ModbusUART_SPI_UART_ISR);
            ModbusUART_SCB_IRQ_SetPriority((uint8)ModbusUART_SCB_IRQ_INTC_PRIOR_NUMBER);

            /* Configure interrupt sources */
            ModbusUART_INTR_I2C_EC_MASK_REG = ModbusUART_NO_INTR_SOURCES;
            ModbusUART_INTR_SPI_EC_MASK_REG = ModbusUART_NO_INTR_SOURCES;
            ModbusUART_INTR_SLAVE_MASK_REG  = ModbusUART_NO_INTR_SOURCES;
            ModbusUART_INTR_MASTER_MASK_REG = ModbusUART_NO_INTR_SOURCES;
            ModbusUART_INTR_RX_MASK_REG     = config->rxInterruptMask;
            ModbusUART_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            ModbusUART_rxBufferHead     = 0u;
            ModbusUART_rxBufferTail     = 0u;
            ModbusUART_rxBufferOverflow = 0u;

            /* Clrea TX buffer indexes */
            ModbusUART_txBufferHead = 0u;
            ModbusUART_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: ModbusUART_UartInit
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
    void ModbusUART_UartInit(void)
    {
        /* Configure UART interface */
        ModbusUART_CTRL_REG = ModbusUART_UART_DEFAULT_CTRL;

        /* Confiuure submode: UART, SmartCard or IrDA */
        ModbusUART_UART_CTRL_REG = ModbusUART_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        ModbusUART_UART_RX_CTRL_REG = ModbusUART_UART_DEFAULT_UART_RX_CTRL;
        ModbusUART_RX_CTRL_REG      = ModbusUART_UART_DEFAULT_RX_CTRL;
        ModbusUART_RX_FIFO_CTRL_REG = ModbusUART_UART_DEFAULT_RX_FIFO_CTRL;
        ModbusUART_RX_MATCH_REG     = ModbusUART_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        ModbusUART_UART_TX_CTRL_REG = ModbusUART_UART_DEFAULT_UART_TX_CTRL;
        ModbusUART_TX_CTRL_REG      = ModbusUART_UART_DEFAULT_TX_CTRL;
        ModbusUART_TX_FIFO_CTRL_REG = ModbusUART_UART_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with UART handler */
        #if(ModbusUART_SCB_IRQ_INTERNAL)
            ModbusUART_SCB_IRQ_Disable();
            ModbusUART_SCB_IRQ_SetVector(&ModbusUART_SPI_UART_ISR);
            ModbusUART_SCB_IRQ_SetPriority((uint8)ModbusUART_SCB_IRQ_INTC_PRIOR_NUMBER);
        #endif /* (ModbusUART_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
        #if(ModbusUART_UART_RX_WAKEUP_IRQ)
            ModbusUART_RX_WAKEUP_IRQ_StartEx(&ModbusUART_UART_WAKEUP_ISR);
            ModbusUART_RX_WAKEUP_IRQ_Disable();
        #endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */
        
        /* Configure interrupt sources */
        ModbusUART_INTR_I2C_EC_MASK_REG = ModbusUART_UART_DEFAULT_INTR_I2C_EC_MASK;
        ModbusUART_INTR_SPI_EC_MASK_REG = ModbusUART_UART_DEFAULT_INTR_SPI_EC_MASK;
        ModbusUART_INTR_SLAVE_MASK_REG  = ModbusUART_UART_DEFAULT_INTR_SLAVE_MASK;
        ModbusUART_INTR_MASTER_MASK_REG = ModbusUART_UART_DEFAULT_INTR_MASTER_MASK;
        ModbusUART_INTR_RX_MASK_REG     = ModbusUART_UART_DEFAULT_INTR_RX_MASK;
        ModbusUART_INTR_TX_MASK_REG     = ModbusUART_UART_DEFAULT_INTR_TX_MASK;

        #if(ModbusUART_INTERNAL_RX_SW_BUFFER_CONST)
            ModbusUART_rxBufferHead     = 0u;
            ModbusUART_rxBufferTail     = 0u;
            ModbusUART_rxBufferOverflow = 0u;
        #endif /* (ModbusUART_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(ModbusUART_INTERNAL_TX_SW_BUFFER_CONST)
            ModbusUART_txBufferHead = 0u;
            ModbusUART_txBufferTail = 0u;
        #endif /* (ModbusUART_INTERNAL_TX_SW_BUFFER_CONST) */
    }

#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: ModbusUART_UartSetRxAddress
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
void ModbusUART_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = ModbusUART_RX_MATCH_REG;

    matchReg &= ((uint32) ~ModbusUART_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & ModbusUART_RX_MATCH_ADDR_MASK)); /* Set address  */

    ModbusUART_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: ModbusUART_UartSetRxAddressMask
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
void ModbusUART_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = ModbusUART_RX_MATCH_REG;

    matchReg &= ((uint32) ~ModbusUART_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << ModbusUART_RX_MATCH_MASK_POS));

    ModbusUART_RX_MATCH_REG = matchReg;
}


#if(ModbusUART_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: ModbusUART_UartGetChar
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
    uint32 ModbusUART_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Read data only if there is data to read */
        if(0u != ModbusUART_SpiUartGetRxBufferSize())
        {
            rxData = ModbusUART_SpiUartReadRxData();
        }

        if(ModbusUART_CHECK_INTR_RX(ModbusUART_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occured: return zero */
            ModbusUART_ClearRxInterruptSource(ModbusUART_INTR_RX_ERR);
        }

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: ModbusUART_UartGetByte
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
    uint32 ModbusUART_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;
        uint32 intSourceMask;

        intSourceMask = ModbusUART_SpiUartDisableIntRx();

        if(0u != ModbusUART_SpiUartGetRxBufferSize())
        {
             /*
             * Enable interrupt to receive more bytes: at least one byte is in
             * buffer.
             */
            ModbusUART_SpiUartEnableIntRx(intSourceMask);

            /* Get received byte */
            rxData = ModbusUART_SpiUartReadRxData();
        }
        else
        {
            /*
            * Read byte directly from RX FIFO: the underflow is raised in case
            * of empty. In other case the first received byte will be read.
            */
            rxData = ModbusUART_RX_FIFO_RD_REG;

            /*
            * Enable interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by interrupt routine in case
            * byte was received and read above.
            */
            ModbusUART_SpiUartEnableIntRx(intSourceMask);
        }

        /* Get and clear RX error mask */
        tmpStatus = (ModbusUART_GetRxInterruptSource() & ModbusUART_INTR_RX_ERR);
        ModbusUART_ClearRxInterruptSource(ModbusUART_INTR_RX_ERR);

        /*
        * Put together data and error status:
        * MP mode and accept address: the 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return(rxData);
    }

#endif /* (ModbusUART_UART_RX_DIRECTION) */


#if(ModbusUART_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: ModbusUART_UartPutString
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
    void ModbusUART_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data will be sent */
        while(string[bufIndex] != ((char8) 0))
        {
            ModbusUART_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: ModbusUART_UartPutCRLF
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
    void ModbusUART_UartPutCRLF(uint32 txDataByte)
    {
        ModbusUART_UartPutChar(txDataByte);  /* Blocks the control flow until all data will be sent */
        ModbusUART_UartPutChar(0x0Du);       /* Blocks the control flow until all data will be sent */
        ModbusUART_UartPutChar(0x0Au);       /* Blocks the control flow until all data will be sent */
    }
#endif /* (ModbusUART_UART_TX_DIRECTION) */


#if(ModbusUART_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: ModbusUART_UartSaveConfig
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
    void ModbusUART_UartSaveConfig(void)
    {
        /* Clear interrupt activy:
        *  - set skip start and disable RX. On GPIO wakeup the RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers while normal operations.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        ModbusUART_UART_RX_CTRL_REG |= ModbusUART_UART_RX_CTRL_SKIP_START;

        #if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
            #if(ModbusUART_MOSI_SCL_RX_WAKE_PIN)
                (void) ModbusUART_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
            #endif /* (ModbusUART_MOSI_SCL_RX_WAKE_PIN) */
        #else
            #if(ModbusUART_UART_RX_WAKE_PIN)
                (void) ModbusUART_rx_wake_ClearInterrupt();
            #endif /* (ModbusUART_UART_RX_WAKE_PIN) */
        #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */

        #if(ModbusUART_UART_RX_WAKEUP_IRQ)
            ModbusUART_RX_WAKEUP_IRQ_ClearPending();
            ModbusUART_RX_WAKEUP_IRQ_Enable();
        #endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: ModbusUART_UartRestoreConfig
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
    void ModbusUART_UartRestoreConfig(void)
    {
        /* Disable RX GPIO interrupt: no more triggers in active mode */
        #if(ModbusUART_UART_RX_WAKEUP_IRQ)
            ModbusUART_RX_WAKEUP_IRQ_Disable();
        #endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (ModbusUART_UART_WAKE_ENABLE_CONST) */


#if(ModbusUART_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: ModbusUART_UART_WAKEUP_ISR
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
    CY_ISR(ModbusUART_UART_WAKEUP_ISR)
    {
        /* Clear interrupt source: the event becomes multi triggerred and only disabled
        * by ModbusUART_UartRestoreConfig() call.
        */
        #if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
            #if(ModbusUART_MOSI_SCL_RX_WAKE_PIN)
                (void) ModbusUART_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
            #endif /* (ModbusUART_MOSI_SCL_RX_WAKE_PIN) */
        #else
            #if(ModbusUART_UART_RX_WAKE_PIN)
                (void) ModbusUART_rx_wake_ClearInterrupt();
            #endif /* (ModbusUART_UART_RX_WAKE_PIN) */
        #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
    }
#endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
