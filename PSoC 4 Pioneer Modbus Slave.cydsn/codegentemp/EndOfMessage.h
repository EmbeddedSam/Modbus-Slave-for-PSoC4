/*******************************************************************************
* File Name: EndOfMessage.h
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
#if !defined(CY_ISR_EndOfMessage_H)
#define CY_ISR_EndOfMessage_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void EndOfMessage_Start(void);
void EndOfMessage_StartEx(cyisraddress address);
void EndOfMessage_Stop(void);

CY_ISR_PROTO(EndOfMessage_Interrupt);

void EndOfMessage_SetVector(cyisraddress address);
cyisraddress EndOfMessage_GetVector(void);

void EndOfMessage_SetPriority(uint8 priority);
uint8 EndOfMessage_GetPriority(void);

void EndOfMessage_Enable(void);
uint8 EndOfMessage_GetState(void);
void EndOfMessage_Disable(void);

void EndOfMessage_SetPending(void);
void EndOfMessage_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the EndOfMessage ISR. */
#define EndOfMessage_INTC_VECTOR            ((reg32 *) EndOfMessage__INTC_VECT)

/* Address of the EndOfMessage ISR priority. */
#define EndOfMessage_INTC_PRIOR             ((reg32 *) EndOfMessage__INTC_PRIOR_REG)

/* Priority of the EndOfMessage interrupt. */
#define EndOfMessage_INTC_PRIOR_NUMBER      EndOfMessage__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable EndOfMessage interrupt. */
#define EndOfMessage_INTC_SET_EN            ((reg32 *) EndOfMessage__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the EndOfMessage interrupt. */
#define EndOfMessage_INTC_CLR_EN            ((reg32 *) EndOfMessage__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the EndOfMessage interrupt state to pending. */
#define EndOfMessage_INTC_SET_PD            ((reg32 *) EndOfMessage__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the EndOfMessage interrupt. */
#define EndOfMessage_INTC_CLR_PD            ((reg32 *) EndOfMessage__INTC_CLR_PD_REG)



#endif /* CY_ISR_EndOfMessage_H */


/* [] END OF FILE */
