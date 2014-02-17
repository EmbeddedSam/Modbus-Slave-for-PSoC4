/*******************************************************************************
* File Name: MessageTimer_PM.c
* Version 1.0
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "MessageTimer.h"

static MessageTimer_BACKUP_STRUCT MessageTimer_backup;


/*******************************************************************************
* Function Name: MessageTimer_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: MessageTimer_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_Sleep(void)
{
    if(0u != (MessageTimer_BLOCK_CONTROL_REG & MessageTimer_MASK))
    {
        MessageTimer_backup.enableState = 1u;
    }
    else
    {
        MessageTimer_backup.enableState = 0u;
    }

    MessageTimer_Stop();
    MessageTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: MessageTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: MessageTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_Wakeup(void)
{
    MessageTimer_RestoreConfig();

    if(0u != MessageTimer_backup.enableState)
    {
        MessageTimer_Enable();
    }
}


/* [] END OF FILE */
