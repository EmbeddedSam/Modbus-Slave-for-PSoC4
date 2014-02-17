/*******************************************************************************
* File Name: ModbusComms.c
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

#include "ModbusComms_PVT.h"

#if(ModbusComms_SCB_MODE_I2C_INC)
    #include "ModbusComms_I2C_PVT.h"
#endif /* (ModbusComms_SCB_MODE_I2C_INC) */

#if(ModbusComms_SCB_MODE_EZI2C_INC)
    #include "ModbusComms_EZI2C_PVT.h"
#endif /* (ModbusComms_SCB_MODE_EZI2C_INC) */

#if(ModbusComms_SCB_MODE_SPI_INC || ModbusComms_SCB_MODE_UART_INC)
    #include "ModbusComms_SPI_UART_PVT.h"
#endif /* (ModbusComms_SCB_MODE_SPI_INC || ModbusComms_SCB_MODE_UART_INC) */


/**********************************
*    Run Time Configuration Vars
**********************************/

/* Stores internal component configuration for unconfigured mode */
#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common config vars */
    uint8 ModbusComms_scbMode = ModbusComms_SCB_MODE_UNCONFIG;
    uint8 ModbusComms_scbEnableWake;
    uint8 ModbusComms_scbEnableIntr;

    /* I2C config vars */
    uint8 ModbusComms_mode;
    uint8 ModbusComms_acceptAddr;

    /* SPI/UART config vars */
    volatile uint8 * ModbusComms_rxBuffer;
    uint8  ModbusComms_rxDataBits;
    uint32 ModbusComms_rxBufferSize;

    volatile uint8 * ModbusComms_txBuffer;
    uint8  ModbusComms_txDataBits;
    uint32 ModbusComms_txBufferSize;

    /* EZI2C config vars */
    uint8 ModbusComms_numberOfAddr;
    uint8 ModbusComms_subAddrSize;
#endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */


/**********************************
*     Common SCB Vars
**********************************/

uint8 ModbusComms_initVar = 0u;
cyisraddress ModbusComms_customIntrHandler = NULL;


/***************************************
*    Private Function Prototypes
***************************************/

static void ModbusComms_ScbEnableIntr(void);
static void ModbusComms_ScbModeStop(void);


/*******************************************************************************
* Function Name: ModbusComms_Init
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
void ModbusComms_Init(void)
{
#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
    if(ModbusComms_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        ModbusComms_initVar = 0u; /* Clear init var */
    }
    else
    {
        /* Initialization was done before call */
    }

#elif(ModbusComms_SCB_MODE_I2C_CONST_CFG)
    ModbusComms_I2CInit();

#elif(ModbusComms_SCB_MODE_SPI_CONST_CFG)
    ModbusComms_SpiInit();

#elif(ModbusComms_SCB_MODE_UART_CONST_CFG)
    ModbusComms_UartInit();

#elif(ModbusComms_SCB_MODE_EZI2C_CONST_CFG)
    ModbusComms_EzI2CInit();

#endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusComms_Enable
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
void ModbusComms_Enable(void)
{
#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
    if(!ModbusComms_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        /* Enable SCB block, only if already configured */
        ModbusComms_CTRL_REG |= ModbusComms_CTRL_ENABLED;
        
        /* Enable interrupt */
        ModbusComms_ScbEnableIntr();
    }
#else
    ModbusComms_CTRL_REG |= ModbusComms_CTRL_ENABLED; /* Enable SCB block */
    
    ModbusComms_ScbEnableIntr();
#endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusComms_Start
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
*  ModbusComms_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void ModbusComms_Start(void)
{
    if(0u == ModbusComms_initVar)
    {
        ModbusComms_initVar = 1u; /* Component was initialized */
        ModbusComms_Init();       /* Initialize component      */
    }

    ModbusComms_Enable();
}


/*******************************************************************************
* Function Name: ModbusComms_Stop
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
void ModbusComms_Stop(void)
{
#if(ModbusComms_SCB_IRQ_INTERNAL)
    ModbusComms_SCB_IRQ_Disable();     /* Disable interrupt before block */
#endif /* (ModbusComms_SCB_IRQ_INTERNAL) */

    ModbusComms_CTRL_REG &= (uint32) ~ModbusComms_CTRL_ENABLED;  /* Disable SCB block */

#if(ModbusComms_SCB_IRQ_INTERNAL)
    ModbusComms_SCB_IRQ_ClearPending(); /* Clear pending interrupt */
#endif /* (ModbusComms_SCB_IRQ_INTERNAL) */
    
    ModbusComms_ScbModeStop(); /* Calls scbMode specific Stop function */
}


