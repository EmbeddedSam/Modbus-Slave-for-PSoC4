/*******************************************************************************
* File Name: ModbusComms_PINS.h
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

#if !defined(CY_SCB_PINS_ModbusComms_H)
#define CY_SCB_PINS_ModbusComms_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define ModbusComms_REMOVE_MOSI_SCL_RX_WAKE_PIN    (1u)
#define ModbusComms_REMOVE_MOSI_SCL_RX_PIN         (1u)
#define ModbusComms_REMOVE_MISO_SDA_TX_PIN         (1u)
#define ModbusComms_REMOVE_SCLK_PIN                (1u)
#define ModbusComms_REMOVE_SS0_PIN                 (1u)
#define ModbusComms_REMOVE_SS1_PIN                 (1u)
#define ModbusComms_REMOVE_SS2_PIN                 (1u)
#define ModbusComms_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define ModbusComms_REMOVE_I2C_PINS                (1u)
#define ModbusComms_REMOVE_SPI_MASTER_PINS         (1u)
#define ModbusComms_REMOVE_SPI_SLAVE_PINS          (1u)
#define ModbusComms_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define ModbusComms_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define ModbusComms_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define ModbusComms_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define ModbusComms_REMOVE_UART_TX_PIN             (0u)
#define ModbusComms_REMOVE_UART_RX_TX_PIN          (1u)
#define ModbusComms_REMOVE_UART_RX_PIN             (0u)
#define ModbusComms_REMOVE_UART_RX_WAKE_PIN        (1u)

/* Unconfigured pins */
#define ModbusComms_MOSI_SCL_RX_WAKE_PIN   (0u == ModbusComms_REMOVE_MOSI_SCL_RX_WAKE_PIN)
#define ModbusComms_MOSI_SCL_RX_PIN        (0u == ModbusComms_REMOVE_MOSI_SCL_RX_PIN)
#define ModbusComms_MISO_SDA_TX_PIN        (0u == ModbusComms_REMOVE_MISO_SDA_TX_PIN)
#define ModbusComms_SCLK_PIN               (0u == ModbusComms_REMOVE_SCLK_PIN)
#define ModbusComms_SS0_PIN                (0u == ModbusComms_REMOVE_SS0_PIN)
#define ModbusComms_SS1_PIN                (0u == ModbusComms_REMOVE_SS1_PIN)
#define ModbusComms_SS2_PIN                (0u == ModbusComms_REMOVE_SS2_PIN)
#define ModbusComms_SS3_PIN                (0u == ModbusComms_REMOVE_SS3_PIN)

/* Mode defined pins */
#define ModbusComms_I2C_PINS               (0u == ModbusComms_REMOVE_I2C_PINS)
#define ModbusComms_SPI_MASTER_PINS        (0u == ModbusComms_REMOVE_SPI_MASTER_PINS) 
#define ModbusComms_SPI_SLAVE_PINS         (0u == ModbusComms_REMOVE_SPI_SLAVE_PINS)
#define ModbusComms_SPI_MASTER_SS0_PIN     (0u == ModbusComms_REMOVE_SPI_MASTER_SS0_PIN)
#define ModbusComms_SPI_MASTER_SS1_PIN     (0u == ModbusComms_REMOVE_SPI_MASTER_SS1_PIN)
#define ModbusComms_SPI_MASTER_SS2_PIN     (0u == ModbusComms_REMOVE_SPI_MASTER_SS2_PIN)
#define ModbusComms_SPI_MASTER_SS3_PIN     (0u == ModbusComms_REMOVE_SPI_MASTER_SS3_PIN)
#define ModbusComms_UART_TX_PIN            (0u == ModbusComms_REMOVE_UART_TX_PIN)
#define ModbusComms_UART_RX_TX_PIN         (0u == ModbusComms_REMOVE_UART_RX_TX_PIN)
#define ModbusComms_UART_RX_PIN            (0u == ModbusComms_REMOVE_UART_RX_PIN)
#define ModbusComms_UART_RX_WAKE_PIN       (0u == ModbusComms_REMOVE_UART_RX_WAKE_PIN)


