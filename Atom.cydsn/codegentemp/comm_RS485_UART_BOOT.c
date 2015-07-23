/*******************************************************************************
* File Name: comm_RS485_UART_BOOT.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the bootloader
*  communication support in the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "comm_RS485_UART_BOOT.h"


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (comm_RS485_UART_BTLDR_COMM_MODE_ENABLED)

/*******************************************************************************
* Function Name: comm_RS485_UART_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStart function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void comm_RS485_UART_CyBtldrCommStart(void)
{
    #if(comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(comm_RS485_UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            comm_RS485_UART_I2CCyBtldrCommStart();
        }
        else if(comm_RS485_UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            comm_RS485_UART_SpiCyBtldrCommStart();
        }
        else if(comm_RS485_UART_SCB_MODE_UART_RUNTM_CFG)
        {
            comm_RS485_UART_UartCyBtldrCommStart();
        }
        else if(comm_RS485_UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
             comm_RS485_UART_EzI2CCyBtldrCommStart();
        }
        else
        {
            /* Unknown mode */
        }
    #elif(comm_RS485_UART_SCB_MODE_I2C_CONST_CFG)
        comm_RS485_UART_I2CCyBtldrCommStart();

    #elif(comm_RS485_UART_SCB_MODE_SPI_CONST_CFG)
        comm_RS485_UART_SpiCyBtldrCommStart();

    #elif(comm_RS485_UART_SCB_MODE_UART_CONST_CFG)
        comm_RS485_UART_UartCyBtldrCommStart();

    #elif(comm_RS485_UART_SCB_MODE_EZI2C_CONST_CFG)
        comm_RS485_UART_EzI2CCyBtldrCommStart();

    #else
        /* Unknown mode */

    #endif /* (comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: comm_RS485_UART_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStop function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void comm_RS485_UART_CyBtldrCommStop(void)
{
    #if(comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(comm_RS485_UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            comm_RS485_UART_I2CCyBtldrCommStop();
        }
        else if(comm_RS485_UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            comm_RS485_UART_SpiCyBtldrCommStop();
        }
        else if(comm_RS485_UART_SCB_MODE_UART_RUNTM_CFG)
        {
            comm_RS485_UART_UartCyBtldrCommStop();
        }
        else if(comm_RS485_UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            comm_RS485_UART_EzI2CCyBtldrCommStop();
        }
        else
        {
            /* Unknown mode */
        }
    #elif(comm_RS485_UART_SCB_MODE_I2C_CONST_CFG)
        comm_RS485_UART_I2CCyBtldrCommStop();

    #elif(comm_RS485_UART_SCB_MODE_SPI_CONST_CFG)
        comm_RS485_UART_SpiCyBtldrCommStop();

    #elif(comm_RS485_UART_SCB_MODE_UART_CONST_CFG)
        comm_RS485_UART_UartCyBtldrCommStop();

    #elif(comm_RS485_UART_SCB_MODE_EZI2C_CONST_CFG)
        comm_RS485_UART_EzI2CCyBtldrCommStop();

    #else
        /* Unknown mode */

    #endif /* (comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: comm_RS485_UART_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommReset function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void comm_RS485_UART_CyBtldrCommReset(void)
{
    #if(comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(comm_RS485_UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            comm_RS485_UART_I2CCyBtldrCommReset();
        }
        else if(comm_RS485_UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            comm_RS485_UART_SpiCyBtldrCommReset();
        }
        else if(comm_RS485_UART_SCB_MODE_UART_RUNTM_CFG)
        {
            comm_RS485_UART_UartCyBtldrCommReset();
        }
        else if(comm_RS485_UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            comm_RS485_UART_EzI2CCyBtldrCommReset();
        }
        else
        {
            /* Unknown mode */
        }
    #elif(comm_RS485_UART_SCB_MODE_I2C_CONST_CFG)
        comm_RS485_UART_I2CCyBtldrCommReset();

    #elif(comm_RS485_UART_SCB_MODE_SPI_CONST_CFG)
        comm_RS485_UART_SpiCyBtldrCommReset();

    #elif(comm_RS485_UART_SCB_MODE_UART_CONST_CFG)
        comm_RS485_UART_UartCyBtldrCommReset();

    #elif(comm_RS485_UART_SCB_MODE_EZI2C_CONST_CFG)
        comm_RS485_UART_EzI2CCyBtldrCommReset();

    #else
        /* Unknown mode */

    #endif /* (comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: comm_RS485_UART_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommRead function of the bootloader communication
*  component for the selected mode.
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
cystatus comm_RS485_UART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(comm_RS485_UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = comm_RS485_UART_I2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(comm_RS485_UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = comm_RS485_UART_SpiCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(comm_RS485_UART_SCB_MODE_UART_RUNTM_CFG)
        {
            status = comm_RS485_UART_UartCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(comm_RS485_UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = comm_RS485_UART_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }

    #elif(comm_RS485_UART_SCB_MODE_I2C_CONST_CFG)
        status = comm_RS485_UART_I2CCyBtldrCommRead(pData, size, count, timeOut);

    #elif(comm_RS485_UART_SCB_MODE_SPI_CONST_CFG)
        status = comm_RS485_UART_SpiCyBtldrCommRead(pData, size, count, timeOut);

    #elif(comm_RS485_UART_SCB_MODE_UART_CONST_CFG)
        status = comm_RS485_UART_UartCyBtldrCommRead(pData, size, count, timeOut);

    #elif(comm_RS485_UART_SCB_MODE_EZI2C_CONST_CFG)
        status = comm_RS485_UART_EzI2CCyBtldrCommRead(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}


/*******************************************************************************
* Function Name: comm_RS485_UART_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommWrite  function of the bootloader communication
*  component for the selected mode.
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
cystatus comm_RS485_UART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG)
        if(comm_RS485_UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = comm_RS485_UART_I2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(comm_RS485_UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = comm_RS485_UART_SpiCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(comm_RS485_UART_SCB_MODE_UART_RUNTM_CFG)
        {
            status = comm_RS485_UART_UartCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(comm_RS485_UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = comm_RS485_UART_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode */
        }
    #elif(comm_RS485_UART_SCB_MODE_I2C_CONST_CFG)
        status = comm_RS485_UART_I2CCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(comm_RS485_UART_SCB_MODE_SPI_CONST_CFG)
        status = comm_RS485_UART_SpiCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(comm_RS485_UART_SCB_MODE_UART_CONST_CFG)
        status = comm_RS485_UART_UartCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(comm_RS485_UART_SCB_MODE_EZI2C_CONST_CFG)
        status = comm_RS485_UART_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode */

    #endif /* (comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (comm_RS485_UART_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */
