/*******************************************************************************
* File Name: ModbusUART_rx.h  
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

#if !defined(CY_PINS_ModbusUART_rx_H) /* Pins ModbusUART_rx_H */
#define CY_PINS_ModbusUART_rx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ModbusUART_rx_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ModbusUART_rx_Write(uint8 value) ;
void    ModbusUART_rx_SetDriveMode(uint8 mode) ;
uint8   ModbusUART_rx_ReadDataReg(void) ;
uint8   ModbusUART_rx_Read(void) ;
uint8   ModbusUART_rx_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ModbusUART_rx_DRIVE_MODE_BITS        (3)
#define ModbusUART_rx_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ModbusUART_rx_DRIVE_MODE_BITS))
#define ModbusUART_rx_DRIVE_MODE_SHIFT       (0x00u)
#define ModbusUART_rx_DRIVE_MODE_MASK        (0x07u << ModbusUART_rx_DRIVE_MODE_SHIFT)

#define ModbusUART_rx_DM_ALG_HIZ         (0x00u << ModbusUART_rx_DRIVE_MODE_SHIFT)
#define ModbusUART_rx_DM_DIG_HIZ         (0x01u << ModbusUART_rx_DRIVE_MODE_SHIFT)
#define ModbusUART_rx_DM_RES_UP          (0x02u << ModbusUART_rx_DRIVE_MODE_SHIFT)
#define ModbusUART_rx_DM_RES_DWN         (0x03u << ModbusUART_rx_DRIVE_MODE_SHIFT)
#define ModbusUART_rx_DM_OD_LO           (0x04u << ModbusUART_rx_DRIVE_MODE_SHIFT)
#define ModbusUART_rx_DM_OD_HI           (0x05u << ModbusUART_rx_DRIVE_MODE_SHIFT)
#define ModbusUART_rx_DM_STRONG          (0x06u << ModbusUART_rx_DRIVE_MODE_SHIFT)
#define ModbusUART_rx_DM_RES_UPDWN       (0x07u << ModbusUART_rx_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define ModbusUART_rx_MASK               ModbusUART_rx__MASK
#define ModbusUART_rx_SHIFT              ModbusUART_rx__SHIFT
#define ModbusUART_rx_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ModbusUART_rx_PS                     (* (reg32 *) ModbusUART_rx__PS)
/* Port Configuration */
#define ModbusUART_rx_PC                     (* (reg32 *) ModbusUART_rx__PC)
/* Data Register */
#define ModbusUART_rx_DR                     (* (reg32 *) ModbusUART_rx__DR)
/* Input Buffer Disable Override */
#define ModbusUART_rx_INP_DIS                (* (reg32 *) ModbusUART_rx__PC2)


#if defined(ModbusUART_rx__INTSTAT)  /* Interrupt Registers */

    #define ModbusUART_rx_INTSTAT                (* (reg32 *) ModbusUART_rx__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins ModbusUART_rx_H */


/* [] END OF FILE */