/***************************************
*             Includes
****************************************/

#if(ModbusComms_MOSI_SCL_RX_WAKE_PIN)
    #include "ModbusComms_spi_mosi_i2c_scl_uart_rx_wake.h"
#endif /* (ModbusComms_MOSI_SCL_RX_WAKE_PIN) */

#if(ModbusComms_MOSI_SCL_RX_PIN)
    #include "ModbusComms_spi_mosi_i2c_scl_uart_rx.h"
#endif /* (ModbusComms_MOSI_SCL_RX_PIN) */

#if(ModbusComms_MISO_SDA_TX_PIN)
    #include "ModbusComms_spi_miso_i2c_sda_uart_tx.h"
#endif /* (ModbusComms_MISO_SDA_TX_PIN_PIN) */

#if(ModbusComms_SCLK_PIN)
    #include "ModbusComms_spi_sclk.h"
#endif /* (ModbusComms_SCLK_PIN) */

#if(ModbusComms_SS0_PIN)
    #include "ModbusComms_spi_ss0.h"
#endif /* (ModbusComms_SS1_PIN) */

#if(ModbusComms_SS1_PIN)
    #include "ModbusComms_spi_ss1.h"
#endif /* (ModbusComms_SS1_PIN) */

#if(ModbusComms_SS2_PIN)
    #include "ModbusComms_spi_ss2.h"
#endif /* (ModbusComms_SS2_PIN) */

#if(ModbusComms_SS3_PIN)
    #include "ModbusComms_spi_ss3.h"
#endif /* (ModbusComms_SS3_PIN) */

#if(ModbusComms_I2C_PINS)
    #include "ModbusComms_scl.h"
    #include "ModbusComms_sda.h"
#endif /* (ModbusComms_I2C_PINS) */
    
#if(ModbusComms_SPI_MASTER_PINS)
    #include "ModbusComms_sclk_m.h"
    #include "ModbusComms_mosi_m.h"
    #include "ModbusComms_miso_m.h"
#endif /* (ModbusComms_SPI_MASTER_PINS) */

#if(ModbusComms_SPI_SLAVE_PINS)
    #include "ModbusComms_sclk_s.h"
    #include "ModbusComms_mosi_s.h"
    #include "ModbusComms_miso_s.h"
    #include "ModbusComms_ss_s.h"
#endif /* (ModbusComms_SPI_SLAVE_PINS) */

#if(ModbusComms_SPI_MASTER_SS0_PIN)
    #include "ModbusComms_ss0_m.h"
#endif /* (ModbusComms_SPI_MASTER_SS0_PIN) */

#if(ModbusComms_SPI_MASTER_SS1_PIN)
    #include "ModbusComms_ss1_m.h"
#endif /* (ModbusComms_SPI_MASTER_SS1_PIN) */

#if(ModbusComms_SPI_MASTER_SS2_PIN)
    #include "ModbusComms_ss2_m.h"
#endif /* (ModbusComms_SPI_MASTER_SS2_PIN) */

#if(ModbusComms_SPI_MASTER_SS3_PIN)
    #include "ModbusComms_ss3_m.h"
#endif /* (ModbusComms_SPI_MASTER_SS3_PIN) */

#if(ModbusComms_UART_TX_PIN)
    #include "ModbusComms_tx.h"
#endif /* (ModbusComms_UART_TX_PIN) */

#if(ModbusComms_UART_RX_TX_PIN)
    #include "ModbusComms_rx_tx.h"
#endif /* (ModbusComms_UART_RX_TX_PIN) */

#if(ModbusComms_UART_RX_PIN)
    #include "ModbusComms_rx.h"
#endif /* (ModbusComms_UART_RX_PIN) */

#if(ModbusComms_UART_RX_WAKE_PIN)
    #include "ModbusComms_rx_wake.h"
