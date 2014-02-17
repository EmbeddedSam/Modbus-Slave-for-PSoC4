/*******************************************************************************
* File Name: ModbusUART.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the SCB Component.
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

#if(ModbusUART_SCB_MODE_I2C_INC)
    #include "ModbusUART_I2C_PVT.h"
#endif /* (ModbusUART_SCB_MODE_I2C_INC) */

#if(ModbusUART_SCB_MODE_EZI2C_INC)
    #include "ModbusUART_EZI2C_PVT.h"
#endif /* (ModbusUART_SCB_MODE_EZI2C_INC) */

#if(ModbusUART_SCB_MODE_SPI_INC || ModbusUART_SCB_MODE_UART_INC)
    #include "ModbusUART_SPI_UART_PVT.h"
#endif /* (ModbusUART_SCB_MODE_SPI_INC || ModbusUART_SCB_MODE_UART_INC) */


/**********************************
*    Run Time Configuration Vars
**********************************/

/* Stores internal component configuration for unconfigured mode */
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common config vars */
    uint8 ModbusUART_scbMode = ModbusUART_SCB_MODE_UNCONFIG;
    uint8 ModbusUART_scbEnableWake;
    uint8 ModbusUART_scbEnableIntr;

    /* I2C config vars */
    uint8 ModbusUART_mode;
    uint8 ModbusUART_acceptAddr;

    /* SPI/UART config vars */
    volatile uint8 * ModbusUART_rxBuffer;
    uint8  ModbusUART_rxDataBits;
    uint32 ModbusUART_rxBufferSize;

    volatile uint8 * ModbusUART_txBuffer;
    uint8  ModbusUART_txDataBits;
    uint32 ModbusUART_txBufferSize;

    /* EZI2C config vars */
    uint8 ModbusUART_numberOfAddr;
    uint8 ModbusUART_subAddrSize;
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */


/**********************************
*     Common SCB Vars
**********************************/

uint8 ModbusUART_initVar = 0u;
cyisraddress ModbusUART_customIntrHandler = NULL;


/***************************************
*    Private Function Prototypes
***************************************/

static void ModbusUART_ScbEnableIntr(void);
static void ModbusUART_ScbModeStop(void);


/*******************************************************************************
* Function Name: ModbusUART_Init
********************************************************************************
*
* Summary:
*  Initializes SCB component to operate in one of selected configurations:
*  I2C, SPI, UART, EZI2C or EZSPI.
*  This function does not do any initialization when configuration is set to
*  Unconfigured SCB.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_Init(void)
{
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    if(ModbusUART_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        ModbusUART_initVar = 0u; /* Clear init var */
    }
    else
    {
        /* Initialization was done before call */
    }

#elif(ModbusUART_SCB_MODE_I2C_CONST_CFG)
    ModbusUART_I2CInit();

#elif(ModbusUART_SCB_MODE_SPI_CONST_CFG)
    ModbusUART_SpiInit();

#elif(ModbusUART_SCB_MODE_UART_CONST_CFG)
    ModbusUART_UartInit();

#elif(ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
    ModbusUART_EzI2CInit();

#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_Enable
********************************************************************************
*
* Summary:
*  Enables SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_Enable(void)
{
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    if(!ModbusUART_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        /* Enable SCB block, only if already configured */
        ModbusUART_CTRL_REG |= ModbusUART_CTRL_ENABLED;
        
        /* Enable interrupt */
        ModbusUART_ScbEnableIntr();
    }
#else
    ModbusUART_CTRL_REG |= ModbusUART_CTRL_ENABLED; /* Enable SCB block */
    
    ModbusUART_ScbEnableIntr();
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call the component is enabled and ready for operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ModbusUART_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void ModbusUART_Start(void)
{
    if(0u == ModbusUART_initVar)
    {
        ModbusUART_initVar = 1u; /* Component was initialized */
        ModbusUART_Init();       /* Initialize component      */
    }

    ModbusUART_Enable();
}


/*******************************************************************************
* Function Name: ModbusUART_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_Stop(void)
{
#if(ModbusUART_SCB_IRQ_INTERNAL)
    ModbusUART_SCB_IRQ_Disable();     /* Disable interrupt before block */
#endif /* (ModbusUART_SCB_IRQ_INTERNAL) */

    ModbusUART_CTRL_REG &= (uint32) ~ModbusUART_CTRL_ENABLED;  /* Disable SCB block */

#if(ModbusUART_SCB_IRQ_INTERNAL)
    ModbusUART_SCB_IRQ_ClearPending(); /* Clear pending interrupt */
#endif /* (ModbusUART_SCB_IRQ_INTERNAL) */
    
    ModbusUART_ScbModeStop(); /* Calls scbMode specific Stop function */
}


