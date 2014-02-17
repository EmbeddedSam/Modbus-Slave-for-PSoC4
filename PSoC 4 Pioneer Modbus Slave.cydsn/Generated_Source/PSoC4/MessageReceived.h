/*******************************************************************************
* File Name: MessageReceived.h
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
#if !defined(CY_ISR_MessageReceived_H)
#define CY_ISR_MessageReceived_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void MessageReceived_Start(void);
void MessageReceived_StartEx(cyisraddress address);
void MessageReceived_Stop(void);

CY_ISR_PROTO(MessageReceived_Interrupt);

void MessageReceived_SetVector(cyisraddress address);
cyisraddress MessageReceived_GetVector(void);

void MessageReceived_SetPriority(uint8 priority);
uint8 MessageReceived_GetPriority(void);

void MessageReceived_Enable(void);
uint8 MessageReceived_GetState(void);
void MessageReceived_Disable(void);

void MessageReceived_SetPending(void);
void MessageReceived_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the MessageReceived ISR. */
#define MessageReceived_INTC_VECTOR            ((reg32 *) MessageReceived__INTC_VECT)

/* Address of the MessageReceived ISR priority. */
#define MessageReceived_INTC_PRIOR             ((reg32 *) MessageReceived__INTC_PRIOR_REG)

/* Priority of the MessageReceived interrupt. */
#define MessageReceived_INTC_PRIOR_NUMBER      MessageReceived__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable MessageReceived interrupt. */
#define MessageReceived_INTC_SET_EN            ((reg32 *) MessageReceived__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the MessageReceived interrupt. */
#define MessageReceived_INTC_CLR_EN            ((reg32 *) MessageReceived__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the MessageReceived interrupt state to pending. */
#define MessageReceived_INTC_SET_PD            ((reg32 *) MessageReceived__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the MessageReceived interrupt. */
#define MessageReceived_INTC_CLR_PD            ((reg32 *) MessageReceived__INTC_CLR_PD_REG)



#endif /* CY_ISR_MessageReceived_H */


/* [] END OF FILE */
