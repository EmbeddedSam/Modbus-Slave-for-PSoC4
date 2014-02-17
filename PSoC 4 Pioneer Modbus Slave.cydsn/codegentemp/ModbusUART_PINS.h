/*******************************************************************************
* File Name: ModbusUART_PINS.h
* Version 1.10
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_ModbusUART_H)
#define CY_SCB_PINS_ModbusUART_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define ModbusUART_REMOVE_MOSI_SCL_RX_WAKE_PIN    (1u)
#define ModbusUART_REMOVE_MOSI_SCL_RX_PIN         (1u)
#define ModbusUART_REMOVE_MISO_SDA_TX_PIN         (1u)
#define ModbusUART_REMOVE_SCLK_PIN                (1u)
#define ModbusUART_REMOVE_SS0_PIN                 (1u)
#define ModbusUART_REMOVE_SS1_PIN                 (1u)
#define ModbusUART_REMOVE_SS2_PIN                 (1u)
#define ModbusUART_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define ModbusUART_REMOVE_I2C_PINS                (1u)
#define ModbusUART_REMOVE_SPI_MASTER_PINS         (1u)
#define ModbusUART_REMOVE_SPI_SLAVE_PINS          (1u)
#define ModbusUART_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define ModbusUART_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define ModbusUART_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define ModbusUART_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define ModbusUART_REMOVE_UART_TX_PIN             (0u)
#define ModbusUART_REMOVE_UART_RX_TX_PIN          (1u)
#define ModbusUART_REMOVE_UART_RX_PIN             (0u)
#define ModbusUART_REMOVE_UART_RX_WAKE_PIN        (1u)

/* Unconfigured pins */
#define ModbusUART_MOSI_SCL_RX_WAKE_PIN   (0u == ModbusUART_REMOVE_MOSI_SCL_RX_WAKE_PIN)
#define ModbusUART_MOSI_SCL_RX_PIN        (0u == ModbusUART_REMOVE_MOSI_SCL_RX_PIN)
#define ModbusUART_MISO_SDA_TX_PIN        (0u == ModbusUART_REMOVE_MISO_SDA_TX_PIN)
#define ModbusUART_SCLK_PIN               (0u == ModbusUART_REMOVE_SCLK_PIN)
#define ModbusUART_SS0_PIN                (0u == ModbusUART_REMOVE_SS0_PIN)
#define ModbusUART_SS1_PIN                (0u == ModbusUART_REMOVE_SS1_PIN)
#define ModbusUART_SS2_PIN                (0u == ModbusUART_REMOVE_SS2_PIN)
#define ModbusUART_SS3_PIN                (0u == ModbusUART_REMOVE_SS3_PIN)

/* Mode defined pins */
#define ModbusUART_I2C_PINS               (0u == ModbusUART_REMOVE_I2C_PINS)
#define ModbusUART_SPI_MASTER_PINS        (0u == ModbusUART_REMOVE_SPI_MASTER_PINS) 
#define ModbusUART_SPI_SLAVE_PINS         (0u == ModbusUART_REMOVE_SPI_SLAVE_PINS)
#define ModbusUART_SPI_MASTER_SS0_PIN     (0u == ModbusUART_REMOVE_SPI_MASTER_SS0_PIN)
#define ModbusUART_SPI_MASTER_SS1_PIN     (0u == ModbusUART_REMOVE_SPI_MASTER_SS1_PIN)
#define ModbusUART_SPI_MASTER_SS2_PIN     (0u == ModbusUART_REMOVE_SPI_MASTER_SS2_PIN)
#define ModbusUART_SPI_MASTER_SS3_PIN     (0u == ModbusUART_REMOVE_SPI_MASTER_SS3_PIN)
#define ModbusUART_UART_TX_PIN            (0u == ModbusUART_REMOVE_UART_TX_PIN)
#define ModbusUART_UART_RX_TX_PIN         (0u == ModbusUART_REMOVE_UART_RX_TX_PIN)
#define ModbusUART_UART_RX_PIN            (0u == ModbusUART_REMOVE_UART_RX_PIN)
#define ModbusUART_UART_RX_WAKE_PIN       (0u == ModbusUART_REMOVE_UART_RX_WAKE_PIN)


/***************************************
*             Includes
****************************************/

#if(ModbusUART_MOSI_SCL_RX_WAKE_PIN)
    #include "ModbusUART_spi_mosi_i2c_scl_uart_rx_wake.h"
#endif /* (ModbusUART_MOSI_SCL_RX_WAKE_PIN) */

#if(ModbusUART_MOSI_SCL_RX_PIN)
    #include "ModbusUART_spi_mosi_i2c_scl_uart_rx.h"
#endif /* (ModbusUART_MOSI_SCL_RX_PIN) */

