/*******************************************************************************
* File Name: TimerPin.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_TimerPin_H) /* Pins TimerPin_H */
#define CY_PINS_TimerPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "TimerPin_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    TimerPin_Write(uint8 value) ;
void    TimerPin_SetDriveMode(uint8 mode) ;
uint8   TimerPin_ReadDataReg(void) ;
uint8   TimerPin_Read(void) ;
uint8   TimerPin_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TimerPin_DRIVE_MODE_BITS        (3)
#define TimerPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - TimerPin_DRIVE_MODE_BITS))
#define TimerPin_DRIVE_MODE_SHIFT       (0x00u)
#define TimerPin_DRIVE_MODE_MASK        (0x07u << TimerPin_DRIVE_MODE_SHIFT)

#define TimerPin_DM_ALG_HIZ         (0x00u << TimerPin_DRIVE_MODE_SHIFT)
#define TimerPin_DM_DIG_HIZ         (0x01u << TimerPin_DRIVE_MODE_SHIFT)
#define TimerPin_DM_RES_UP          (0x02u << TimerPin_DRIVE_MODE_SHIFT)
#define TimerPin_DM_RES_DWN         (0x03u << TimerPin_DRIVE_MODE_SHIFT)
#define TimerPin_DM_OD_LO           (0x04u << TimerPin_DRIVE_MODE_SHIFT)
#define TimerPin_DM_OD_HI           (0x05u << TimerPin_DRIVE_MODE_SHIFT)
#define TimerPin_DM_STRONG          (0x06u << TimerPin_DRIVE_MODE_SHIFT)
#define TimerPin_DM_RES_UPDWN       (0x07u << TimerPin_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define TimerPin_MASK               TimerPin__MASK
#define TimerPin_SHIFT              TimerPin__SHIFT
#define TimerPin_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TimerPin_PS                     (* (reg32 *) TimerPin__PS)
/* Port Configuration */
#define TimerPin_PC                     (* (reg32 *) TimerPin__PC)
/* Data Register */
#define TimerPin_DR                     (* (reg32 *) TimerPin__DR)
/* Input Buffer Disable Override */
#define TimerPin_INP_DIS                (* (reg32 *) TimerPin__PC2)


#if defined(TimerPin__INTSTAT)  /* Interrupt Registers */

    #define TimerPin_INTSTAT                (* (reg32 *) TimerPin__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins TimerPin_H */


/* [] END OF FILE */
