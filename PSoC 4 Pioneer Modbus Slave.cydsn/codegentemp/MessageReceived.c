/*******************************************************************************
* File Name: MessageReceived.c  
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
#include <MessageReceived.h>

#if !defined(MessageReceived__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START MessageReceived_intc` */

/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: MessageReceived_Start
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
void MessageReceived_Start(void)
{
    /* For all we know the interrupt is active. */
    MessageReceived_Disable();

    /* Set the ISR to point to the MessageReceived Interrupt. */
    MessageReceived_SetVector(&MessageReceived_Interrupt);

    /* Set the priority. */
    MessageReceived_SetPriority((uint8)MessageReceived_INTC_PRIOR_NUMBER);

    /* Enable it. */
    MessageReceived_Enable();
}


/*******************************************************************************
* Function Name: MessageReceived_StartEx
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
void MessageReceived_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    MessageReceived_Disable();

    /* Set the ISR to point to the MessageReceived Interrupt. */
    MessageReceived_SetVector(address);

    /* Set the priority. */
    MessageReceived_SetPriority((uint8)MessageReceived_INTC_PRIOR_NUMBER);

    /* Enable it. */
    MessageReceived_Enable();
}


/*******************************************************************************
* Function Name: MessageReceived_Stop
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
void MessageReceived_Stop(void)
{
    /* Disable this interrupt. */
    MessageReceived_Disable();

    /* Set the ISR to point to the passive one. */
    MessageReceived_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: MessageReceived_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for MessageReceived.
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
CY_ISR(MessageReceived_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START MessageReceived_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: MessageReceived_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling MessageReceived_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use MessageReceived_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void MessageReceived_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + MessageReceived__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: MessageReceived_GetVector
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
cyisraddress MessageReceived_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + MessageReceived__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: MessageReceived_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling MessageReceived_Start
*   or MessageReceived_StartEx will override any effect this method would 
*   have had. This method should only be called after MessageReceived_Start or 
*   MessageReceived_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void MessageReceived_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((MessageReceived__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *MessageReceived_INTC_PRIOR = (*MessageReceived_INTC_PRIOR & (uint32)(~MessageReceived__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: MessageReceived_GetPriority
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
uint8 MessageReceived_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((MessageReceived__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*MessageReceived_INTC_PRIOR & MessageReceived__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: MessageReceived_Enable
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
void MessageReceived_Enable(void)
{
    /* Enable the general interrupt. */
    *MessageReceived_INTC_SET_EN = MessageReceived__INTC_MASK;
}


/*******************************************************************************
* Function Name: MessageReceived_GetState
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
uint8 MessageReceived_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*MessageReceived_INTC_SET_EN & (uint32)MessageReceived__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: MessageReceived_Disable
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
void MessageReceived_Disable(void)
{
    /* Disable the general interrupt. */
    *MessageReceived_INTC_CLR_EN = MessageReceived__INTC_MASK;
}


/*******************************************************************************
* Function Name: MessageReceived_SetPending
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
void MessageReceived_SetPending(void)
{
    *MessageReceived_INTC_SET_PD = MessageReceived__INTC_MASK;
}


/*******************************************************************************
* Function Name: MessageReceived_ClearPending
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
void MessageReceived_ClearPending(void)
{
    *MessageReceived_INTC_CLR_PD = MessageReceived__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