#if(ModbusUART_MISO_SDA_TX_PIN)
    #include "ModbusUART_spi_miso_i2c_sda_uart_tx.h"
#endif /* (ModbusUART_MISO_SDA_TX_PIN_PIN) */

#if(ModbusUART_SCLK_PIN)
    #include "ModbusUART_spi_sclk.h"
#endif /* (ModbusUART_SCLK_PIN) */

#if(ModbusUART_SS0_PIN)
    #include "ModbusUART_spi_ss0.h"
#endif /* (ModbusUART_SS1_PIN) */

#if(ModbusUART_SS1_PIN)
    #include "ModbusUART_spi_ss1.h"
#endif /* (ModbusUART_SS1_PIN) */

#if(ModbusUART_SS2_PIN)
    #include "ModbusUART_spi_ss2.h"
#endif /* (ModbusUART_SS2_PIN) */

#if(ModbusUART_SS3_PIN)
    #include "ModbusUART_spi_ss3.h"
#endif /* (ModbusUART_SS3_PIN) */

#if(ModbusUART_I2C_PINS)
    #include "ModbusUART_scl.h"
    #include "ModbusUART_sda.h"
#endif /* (ModbusUART_I2C_PINS) */
    
#if(ModbusUART_SPI_MASTER_PINS)
    #include "ModbusUART_sclk_m.h"
    #include "ModbusUART_mosi_m.h"
    #include "ModbusUART_miso_m.h"
#endif /* (ModbusUART_SPI_MASTER_PINS) */

#if(ModbusUART_SPI_SLAVE_PINS)
    #include "ModbusUART_sclk_s.h"
    #include "ModbusUART_mosi_s.h"
    #include "ModbusUART_miso_s.h"
    #include "ModbusUART_ss_s.h"
#endif /* (ModbusUART_SPI_SLAVE_PINS) */

#if(ModbusUART_SPI_MASTER_SS0_PIN)
    #include "ModbusUART_ss0_m.h"
#endif /* (ModbusUART_SPI_MASTER_SS0_PIN) */

#if(ModbusUART_SPI_MASTER_SS1_PIN)
    #include "ModbusUART_ss1_m.h"
#endif /* (ModbusUART_SPI_MASTER_SS1_PIN) */

#if(ModbusUART_SPI_MASTER_SS2_PIN)
    #include "ModbusUART_ss2_m.h"
#endif /* (ModbusUART_SPI_MASTER_SS2_PIN) */

#if(ModbusUART_SPI_MASTER_SS3_PIN)
    #include "ModbusUART_ss3_m.h"
#endif /* (ModbusUART_SPI_MASTER_SS3_PIN) */

#if(ModbusUART_UART_TX_PIN)
    #include "ModbusUART_tx.h"
#endif /* (ModbusUART_UART_TX_PIN) */

#if(ModbusUART_UART_RX_TX_PIN)
    #include "ModbusUART_rx_tx.h"
#endif /* (ModbusUART_UART_RX_TX_PIN) */

#if(ModbusUART_UART_RX_PIN)
    #include "ModbusUART_rx.h"
#endif /* (ModbusUART_UART_RX_PIN) */

#if(ModbusUART_UART_RX_WAKE_PIN)
    #include "ModbusUART_rx_wake.h"
#endif /* (ModbusUART_UART_RX_WAKE_PIN) */


/***************************************
*              Registers
***************************************/

#if(ModbusUART_MOSI_SCL_RX_WAKE_PIN)
    #define ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_REG  \
                                                (*(reg32 *) ModbusUART_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_PTR  \
                                                ( (reg32 *) ModbusUART_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_MASK \
                                                (ModbusUART_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_MASK)
    #define ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_POS  \
                                                (ModbusUART_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_SHIFT)

    #define ModbusUART_MOSI_SCL_RX_WAKE_INTCFG_REG    (*(reg32 *) \
                                                              ModbusUART_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)
    #define ModbusUART_MOSI_SCL_RX_WAKE_INTCFG_PTR    ( (reg32 *) \
                                                              ModbusUART_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)

    #define ModbusUART_INTCFG_TYPE_MASK                  (0x03u)
    #define ModbusUART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS  (ModbusUART_spi_mosi_i2c_scl_uart_rx_wake__SHIFT)
    #define ModbusUART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK ((uint32)                                           \
                                                                    ((uint32) ModbusUART_INTCFG_TYPE_MASK << \
                                                                    ModbusUART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS))
#endif /* (ModbusUART_MOSI_SCL_RX_WAKE_PIN) */

#if(ModbusUART_MOSI_SCL_RX_PIN)
    #define ModbusUART_MOSI_SCL_RX_HSIOM_REG      (*(reg32 *) ModbusUART_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define ModbusUART_MOSI_SCL_RX_HSIOM_PTR      ( (reg32 *) ModbusUART_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define ModbusUART_MOSI_SCL_RX_HSIOM_MASK     (ModbusUART_spi_mosi_i2c_scl_uart_rx__0__HSIOM_MASK)
    #define ModbusUART_MOSI_SCL_RX_HSIOM_POS      (ModbusUART_spi_mosi_i2c_scl_uart_rx__0__HSIOM_SHIFT)