#endif /* (ModbusComms_UART_RX_WAKE_PIN) */


/***************************************
*              Registers
***************************************/

#if(ModbusComms_MOSI_SCL_RX_WAKE_PIN)
    #define ModbusComms_MOSI_SCL_RX_WAKE_HSIOM_REG  \
                                                (*(reg32 *) ModbusComms_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define ModbusComms_MOSI_SCL_RX_WAKE_HSIOM_PTR  \
                                                ( (reg32 *) ModbusComms_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define ModbusComms_MOSI_SCL_RX_WAKE_HSIOM_MASK \
                                                (ModbusComms_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_MASK)
    #define ModbusComms_MOSI_SCL_RX_WAKE_HSIOM_POS  \
                                                (ModbusComms_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_SHIFT)

    #define ModbusComms_MOSI_SCL_RX_WAKE_INTCFG_REG    (*(reg32 *) \
                                                              ModbusComms_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)
    #define ModbusComms_MOSI_SCL_RX_WAKE_INTCFG_PTR    ( (reg32 *) \
                                                              ModbusComms_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)

    #define ModbusComms_INTCFG_TYPE_MASK                  (0x03u)
    #define ModbusComms_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS  (ModbusComms_spi_mosi_i2c_scl_uart_rx_wake__SHIFT)
    #define ModbusComms_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK ((uint32)                                           \
                                                                    ((uint32) ModbusComms_INTCFG_TYPE_MASK << \
                                                                    ModbusComms_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS))
#endif /* (ModbusComms_MOSI_SCL_RX_WAKE_PIN) */

#if(ModbusComms_MOSI_SCL_RX_PIN)
    #define ModbusComms_MOSI_SCL_RX_HSIOM_REG      (*(reg32 *) ModbusComms_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define ModbusComms_MOSI_SCL_RX_HSIOM_PTR      ( (reg32 *) ModbusComms_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define ModbusComms_MOSI_SCL_RX_HSIOM_MASK     (ModbusComms_spi_mosi_i2c_scl_uart_rx__0__HSIOM_MASK)
    #define ModbusComms_MOSI_SCL_RX_HSIOM_POS      (ModbusComms_spi_mosi_i2c_scl_uart_rx__0__HSIOM_SHIFT)
#endif /* (ModbusComms_MOSI_SCL_RX_PIN) */

#if(ModbusComms_MISO_SDA_TX_PIN)
    #define ModbusComms_MISO_SDA_TX_HSIOM_REG      (*(reg32 *) ModbusComms_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define ModbusComms_MISO_SDA_TX_HSIOM_PTR      ( (reg32 *) ModbusComms_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define ModbusComms_MISO_SDA_TX_HSIOM_MASK     (ModbusComms_spi_miso_i2c_sda_uart_tx__0__HSIOM_MASK)
    #define ModbusComms_MISO_SDA_TX_HSIOM_POS      (ModbusComms_spi_miso_i2c_sda_uart_tx__0__HSIOM_SHIFT)
#endif /* (ModbusComms_MISO_SDA_TX_PIN_PIN) */

#if(ModbusComms_SCLK_PIN)
    #define ModbusComms_SCLK_HSIOM_REG     (*(reg32 *) ModbusComms_spi_sclk__0__HSIOM)
    #define ModbusComms_SCLK_HSIOM_PTR     ( (reg32 *) ModbusComms_spi_sclk__0__HSIOM)
    #define ModbusComms_SCLK_HSIOM_MASK    (ModbusComms_spi_sclk__0__HSIOM_MASK)
    #define ModbusComms_SCLK_HSIOM_POS     (ModbusComms_spi_sclk__0__HSIOM_SHIFT)
#endif /* (ModbusComms_SCLK_PIN) */

