/*******************************************************************************
* File Name: ModbusComms_SCBCLK.h
* Version 2.0
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_ModbusComms_SCBCLK_H)
#define CY_CLOCK_ModbusComms_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void ModbusComms_SCBCLK_Start(void);
void ModbusComms_SCBCLK_Stop(void);

void ModbusComms_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 ModbusComms_SCBCLK_GetDividerRegister(void);
uint8  ModbusComms_SCBCLK_GetFractionalDividerRegister(void);

#define ModbusComms_SCBCLK_Enable()                         ModbusComms_SCBCLK_Start()
#define ModbusComms_SCBCLK_Disable()                        ModbusComms_SCBCLK_Stop()
#define ModbusComms_SCBCLK_SetDividerRegister(clkDivider, reset)  \
                        ModbusComms_SCBCLK_SetFractionalDividerRegister((clkDivider), 0)
#define ModbusComms_SCBCLK_SetDivider(clkDivider)           ModbusComms_SCBCLK_SetDividerRegister((clkDivider), 1)
#define ModbusComms_SCBCLK_SetDividerValue(clkDivider)      ModbusComms_SCBCLK_SetDividerRegister((clkDivider) - 1, 1)


/***************************************
*             Registers
***************************************/

#define ModbusComms_SCBCLK_DIV_REG    (*(reg32 *)ModbusComms_SCBCLK__REGISTER)
#define ModbusComms_SCBCLK_ENABLE_REG ModbusComms_SCBCLK_DIV_REG

#endif /* !defined(CY_CLOCK_ModbusComms_SCBCLK_H) */

/* [] END OF FILE */