#endif /* (ModbusUART_MOSI_SCL_RX_PIN) */

#if(ModbusUART_MISO_SDA_TX_PIN)
    #define ModbusUART_MISO_SDA_TX_HSIOM_REG      (*(reg32 *) ModbusUART_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define ModbusUART_MISO_SDA_TX_HSIOM_PTR      ( (reg32 *) ModbusUART_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define ModbusUART_MISO_SDA_TX_HSIOM_MASK     (ModbusUART_spi_miso_i2c_sda_uart_tx__0__HSIOM_MASK)
    #define ModbusUART_MISO_SDA_TX_HSIOM_POS      (ModbusUART_spi_miso_i2c_sda_uart_tx__0__HSIOM_SHIFT)
#endif /* (ModbusUART_MISO_SDA_TX_PIN_PIN) */

#if(ModbusUART_SCLK_PIN)
    #define ModbusUART_SCLK_HSIOM_REG     (*(reg32 *) ModbusUART_spi_sclk__0__HSIOM)
    #define ModbusUART_SCLK_HSIOM_PTR     ( (reg32 *) ModbusUART_spi_sclk__0__HSIOM)
    #define ModbusUART_SCLK_HSIOM_MASK    (ModbusUART_spi_sclk__0__HSIOM_MASK)
    #define ModbusUART_SCLK_HSIOM_POS     (ModbusUART_spi_sclk__0__HSIOM_SHIFT)
#endif /* (ModbusUART_SCLK_PIN) */

#if(ModbusUART_SS0_PIN)
    #define ModbusUART_SS0_HSIOM_REG      (*(reg32 *) ModbusUART_spi_ss0__0__HSIOM)
    #define ModbusUART_SS0_HSIOM_PTR      ( (reg32 *) ModbusUART_spi_ss0__0__HSIOM)
    #define ModbusUART_SS0_HSIOM_MASK     (ModbusUART_spi_ss0__0__HSIOM_MASK)
    #define ModbusUART_SS0_HSIOM_POS      (ModbusUART_spi_ss0__0__HSIOM_SHIFT)
#endif /* (ModbusUART_SS1_PIN) */

#if(ModbusUART_SS1_PIN)
    #define ModbusUART_SS1_HSIOM_REG      (*(reg32 *) ModbusUART_spi_ss1__0__HSIOM)
    #define ModbusUART_SS1_HSIOM_PTR      ( (reg32 *) ModbusUART_spi_ss1__0__HSIOM)
    #define ModbusUART_SS1_HSIOM_MASK     (ModbusUART_spi_ss1__0__HSIOM_MASK)
    #define ModbusUART_SS1_HSIOM_POS      (ModbusUART_spi_ss1__0__HSIOM_SHIFT)
#endif /* (ModbusUART_SS1_PIN) */

#if(ModbusUART_SS2_PIN)
    #define ModbusUART_SS2_HSIOM_REG     (*(reg32 *) ModbusUART_spi_ss2__0__HSIOM)
    #define ModbusUART_SS2_HSIOM_PTR     ( (reg32 *) ModbusUART_spi_ss2__0__HSIOM)
    #define ModbusUART_SS2_HSIOM_MASK    (ModbusUART_spi_ss2__0__HSIOM_MASK)
    #define ModbusUART_SS2_HSIOM_POS     (ModbusUART_spi_ss2__0__HSIOM_SHIFT)
#endif /* (ModbusUART_SS2_PIN) */

#if(ModbusUART_SS3_PIN)
    #define ModbusUART_SS3_HSIOM_REG     (*(reg32 *) ModbusUART_spi_ss3__0__HSIOM)
    #define ModbusUART_SS3_HSIOM_PTR     ( (reg32 *) ModbusUART_spi_ss3__0__HSIOM)
    #define ModbusUART_SS3_HSIOM_MASK    (ModbusUART_spi_ss3__0__HSIOM_MASK)
    #define ModbusUART_SS3_HSIOM_POS     (ModbusUART_spi_ss3__0__HSIOM_SHIFT)
#endif /* (ModbusUART_SS3_PIN) */

