/*******************************************************************************
* File Name: comm_RS485_UART_SPI_UART_PVT.h
* Version 2.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_comm_RS485_UART_H)
#define CY_SCB_SPI_UART_PVT_comm_RS485_UART_H

#include "comm_RS485_UART_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if(comm_RS485_UART_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  comm_RS485_UART_rxBufferHead;
    extern volatile uint32  comm_RS485_UART_rxBufferTail;
    extern volatile uint8   comm_RS485_UART_rxBufferOverflow;
#endif /* (comm_RS485_UART_INTERNAL_RX_SW_BUFFER_CONST) */

#if(comm_RS485_UART_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  comm_RS485_UART_txBufferHead;
    extern volatile uint32  comm_RS485_UART_txBufferTail;
#endif /* (comm_RS485_UART_INTERNAL_TX_SW_BUFFER_CONST) */

#if(comm_RS485_UART_INTERNAL_RX_SW_BUFFER)
    extern volatile uint16 comm_RS485_UART_rxBufferInternal[comm_RS485_UART_RX_BUFFER_SIZE];
#endif /* (comm_RS485_UART_INTERNAL_RX_SW_BUFFER) */

#if(comm_RS485_UART_INTERNAL_TX_SW_BUFFER)
    extern volatile uint16 comm_RS485_UART_txBufferInternal[comm_RS485_UART_TX_BUFFER_SIZE];
#endif /* (comm_RS485_UART_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(comm_RS485_UART_SCB_MODE_SPI_CONST_CFG)
    void comm_RS485_UART_SpiInit(void);
#endif /* (comm_RS485_UART_SCB_MODE_SPI_CONST_CFG) */

#if(comm_RS485_UART_SPI_WAKE_ENABLE_CONST)
    void comm_RS485_UART_SpiSaveConfig(void);
    void comm_RS485_UART_SpiRestoreConfig(void);
#endif /* (comm_RS485_UART_SPI_WAKE_ENABLE_CONST) */

#if(comm_RS485_UART_SCB_MODE_UART_CONST_CFG)
    void comm_RS485_UART_UartInit(void);
#endif /* (comm_RS485_UART_SCB_MODE_UART_CONST_CFG) */

#if(comm_RS485_UART_UART_WAKE_ENABLE_CONST)
    void comm_RS485_UART_UartSaveConfig(void);
    void comm_RS485_UART_UartRestoreConfig(void);
    #define comm_RS485_UART_UartStop() \
        do{                             \
            comm_RS485_UART_UART_RX_CTRL_REG &= ~comm_RS485_UART_UART_RX_CTRL_SKIP_START; \
        }while(0)
#else
        #define comm_RS485_UART_UartStop() do{ /* Does nothing */ }while(0)

#endif /* (comm_RS485_UART_UART_WAKE_ENABLE_CONST) */

/* Interrupt processing */
#define comm_RS485_UART_SpiUartEnableIntRx(intSourceMask)  comm_RS485_UART_SetRxInterruptMode(intSourceMask)
#define comm_RS485_UART_SpiUartEnableIntTx(intSourceMask)  comm_RS485_UART_SetTxInterruptMode(intSourceMask)
uint32  comm_RS485_UART_SpiUartDisableIntRx(void);
uint32  comm_RS485_UART_SpiUartDisableIntTx(void);


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in comm_RS485_UART_SetPins() */
#define comm_RS485_UART_UART_RX_PIN_ENABLE    (comm_RS485_UART_UART_RX)
#define comm_RS485_UART_UART_TX_PIN_ENABLE    (comm_RS485_UART_UART_TX)

/* UART RTS and CTS position to be used in  comm_RS485_UART_SetPins() */
#define comm_RS485_UART_UART_RTS_PIN_ENABLE    (0x10u)
#define comm_RS485_UART_UART_CTS_PIN_ENABLE    (0x20u)

#endif /* (CY_SCB_SPI_UART_PVT_comm_RS485_UART_H) */


/* [] END OF FILE */
