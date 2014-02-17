/*******************************************************************************
* File Name: ModbusComms_PM.c
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

#include "ModbusComms.h"
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


/***************************************
*   Backup Structure declaration
***************************************/

ModbusComms_BACKUP_STRUCT ModbusComms_backup =
{
    0u, /* enableState */
};


/*******************************************************************************
* Function Name: ModbusComms_Sleep
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
void ModbusComms_Sleep(void)
{
#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)

    if(0u != ModbusComms_scbEnableWake)
    {
        if(ModbusComms_SCB_MODE_I2C_RUNTM_CFG)
        {
            ModbusComms_I2CSaveConfig();
        }
        else if(ModbusComms_SCB_MODE_SPI_RUNTM_CFG)
        {
            ModbusComms_SpiSaveConfig();
        }
        else if(ModbusComms_SCB_MODE_UART_RUNTM_CFG)
        {
            ModbusComms_UartSaveConfig();
        }
        else if(ModbusComms_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            ModbusComms_EzI2CSaveConfig();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    }
    else
    {
        ModbusComms_backup.enableState = (uint8) ModbusComms_GET_CTRL_ENABLED;
        
        if(0u != ModbusComms_backup.enableState)
        {
            ModbusComms_Stop();
        }
    }
    
    ModbusComms_DisableTxPinsInputBuffer();
    
#else
    
    #if defined (ModbusComms_I2C_WAKE_ENABLE_CONST) && (ModbusComms_I2C_WAKE_ENABLE_CONST)
        ModbusComms_I2CSaveConfig();
        
    #elif defined (ModbusComms_SPI_WAKE_ENABLE_CONST) && (ModbusComms_SPI_WAKE_ENABLE_CONST)
        ModbusComms_SpiSaveConfig();
        
    #elif defined (ModbusComms_UART_WAKE_ENABLE_CONST) && (ModbusComms_UART_WAKE_ENABLE_CONST)
        ModbusComms_UartSaveConfig();
        
    #elif defined (ModbusComms_EZI2C_WAKE_ENABLE_CONST) && (ModbusComms_EZI2C_WAKE_ENABLE_CONST)
        ModbusComms_EzI2CSaveConfig();
    
    #else
        
        ModbusComms_backup.enableState = (uint8) ModbusComms_GET_CTRL_ENABLED;
        
        /* Check enable state */
        if(0u != ModbusComms_backup.enableState)
        {
            ModbusComms_Stop();
        }
        
    #endif /* defined (ModbusComms_SCB_MODE_I2C_CONST_CFG) && (ModbusComms_I2C_WAKE_ENABLE_CONST) */
    
    ModbusComms_DisableTxPinsInputBuffer();
    
#endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusComms_Wakeup
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
void ModbusComms_Wakeup(void)
{
#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)

    ModbusComms_EnableTxPinsInputBuffer();
        
    if(0u != ModbusComms_scbEnableWake)
    {
        if(ModbusComms_SCB_MODE_I2C_RUNTM_CFG)
        {
            ModbusComms_I2CRestoreConfig();
        }
        else if(ModbusComms_SCB_MODE_SPI_RUNTM_CFG)
        {
            ModbusComms_SpiRestoreConfig();
        }
        else if(ModbusComms_SCB_MODE_UART_RUNTM_CFG)
        {
            ModbusComms_UartRestoreConfig();
        }
        else if(ModbusComms_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            ModbusComms_EzI2CRestoreConfig();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    }
    else
    {    
        /* Restore enable state */
        if(0u != ModbusComms_backup.enableState)
        {
            ModbusComms_Enable();
        }
    }

#else
    
    ModbusComms_EnableTxPinsInputBuffer();
        
    #if defined (ModbusComms_I2C_WAKE_ENABLE_CONST) && (ModbusComms_I2C_WAKE_ENABLE_CONST)
        ModbusComms_I2CRestoreConfig();
        
    #elif defined (ModbusComms_SPI_WAKE_ENABLE_CONST) && (ModbusComms_SPI_WAKE_ENABLE_CONST)
        ModbusComms_SpiRestoreConfig();
        
    #elif defined (ModbusComms_UART_WAKE_ENABLE_CONST) && (ModbusComms_UART_WAKE_ENABLE_CONST)
        ModbusComms_UartRestoreConfig();
        
    #elif defined (ModbusComms_EZI2C_WAKE_ENABLE_CONST) && (ModbusComms_EZI2C_WAKE_ENABLE_CONST)
        ModbusComms_EzI2CRestoreConfig();
    
    #else
        /* Check enable state */
        if(0u != ModbusComms_backup.enableState)
        {
            ModbusComms_Enable();
        }
        
    #endif /* (ModbusComms_I2C_WAKE_ENABLE_CONST) */

#endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusComms_DisableTxPinsInputBuffer
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
void ModbusComms_DisableTxPinsInputBuffer(void)
{
#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
    
    /* SCB mode is I2C and EZI2C: bus is pulled-up. Does nothing */
       
    if(ModbusComms_SCB_MODE_SPI_RUNTM_CFG)
    {
        if(0u != (ModbusComms_SPI_CTRL_REG & ModbusComms_SPI_CTRL_MASTER))
        /* SPI Master */
        {
        #if(ModbusComms_MOSI_SCL_RX_WAKE_PIN)
            ModbusComms_spi_mosi_i2c_scl_uart_rx_wake_INP_DIS |= \
                                                                ModbusComms_spi_mosi_i2c_scl_uart_rx_wake_MASK;
        #endif /* (ModbusComms_MOSI_SCL_RX_WAKE_PIN) */

        #if(ModbusComms_MOSI_SCL_RX_PIN)
            ModbusComms_spi_mosi_i2c_scl_uart_rx_INP_DIS |= ModbusComms_spi_mosi_i2c_scl_uart_rx_MASK;
        #endif /* (ModbusComms_MOSI_SCL_RX_PIN) */

        #if(ModbusComms_MISO_SDA_TX_PIN)
            ModbusComms_spi_miso_i2c_sda_uart_tx_INP_DIS |= ModbusComms_spi_miso_i2c_sda_uart_tx_MASK;
        #endif /* (ModbusComms_MISO_SDA_TX_PIN_PIN) */

        #if(ModbusComms_SCLK_PIN)
            ModbusComms_spi_sclk_INP_DIS |= ModbusComms_spi_sclk_MASK;
        #endif /* (ModbusComms_SCLK_PIN) */

        #if(ModbusComms_SS0_PIN)
            ModbusComms_spi_ss0_INP_DIS |= ModbusComms_spi_ss0_MASK;
        #endif /* (ModbusComms_SS1_PIN) */

        #if(ModbusComms_SS1_PIN)
            ModbusComms_spi_ss1_INP_DIS |= ModbusComms_spi_ss1_MASK;
        #endif /* (ModbusComms_SS1_PIN) */

        #if(ModbusComms_SS2_PIN)
            ModbusComms_spi_ss2_INP_DIS |= ModbusComms_spi_ss2_MASK;
        #endif /* (ModbusComms_SS2_PIN) */

        #if(ModbusComms_SS3_PIN)
            ModbusComms_spi_ss3_INP_DIS |= ModbusComms_spi_ss3_MASK;
        #endif /* (ModbusComms_SS3_PIN) */
        }
        else
        /* SPI Slave */
        {
        #if(ModbusComms_MISO_SDA_TX_PIN)
            ModbusComms_spi_miso_i2c_sda_uart_tx_INP_DIS |= ModbusComms_spi_miso_i2c_sda_uart_tx_MASK;
        #endif /* (ModbusComms_MISO_SDA_TX_PIN_PIN) */
        }
    }
    else if (ModbusComms_SCB_MODE_UART_RUNTM_CFG)
    {
        if(ModbusComms_UART_CTRL_MODE_UART_SMARTCARD != 
            (ModbusComms_UART_CTRL_REG & ModbusComms_UART_CTRL_MODE_MASK))
        /* UART Standard or IrDA */
        {
        #if(ModbusComms_MISO_SDA_TX_PIN)
            ModbusComms_spi_miso_i2c_sda_uart_tx_INP_DIS |= ModbusComms_spi_miso_i2c_sda_uart_tx_MASK;
        #endif /* (ModbusComms_MISO_SDA_TX_PIN_PIN) */
        }
    }
    else
    {
        /* Does nothing */
    }
    
#else
    
    /* SCB mode is I2C and EZI2C: bus is pulled-up. Does nothing */
        
    /* SCB mode is SPI Master */
    #if(ModbusComms_SPI_MASTER_PINS)
        ModbusComms_sclk_m_INP_DIS |= ModbusComms_sclk_m_MASK;
        ModbusComms_mosi_m_INP_DIS |= ModbusComms_mosi_m_MASK;
        ModbusComms_miso_m_INP_DIS |= ModbusComms_miso_m_MASK;
    #endif /* (ModbusComms_SPI_MASTER_PINS) */

    #if(ModbusComms_SPI_MASTER_SS0_PIN)
        ModbusComms_ss0_m_INP_DIS |= ModbusComms_ss0_m_MASK;
    #endif /* (ModbusComms_SPI_MASTER_SS0_PIN) */

    #if(ModbusComms_SPI_MASTER_SS1_PIN)
        ModbusComms_ss1_m_INP_DIS |= ModbusComms_ss1_m_MASK;
    #endif /* (ModbusComms_SPI_MASTER_SS1_PIN) */

    #if(ModbusComms_SPI_MASTER_SS2_PIN)
        ModbusComms_ss2_m_INP_DIS |= ModbusComms_ss2_m_MASK;
    #endif /* (ModbusComms_SPI_MASTER_SS2_PIN) */

    #if(ModbusComms_SPI_MASTER_SS3_PIN)
        ModbusComms_ss3_m_INP_DIS |= ModbusComms_ss3_m_MASK;
    #endif /* (ModbusComms_SPI_MASTER_SS3_PIN) */
    
    /* SCB mode is SPI Slave */
    #if(ModbusComms_SPI_SLAVE_PINS)
        ModbusComms_miso_s_INP_DIS |= ModbusComms_miso_s_MASK;
    #endif /* (ModbusComms_SPI_SLAVE_PINS) */

    /* SCB mode is UART */
    #if(ModbusComms_UART_TX_PIN)
        ModbusComms_tx_INP_DIS |= ModbusComms_tx_MASK;
    #endif /* (ModbusComms_UART_TX_PIN) */

#endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusComms_EnableTxPinsInputBuffer
********************************************************************************
*
* Summary:
*  Enables input buffers for TX pins. Restore changes done byte
*ModbusComms_DisableTxPinsInputBuffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusComms_EnableTxPinsInputBuffer(void)
{
#if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
    if(ModbusComms_SCB_MODE_SPI_RUNTM_CFG)
    {
        if(0u != (ModbusComms_SPI_CTRL_REG & ModbusComms_SPI_CTRL_MASTER))
        /* SPI Master */
        {
        #if(ModbusComms_MOSI_SCL_RX_WAKE_PIN)
            ModbusComms_spi_mosi_i2c_scl_uart_rx_wake_INP_DIS &= \
                                            (uint32) ~((uint32) ModbusComms_spi_mosi_i2c_scl_uart_rx_wake_MASK);
        #endif /* (ModbusComms_MOSI_SCL_RX_WAKE_PIN) */

        #if(ModbusComms_MOSI_SCL_RX_PIN)
            ModbusComms_spi_mosi_i2c_scl_uart_rx_INP_DIS &= \
                                            (uint32) ~((uint32) ModbusComms_spi_mosi_i2c_scl_uart_rx_MASK);
        #endif /* (ModbusComms_MOSI_SCL_RX_PIN) */

        #if(ModbusComms_MISO_SDA_TX_PIN)
            ModbusComms_spi_miso_i2c_sda_uart_tx_INP_DIS &= \
                                            (uint32) ~((uint32) ModbusComms_spi_miso_i2c_sda_uart_tx_MASK);
        #endif /* (ModbusComms_MISO_SDA_TX_PIN_PIN) */

        #if(ModbusComms_SCLK_PIN)
            ModbusComms_spi_sclk_INP_DIS &= (uint32) ~((uint32) ModbusComms_spi_sclk_MASK);
        #endif /* (ModbusComms_SCLK_PIN) */

        #if(ModbusComms_SS0_PIN)
            ModbusComms_spi_ss0_INP_DIS &= (uint32) ~((uint32) ModbusComms_spi_ss0_MASK);
        #endif /* (ModbusComms_SS1_PIN) */

        #if(ModbusComms_SS1_PIN)
            ModbusComms_spi_ss1_INP_DIS &= (uint32) ~((uint32) ModbusComms_spi_ss1_MASK);
        #endif /* (ModbusComms_SS1_PIN) */

        #if(ModbusComms_SS2_PIN)
            ModbusComms_spi_ss2_INP_DIS &= (uint32) ~((uint32) ModbusComms_spi_ss2_MASK);
        #endif /* (ModbusComms_SS2_PIN) */

        #if(ModbusComms_SS3_PIN)
            ModbusComms_spi_ss3_INP_DIS &= (uint32) ~((uint32) ModbusComms_spi_ss3_MASK);
        #endif /* (ModbusComms_SS3_PIN) */
        }
        else
        /* SPI Slave */
        {
        #if(ModbusComms_MISO_SDA_TX_PIN)
            ModbusComms_spi_miso_i2c_sda_uart_tx_INP_DIS &= \
                                                (uint32) ~((uint32) ModbusComms_spi_miso_i2c_sda_uart_tx_MASK);
        #endif /* (ModbusComms_MISO_SDA_TX_PIN_PIN) */
        }
    }
    else if (ModbusComms_SCB_MODE_UART_RUNTM_CFG)
    {
        if(ModbusComms_UART_CTRL_MODE_UART_SMARTCARD != 
                (ModbusComms_UART_CTRL_REG & ModbusComms_UART_CTRL_MODE_MASK))
        /* UART Standard or IrDA */
        {
        #if(ModbusComms_MISO_SDA_TX_PIN)
            ModbusComms_spi_miso_i2c_sda_uart_tx_INP_DIS &= \
                                                (uint32) ~((uint32) ModbusComms_spi_miso_i2c_sda_uart_tx_MASK);
        #endif /* (ModbusComms_MISO_SDA_TX_PIN_PIN) */
        }
    }
    else
    {
        /* Does nothing */
    }
    
#else
        
    /* SCB mode is SPI Master */
    #if(ModbusComms_SPI_MASTER_PINS)
        ModbusComms_sclk_m_INP_DIS &= (uint32) ~((uint32) ModbusComms_sclk_m_MASK);
        ModbusComms_mosi_m_INP_DIS &= (uint32) ~((uint32) ModbusComms_mosi_m_MASK);
        ModbusComms_miso_m_INP_DIS &= (uint32) ~((uint32) ModbusComms_miso_m_MASK);
    #endif /* (ModbusComms_SPI_MASTER_PINS) */

    #if(ModbusComms_SPI_MASTER_SS0_PIN)
        ModbusComms_ss0_m_INP_DIS &= (uint32) ~((uint32) ModbusComms_ss0_m_MASK);
    #endif /* (ModbusComms_SPI_MASTER_SS0_PIN) */

    #if(ModbusComms_SPI_MASTER_SS1_PIN)
        ModbusComms_ss1_m_INP_DIS &= (uint32) ~((uint32) ModbusComms_ss1_m_MASK);
    #endif /* (ModbusComms_SPI_MASTER_SS1_PIN) */

    #if(ModbusComms_SPI_MASTER_SS2_PIN)
        ModbusComms_ss2_m_INP_DIS &= (uint32) ~((uint32) ModbusComms_ss2_m_MASK);
    #endif /* (ModbusComms_SPI_MASTER_SS2_PIN) */

    #if(ModbusComms_SPI_MASTER_SS3_PIN)
        ModbusComms_ss3_m_INP_DIS &= (uint32) ~((uint32) ModbusComms_ss3_m_MASK);
    #endif /* (ModbusComms_SPI_MASTER_SS3_PIN) */
    
    /* SCB mode is SPI Slave */
    #if(ModbusComms_SPI_SLAVE_PINS)
        ModbusComms_miso_s_INP_DIS &= (uint32) ~((uint32) ModbusComms_miso_s_MASK);
    #endif /* (ModbusComms_SPI_SLAVE_PINS) */

    /* SCB mode is UART */
    #if(ModbusComms_UART_TX_PIN)
        ModbusComms_tx_INP_DIS &= (uint32) ~((uint32) ModbusComms_tx_MASK);
    #endif /* (ModbusComms_UART_TX_PIN) */

#endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