#if(ModbusComms_SS0_PIN)
    #define ModbusComms_SS0_HSIOM_REG      (*(reg32 *) ModbusComms_spi_ss0__0__HSIOM)
    #define ModbusComms_SS0_HSIOM_PTR      ( (reg32 *) ModbusComms_spi_ss0__0__HSIOM)
    #define ModbusComms_SS0_HSIOM_MASK     (ModbusComms_spi_ss0__0__HSIOM_MASK)
    #define ModbusComms_SS0_HSIOM_POS      (ModbusComms_spi_ss0__0__HSIOM_SHIFT)
#endif /* (ModbusComms_SS1_PIN) */

#if(ModbusComms_SS1_PIN)
    #define ModbusComms_SS1_HSIOM_REG      (*(reg32 *) ModbusComms_spi_ss1__0__HSIOM)
    #define ModbusComms_SS1_HSIOM_PTR      ( (reg32 *) ModbusComms_spi_ss1__0__HSIOM)
    #define ModbusComms_SS1_HSIOM_MASK     (ModbusComms_spi_ss1__0__HSIOM_MASK)
    #define ModbusComms_SS1_HSIOM_POS      (ModbusComms_spi_ss1__0__HSIOM_SHIFT)
#endif /* (ModbusComms_SS1_PIN) */

#if(ModbusComms_SS2_PIN)
    #define ModbusComms_SS2_HSIOM_REG     (*(reg32 *) ModbusComms_spi_ss2__0__HSIOM)
    #define ModbusComms_SS2_HSIOM_PTR     ( (reg32 *) ModbusComms_spi_ss2__0__HSIOM)
    #define ModbusComms_SS2_HSIOM_MASK    (ModbusComms_spi_ss2__0__HSIOM_MASK)
    #define ModbusComms_SS2_HSIOM_POS     (ModbusComms_spi_ss2__0__HSIOM_SHIFT)
#endif /* (ModbusComms_SS2_PIN) */

#if(ModbusComms_SS3_PIN)
    #define ModbusComms_SS3_HSIOM_REG     (*(reg32 *) ModbusComms_spi_ss3__0__HSIOM)
    #define ModbusComms_SS3_HSIOM_PTR     ( (reg32 *) ModbusComms_spi_ss3__0__HSIOM)
    #define ModbusComms_SS3_HSIOM_MASK    (ModbusComms_spi_ss3__0__HSIOM_MASK)
    #define ModbusComms_SS3_HSIOM_POS     (ModbusComms_spi_ss3__0__HSIOM_SHIFT)
#endif /* (ModbusComms_SS3_PIN) */

#if(ModbusComms_I2C_PINS)
    #define ModbusComms_SCL_HSIOM_REG     (*(reg32 *) ModbusComms_scl__0__HSIOM)
    #define ModbusComms_SCL_HSIOM_PTR     ( (reg32 *) ModbusComms_scl__0__HSIOM)
    #define ModbusComms_SCL_HSIOM_MASK    (ModbusComms_scl__0__HSIOM_MASK)
    #define ModbusComms_SCL_HSIOM_POS     (ModbusComms_scl__0__HSIOM_SHIFT)

    #define ModbusComms_SDA_HSIOM_REG     (*(reg32 *) ModbusComms_sda__0__HSIOM)
    #define ModbusComms_SDA_HSIOM_PTR     ( (reg32 *) ModbusComms_sda__0__HSIOM)
    #define ModbusComms_SDA_HSIOM_MASK    (ModbusComms_sda__0__HSIOM_MASK)
    #define ModbusComms_SDA_HSIOM_POS     (ModbusComms_sda__0__HSIOM_SHIFT)
#endif /* (ModbusComms_I2C_PINS) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constanst */
#define ModbusComms_HSIOM_DEF_SEL      (0x00u)
#define ModbusComms_HSIOM_GPIO_SEL     (0x00u)
#define ModbusComms_HSIOM_UART_SEL     (0x09u)
#define ModbusComms_HSIOM_I2C_SEL      (0x0Eu)
#define ModbusComms_HSIOM_SPI_SEL      (0x0Fu)