#if(ModbusUART_I2C_PINS)
    #define ModbusUART_SCL_HSIOM_REG     (*(reg32 *) ModbusUART_scl__0__HSIOM)
    #define ModbusUART_SCL_HSIOM_PTR     ( (reg32 *) ModbusUART_scl__0__HSIOM)
    #define ModbusUART_SCL_HSIOM_MASK    (ModbusUART_scl__0__HSIOM_MASK)
    #define ModbusUART_SCL_HSIOM_POS     (ModbusUART_scl__0__HSIOM_SHIFT)

    #define ModbusUART_SDA_HSIOM_REG     (*(reg32 *) ModbusUART_sda__0__HSIOM)
    #define ModbusUART_SDA_HSIOM_PTR     ( (reg32 *) ModbusUART_sda__0__HSIOM)
    #define ModbusUART_SDA_HSIOM_MASK    (ModbusUART_sda__0__HSIOM_MASK)
    #define ModbusUART_SDA_HSIOM_POS     (ModbusUART_sda__0__HSIOM_SHIFT)
#endif /* (ModbusUART_I2C_PINS) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constanst */
#define ModbusUART_HSIOM_DEF_SEL      (0x00u)
#define ModbusUART_HSIOM_GPIO_SEL     (0x00u)
#define ModbusUART_HSIOM_UART_SEL     (0x09u)
#define ModbusUART_HSIOM_I2C_SEL      (0x0Eu)
#define ModbusUART_HSIOM_SPI_SEL      (0x0Fu)

#define ModbusUART_SCB_PINS_NUMBER            (7u)
#define ModbusUART_MOSI_SCL_RX_PIN_INDEX      (0u) /* RX pins without interrupt */
#define ModbusUART_MOSI_SCL_RX_WAKE_PIN_INDEX (0u) /* RX pin with interrupt     */
#define ModbusUART_MISO_SDA_TX_PIN_INDEX      (1u)
#define ModbusUART_SCLK_PIN_INDEX             (2u)
#define ModbusUART_SS0_PIN_INDEX              (3u)
#define ModbusUART_SS1_PIN_INDEX              (4u)
#define ModbusUART_SS2_PIN_INDEX              (5u)
#define ModbusUART_SS3_PIN_INDEX              (6u)

#define ModbusUART_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin DM defines */
#define ModbusUART_PIN_DM_ALG_HIZ  (0u)
#define ModbusUART_PIN_DM_DIG_HIZ  (1u)
#define ModbusUART_PIN_DM_OD_LO    (4u)
#define ModbusUART_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

#define ModbusUART_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        /* Sets new bits-mask */                 \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

#define ModbusUART_SET_HSIOM_SEL(reg, mask, pos, sel) ModbusUART_SET_REGISTER_BITS(reg, mask, pos, sel)
#define ModbusUART_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        ModbusUART_SET_REGISTER_BITS(reg, mask, pos, intType)


/* ModbusUART_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  ModbusUART_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* Unconfigured SCB: scl singnal */
#if(ModbusUART_MOSI_SCL_RX_WAKE_PIN)
    #define ModbusUART_SET_I2C_SCL_DR(val) \
                            ModbusUART_spi_mosi_i2c_scl_uart_rx_wake_Write(val)

    #define ModbusUART_SET_I2C_SCL_HSIOM_SEL(sel) \
                    ModbusUART_SET_HSIOM_SEL(ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_REG,  \
                                                   ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_MASK, \
                                                   ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_POS,  \
                                                   (sel))

#elif(ModbusUART_MOSI_SCL_RX_PIN)
    #define ModbusUART_SET_I2C_SCL_DR(val) \
                            ModbusUART_spi_mosi_i2c_scl_uart_rx_Write(val)


    #define ModbusUART_SET_I2C_SCL_HSIOM_SEL(sel) \
                            ModbusUART_SET_HSIOM_SEL(ModbusUART_MOSI_SCL_RX_HSIOM_REG,  \
                                                           ModbusUART_MOSI_SCL_RX_HSIOM_MASK, \
                                                           ModbusUART_MOSI_SCL_RX_HSIOM_POS,  \
                                                           (sel))
#else
    #if(!ModbusUART_I2C_PINS)
        #define ModbusUART_SET_I2C_SCL_DR(val) \
                                                 do{ ; }while(0)
        #define ModbusUART_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                        do{ ; }while(0)

    #endif /* (!ModbusUART_I2C_PINS) */
#endif /* (ModbusUART_MOSI_SCL_RX_PIN) */

/* SCB I2C: scl singal */
#if(ModbusUART_I2C_PINS)
    #define ModbusUART_SET_I2C_SCL_DR(val) ModbusUART_scl_Write(val)

    #define ModbusUART_SET_I2C_SCL_HSIOM_SEL(sel) \
                          ModbusUART_SET_HSIOM_SEL(ModbusUART_SCL_HSIOM_REG,  \
                                                         ModbusUART_SCL_HSIOM_MASK, \
                                                         ModbusUART_SCL_HSIOM_POS,  \
                                                         (sel))

#endif /* (ModbusUART_I2C_PINS) */


#endif /* (CY_SCB_PINS_ModbusUART_H) */


/* [] END OF FILE */
