/*******************************************************************************
* File Name: comm_RS485_UART_PM.c
* Version 2.0
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "comm_RS485_UART.h"
#include "comm_RS485_UART_PVT.h"

#if(comm_RS485_UART_SCB_MODE_I2C_INC)
    #include "comm_RS485_UART_I2C_PVT.h"
#endif /* (comm_RS485_UART_SCB_MODE_I2C_INC) */

#if(comm_RS485_UART_SCB_MODE_EZI2C_INC)
    #include "comm_RS485_UART_EZI2C_PVT.h"
#endif /* (comm_RS485_UART_SCB_MODE_EZI2C_INC) */

#if(comm_RS485_UART_SCB_MODE_SPI_INC || comm_RS485_UART_SCB_MODE_UART_INC)
    #include "comm_RS485_UART_SPI_UART_PVT.h"
#endif /* (comm_RS485_UART_SCB_MODE_SPI_INC || comm_RS485_UART_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG || \
   (comm_RS485_UART_SCB_MODE_I2C_CONST_CFG   && (!comm_RS485_UART_I2C_WAKE_ENABLE_CONST))   || \
   (comm_RS485_UART_SCB_MODE_EZI2C_CONST_CFG && (!comm_RS485_UART_EZI2C_WAKE_ENABLE_CONST)) || \
   (comm_RS485_UART_SCB_MODE_SPI_CONST_CFG   && (!comm_RS485_UART_SPI_WAKE_ENABLE_CONST))   || \
   (comm_RS485_UART_SCB_MODE_UART_CONST_CFG  && (!comm_RS485_UART_UART_WAKE_ENABLE_CONST)))

    comm_RS485_UART_BACKUP_STRUCT comm_RS485_UART_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: comm_RS485_UART_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component to enter Deep Sleep.
*  The "Enable wakeup from Sleep Mode" selection has an influence on
*  this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void comm_RS485_UART_Sleep(void)
{
#if(comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    if(comm_RS485_UART_SCB_WAKE_ENABLE_CHECK)
    {
        if(comm_RS485_UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            comm_RS485_UART_I2CSaveConfig();
        }
        else if(comm_RS485_UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            comm_RS485_UART_EzI2CSaveConfig();
        }
    #if(!comm_RS485_UART_CY_SCBIP_V1)
        else if(comm_RS485_UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            comm_RS485_UART_SpiSaveConfig();
        }
        else if(comm_RS485_UART_SCB_MODE_UART_RUNTM_CFG)
        {
            comm_RS485_UART_UartSaveConfig();
        }
    #endif /* (!comm_RS485_UART_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        comm_RS485_UART_backup.enableState = (uint8) comm_RS485_UART_GET_CTRL_ENABLED;

        if(0u != comm_RS485_UART_backup.enableState)
        {
            comm_RS485_UART_Stop();
        }
    }

#else

    #if (comm_RS485_UART_SCB_MODE_I2C_CONST_CFG && comm_RS485_UART_I2C_WAKE_ENABLE_CONST)
        comm_RS485_UART_I2CSaveConfig();

    #elif (comm_RS485_UART_SCB_MODE_EZI2C_CONST_CFG && comm_RS485_UART_EZI2C_WAKE_ENABLE_CONST)
        comm_RS485_UART_EzI2CSaveConfig();

    #elif (comm_RS485_UART_SCB_MODE_SPI_CONST_CFG && comm_RS485_UART_SPI_WAKE_ENABLE_CONST)
        comm_RS485_UART_SpiSaveConfig();

    #elif (comm_RS485_UART_SCB_MODE_UART_CONST_CFG && comm_RS485_UART_UART_WAKE_ENABLE_CONST)
        comm_RS485_UART_UartSaveConfig();

    #else

        comm_RS485_UART_backup.enableState = (uint8) comm_RS485_UART_GET_CTRL_ENABLED;

        if(0u != comm_RS485_UART_backup.enableState)
        {
            comm_RS485_UART_Stop();
        }

    #endif /* defined (comm_RS485_UART_SCB_MODE_I2C_CONST_CFG) && (comm_RS485_UART_I2C_WAKE_ENABLE_CONST) */

#endif /* (comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: comm_RS485_UART_Wakeup
********************************************************************************
*
* Summary:
*  Prepares the component for the Active mode operation after exiting
*  Deep Sleep. The "Enable wakeup from Sleep Mode" option has an influence
*  on this function implementation.
*  This function should not be called after exiting Sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void comm_RS485_UART_Wakeup(void)
{
#if(comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    if(comm_RS485_UART_SCB_WAKE_ENABLE_CHECK)
    {
        if(comm_RS485_UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            comm_RS485_UART_I2CRestoreConfig();
        }
        else if(comm_RS485_UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            comm_RS485_UART_EzI2CRestoreConfig();
        }
    #if(!comm_RS485_UART_CY_SCBIP_V1)
        else if(comm_RS485_UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            comm_RS485_UART_SpiRestoreConfig();
        }
        else if(comm_RS485_UART_SCB_MODE_UART_RUNTM_CFG)
        {
            comm_RS485_UART_UartRestoreConfig();
        }
    #endif /* (!comm_RS485_UART_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != comm_RS485_UART_backup.enableState)
        {
            comm_RS485_UART_Enable();
        }
    }

#else

    #if (comm_RS485_UART_SCB_MODE_I2C_CONST_CFG  && comm_RS485_UART_I2C_WAKE_ENABLE_CONST)
        comm_RS485_UART_I2CRestoreConfig();

    #elif (comm_RS485_UART_SCB_MODE_EZI2C_CONST_CFG && comm_RS485_UART_EZI2C_WAKE_ENABLE_CONST)
        comm_RS485_UART_EzI2CRestoreConfig();

    #elif (comm_RS485_UART_SCB_MODE_SPI_CONST_CFG && comm_RS485_UART_SPI_WAKE_ENABLE_CONST)
        comm_RS485_UART_SpiRestoreConfig();

    #elif (comm_RS485_UART_SCB_MODE_UART_CONST_CFG && comm_RS485_UART_UART_WAKE_ENABLE_CONST)
        comm_RS485_UART_UartRestoreConfig();

    #else

        if(0u != comm_RS485_UART_backup.enableState)
        {
            comm_RS485_UART_Enable();
        }

    #endif /* (comm_RS485_UART_I2C_WAKE_ENABLE_CONST) */

#endif /* (comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
