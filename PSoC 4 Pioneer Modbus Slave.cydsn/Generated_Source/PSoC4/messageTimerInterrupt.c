/*******************************************************************************
* File Name: messageTimerInterrupt.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <messageTimerInterrupt.h>

#if !defined(messageTimerInterrupt__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START messageTimerInterrupt_intc` */
#include <messageTimer.h>
extern uint8 volatile interruptFlag;
/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: messageTimerInterrupt_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void messageTimerInterrupt_Start(void)
{
    /* For all we know the interrupt is active. */
    messageTimerInterrupt_Disable();

    /* Set the ISR to point to the messageTimerInterrupt Interrupt. */
    messageTimerInterrupt_SetVector(&messageTimerInterrupt_Interrupt);

    /* Set the priority. */
    messageTimerInterrupt_SetPriority((uint8)messageTimerInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    messageTimerInterrupt_Enable();
}


/*******************************************************************************
* Function Name: messageTimerInterrupt_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void messageTimerInterrupt_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    messageTimerInterrupt_Disable();

    /* Set the ISR to point to the messageTimerInterrupt Interrupt. */
    messageTimerInterrupt_SetVector(address);

    /* Set the priority. */
    messageTimerInterrupt_SetPriority((uint8)messageTimerInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    messageTimerInterrupt_Enable();
}


/*******************************************************************************
* Function Name: messageTimerInterrupt_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
void messageTimerInterrupt_Stop(void)
{
    /* Disable this interrupt. */
    messageTimerInterrupt_Disable();

    /* Set the ISR to point to the passive one. */
    messageTimerInterrupt_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: messageTimerInterrupt_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for messageTimerInterrupt.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/

/*******************************************************************************
* Function Name: messageTimerInterrupt_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling messageTimerInterrupt_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use messageTimerInterrupt_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void messageTimerInterrupt_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + messageTimerInterrupt__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: messageTimerInterrupt_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress messageTimerInterrupt_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + messageTimerInterrupt__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: messageTimerInterrupt_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling messageTimerInterrupt_Start
*   or messageTimerInterrupt_StartEx will override any effect this method would 
*   have had. This method should only be called after messageTimerInterrupt_Start or 
*   messageTimerInterrupt_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void messageTimerInterrupt_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((messageTimerInterrupt__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *messageTimerInterrupt_INTC_PRIOR = (*messageTimerInterrupt_INTC_PRIOR & (uint32)(~messageTimerInterrupt__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: messageTimerInterrupt_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 3, 0 being the highest.
*
*******************************************************************************/
uint8 messageTimerInterrupt_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((messageTimerInterrupt__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*messageTimerInterrupt_INTC_PRIOR & messageTimerInterrupt__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: messageTimerInterrupt_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void messageTimerInterrupt_Enable(void)
{
    /* Enable the general interrupt. */
    *messageTimerInterrupt_INTC_SET_EN = messageTimerInterrupt__INTC_MASK;
}


/*******************************************************************************
* Function Name: messageTimerInterrupt_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 messageTimerInterrupt_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*messageTimerInterrupt_INTC_SET_EN & (uint32)messageTimerInterrupt__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: messageTimerInterrupt_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void messageTimerInterrupt_Disable(void)
{
    /* Disable the general interrupt. */
    *messageTimerInterrupt_INTC_CLR_EN = messageTimerInterrupt__INTC_MASK;
}


/*******************************************************************************
* Function Name: messageTimerInterrupt_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void messageTimerInterrupt_SetPending(void)
{
    *messageTimerInterrupt_INTC_SET_PD = messageTimerInterrupt__INTC_MASK;
}


/*******************************************************************************
* Function Name: messageTimerInterrupt_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void messageTimerInterrupt_ClearPending(void)
{
    *messageTimerInterrupt_INTC_CLR_PD = messageTimerInterrupt__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
#if 0 /* begin disabled code */
`#start timer_ISR_Interrupt` -- section removed from template
	uint32 source;
    interruptFlag = 1;
	source = messageTimer_GetInterruptSource();
    messageTimer_ClearInterrupt(source);
`#end`

#endif /* end disabled code */
