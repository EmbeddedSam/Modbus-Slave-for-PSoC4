/*******************************************************************************
* File Name: MessageTimerClock.h
* Version 2.10
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

#if !defined(CY_CLOCK_MessageTimerClock_H)
#define CY_CLOCK_MessageTimerClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void MessageTimerClock_Start(void);
void MessageTimerClock_Stop(void);

void MessageTimerClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 MessageTimerClock_GetDividerRegister(void);
uint8  MessageTimerClock_GetFractionalDividerRegister(void);

#define MessageTimerClock_Enable()                         MessageTimerClock_Start()
#define MessageTimerClock_Disable()                        MessageTimerClock_Stop()
#define MessageTimerClock_SetDividerRegister(clkDivider, reset)  \
                        MessageTimerClock_SetFractionalDividerRegister((clkDivider), 0u)
#define MessageTimerClock_SetDivider(clkDivider)           MessageTimerClock_SetDividerRegister((clkDivider), 1u)
#define MessageTimerClock_SetDividerValue(clkDivider)      MessageTimerClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/

#define MessageTimerClock_DIV_REG    (*(reg32 *)MessageTimerClock__REGISTER)
#define MessageTimerClock_ENABLE_REG MessageTimerClock_DIV_REG

#endif /* !defined(CY_CLOCK_MessageTimerClock_H) */

/* [] END OF FILE */
