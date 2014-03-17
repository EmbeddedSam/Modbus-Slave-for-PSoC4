/*******************************************************************************
* File Name: EndOfMessage.c  
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
#include <EndOfMessage.h>

#if !defined(EndOfMessage__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START EndOfMessage_intc` */

/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: EndOfMessage_Start
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
void EndOfMessage_Start(void)
{
    /* For all we know the interrupt is active. */
    EndOfMessage_Disable();

    /* Set the ISR to point to the EndOfMessage Interrupt. */
    EndOfMessage_SetVector(&EndOfMessage_Interrupt);

    /* Set the priority. */
    EndOfMessage_SetPriority((uint8)EndOfMessage_INTC_PRIOR_NUMBER);

    /* Enable it. */
    EndOfMessage_Enable();
}


/*******************************************************************************
* Function Name: EndOfMessage_StartEx
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
void EndOfMessage_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    EndOfMessage_Disable();

    /* Set the ISR to point to the EndOfMessage Interrupt. */
    EndOfMessage_SetVector(address);

    /* Set the priority. */
    EndOfMessage_SetPriority((uint8)EndOfMessage_INTC_PRIOR_NUMBER);

    /* Enable it. */
    EndOfMessage_Enable();
}


/*******************************************************************************
* Function Name: EndOfMessage_Stop
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
void EndOfMessage_Stop(void)
{
    /* Disable this interrupt. */
    EndOfMessage_Disable();

    /* Set the ISR to point to the passive one. */
    EndOfMessage_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: EndOfMessage_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for EndOfMessage.
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
CY_ISR(EndOfMessage_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START EndOfMessage_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: EndOfMessage_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling EndOfMessage_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use EndOfMessage_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void EndOfMessage_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + EndOfMessage__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: EndOfMessage_GetVector
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
cyisraddress EndOfMessage_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + EndOfMessage__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: EndOfMessage_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling EndOfMessage_Start
*   or EndOfMessage_StartEx will override any effect this method would 
*   have had. This method should only be called after EndOfMessage_Start or 
*   EndOfMessage_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void EndOfMessage_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((EndOfMessage__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *EndOfMessage_INTC_PRIOR = (*EndOfMessage_INTC_PRIOR & (uint32)(~EndOfMessage__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: EndOfMessage_GetPriority
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
uint8 EndOfMessage_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((EndOfMessage__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*EndOfMessage_INTC_PRIOR & EndOfMessage__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: EndOfMessage_Enable
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
void EndOfMessage_Enable(void)
{
    /* Enable the general interrupt. */
    *EndOfMessage_INTC_SET_EN = EndOfMessage__INTC_MASK;
}


/*******************************************************************************
* Function Name: EndOfMessage_GetState
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
uint8 EndOfMessage_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*EndOfMessage_INTC_SET_EN & (uint32)EndOfMessage__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: EndOfMessage_Disable
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
void EndOfMessage_Disable(void)
{
    /* Disable the general interrupt. */
    *EndOfMessage_INTC_CLR_EN = EndOfMessage__INTC_MASK;
}


/*******************************************************************************
* Function Name: EndOfMessage_SetPending
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
void EndOfMessage_SetPending(void)
{
    *EndOfMessage_INTC_SET_PD = EndOfMessage__INTC_MASK;
}


/*******************************************************************************
* Function Name: EndOfMessage_ClearPending
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
void EndOfMessage_ClearPending(void)
{
    *EndOfMessage_INTC_CLR_PD = EndOfMessage__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