#define ModbusComms_SCB_PINS_NUMBER            (7u)
#define ModbusComms_MOSI_SCL_RX_PIN_INDEX      (0u) /* RX pins without interrupt */
#define ModbusComms_MOSI_SCL_RX_WAKE_PIN_INDEX (0u) /* RX pin with interrupt     */
#define ModbusComms_MISO_SDA_TX_PIN_INDEX      (1u)
#define ModbusComms_SCLK_PIN_INDEX             (2u)
#define ModbusComms_SS0_PIN_INDEX              (3u)
#define ModbusComms_SS1_PIN_INDEX              (4u)
#define ModbusComms_SS2_PIN_INDEX              (5u)
#define ModbusComms_SS3_PIN_INDEX              (6u)

#define ModbusComms_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin DM defines */
#define ModbusComms_PIN_DM_ALG_HIZ  (0u)
#define ModbusComms_PIN_DM_DIG_HIZ  (1u)
#define ModbusComms_PIN_DM_OD_LO    (4u)
#define ModbusComms_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

#define ModbusComms_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        /* Sets new bits-mask */                 \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

#define ModbusComms_SET_HSIOM_SEL(reg, mask, pos, sel) ModbusComms_SET_REGISTER_BITS(reg, mask, pos, sel)
#define ModbusComms_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        ModbusComms_SET_REGISTER_BITS(reg, mask, pos, intType)


/* ModbusComms_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  ModbusComms_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* Unconfigured SCB: scl singnal */
#if(ModbusComms_MOSI_SCL_RX_WAKE_PIN)
    #define ModbusComms_SET_I2C_SCL_DR(val) \
                            ModbusComms_spi_mosi_i2c_scl_uart_rx_wake_Write(val)

    #define ModbusComms_SET_I2C_SCL_HSIOM_SEL(sel) \
                    ModbusComms_SET_HSIOM_SEL(ModbusComms_MOSI_SCL_RX_WAKE_HSIOM_REG,  \
                                                   ModbusComms_MOSI_SCL_RX_WAKE_HSIOM_MASK, \
                                                   ModbusComms_MOSI_SCL_RX_WAKE_HSIOM_POS,  \
                                                   (sel))

#elif(ModbusComms_MOSI_SCL_RX_PIN)
    #define ModbusComms_SET_I2C_SCL_DR(val) \
                            ModbusComms_spi_mosi_i2c_scl_uart_rx_Write(val)


    #define ModbusComms_SET_I2C_SCL_HSIOM_SEL(sel) \
                            ModbusComms_SET_HSIOM_SEL(ModbusComms_MOSI_SCL_RX_HSIOM_REG,  \
                                                           ModbusComms_MOSI_SCL_RX_HSIOM_MASK, \
                                                           ModbusComms_MOSI_SCL_RX_HSIOM_POS,  \
                                                           (sel))
#else
    #if(!ModbusComms_I2C_PINS)
        #define ModbusComms_SET_I2C_SCL_DR(val) \
                                                 do{ ; }while(0)
        #define ModbusComms_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                        do{ ; }while(0)

    #endif /* (!ModbusComms_I2C_PINS) */
#endif /* (ModbusComms_MOSI_SCL_RX_PIN) */

/* SCB I2C: scl singal */
#if(ModbusComms_I2C_PINS)
    #define ModbusComms_SET_I2C_SCL_DR(val) ModbusComms_scl_Write(val)

    #define ModbusComms_SET_I2C_SCL_HSIOM_SEL(sel) \
                          ModbusComms_SET_HSIOM_SEL(ModbusComms_SCL_HSIOM_REG,  \
                                                         ModbusComms_SCL_HSIOM_MASK, \
                                                         ModbusComms_SCL_HSIOM_POS,  \
                                                         (sel))

#endif /* (ModbusComms_I2C_PINS) */


#endif /* (CY_SCB_PINS_ModbusComms_H) */


/* [] END OF FILE */
