/*******************************************************************************
* File Name: .h
* Version 2.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_comm_RS485_UART_H)
#define CY_SCB_PVT_comm_RS485_UART_H

#include "comm_RS485_UART.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define comm_RS485_UART_SetI2CExtClkInterruptMode(interruptMask) comm_RS485_UART_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define comm_RS485_UART_ClearI2CExtClkInterruptSource(interruptMask) comm_RS485_UART_CLEAR_INTR_I2C_EC(interruptMask)
#define comm_RS485_UART_GetI2CExtClkInterruptSource()                (comm_RS485_UART_INTR_I2C_EC_REG)
#define comm_RS485_UART_GetI2CExtClkInterruptMode()                  (comm_RS485_UART_INTR_I2C_EC_MASK_REG)
#define comm_RS485_UART_GetI2CExtClkInterruptSourceMasked()          (comm_RS485_UART_INTR_I2C_EC_MASKED_REG)

#if (!comm_RS485_UART_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define comm_RS485_UART_SetSpiExtClkInterruptMode(interruptMask) \
                                                                comm_RS485_UART_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define comm_RS485_UART_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                comm_RS485_UART_CLEAR_INTR_SPI_EC(interruptMask)
    #define comm_RS485_UART_GetExtSpiClkInterruptSource()                 (comm_RS485_UART_INTR_SPI_EC_REG)
    #define comm_RS485_UART_GetExtSpiClkInterruptMode()                   (comm_RS485_UART_INTR_SPI_EC_MASK_REG)
    #define comm_RS485_UART_GetExtSpiClkInterruptSourceMasked()           (comm_RS485_UART_INTR_SPI_EC_MASKED_REG)
#endif /* (!comm_RS485_UART_CY_SCBIP_V1) */

#if(comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void comm_RS485_UART_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if !defined (CY_REMOVE_comm_RS485_UART_CUSTOM_INTR_HANDLER)
    extern cyisraddress comm_RS485_UART_customIntrHandler;
#endif /* !defined (CY_REMOVE_comm_RS485_UART_CUSTOM_INTR_HANDLER) */

extern comm_RS485_UART_BACKUP_STRUCT comm_RS485_UART_backup;

#if(comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 comm_RS485_UART_scbMode;
    extern uint8 comm_RS485_UART_scbEnableWake;
    extern uint8 comm_RS485_UART_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 comm_RS485_UART_mode;
    extern uint8 comm_RS485_UART_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * comm_RS485_UART_rxBuffer;
    extern uint8   comm_RS485_UART_rxDataBits;
    extern uint32  comm_RS485_UART_rxBufferSize;

    extern volatile uint8 * comm_RS485_UART_txBuffer;
    extern uint8   comm_RS485_UART_txDataBits;
    extern uint32  comm_RS485_UART_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 comm_RS485_UART_numberOfAddr;
    extern uint8 comm_RS485_UART_subAddrSize;
#endif /* (comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define comm_RS485_UART_SCB_MODE_I2C_RUNTM_CFG     (comm_RS485_UART_SCB_MODE_I2C      == comm_RS485_UART_scbMode)
    #define comm_RS485_UART_SCB_MODE_SPI_RUNTM_CFG     (comm_RS485_UART_SCB_MODE_SPI      == comm_RS485_UART_scbMode)
    #define comm_RS485_UART_SCB_MODE_UART_RUNTM_CFG    (comm_RS485_UART_SCB_MODE_UART     == comm_RS485_UART_scbMode)
    #define comm_RS485_UART_SCB_MODE_EZI2C_RUNTM_CFG   (comm_RS485_UART_SCB_MODE_EZI2C    == comm_RS485_UART_scbMode)
    #define comm_RS485_UART_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (comm_RS485_UART_SCB_MODE_UNCONFIG == comm_RS485_UART_scbMode)

    /* Defines wakeup enable */
    #define comm_RS485_UART_SCB_WAKE_ENABLE_CHECK       (0u != comm_RS485_UART_scbEnableWake)
#endif /* (comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_SCB_PINS_NUMBER    (7u)
#else
    #define comm_RS485_UART_SCB_PINS_NUMBER    (2u)
#endif /* (!comm_RS485_UART_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_comm_RS485_UART_H) */


/* [] END OF FILE */