/*******************************************************************************
* Function Name: ModbusComms_SetCustomInterruptHandler
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
void ModbusComms_SetCustomInterruptHandler(cyisraddress func)
{
    ModbusComms_customIntrHandler = func; /* Register interrupt handler */
}


/*******************************************************************************
* Function Name: ModbusComms_ScbModeEnableIntr
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
static void ModbusComms_ScbEnableIntr(void)
{
#if(ModbusComms_SCB_IRQ_INTERNAL)
    #if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Enable interrupt source */
        if(0u != ModbusComms_scbEnableIntr)
        {
            ModbusComms_SCB_IRQ_Enable();
        }
    #else
        ModbusComms_SCB_IRQ_Enable();
        
    #endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (ModbusComms_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: ModbusComms_ScbModeEnableIntr
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
static void ModbusComms_ScbModeStop(void)
{
#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
    if(ModbusComms_SCB_MODE_I2C_RUNTM_CFG)
    {
        ModbusComms_I2CStop();
    }
    else if(ModbusComms_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        ModbusComms_EzI2CStop();
    }
    else
    {
        /* None of modes above */
    }
#elif(ModbusComms_SCB_MODE_I2C_CONST_CFG)
    ModbusComms_I2CStop();

#elif(ModbusComms_SCB_MODE_EZI2C_CONST_CFG)
    ModbusComms_EzI2CStop();

#endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: ModbusComms_SetPins
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
    void ModbusComms_SetPins(uint32 mode, uint32 subMode, uint32 uartTxRx)
    {
        uint32 hsiomSel[ModbusComms_SCB_PINS_NUMBER];
        uint32 pinsDm  [ModbusComms_SCB_PINS_NUMBER];
        uint32 i;

        /* Make all unused */
        for(i = 0u; i < ModbusComms_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i] = ModbusComms_HSIOM_DEF_SEL;
            pinsDm[i]   = ModbusComms_PIN_DM_ALG_HIZ;
        }

        /* Choice the Dm and HSIOM */
        if((ModbusComms_SCB_MODE_I2C   == mode) ||
           (ModbusComms_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[ModbusComms_MOSI_SCL_RX_PIN_INDEX] = ModbusComms_HSIOM_I2C_SEL;
            hsiomSel[ModbusComms_MISO_SDA_TX_PIN_INDEX] = ModbusComms_HSIOM_I2C_SEL;

            pinsDm[ModbusComms_MOSI_SCL_RX_PIN_INDEX] = ModbusComms_PIN_DM_OD_LO;
            pinsDm[ModbusComms_MISO_SDA_TX_PIN_INDEX] = ModbusComms_PIN_DM_OD_LO;
        }
        else if(ModbusComms_SCB_MODE_SPI == mode)
        {
            hsiomSel[ModbusComms_MOSI_SCL_RX_PIN_INDEX] = ModbusComms_HSIOM_SPI_SEL;
            hsiomSel[ModbusComms_MISO_SDA_TX_PIN_INDEX] = ModbusComms_HSIOM_SPI_SEL;
            hsiomSel[ModbusComms_SCLK_PIN_INDEX]        = ModbusComms_HSIOM_SPI_SEL;

            if(ModbusComms_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[ModbusComms_MOSI_SCL_RX_PIN_INDEX] = ModbusComms_PIN_DM_DIG_HIZ;
                pinsDm[ModbusComms_MISO_SDA_TX_PIN_INDEX] = ModbusComms_PIN_DM_STRONG;
                pinsDm[ModbusComms_SCLK_PIN_INDEX]        = ModbusComms_PIN_DM_DIG_HIZ;

            #if(ModbusComms_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[ModbusComms_SS0_PIN_INDEX] = ModbusComms_HSIOM_SPI_SEL;
                pinsDm  [ModbusComms_SS0_PIN_INDEX] = ModbusComms_PIN_DM_DIG_HIZ;
            #endif /* (ModbusComms_SS1_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[ModbusComms_MOSI_SCL_RX_PIN_INDEX] = ModbusComms_PIN_DM_STRONG;
                pinsDm[ModbusComms_MISO_SDA_TX_PIN_INDEX] = ModbusComms_PIN_DM_DIG_HIZ;
                pinsDm[ModbusComms_SCLK_PIN_INDEX]        = ModbusComms_PIN_DM_STRONG;

            #if(ModbusComms_SS0_PIN)
                hsiomSel[ModbusComms_SS0_PIN_INDEX] = ModbusComms_HSIOM_SPI_SEL;
                pinsDm  [ModbusComms_SS0_PIN_INDEX] = ModbusComms_PIN_DM_STRONG;
            #endif /* (ModbusComms_SS0_PIN) */

            #if(ModbusComms_SS1_PIN)
                hsiomSel[ModbusComms_SS1_PIN_INDEX] = ModbusComms_HSIOM_SPI_SEL;
                pinsDm  [ModbusComms_SS1_PIN_INDEX] = ModbusComms_PIN_DM_STRONG;
            #endif /* (ModbusComms_SS1_PIN) */

            #if(ModbusComms_SS2_PIN)
                hsiomSel[ModbusComms_SS2_PIN_INDEX] = ModbusComms_HSIOM_SPI_SEL;
                pinsDm  [ModbusComms_SS2_PIN_INDEX] = ModbusComms_PIN_DM_STRONG;
            #endif /* (ModbusComms_SS2_PIN) */

            #if(ModbusComms_SS3_PIN)
                hsiomSel[ModbusComms_SS3_PIN_INDEX] = ModbusComms_HSIOM_SPI_SEL;
                pinsDm  [ModbusComms_SS3_PIN_INDEX] = ModbusComms_PIN_DM_STRONG;
            #endif /* (ModbusComms_SS2_PIN) */
            }
        }
        else /* UART */
        {
            if(ModbusComms_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[ModbusComms_MISO_SDA_TX_PIN_INDEX] = ModbusComms_HSIOM_UART_SEL;
                pinsDm  [ModbusComms_MISO_SDA_TX_PIN_INDEX] = ModbusComms_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if(0u != (ModbusComms_UART_RX & uartTxRx))
                {
                    hsiomSel[ModbusComms_MOSI_SCL_RX_PIN_INDEX] = ModbusComms_HSIOM_UART_SEL;
                    pinsDm  [ModbusComms_MOSI_SCL_RX_PIN_INDEX] = ModbusComms_PIN_DM_DIG_HIZ;
                }

                if(0u != (ModbusComms_UART_TX & uartTxRx))
                {
                    hsiomSel[ModbusComms_MISO_SDA_TX_PIN_INDEX] = ModbusComms_HSIOM_UART_SEL;
                    pinsDm  [ModbusComms_MISO_SDA_TX_PIN_INDEX] = ModbusComms_PIN_DM_STRONG;
                }
            }
        }

        /* Condfigure pins: set HSIOM and DM */
        /* Condfigure pins: DR registers configuration remains unchanged for cyfitter_cfg() */

    #if(ModbusComms_MOSI_SCL_RX_PIN)
        ModbusComms_SET_HSIOM_SEL(ModbusComms_MOSI_SCL_RX_HSIOM_REG,
                                       ModbusComms_MOSI_SCL_RX_HSIOM_MASK,
                                       ModbusComms_MOSI_SCL_RX_HSIOM_POS,
                                       hsiomSel[ModbusComms_MOSI_SCL_RX_PIN_INDEX]);
    #endif /* (ModbusComms_MOSI_SCL_RX_PIN) */

    #if(ModbusComms_MOSI_SCL_RX_WAKE_PIN)
        ModbusComms_SET_HSIOM_SEL(ModbusComms_MOSI_SCL_RX_WAKE_HSIOM_REG,
                                       ModbusComms_MOSI_SCL_RX_WAKE_HSIOM_MASK,
                                       ModbusComms_MOSI_SCL_RX_WAKE_HSIOM_POS,
                                       hsiomSel[ModbusComms_MOSI_SCL_RX_WAKE_PIN_INDEX]);
    #endif /* (ModbusComms_MOSI_SCL_RX_WAKE_PIN) */

    #if(ModbusComms_MISO_SDA_TX_PIN)
        ModbusComms_SET_HSIOM_SEL(ModbusComms_MISO_SDA_TX_HSIOM_REG,
                                       ModbusComms_MISO_SDA_TX_HSIOM_MASK,
                                       ModbusComms_MISO_SDA_TX_HSIOM_POS,
                                       hsiomSel[ModbusComms_MISO_SDA_TX_PIN_INDEX]);
    #endif /* (ModbusComms_MOSI_SCL_RX_PIN) */

    #if(ModbusComms_SCLK_PIN)
        ModbusComms_SET_HSIOM_SEL(ModbusComms_SCLK_HSIOM_REG, ModbusComms_SCLK_HSIOM_MASK,
                                       ModbusComms_SCLK_HSIOM_POS, hsiomSel[ModbusComms_SCLK_PIN_INDEX]);
    #endif /* (ModbusComms_SCLK_PIN) */

    #if(ModbusComms_SS0_PIN)
        ModbusComms_SET_HSIOM_SEL(ModbusComms_SS0_HSIOM_REG, ModbusComms_SS0_HSIOM_MASK,
                                       ModbusComms_SS0_HSIOM_POS, hsiomSel[ModbusComms_SS0_PIN_INDEX]);
    #endif /* (ModbusComms_SS1_PIN) */

    #if(ModbusComms_SS1_PIN)
        ModbusComms_SET_HSIOM_SEL(ModbusComms_SS1_HSIOM_REG, ModbusComms_SS1_HSIOM_MASK,
                                       ModbusComms_SS1_HSIOM_POS, hsiomSel[ModbusComms_SS1_PIN_INDEX]);
    #endif /* (ModbusComms_SS1_PIN) */

    #if(ModbusComms_SS2_PIN)
        ModbusComms_SET_HSIOM_SEL(ModbusComms_SS2_HSIOM_REG, ModbusComms_SS2_HSIOM_MASK,
                                       ModbusComms_SS2_HSIOM_POS, hsiomSel[ModbusComms_SS2_PIN_INDEX]);
    #endif /* (ModbusComms_SS2_PIN) */

    #if(ModbusComms_SS3_PIN)
        ModbusComms_SET_HSIOM_SEL(ModbusComms_SS3_HSIOM_REG,  ModbusComms_SS3_HSIOM_MASK,
                                       ModbusComms_SS3_HSIOM_POS, hsiomSel[ModbusComms_SS3_PIN_INDEX]);
    #endif /* (ModbusComms_SS3_PIN) */



    #if(ModbusComms_MOSI_SCL_RX_PIN)
        ModbusComms_spi_mosi_i2c_scl_uart_rx_SetDriveMode((uint8)
                                                               pinsDm[ModbusComms_MOSI_SCL_RX_PIN_INDEX]);
    #endif /* (ModbusComms_MOSI_SCL_RX_PIN) */

    #if(ModbusComms_MOSI_SCL_RX_WAKE_PIN)
    ModbusComms_spi_mosi_i2c_scl_uart_rx_wake_SetDriveMode((uint8)
                                                               pinsDm[ModbusComms_MOSI_SCL_RX_WAKE_PIN_INDEX]);

    /* Set interrupt on rising edge */
    ModbusComms_SET_INCFG_TYPE(ModbusComms_MOSI_SCL_RX_WAKE_INTCFG_REG,
                                    ModbusComms_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK,
                                    ModbusComms_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS,
                                    ModbusComms_INTCFG_TYPE_FALLING_EDGE);

    #endif /* (ModbusComms_MOSI_SCL_RX_WAKE_PIN) */

    #if(ModbusComms_MISO_SDA_TX_PIN)
        ModbusComms_spi_miso_i2c_sda_uart_tx_SetDriveMode((uint8)
                                                                    pinsDm[ModbusComms_MISO_SDA_TX_PIN_INDEX]);
    #endif /* (ModbusComms_MOSI_SCL_RX_PIN) */

    #if(ModbusComms_SCLK_PIN)
        ModbusComms_spi_sclk_SetDriveMode((uint8) pinsDm[ModbusComms_SCLK_PIN_INDEX]);
    #endif /* (ModbusComms_SCLK_PIN) */

    #if(ModbusComms_SS0_PIN)
        ModbusComms_spi_ss0_SetDriveMode((uint8) pinsDm[ModbusComms_SS0_PIN_INDEX]);
    #endif /* (ModbusComms_SS0_PIN) */

    #if(ModbusComms_SS1_PIN)
        ModbusComms_spi_ss1_SetDriveMode((uint8) pinsDm[ModbusComms_SS1_PIN_INDEX]);
    #endif /* (ModbusComms_SS1_PIN) */

    #if(ModbusComms_SS2_PIN)
        ModbusComms_spi_ss2_SetDriveMode((uint8) pinsDm[ModbusComms_SS2_PIN_INDEX]);
    #endif /* (ModbusComms_SS2_PIN) */

    #if(ModbusComms_SS3_PIN)
        ModbusComms_spi_ss3_SetDriveMode((uint8) pinsDm[ModbusComms_SS3_PIN_INDEX]);
    #endif /* (ModbusComms_SS3_PIN) */
    }

#endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
