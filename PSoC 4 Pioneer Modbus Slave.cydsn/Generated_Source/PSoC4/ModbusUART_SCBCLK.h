/*******************************************************************************
* File Name: ModbusUART_SCBCLK.h
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

#if !defined(CY_CLOCK_ModbusUART_SCBCLK_H)
#define CY_CLOCK_ModbusUART_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void ModbusUART_SCBCLK_Start(void);
void ModbusUART_SCBCLK_Stop(void);

void ModbusUART_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 ModbusUART_SCBCLK_GetDividerRegister(void);
uint8  ModbusUART_SCBCLK_GetFractionalDividerRegister(void);

#define ModbusUART_SCBCLK_Enable()                         ModbusUART_SCBCLK_Start()
#define ModbusUART_SCBCLK_Disable()                        ModbusUART_SCBCLK_Stop()
#define ModbusUART_SCBCLK_SetDividerRegister(clkDivider, reset)  \
                        ModbusUART_SCBCLK_SetFractionalDividerRegister((clkDivider), 0)
#define ModbusUART_SCBCLK_SetDivider(clkDivider)           ModbusUART_SCBCLK_SetDividerRegister((clkDivider), 1)
#define ModbusUART_SCBCLK_SetDividerValue(clkDivider)      ModbusUART_SCBCLK_SetDividerRegister((clkDivider) - 1, 1)


/***************************************
*             Registers
***************************************/

#define ModbusUART_SCBCLK_DIV_REG    (*(reg32 *)ModbusUART_SCBCLK__REGISTER)
#define ModbusUART_SCBCLK_ENABLE_REG ModbusUART_SCBCLK_DIV_REG

#endif /* !defined(CY_CLOCK_ModbusUART_SCBCLK_H) */

/* [] END OF FILE */
