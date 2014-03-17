/*******************************************************************************
* File Name: lineDriver.h  
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

#if !defined(CY_PINS_lineDriver_H) /* Pins lineDriver_H */
#define CY_PINS_lineDriver_H

#include "cytypes.h"
#include "cyfitter.h"
#include "lineDriver_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    lineDriver_Write(uint8 value) ;
void    lineDriver_SetDriveMode(uint8 mode) ;
uint8   lineDriver_ReadDataReg(void) ;
uint8   lineDriver_Read(void) ;
uint8   lineDriver_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define lineDriver_DRIVE_MODE_BITS        (3)
#define lineDriver_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - lineDriver_DRIVE_MODE_BITS))
#define lineDriver_DRIVE_MODE_SHIFT       (0x00u)
#define lineDriver_DRIVE_MODE_MASK        (0x07u << lineDriver_DRIVE_MODE_SHIFT)

#define lineDriver_DM_ALG_HIZ         (0x00u << lineDriver_DRIVE_MODE_SHIFT)
#define lineDriver_DM_DIG_HIZ         (0x01u << lineDriver_DRIVE_MODE_SHIFT)
#define lineDriver_DM_RES_UP          (0x02u << lineDriver_DRIVE_MODE_SHIFT)
#define lineDriver_DM_RES_DWN         (0x03u << lineDriver_DRIVE_MODE_SHIFT)
#define lineDriver_DM_OD_LO           (0x04u << lineDriver_DRIVE_MODE_SHIFT)
#define lineDriver_DM_OD_HI           (0x05u << lineDriver_DRIVE_MODE_SHIFT)
#define lineDriver_DM_STRONG          (0x06u << lineDriver_DRIVE_MODE_SHIFT)
#define lineDriver_DM_RES_UPDWN       (0x07u << lineDriver_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define lineDriver_MASK               lineDriver__MASK
#define lineDriver_SHIFT              lineDriver__SHIFT
#define lineDriver_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define lineDriver_PS                     (* (reg32 *) lineDriver__PS)
/* Port Configuration */
#define lineDriver_PC                     (* (reg32 *) lineDriver__PC)
/* Data Register */
#define lineDriver_DR                     (* (reg32 *) lineDriver__DR)
/* Input Buffer Disable Override */
#define lineDriver_INP_DIS                (* (reg32 *) lineDriver__PC2)


#if defined(lineDriver__INTSTAT)  /* Interrupt Registers */

    #define lineDriver_INTSTAT                (* (reg32 *) lineDriver__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins lineDriver_H */


/* [] END OF FILE */
