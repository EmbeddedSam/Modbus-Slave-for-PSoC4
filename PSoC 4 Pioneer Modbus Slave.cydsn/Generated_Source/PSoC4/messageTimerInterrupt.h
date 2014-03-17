/*******************************************************************************
* File Name: messageTimerInterrupt.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_messageTimerInterrupt_H)
#define CY_ISR_messageTimerInterrupt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void messageTimerInterrupt_Start(void);
void messageTimerInterrupt_StartEx(cyisraddress address);
void messageTimerInterrupt_Stop(void);



void messageTimerInterrupt_SetVector(cyisraddress address);
cyisraddress messageTimerInterrupt_GetVector(void);

void messageTimerInterrupt_SetPriority(uint8 priority);
uint8 messageTimerInterrupt_GetPriority(void);

void messageTimerInterrupt_Enable(void);
uint8 messageTimerInterrupt_GetState(void);
void messageTimerInterrupt_Disable(void);

void messageTimerInterrupt_SetPending(void);
void messageTimerInterrupt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the messageTimerInterrupt ISR. */
#define messageTimerInterrupt_INTC_VECTOR            ((reg32 *) messageTimerInterrupt__INTC_VECT)

/* Address of the messageTimerInterrupt ISR priority. */
#define messageTimerInterrupt_INTC_PRIOR             ((reg32 *) messageTimerInterrupt__INTC_PRIOR_REG)

/* Priority of the messageTimerInterrupt interrupt. */
#define messageTimerInterrupt_INTC_PRIOR_NUMBER      messageTimerInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable messageTimerInterrupt interrupt. */
#define messageTimerInterrupt_INTC_SET_EN            ((reg32 *) messageTimerInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the messageTimerInterrupt interrupt. */
#define messageTimerInterrupt_INTC_CLR_EN            ((reg32 *) messageTimerInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the messageTimerInterrupt interrupt state to pending. */
#define messageTimerInterrupt_INTC_SET_PD            ((reg32 *) messageTimerInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the messageTimerInterrupt interrupt. */
#define messageTimerInterrupt_INTC_CLR_PD            ((reg32 *) messageTimerInterrupt__INTC_CLR_PD_REG)



#endif /* CY_ISR_messageTimerInterrupt_H */


/* [] END OF FILE */
