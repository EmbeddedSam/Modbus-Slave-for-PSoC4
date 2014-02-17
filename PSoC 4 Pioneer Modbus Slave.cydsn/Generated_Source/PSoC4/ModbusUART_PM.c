/*******************************************************************************
* File Name: ModbusUART_PM.c
* Version 1.10
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ModbusUART.h"
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


/***************************************
*   Backup Structure declaration
***************************************/

ModbusUART_BACKUP_STRUCT ModbusUART_backup =
{
    0u, /* enableState */
};


/*******************************************************************************
* Function Name: ModbusUART_Sleep
********************************************************************************
*
* Summary:
*  Calls SaveConfig function fucntion for selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_Sleep(void)
{
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)

    if(0u != ModbusUART_scbEnableWake)
    {
        if(ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
        {
            ModbusUART_I2CSaveConfig();
        }
        else if(ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
        {
            ModbusUART_SpiSaveConfig();
        }
        else if(ModbusUART_SCB_MODE_UART_RUNTM_CFG)
        {
            ModbusUART_UartSaveConfig();
        }
        else if(ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            ModbusUART_EzI2CSaveConfig();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    }
    else
    {
        ModbusUART_backup.enableState = (uint8) ModbusUART_GET_CTRL_ENABLED;
        
        if(0u != ModbusUART_backup.enableState)
        {
            ModbusUART_Stop();
        }
    }
    
    ModbusUART_DisableTxPinsInputBuffer();
    
#else
    
    #if defined (ModbusUART_I2C_WAKE_ENABLE_CONST) && (ModbusUART_I2C_WAKE_ENABLE_CONST)
        ModbusUART_I2CSaveConfig();
        
    #elif defined (ModbusUART_SPI_WAKE_ENABLE_CONST) && (ModbusUART_SPI_WAKE_ENABLE_CONST)
        ModbusUART_SpiSaveConfig();
        
    #elif defined (ModbusUART_UART_WAKE_ENABLE_CONST) && (ModbusUART_UART_WAKE_ENABLE_CONST)
        ModbusUART_UartSaveConfig();
        
    #elif defined (ModbusUART_EZI2C_WAKE_ENABLE_CONST) && (ModbusUART_EZI2C_WAKE_ENABLE_CONST)
        ModbusUART_EzI2CSaveConfig();
    
    #else
        
        ModbusUART_backup.enableState = (uint8) ModbusUART_GET_CTRL_ENABLED;
        
        /* Check enable state */
        if(0u != ModbusUART_backup.enableState)
        {
            ModbusUART_Stop();
        }
        
    #endif /* defined (ModbusUART_SCB_MODE_I2C_CONST_CFG) && (ModbusUART_I2C_WAKE_ENABLE_CONST) */
    
    ModbusUART_DisableTxPinsInputBuffer();
    
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_Wakeup
********************************************************************************
*
* Summary:
*  Calls RestoreConfig function fucntion for selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_Wakeup(void)
{
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)

    ModbusUART_EnableTxPinsInputBuffer();
        
    if(0u != ModbusUART_scbEnableWake)
    {
        if(ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
        {
            ModbusUART_I2CRestoreConfig();
        }
        else if(ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
        {
            ModbusUART_SpiRestoreConfig();
        }
        else if(ModbusUART_SCB_MODE_UART_RUNTM_CFG)
        {
            ModbusUART_UartRestoreConfig();
        }
        else if(ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            ModbusUART_EzI2CRestoreConfig();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    }
    else
    {    
        /* Restore enable state */
        if(0u != ModbusUART_backup.enableState)
        {
            ModbusUART_Enable();
        }
    }

#else
    
    ModbusUART_EnableTxPinsInputBuffer();
        
    #if defined (ModbusUART_I2C_WAKE_ENABLE_CONST) && (ModbusUART_I2C_WAKE_ENABLE_CONST)
        ModbusUART_I2CRestoreConfig();
        
    #elif defined (ModbusUART_SPI_WAKE_ENABLE_CONST) && (ModbusUART_SPI_WAKE_ENABLE_CONST)
        ModbusUART_SpiRestoreConfig();
        
    #elif defined (ModbusUART_UART_WAKE_ENABLE_CONST) && (ModbusUART_UART_WAKE_ENABLE_CONST)
        ModbusUART_UartRestoreConfig();
        
    #elif defined (ModbusUART_EZI2C_WAKE_ENABLE_CONST) && (ModbusUART_EZI2C_WAKE_ENABLE_CONST)
        ModbusUART_EzI2CRestoreConfig();
    
    #else
        /* Check enable state */
        if(0u != ModbusUART_backup.enableState)
        {
            ModbusUART_Enable();
        }
        
    #endif /* (ModbusUART_I2C_WAKE_ENABLE_CONST) */

#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_DisableTxPinsInputBuffer
********************************************************************************
*
* Summary:
*  Disables input buffers for TX pins. This action removes leakage current while
*  low power mode (Cypress ID 149635).
*   SCB mode is I2C and EZI2C: bus is pulled-up. Leave pins as it is.
*   SCB mode SPI:
*     Slave  - disable input buffer for MISO pin.
*     Master - disable input buffer for all pins.
*   SCB mode SmartCard: 
*     Standard and IrDA - disable input buffer for TX pin.
*     SmartCard - RX_TX pin is pulled-up. Leave pin as it is.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_DisableTxPinsInputBuffer(void)
{
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    
    /* SCB mode is I2C and EZI2C: bus is pulled-up. Does nothing */
       
    if(ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
    {
        if(0u != (ModbusUART_SPI_CTRL_REG & ModbusUART_SPI_CTRL_MASTER))
        /* SPI Master */
        {
        #if(ModbusUART_MOSI_SCL_RX_WAKE_PIN)
            ModbusUART_spi_mosi_i2c_scl_uart_rx_wake_INP_DIS |= \
                                                                ModbusUART_spi_mosi_i2c_scl_uart_rx_wake_MASK;
        #endif /* (ModbusUART_MOSI_SCL_RX_WAKE_PIN) */

        #if(ModbusUART_MOSI_SCL_RX_PIN)
            ModbusUART_spi_mosi_i2c_scl_uart_rx_INP_DIS |= ModbusUART_spi_mosi_i2c_scl_uart_rx_MASK;
        #endif /* (ModbusUART_MOSI_SCL_RX_PIN) */

        #if(ModbusUART_MISO_SDA_TX_PIN)
            ModbusUART_spi_miso_i2c_sda_uart_tx_INP_DIS |= ModbusUART_spi_miso_i2c_sda_uart_tx_MASK;
        #endif /* (ModbusUART_MISO_SDA_TX_PIN_PIN) */

        #if(ModbusUART_SCLK_PIN)
            ModbusUART_spi_sclk_INP_DIS |= ModbusUART_spi_sclk_MASK;
        #endif /* (ModbusUART_SCLK_PIN) */

        #if(ModbusUART_SS0_PIN)
            ModbusUART_spi_ss0_INP_DIS |= ModbusUART_spi_ss0_MASK;
        #endif /* (ModbusUART_SS1_PIN) */

        #if(ModbusUART_SS1_PIN)
            ModbusUART_spi_ss1_INP_DIS |= ModbusUART_spi_ss1_MASK;
        #endif /* (ModbusUART_SS1_PIN) */

        #if(ModbusUART_SS2_PIN)
            ModbusUART_spi_ss2_INP_DIS |= ModbusUART_spi_ss2_MASK;
        #endif /* (ModbusUART_SS2_PIN) */

        #if(ModbusUART_SS3_PIN)
            ModbusUART_spi_ss3_INP_DIS |= ModbusUART_spi_ss3_MASK;
        #endif /* (ModbusUART_SS3_PIN) */
        }
        else
        /* SPI Slave */
        {
        #if(ModbusUART_MISO_SDA_TX_PIN)
            ModbusUART_spi_miso_i2c_sda_uart_tx_INP_DIS |= ModbusUART_spi_miso_i2c_sda_uart_tx_MASK;
        #endif /* (ModbusUART_MISO_SDA_TX_PIN_PIN) */
        }
    }
    else if (ModbusUART_SCB_MODE_UART_RUNTM_CFG)
    {
        if(ModbusUART_UART_CTRL_MODE_UART_SMARTCARD != 
            (ModbusUART_UART_CTRL_REG & ModbusUART_UART_CTRL_MODE_MASK))
        /* UART Standard or IrDA */
        {
        #if(ModbusUART_MISO_SDA_TX_PIN)
            ModbusUART_spi_miso_i2c_sda_uart_tx_INP_DIS |= ModbusUART_spi_miso_i2c_sda_uart_tx_MASK;
        #endif /* (ModbusUART_MISO_SDA_TX_PIN_PIN) */
        }
    }
    else
    {
        /* Does nothing */
    }
    
#else
    
    /* SCB mode is I2C and EZI2C: bus is pulled-up. Does nothing */
        
    /* SCB mode is SPI Master */
    #if(ModbusUART_SPI_MASTER_PINS)
        ModbusUART_sclk_m_INP_DIS |= ModbusUART_sclk_m_MASK;
        ModbusUART_mosi_m_INP_DIS |= ModbusUART_mosi_m_MASK;
        ModbusUART_miso_m_INP_DIS |= ModbusUART_miso_m_MASK;
    #endif /* (ModbusUART_SPI_MASTER_PINS) */

    #if(ModbusUART_SPI_MASTER_SS0_PIN)
        ModbusUART_ss0_m_INP_DIS |= ModbusUART_ss0_m_MASK;
    #endif /* (ModbusUART_SPI_MASTER_SS0_PIN) */

    #if(ModbusUART_SPI_MASTER_SS1_PIN)
        ModbusUART_ss1_m_INP_DIS |= ModbusUART_ss1_m_MASK;
    #endif /* (ModbusUART_SPI_MASTER_SS1_PIN) */

    #if(ModbusUART_SPI_MASTER_SS2_PIN)
        ModbusUART_ss2_m_INP_DIS |= ModbusUART_ss2_m_MASK;
    #endif /* (ModbusUART_SPI_MASTER_SS2_PIN) */

    #if(ModbusUART_SPI_MASTER_SS3_PIN)
        ModbusUART_ss3_m_INP_DIS |= ModbusUART_ss3_m_MASK;
    #endif /* (ModbusUART_SPI_MASTER_SS3_PIN) */
    
    /* SCB mode is SPI Slave */
    #if(ModbusUART_SPI_SLAVE_PINS)
        ModbusUART_miso_s_INP_DIS |= ModbusUART_miso_s_MASK;
    #endif /* (ModbusUART_SPI_SLAVE_PINS) */

    /* SCB mode is UART */
    #if(ModbusUART_UART_TX_PIN)
        ModbusUART_tx_INP_DIS |= ModbusUART_tx_MASK;
    #endif /* (ModbusUART_UART_TX_PIN) */

#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_EnableTxPinsInputBuffer
********************************************************************************
*
* Summary:
*  Enables input buffers for TX pins. Restore changes done byte
*ModbusUART_DisableTxPinsInputBuffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusUART_EnableTxPinsInputBuffer(void)
{
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    if(ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
    {
        if(0u != (ModbusUART_SPI_CTRL_REG & ModbusUART_SPI_CTRL_MASTER))
        /* SPI Master */
        {
        #if(ModbusUART_MOSI_SCL_RX_WAKE_PIN)
            ModbusUART_spi_mosi_i2c_scl_uart_rx_wake_INP_DIS &= \
                                            (uint32) ~((uint32) ModbusUART_spi_mosi_i2c_scl_uart_rx_wake_MASK);
        #endif /* (ModbusUART_MOSI_SCL_RX_WAKE_PIN) */

        #if(ModbusUART_MOSI_SCL_RX_PIN)
            ModbusUART_spi_mosi_i2c_scl_uart_rx_INP_DIS &= \
                                            (uint32) ~((uint32) ModbusUART_spi_mosi_i2c_scl_uart_rx_MASK);
        #endif /* (ModbusUART_MOSI_SCL_RX_PIN) */

        #if(ModbusUART_MISO_SDA_TX_PIN)
            ModbusUART_spi_miso_i2c_sda_uart_tx_INP_DIS &= \
                                            (uint32) ~((uint32) ModbusUART_spi_miso_i2c_sda_uart_tx_MASK);
        #endif /* (ModbusUART_MISO_SDA_TX_PIN_PIN) */

        #if(ModbusUART_SCLK_PIN)
            ModbusUART_spi_sclk_INP_DIS &= (uint32) ~((uint32) ModbusUART_spi_sclk_MASK);
        #endif /* (ModbusUART_SCLK_PIN) */

        #if(ModbusUART_SS0_PIN)
            ModbusUART_spi_ss0_INP_DIS &= (uint32) ~((uint32) ModbusUART_spi_ss0_MASK);
        #endif /* (ModbusUART_SS1_PIN) */

        #if(ModbusUART_SS1_PIN)
            ModbusUART_spi_ss1_INP_DIS &= (uint32) ~((uint32) ModbusUART_spi_ss1_MASK);
        #endif /* (ModbusUART_SS1_PIN) */

        #if(ModbusUART_SS2_PIN)
            ModbusUART_spi_ss2_INP_DIS &= (uint32) ~((uint32) ModbusUART_spi_ss2_MASK);
        #endif /* (ModbusUART_SS2_PIN) */

        #if(ModbusUART_SS3_PIN)
            ModbusUART_spi_ss3_INP_DIS &= (uint32) ~((uint32) ModbusUART_spi_ss3_MASK);
        #endif /* (ModbusUART_SS3_PIN) */
        }
        else
        /* SPI Slave */
        {
        #if(ModbusUART_MISO_SDA_TX_PIN)
            ModbusUART_spi_miso_i2c_sda_uart_tx_INP_DIS &= \
                                                (uint32) ~((uint32) ModbusUART_spi_miso_i2c_sda_uart_tx_MASK);
        #endif /* (ModbusUART_MISO_SDA_TX_PIN_PIN) */
        }
    }
    else if (ModbusUART_SCB_MODE_UART_RUNTM_CFG)
    {
        if(ModbusUART_UART_CTRL_MODE_UART_SMARTCARD != 
                (ModbusUART_UART_CTRL_REG & ModbusUART_UART_CTRL_MODE_MASK))
        /* UART Standard or IrDA */
        {
        #if(ModbusUART_MISO_SDA_TX_PIN)
            ModbusUART_spi_miso_i2c_sda_uart_tx_INP_DIS &= \
                                                (uint32) ~((uint32) ModbusUART_spi_miso_i2c_sda_uart_tx_MASK);
        #endif /* (ModbusUART_MISO_SDA_TX_PIN_PIN) */
        }
    }
    else
    {
        /* Does nothing */
    }
    
#else
        
    /* SCB mode is SPI Master */
    #if(ModbusUART_SPI_MASTER_PINS)
        ModbusUART_sclk_m_INP_DIS &= (uint32) ~((uint32) ModbusUART_sclk_m_MASK);
        ModbusUART_mosi_m_INP_DIS &= (uint32) ~((uint32) ModbusUART_mosi_m_MASK);
        ModbusUART_miso_m_INP_DIS &= (uint32) ~((uint32) ModbusUART_miso_m_MASK);
    #endif /* (ModbusUART_SPI_MASTER_PINS) */

    #if(ModbusUART_SPI_MASTER_SS0_PIN)
        ModbusUART_ss0_m_INP_DIS &= (uint32) ~((uint32) ModbusUART_ss0_m_MASK);
    #endif /* (ModbusUART_SPI_MASTER_SS0_PIN) */

    #if(ModbusUART_SPI_MASTER_SS1_PIN)
        ModbusUART_ss1_m_INP_DIS &= (uint32) ~((uint32) ModbusUART_ss1_m_MASK);
    #endif /* (ModbusUART_SPI_MASTER_SS1_PIN) */

    #if(ModbusUART_SPI_MASTER_SS2_PIN)
        ModbusUART_ss2_m_INP_DIS &= (uint32) ~((uint32) ModbusUART_ss2_m_MASK);
    #endif /* (ModbusUART_SPI_MASTER_SS2_PIN) */

    #if(ModbusUART_SPI_MASTER_SS3_PIN)
        ModbusUART_ss3_m_INP_DIS &= (uint32) ~((uint32) ModbusUART_ss3_m_MASK);
    #endif /* (ModbusUART_SPI_MASTER_SS3_PIN) */
    
    /* SCB mode is SPI Slave */
    #if(ModbusUART_SPI_SLAVE_PINS)
        ModbusUART_miso_s_INP_DIS &= (uint32) ~((uint32) ModbusUART_miso_s_MASK);
    #endif /* (ModbusUART_SPI_SLAVE_PINS) */

    /* SCB mode is UART */
    #if(ModbusUART_UART_TX_PIN)
        ModbusUART_tx_INP_DIS &= (uint32) ~((uint32) ModbusUART_tx_MASK);
    #endif /* (ModbusUART_UART_TX_PIN) */

#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
