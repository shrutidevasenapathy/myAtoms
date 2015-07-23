/*******************************************************************************
* File Name: comm_RS485_UART_SPI_UART_INT.c
* Version 2.0
*
* Description:
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "comm_RS485_UART_PVT.h"
#include "comm_RS485_UART_SPI_UART_PVT.h"


/*******************************************************************************
* Function Name: comm_RS485_UART_SPI_UART_ISR
********************************************************************************
*
* Summary:
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(comm_RS485_UART_SPI_UART_ISR)
{
#if(comm_RS485_UART_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
    uint32 dataRx;
#endif /* (comm_RS485_UART_INTERNAL_RX_SW_BUFFER_CONST) */

#if(comm_RS485_UART_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (comm_RS485_UART_INTERNAL_TX_SW_BUFFER_CONST) */

    if(NULL != comm_RS485_UART_customIntrHandler)
    {
        comm_RS485_UART_customIntrHandler();
    }

    #if(comm_RS485_UART_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        comm_RS485_UART_ClearSpiExtClkInterruptSource(comm_RS485_UART_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if(comm_RS485_UART_CHECK_RX_SW_BUFFER)
    {
        if(comm_RS485_UART_CHECK_INTR_RX_MASKED(comm_RS485_UART_INTR_RX_NOT_EMPTY))
        {
            while(0u != comm_RS485_UART_GET_RX_FIFO_ENTRIES)
            {
                /* Get data from RX FIFO */
                dataRx = comm_RS485_UART_RX_FIFO_RD_REG;

                /* Move local head index */
                locHead = (comm_RS485_UART_rxBufferHead + 1u);

                /* Adjust local head index */
                if(comm_RS485_UART_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if(locHead == comm_RS485_UART_rxBufferTail)
                {
                    /* Overflow: through away new data */
                    comm_RS485_UART_rxBufferOverflow = (uint8) comm_RS485_UART_INTR_RX_OVERFLOW;
                }
                else
                {
                    /* Store received data */
                    comm_RS485_UART_PutWordInRxBuffer(locHead, dataRx);

                    /* Move head index */
                    comm_RS485_UART_rxBufferHead = locHead;
                }
            }

            comm_RS485_UART_ClearRxInterruptSource(comm_RS485_UART_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if(comm_RS485_UART_CHECK_TX_SW_BUFFER)
    {
        if(comm_RS485_UART_CHECK_INTR_TX_MASKED(comm_RS485_UART_INTR_TX_NOT_FULL))
        {
            /* Put data into TX FIFO */
            while(comm_RS485_UART_SPI_UART_FIFO_SIZE != comm_RS485_UART_GET_TX_FIFO_ENTRIES)
            {
                /* Check for room in TX software buffer */
                if(comm_RS485_UART_txBufferHead != comm_RS485_UART_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (comm_RS485_UART_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if(comm_RS485_UART_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    comm_RS485_UART_TX_FIFO_WR_REG = comm_RS485_UART_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    comm_RS485_UART_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    comm_RS485_UART_DISABLE_INTR_TX(comm_RS485_UART_INTR_TX_NOT_FULL);
                    break;
                }
            }

            comm_RS485_UART_ClearTxInterruptSource(comm_RS485_UART_INTR_TX_NOT_FULL);
        }
    }
    #endif
}


/* [] END OF FILE */
