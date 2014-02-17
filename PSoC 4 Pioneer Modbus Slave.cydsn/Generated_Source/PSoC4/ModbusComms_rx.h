/*******************************************************************************
* File Name: ModbusComms_rx.h  
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

#if !defined(CY_PINS_ModbusComms_rx_H) /* Pins ModbusComms_rx_H */
#define CY_PINS_ModbusComms_rx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ModbusComms_rx_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ModbusComms_rx_Write(uint8 value) ;
void    ModbusComms_rx_SetDriveMode(uint8 mode) ;
uint8   ModbusComms_rx_ReadDataReg(void) ;
uint8   ModbusComms_rx_Read(void) ;
uint8   ModbusComms_rx_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ModbusComms_rx_DRIVE_MODE_BITS        (3)
#define ModbusComms_rx_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ModbusComms_rx_DRIVE_MODE_BITS))
#define ModbusComms_rx_DRIVE_MODE_SHIFT       (0x00u)
#define ModbusComms_rx_DRIVE_MODE_MASK        (0x07u << ModbusComms_rx_DRIVE_MODE_SHIFT)

#define ModbusComms_rx_DM_ALG_HIZ         (0x00u << ModbusComms_rx_DRIVE_MODE_SHIFT)
#define ModbusComms_rx_DM_DIG_HIZ         (0x01u << ModbusComms_rx_DRIVE_MODE_SHIFT)
#define ModbusComms_rx_DM_RES_UP          (0x02u << ModbusComms_rx_DRIVE_MODE_SHIFT)
#define ModbusComms_rx_DM_RES_DWN         (0x03u << ModbusComms_rx_DRIVE_MODE_SHIFT)
#define ModbusComms_rx_DM_OD_LO           (0x04u << ModbusComms_rx_DRIVE_MODE_SHIFT)
#define ModbusComms_rx_DM_OD_HI           (0x05u << ModbusComms_rx_DRIVE_MODE_SHIFT)
#define ModbusComms_rx_DM_STRONG          (0x06u << ModbusComms_rx_DRIVE_MODE_SHIFT)
#define ModbusComms_rx_DM_RES_UPDWN       (0x07u << ModbusComms_rx_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define ModbusComms_rx_MASK               ModbusComms_rx__MASK
#define ModbusComms_rx_SHIFT              ModbusComms_rx__SHIFT
#define ModbusComms_rx_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ModbusComms_rx_PS                     (* (reg32 *) ModbusComms_rx__PS)
/* Port Configuration */
#define ModbusComms_rx_PC                     (* (reg32 *) ModbusComms_rx__PC)
/* Data Register */
#define ModbusComms_rx_DR                     (* (reg32 *) ModbusComms_rx__DR)
/* Input Buffer Disable Override */
#define ModbusComms_rx_INP_DIS                (* (reg32 *) ModbusComms_rx__PC2)


#if defined(ModbusComms_rx__INTSTAT)  /* Interrupt Registers */

    #define ModbusComms_rx_INTSTAT                (* (reg32 *) ModbusComms_rx__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins ModbusComms_rx_H */


/* [] END OF FILE */