/*******************************************************************************
* Function Name: ModbusUART_SetCustomInterruptHandler
********************************************************************************
*
* Summary:
*  Registers a function to be called by the internal interrupt handler.
*  First the function that is registered is called, then the internal interrupt
*  handler performs any operations such as software buffer management functions
*  before the interrupt returns.  It is user's responsibility to not break the
*  software buffer operations. Only one custom handler is supported, which is
*  the function provided by the most recent call.
*  At initialization time no custom handler is registered.
*
* Parameters:
*  func: Pointer to the function to register.
*        The value NULL indicates to remove the current custom interrupt
*        handler.
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_SetCustomInterruptHandler(cyisraddress func)
{
    ModbusUART_customIntrHandler = func; /* Register interrupt handler */
}


/*******************************************************************************
* Function Name: ModbusUART_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables interrupt for specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void ModbusUART_ScbEnableIntr(void)
{
#if(ModbusUART_SCB_IRQ_INTERNAL)
    #if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Enable interrupt source */
        if(0u != ModbusUART_scbEnableIntr)
        {
            ModbusUART_SCB_IRQ_Enable();
        }
    #else
        ModbusUART_SCB_IRQ_Enable();
        
    #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (ModbusUART_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: ModbusUART_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Calls Stop function for specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void ModbusUART_ScbModeStop(void)
{
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    if(ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
    {
        ModbusUART_I2CStop();
    }
    else if(ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        ModbusUART_EzI2CStop();
    }
    else
    {
        /* None of modes above */
    }
#elif(ModbusUART_SCB_MODE_I2C_CONST_CFG)
    ModbusUART_I2CStop();

#elif(ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
    ModbusUART_EzI2CStop();

#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: ModbusUART_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets pins settings accordingly to selected operation mode.
    *  Only available in Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when specific mode of operation
    *  selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Submode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartTxRx:  Direction for UART.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void ModbusUART_SetPins(uint32 mode, uint32 subMode, uint32 uartTxRx)
    {
        uint32 hsiomSel[ModbusUART_SCB_PINS_NUMBER];
        uint32 pinsDm  [ModbusUART_SCB_PINS_NUMBER];
        uint32 i;

        /* Make all unused */
        for(i = 0u; i < ModbusUART_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i] = ModbusUART_HSIOM_DEF_SEL;
            pinsDm[i]   = ModbusUART_PIN_DM_ALG_HIZ;
        }

        /* Choice the Dm and HSIOM */
        if((ModbusUART_SCB_MODE_I2C   == mode) ||
           (ModbusUART_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[ModbusUART_MOSI_SCL_RX_PIN_INDEX] = ModbusUART_HSIOM_I2C_SEL;
            hsiomSel[ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_HSIOM_I2C_SEL;

            pinsDm[ModbusUART_MOSI_SCL_RX_PIN_INDEX] = ModbusUART_PIN_DM_OD_LO;
            pinsDm[ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_PIN_DM_OD_LO;
        }
        else if(ModbusUART_SCB_MODE_SPI == mode)
        {
            hsiomSel[ModbusUART_MOSI_SCL_RX_PIN_INDEX] = ModbusUART_HSIOM_SPI_SEL;
            hsiomSel[ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_HSIOM_SPI_SEL;
            hsiomSel[ModbusUART_SCLK_PIN_INDEX]        = ModbusUART_HSIOM_SPI_SEL;

            if(ModbusUART_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[ModbusUART_MOSI_SCL_RX_PIN_INDEX] = ModbusUART_PIN_DM_DIG_HIZ;
                pinsDm[ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                pinsDm[ModbusUART_SCLK_PIN_INDEX]        = ModbusUART_PIN_DM_DIG_HIZ;

            #if(ModbusUART_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[ModbusUART_SS0_PIN_INDEX] = ModbusUART_HSIOM_SPI_SEL;
                pinsDm  [ModbusUART_SS0_PIN_INDEX] = ModbusUART_PIN_DM_DIG_HIZ;
            #endif /* (ModbusUART_SS1_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[ModbusUART_MOSI_SCL_RX_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                pinsDm[ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_PIN_DM_DIG_HIZ;
                pinsDm[ModbusUART_SCLK_PIN_INDEX]        = ModbusUART_PIN_DM_STRONG;

            #if(ModbusUART_SS0_PIN)
                hsiomSel[ModbusUART_SS0_PIN_INDEX] = ModbusUART_HSIOM_SPI_SEL;
                pinsDm  [ModbusUART_SS0_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
            #endif /* (ModbusUART_SS0_PIN) */

            #if(ModbusUART_SS1_PIN)
                hsiomSel[ModbusUART_SS1_PIN_INDEX] = ModbusUART_HSIOM_SPI_SEL;
                pinsDm  [ModbusUART_SS1_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
            #endif /* (ModbusUART_SS1_PIN) */

            #if(ModbusUART_SS2_PIN)
                hsiomSel[ModbusUART_SS2_PIN_INDEX] = ModbusUART_HSIOM_SPI_SEL;
                pinsDm  [ModbusUART_SS2_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
            #endif /* (ModbusUART_SS2_PIN) */

            #if(ModbusUART_SS3_PIN)
                hsiomSel[ModbusUART_SS3_PIN_INDEX] = ModbusUART_HSIOM_SPI_SEL;
                pinsDm  [ModbusUART_SS3_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
            #endif /* (ModbusUART_SS2_PIN) */
            }
        }
        else /* UART */
        {
            if(ModbusUART_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_HSIOM_UART_SEL;
                pinsDm  [ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if(0u != (ModbusUART_UART_RX & uartTxRx))
                {
                    hsiomSel[ModbusUART_MOSI_SCL_RX_PIN_INDEX] = ModbusUART_HSIOM_UART_SEL;
                    pinsDm  [ModbusUART_MOSI_SCL_RX_PIN_INDEX] = ModbusUART_PIN_DM_DIG_HIZ;
                }

                if(0u != (ModbusUART_UART_TX & uartTxRx))
                {
                    hsiomSel[ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_HSIOM_UART_SEL;
                    pinsDm  [ModbusUART_MISO_SDA_TX_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                }
            }
        }

        /* Condfigure pins: set HSIOM and DM */
        /* Condfigure pins: DR registers configuration remains unchanged for cyfitter_cfg() */

    #if(ModbusUART_MOSI_SCL_RX_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_MOSI_SCL_RX_HSIOM_REG,
                                       ModbusUART_MOSI_SCL_RX_HSIOM_MASK,
                                       ModbusUART_MOSI_SCL_RX_HSIOM_POS,
                                       hsiomSel[ModbusUART_MOSI_SCL_RX_PIN_INDEX]);
    #endif /* (ModbusUART_MOSI_SCL_RX_PIN) */

    #if(ModbusUART_MOSI_SCL_RX_WAKE_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_REG,
                                       ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_MASK,
                                       ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_POS,
                                       hsiomSel[ModbusUART_MOSI_SCL_RX_WAKE_PIN_INDEX]);
    #endif /* (ModbusUART_MOSI_SCL_RX_WAKE_PIN) */

    #if(ModbusUART_MISO_SDA_TX_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_MISO_SDA_TX_HSIOM_REG,
                                       ModbusUART_MISO_SDA_TX_HSIOM_MASK,
                                       ModbusUART_MISO_SDA_TX_HSIOM_POS,
                                       hsiomSel[ModbusUART_MISO_SDA_TX_PIN_INDEX]);
    #endif /* (ModbusUART_MOSI_SCL_RX_PIN) */

    #if(ModbusUART_SCLK_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_SCLK_HSIOM_REG, ModbusUART_SCLK_HSIOM_MASK,
                                       ModbusUART_SCLK_HSIOM_POS, hsiomSel[ModbusUART_SCLK_PIN_INDEX]);
    #endif /* (ModbusUART_SCLK_PIN) */

    #if(ModbusUART_SS0_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_SS0_HSIOM_REG, ModbusUART_SS0_HSIOM_MASK,
                                       ModbusUART_SS0_HSIOM_POS, hsiomSel[ModbusUART_SS0_PIN_INDEX]);
    #endif /* (ModbusUART_SS1_PIN) */

    #if(ModbusUART_SS1_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_SS1_HSIOM_REG, ModbusUART_SS1_HSIOM_MASK,
                                       ModbusUART_SS1_HSIOM_POS, hsiomSel[ModbusUART_SS1_PIN_INDEX]);
    #endif /* (ModbusUART_SS1_PIN) */

    #if(ModbusUART_SS2_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_SS2_HSIOM_REG, ModbusUART_SS2_HSIOM_MASK,
                                       ModbusUART_SS2_HSIOM_POS, hsiomSel[ModbusUART_SS2_PIN_INDEX]);
    #endif /* (ModbusUART_SS2_PIN) */

    #if(ModbusUART_SS3_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_SS3_HSIOM_REG,  ModbusUART_SS3_HSIOM_MASK,
                                       ModbusUART_SS3_HSIOM_POS, hsiomSel[ModbusUART_SS3_PIN_INDEX]);
    #endif /* (ModbusUART_SS3_PIN) */



    #if(ModbusUART_MOSI_SCL_RX_PIN)
        ModbusUART_spi_mosi_i2c_scl_uart_rx_SetDriveMode((uint8)
                                                               pinsDm[ModbusUART_MOSI_SCL_RX_PIN_INDEX]);
    #endif /* (ModbusUART_MOSI_SCL_RX_PIN) */

    #if(ModbusUART_MOSI_SCL_RX_WAKE_PIN)
    ModbusUART_spi_mosi_i2c_scl_uart_rx_wake_SetDriveMode((uint8)
                                                               pinsDm[ModbusUART_MOSI_SCL_RX_WAKE_PIN_INDEX]);

    /* Set interrupt on rising edge */
    ModbusUART_SET_INCFG_TYPE(ModbusUART_MOSI_SCL_RX_WAKE_INTCFG_REG,
                                    ModbusUART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK,
                                    ModbusUART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS,
                                    ModbusUART_INTCFG_TYPE_FALLING_EDGE);

    #endif /* (ModbusUART_MOSI_SCL_RX_WAKE_PIN) */

    #if(ModbusUART_MISO_SDA_TX_PIN)
        ModbusUART_spi_miso_i2c_sda_uart_tx_SetDriveMode((uint8)
                                                                    pinsDm[ModbusUART_MISO_SDA_TX_PIN_INDEX]);
    #endif /* (ModbusUART_MOSI_SCL_RX_PIN) */

    #if(ModbusUART_SCLK_PIN)
        ModbusUART_spi_sclk_SetDriveMode((uint8) pinsDm[ModbusUART_SCLK_PIN_INDEX]);
    #endif /* (ModbusUART_SCLK_PIN) */

    #if(ModbusUART_SS0_PIN)
        ModbusUART_spi_ss0_SetDriveMode((uint8) pinsDm[ModbusUART_SS0_PIN_INDEX]);
    #endif /* (ModbusUART_SS0_PIN) */

    #if(ModbusUART_SS1_PIN)
        ModbusUART_spi_ss1_SetDriveMode((uint8) pinsDm[ModbusUART_SS1_PIN_INDEX]);
    #endif /* (ModbusUART_SS1_PIN) */

    #if(ModbusUART_SS2_PIN)
        ModbusUART_spi_ss2_SetDriveMode((uint8) pinsDm[ModbusUART_SS2_PIN_INDEX]);
    #endif /* (ModbusUART_SS2_PIN) */

    #if(ModbusUART_SS3_PIN)
        ModbusUART_spi_ss3_SetDriveMode((uint8) pinsDm[ModbusUART_SS3_PIN_INDEX]);
    #endif /* (ModbusUART_SS3_PIN) */
    }

#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
