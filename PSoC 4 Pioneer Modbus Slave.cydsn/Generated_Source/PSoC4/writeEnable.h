/*******************************************************************************
* File Name: writeEnable.h  
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

#if !defined(CY_PINS_writeEnable_H) /* Pins writeEnable_H */
#define CY_PINS_writeEnable_H

#include "cytypes.h"
#include "cyfitter.h"
#include "writeEnable_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    writeEnable_Write(uint8 value) ;
void    writeEnable_SetDriveMode(uint8 mode) ;
uint8   writeEnable_ReadDataReg(void) ;
uint8   writeEnable_Read(void) ;
uint8   writeEnable_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define writeEnable_DRIVE_MODE_BITS        (3)
#define writeEnable_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - writeEnable_DRIVE_MODE_BITS))
#define writeEnable_DRIVE_MODE_SHIFT       (0x00u)
#define writeEnable_DRIVE_MODE_MASK        (0x07u << writeEnable_DRIVE_MODE_SHIFT)

#define writeEnable_DM_ALG_HIZ         (0x00u << writeEnable_DRIVE_MODE_SHIFT)
#define writeEnable_DM_DIG_HIZ         (0x01u << writeEnable_DRIVE_MODE_SHIFT)
#define writeEnable_DM_RES_UP          (0x02u << writeEnable_DRIVE_MODE_SHIFT)
#define writeEnable_DM_RES_DWN         (0x03u << writeEnable_DRIVE_MODE_SHIFT)
#define writeEnable_DM_OD_LO           (0x04u << writeEnable_DRIVE_MODE_SHIFT)
#define writeEnable_DM_OD_HI           (0x05u << writeEnable_DRIVE_MODE_SHIFT)
#define writeEnable_DM_STRONG          (0x06u << writeEnable_DRIVE_MODE_SHIFT)
#define writeEnable_DM_RES_UPDWN       (0x07u << writeEnable_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define writeEnable_MASK               writeEnable__MASK
#define writeEnable_SHIFT              writeEnable__SHIFT
#define writeEnable_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define writeEnable_PS                     (* (reg32 *) writeEnable__PS)
/* Port Configuration */
#define writeEnable_PC                     (* (reg32 *) writeEnable__PC)
/* Data Register */
#define writeEnable_DR                     (* (reg32 *) writeEnable__DR)
/* Input Buffer Disable Override */
#define writeEnable_INP_DIS                (* (reg32 *) writeEnable__PC2)


#if defined(writeEnable__INTSTAT)  /* Interrupt Registers */

    #define writeEnable_INTSTAT                (* (reg32 *) writeEnable__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins writeEnable_H */


/* [] END OF FILE */
