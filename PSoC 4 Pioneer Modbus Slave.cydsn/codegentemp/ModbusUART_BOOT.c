/*******************************************************************************
* File Name: ModbusUART_BOOT.c
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

#include "ModbusUART.h"

#if(ModbusUART_SCB_MODE_I2C_INC)
    #include "ModbusUART_I2C.h"
#endif /* (ModbusUART_SCB_MODE_I2C_INC) */

#if(ModbusUART_SCB_MODE_EZI2C_INC)
    #include "ModbusUART_EZI2C.h"
#endif /* (ModbusUART_SCB_MODE_EZI2C_INC) */

#if(ModbusUART_SCB_MODE_SPI_INC || ModbusUART_SCB_MODE_UART_INC)
    #include "ModbusUART_SPI_UART.h"
#endif /* (ModbusUART_SCB_MODE_SPI_INC || ModbusUART_SCB_MODE_UART_INC) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusUART) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/*******************************************************************************
* Function Name: ModbusUART_CyBtldrCommStart
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
void ModbusUART_CyBtldrCommStart(void)
{
    #if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
        {
            ModbusUART_I2CCyBtldrCommStart();
        }
        else if(ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
        {
            ModbusUART_SpiCyBtldrCommStart();
        }
        else if(ModbusUART_SCB_MODE_UART_RUNTM_CFG)
        {
            ModbusUART_UartCyBtldrCommStart();
        }
        else if(ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
             ModbusUART_EzI2CCyBtldrCommStart();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(ModbusUART_SCB_MODE_I2C_CONST_CFG)
        ModbusUART_I2CCyBtldrCommStart();

    #elif(ModbusUART_SCB_MODE_SPI_CONST_CFG)
        ModbusUART_SpiCyBtldrCommStart();

    #elif(ModbusUART_SCB_MODE_UART_CONST_CFG)
        ModbusUART_UartCyBtldrCommStart();

    #elif(ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
        ModbusUART_EzI2CCyBtldrCommStart();

    #else
        /* Do nothing */

    #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_CyBtldrCommStop
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
void ModbusUART_CyBtldrCommStop(void)
{
    #if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
        {
            ModbusUART_I2CCyBtldrCommStop();
        }
        else if(ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
        {
            ModbusUART_SpiCyBtldrCommStop();
        }
        else if(ModbusUART_SCB_MODE_UART_RUNTM_CFG)
        {
            ModbusUART_UartCyBtldrCommStop();
        }
        else if(ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            ModbusUART_EzI2CCyBtldrCommStop();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(ModbusUART_SCB_MODE_I2C_CONST_CFG)
        ModbusUART_I2CCyBtldrCommStop();

    #elif(ModbusUART_SCB_MODE_SPI_CONST_CFG)
        ModbusUART_SpiCyBtldrCommStop();

    #elif(ModbusUART_SCB_MODE_UART_CONST_CFG)
        ModbusUART_UartCyBtldrCommStop();

    #elif(ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
        ModbusUART_EzI2CCyBtldrCommStop();

    #else
        /* Do nothing */

    #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_CyBtldrCommReset
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
void ModbusUART_CyBtldrCommReset(void)
{
    #if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
        {
            ModbusUART_I2CCyBtldrCommReset();
        }
        else if(ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
        {
            ModbusUART_SpiCyBtldrCommReset();
        }
        else if(ModbusUART_SCB_MODE_UART_RUNTM_CFG)
        {
            ModbusUART_UartCyBtldrCommReset();
        }
        else if(ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            ModbusUART_EzI2CCyBtldrCommReset();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(ModbusUART_SCB_MODE_I2C_CONST_CFG)
        ModbusUART_I2CCyBtldrCommReset();

    #elif(ModbusUART_SCB_MODE_SPI_CONST_CFG)
        ModbusUART_SpiCyBtldrCommReset();

    #elif(ModbusUART_SCB_MODE_UART_CONST_CFG)
        ModbusUART_UartCyBtldrCommReset();

    #elif(ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
        ModbusUART_EzI2CCyBtldrCommReset();

    #else
        /* Do nothing */

    #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_CyBtldrCommRead
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
cystatus ModbusUART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = ModbusUART_I2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = ModbusUART_SpiCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(ModbusUART_SCB_MODE_UART_RUNTM_CFG)
        {
            status = ModbusUART_UartCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = ModbusUART_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }

    #elif(ModbusUART_SCB_MODE_I2C_CONST_CFG)
        status = ModbusUART_I2CCyBtldrCommRead(pData, size, count, timeOut);

    #elif(ModbusUART_SCB_MODE_SPI_CONST_CFG)
        status = ModbusUART_SpiCyBtldrCommRead(pData, size, count, timeOut);

    #elif(ModbusUART_SCB_MODE_UART_CONST_CFG)
        status = ModbusUART_UartCyBtldrCommRead(pData, size, count, timeOut);

    #elif(ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
        status = ModbusUART_EzI2CCyBtldrCommRead(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}


/*******************************************************************************
* Function Name: ModbusUART_CyBtldrCommWrite
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
cystatus ModbusUART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = ModbusUART_I2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = ModbusUART_SpiCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(ModbusUART_SCB_MODE_UART_RUNTM_CFG)
        {
            status = ModbusUART_UartCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = ModbusUART_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }
    #elif(ModbusUART_SCB_MODE_I2C_CONST_CFG)
        status = ModbusUART_I2CCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(ModbusUART_SCB_MODE_SPI_CONST_CFG)
        status = ModbusUART_SpiCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(ModbusUART_SCB_MODE_UART_CONST_CFG)
        status = ModbusUART_UartCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
        status = ModbusUART_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusUART) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */


/* [] END OF FILE */
