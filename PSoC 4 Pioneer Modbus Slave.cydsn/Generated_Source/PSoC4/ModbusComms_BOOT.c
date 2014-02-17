/*******************************************************************************
* File Name: ModbusComms_BOOT.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the bootloader
*  communication support in SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ModbusComms.h"

#if(ModbusComms_SCB_MODE_I2C_INC)
    #include "ModbusComms_I2C.h"
#endif /* (ModbusComms_SCB_MODE_I2C_INC) */

#if(ModbusComms_SCB_MODE_EZI2C_INC)
    #include "ModbusComms_EZI2C.h"
#endif /* (ModbusComms_SCB_MODE_EZI2C_INC) */

#if(ModbusComms_SCB_MODE_SPI_INC || ModbusComms_SCB_MODE_UART_INC)
    #include "ModbusComms_SPI_UART.h"
#endif /* (ModbusComms_SCB_MODE_SPI_INC || ModbusComms_SCB_MODE_UART_INC) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusComms) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/*******************************************************************************
* Function Name: ModbusComms_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls Start function fucntion of the bootloader communication component for
*  selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusComms_CyBtldrCommStart(void)
{
    #if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
        if(ModbusComms_SCB_MODE_I2C_RUNTM_CFG)
        {
            ModbusComms_I2CCyBtldrCommStart();
        }
        else if(ModbusComms_SCB_MODE_SPI_RUNTM_CFG)
        {
            ModbusComms_SpiCyBtldrCommStart();
        }
        else if(ModbusComms_SCB_MODE_UART_RUNTM_CFG)
        {
            ModbusComms_UartCyBtldrCommStart();
        }
        else if(ModbusComms_SCB_MODE_EZI2C_RUNTM_CFG)
        {
             ModbusComms_EzI2CCyBtldrCommStart();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(ModbusComms_SCB_MODE_I2C_CONST_CFG)
        ModbusComms_I2CCyBtldrCommStart();

    #elif(ModbusComms_SCB_MODE_SPI_CONST_CFG)
        ModbusComms_SpiCyBtldrCommStart();

    #elif(ModbusComms_SCB_MODE_UART_CONST_CFG)
        ModbusComms_UartCyBtldrCommStart();

    #elif(ModbusComms_SCB_MODE_EZI2C_CONST_CFG)
        ModbusComms_EzI2CCyBtldrCommStart();

    #else
        /* Do nothing */

    #endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusComms_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls Stop function fucntion of the bootloader communication component for
*  selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusComms_CyBtldrCommStop(void)
{
    #if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
        if(ModbusComms_SCB_MODE_I2C_RUNTM_CFG)
        {
            ModbusComms_I2CCyBtldrCommStop();
        }
        else if(ModbusComms_SCB_MODE_SPI_RUNTM_CFG)
        {
            ModbusComms_SpiCyBtldrCommStop();
        }
        else if(ModbusComms_SCB_MODE_UART_RUNTM_CFG)
        {
            ModbusComms_UartCyBtldrCommStop();
        }
        else if(ModbusComms_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            ModbusComms_EzI2CCyBtldrCommStop();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(ModbusComms_SCB_MODE_I2C_CONST_CFG)
        ModbusComms_I2CCyBtldrCommStop();

    #elif(ModbusComms_SCB_MODE_SPI_CONST_CFG)
        ModbusComms_SpiCyBtldrCommStop();

    #elif(ModbusComms_SCB_MODE_UART_CONST_CFG)
        ModbusComms_UartCyBtldrCommStop();

    #elif(ModbusComms_SCB_MODE_EZI2C_CONST_CFG)
        ModbusComms_EzI2CCyBtldrCommStop();

    #else
        /* Do nothing */

    #endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusComms_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls reset function fucntion of the bootloader communication component for
*  selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ModbusComms_CyBtldrCommReset(void)
{
    #if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
        if(ModbusComms_SCB_MODE_I2C_RUNTM_CFG)
        {
            ModbusComms_I2CCyBtldrCommReset();
        }
        else if(ModbusComms_SCB_MODE_SPI_RUNTM_CFG)
        {
            ModbusComms_SpiCyBtldrCommReset();
        }
        else if(ModbusComms_SCB_MODE_UART_RUNTM_CFG)
        {
            ModbusComms_UartCyBtldrCommReset();
        }
        else if(ModbusComms_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            ModbusComms_EzI2CCyBtldrCommReset();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(ModbusComms_SCB_MODE_I2C_CONST_CFG)
        ModbusComms_I2CCyBtldrCommReset();

    #elif(ModbusComms_SCB_MODE_SPI_CONST_CFG)
        ModbusComms_SpiCyBtldrCommReset();

    #elif(ModbusComms_SCB_MODE_UART_CONST_CFG)
        ModbusComms_UartCyBtldrCommReset();

    #elif(ModbusComms_SCB_MODE_EZI2C_CONST_CFG)
        ModbusComms_EzI2CCyBtldrCommReset();

    #else
        /* Do nothing */

    #endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusComms_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls read fucntion of the bootloader communication component for selected
*  mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus ModbusComms_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
        if(ModbusComms_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = ModbusComms_I2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(ModbusComms_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = ModbusComms_SpiCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(ModbusComms_SCB_MODE_UART_RUNTM_CFG)
        {
            status = ModbusComms_UartCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(ModbusComms_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = ModbusComms_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }

    #elif(ModbusComms_SCB_MODE_I2C_CONST_CFG)
        status = ModbusComms_I2CCyBtldrCommRead(pData, size, count, timeOut);

    #elif(ModbusComms_SCB_MODE_SPI_CONST_CFG)
        status = ModbusComms_SpiCyBtldrCommRead(pData, size, count, timeOut);

    #elif(ModbusComms_SCB_MODE_UART_CONST_CFG)
        status = ModbusComms_UartCyBtldrCommRead(pData, size, count, timeOut);

    #elif(ModbusComms_SCB_MODE_EZI2C_CONST_CFG)
        status = ModbusComms_EzI2CCyBtldrCommRead(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}


/*******************************************************************************
* Function Name: ModbusComms_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls write fucntion of the bootloader communication component for selected
*  mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus ModbusComms_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG)
        if(ModbusComms_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = ModbusComms_I2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(ModbusComms_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = ModbusComms_SpiCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(ModbusComms_SCB_MODE_UART_RUNTM_CFG)
        {
            status = ModbusComms_UartCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(ModbusComms_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = ModbusComms_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }
    #elif(ModbusComms_SCB_MODE_I2C_CONST_CFG)
        status = ModbusComms_I2CCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(ModbusComms_SCB_MODE_SPI_CONST_CFG)
        status = ModbusComms_SpiCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(ModbusComms_SCB_MODE_UART_CONST_CFG)
        status = ModbusComms_UartCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(ModbusComms_SCB_MODE_EZI2C_CONST_CFG)
        status = ModbusComms_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (ModbusComms_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusComms) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */


/* [] END OF FILE */
