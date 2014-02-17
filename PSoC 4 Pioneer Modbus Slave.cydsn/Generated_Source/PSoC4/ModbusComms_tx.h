/*******************************************************************************
* File Name: ModbusComms_tx.h  
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

#if !defined(CY_PINS_ModbusComms_tx_H) /* Pins ModbusComms_tx_H */
#define CY_PINS_ModbusComms_tx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ModbusComms_tx_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ModbusComms_tx_Write(uint8 value) ;
void    ModbusComms_tx_SetDriveMode(uint8 mode) ;
uint8   ModbusComms_tx_ReadDataReg(void) ;
uint8   ModbusComms_tx_Read(void) ;
uint8   ModbusComms_tx_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ModbusComms_tx_DRIVE_MODE_BITS        (3)
#define ModbusComms_tx_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ModbusComms_tx_DRIVE_MODE_BITS))
#define ModbusComms_tx_DRIVE_MODE_SHIFT       (0x00u)
#define ModbusComms_tx_DRIVE_MODE_MASK        (0x07u << ModbusComms_tx_DRIVE_MODE_SHIFT)

#define ModbusComms_tx_DM_ALG_HIZ         (0x00u << ModbusComms_tx_DRIVE_MODE_SHIFT)
#define ModbusComms_tx_DM_DIG_HIZ         (0x01u << ModbusComms_tx_DRIVE_MODE_SHIFT)
#define ModbusComms_tx_DM_RES_UP          (0x02u << ModbusComms_tx_DRIVE_MODE_SHIFT)
#define ModbusComms_tx_DM_RES_DWN         (0x03u << ModbusComms_tx_DRIVE_MODE_SHIFT)
#define ModbusComms_tx_DM_OD_LO           (0x04u << ModbusComms_tx_DRIVE_MODE_SHIFT)
#define ModbusComms_tx_DM_OD_HI           (0x05u << ModbusComms_tx_DRIVE_MODE_SHIFT)
#define ModbusComms_tx_DM_STRONG          (0x06u << ModbusComms_tx_DRIVE_MODE_SHIFT)
#define ModbusComms_tx_DM_RES_UPDWN       (0x07u << ModbusComms_tx_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define ModbusComms_tx_MASK               ModbusComms_tx__MASK
#define ModbusComms_tx_SHIFT              ModbusComms_tx__SHIFT
#define ModbusComms_tx_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ModbusComms_tx_PS                     (* (reg32 *) ModbusComms_tx__PS)
/* Port Configuration */
#define ModbusComms_tx_PC                     (* (reg32 *) ModbusComms_tx__PC)
/* Data Register */
#define ModbusComms_tx_DR                     (* (reg32 *) ModbusComms_tx__DR)
/* Input Buffer Disable Override */
#define ModbusComms_tx_INP_DIS                (* (reg32 *) ModbusComms_tx__PC2)


#if defined(ModbusComms_tx__INTSTAT)  /* Interrupt Registers */

    #define ModbusComms_tx_INTSTAT                (* (reg32 *) ModbusComms_tx__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins ModbusComms_tx_H */


/* [] END OF FILE */
