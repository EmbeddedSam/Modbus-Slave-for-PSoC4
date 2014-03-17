/*******************************************************************************
* File Name: TimerPin.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "TimerPin.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        TimerPin_PC =   (TimerPin_PC & \
                                (uint32)(~(uint32)(TimerPin_DRIVE_MODE_IND_MASK << (TimerPin_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (TimerPin_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: TimerPin_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void TimerPin_Write(uint8 value) 
{
    uint8 drVal = (uint8)(TimerPin_DR & (uint8)(~TimerPin_MASK));
    drVal = (drVal | ((uint8)(value << TimerPin_SHIFT) & TimerPin_MASK));
    TimerPin_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: TimerPin_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void TimerPin_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(TimerPin__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: TimerPin_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro TimerPin_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 TimerPin_Read(void) 
{
    return (uint8)((TimerPin_PS & TimerPin_MASK) >> TimerPin_SHIFT);
}


/*******************************************************************************
* Function Name: TimerPin_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 TimerPin_ReadDataReg(void) 
{
    return (uint8)((TimerPin_DR & TimerPin_MASK) >> TimerPin_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(TimerPin_INTSTAT) 

    /*******************************************************************************
    * Function Name: TimerPin_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 TimerPin_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(TimerPin_INTSTAT & TimerPin_MASK);
		TimerPin_INTSTAT = maskedStatus;
        return maskedStatus >> TimerPin_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
