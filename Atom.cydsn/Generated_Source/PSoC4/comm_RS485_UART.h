/*******************************************************************************
* File Name: comm_RS485_UART.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_comm_RS485_UART_H)
#define CY_SCB_comm_RS485_UART_H

#include <cydevice_trm.h>
#include <cyfitter.h>
#include <cytypes.h>
#include <CyLib.h>

#define comm_RS485_UART_CY_SCBIP_V0    (CYIPBLOCK_m0s8scb_VERSION == 0u)
#define comm_RS485_UART_CY_SCBIP_V1    (CYIPBLOCK_m0s8scb_VERSION == 1u)
#define comm_RS485_UART_CY_SCBIP_V2    (CYIPBLOCK_m0s8scb_VERSION >= 2u)

#define comm_RS485_UART_SCB_MODE                     (4u)

/* SCB modes enum */
#define comm_RS485_UART_SCB_MODE_I2C                 (0x01u)
#define comm_RS485_UART_SCB_MODE_SPI                 (0x02u)
#define comm_RS485_UART_SCB_MODE_UART                (0x04u)
#define comm_RS485_UART_SCB_MODE_EZI2C               (0x08u)
#define comm_RS485_UART_SCB_MODE_UNCONFIG            (0xFFu)

/* Condition compilation depends on operation mode: Unconfigured implies apply to all modes */
#define comm_RS485_UART_SCB_MODE_I2C_CONST_CFG       (comm_RS485_UART_SCB_MODE_I2C       == comm_RS485_UART_SCB_MODE)
#define comm_RS485_UART_SCB_MODE_SPI_CONST_CFG       (comm_RS485_UART_SCB_MODE_SPI       == comm_RS485_UART_SCB_MODE)
#define comm_RS485_UART_SCB_MODE_UART_CONST_CFG      (comm_RS485_UART_SCB_MODE_UART      == comm_RS485_UART_SCB_MODE)
#define comm_RS485_UART_SCB_MODE_EZI2C_CONST_CFG     (comm_RS485_UART_SCB_MODE_EZI2C     == comm_RS485_UART_SCB_MODE)
#define comm_RS485_UART_SCB_MODE_UNCONFIG_CONST_CFG  (comm_RS485_UART_SCB_MODE_UNCONFIG  == comm_RS485_UART_SCB_MODE)

/* Condition compilation for includes */
#define comm_RS485_UART_SCB_MODE_I2C_INC      (0u !=(comm_RS485_UART_SCB_MODE_I2C   & comm_RS485_UART_SCB_MODE))
#define comm_RS485_UART_SCB_MODE_EZI2C_INC    (0u !=(comm_RS485_UART_SCB_MODE_EZI2C & comm_RS485_UART_SCB_MODE))
#if(!comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_SCB_MODE_SPI_INC  (0u !=(comm_RS485_UART_SCB_MODE_SPI   & comm_RS485_UART_SCB_MODE))
    #define comm_RS485_UART_SCB_MODE_UART_INC (0u !=(comm_RS485_UART_SCB_MODE_UART  & comm_RS485_UART_SCB_MODE))
#else
    #define comm_RS485_UART_SCB_MODE_SPI_INC  (0u)
    #define comm_RS485_UART_SCB_MODE_UART_INC (0u)
#endif /* (!comm_RS485_UART_CY_SCBIP_V1) */

/* Interrupts remove options */
#define comm_RS485_UART_REMOVE_SCB_IRQ             (0u)
#define comm_RS485_UART_SCB_IRQ_INTERNAL           (0u == comm_RS485_UART_REMOVE_SCB_IRQ)

#define comm_RS485_UART_REMOVE_UART_RX_WAKEUP_IRQ  (1u)
#define comm_RS485_UART_UART_RX_WAKEUP_IRQ         (0u == comm_RS485_UART_REMOVE_UART_RX_WAKEUP_IRQ)

/* SCB interrupt enum */
#define comm_RS485_UART_SCB_INTR_MODE_NONE     (0u)
#define comm_RS485_UART_SCB_INTR_MODE_INTERNAL (1u)
#define comm_RS485_UART_SCB_INTR_MODE_EXTERNAL (2u)

/* Internal clock remove option */
#define comm_RS485_UART_REMOVE_SCB_CLK     (0u)
#define comm_RS485_UART_SCB_CLK_INTERNAL   (0u == comm_RS485_UART_REMOVE_SCB_CLK)


/***************************************
*       Includes
****************************************/

#include "comm_RS485_UART_PINS.h"

#if (comm_RS485_UART_SCB_CLK_INTERNAL)
    #include "comm_RS485_UART_SCBCLK.h"
#endif /* (comm_RS485_UART_SCB_CLK_INTERNAL) */


/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint8 enableState;
} comm_RS485_UART_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* Start and Stop APIs */
void comm_RS485_UART_Init(void);
void comm_RS485_UART_Enable(void);
void comm_RS485_UART_Start(void);
void comm_RS485_UART_Stop(void);

/* Sleep and Wakeup APis */
void comm_RS485_UART_Sleep(void);
void comm_RS485_UART_Wakeup(void);

/* Custom interrupt handler */
void comm_RS485_UART_SetCustomInterruptHandler(cyisraddress func);

/* Interface to internal interrupt component */
#if (comm_RS485_UART_SCB_IRQ_INTERNAL)
    #define comm_RS485_UART_EnableInt()        CyIntEnable      (comm_RS485_UART_ISR_NUMBER)
    #define comm_RS485_UART_DisableInt()       CyIntDisable     (comm_RS485_UART_ISR_NUMBER)
    #define comm_RS485_UART_ClearPendingInt()  CyIntClearPending(comm_RS485_UART_ISR_NUMBER)
#endif /* (comm_RS485_UART_SCB_IRQ_INTERNAL) */

#if (comm_RS485_UART_UART_RX_WAKEUP_IRQ)
    #define comm_RS485_UART_RxWakeEnableInt()        CyIntEnable      (comm_RS485_UART_RX_WAKE_ISR_NUMBER)
    #define comm_RS485_UART_RxWakeDisableInt()       CyIntDisable     (comm_RS485_UART_RX_WAKE_ISR_NUMBER)
    #define comm_RS485_UART_RxWakeClearPendingInt()  CyIntClearPending(comm_RS485_UART_RX_WAKE_ISR_NUMBER)
#endif /* (comm_RS485_UART_UART_RX_WAKEUP_IRQ) */

/* Get interrupt cause */
#define comm_RS485_UART_GetInterruptCause()    (comm_RS485_UART_INTR_CAUSE_REG)

/* APIs to service INTR_RX register */
#define comm_RS485_UART_SetRxInterruptMode(interruptMask)     comm_RS485_UART_WRITE_INTR_RX_MASK(interruptMask)
#define comm_RS485_UART_ClearRxInterruptSource(interruptMask) comm_RS485_UART_CLEAR_INTR_RX(interruptMask)
#define comm_RS485_UART_SetRxInterrupt(interruptMask)         comm_RS485_UART_SET_INTR_RX(interruptMask)
#define comm_RS485_UART_GetRxInterruptSource()                (comm_RS485_UART_INTR_RX_REG)
#define comm_RS485_UART_GetRxInterruptMode()                  (comm_RS485_UART_INTR_RX_MASK_REG)
#define comm_RS485_UART_GetRxInterruptSourceMasked()          (comm_RS485_UART_INTR_RX_MASKED_REG)
void comm_RS485_UART_SetRxFifoLevel(uint32 level);

/* APIs to service INTR_TX register */
#define comm_RS485_UART_SetTxInterruptMode(interruptMask)     comm_RS485_UART_WRITE_INTR_TX_MASK(interruptMask)
#define comm_RS485_UART_ClearTxInterruptSource(interruptMask) comm_RS485_UART_CLEAR_INTR_TX(interruptMask)
#define comm_RS485_UART_SetTxInterrupt(interruptMask)         comm_RS485_UART_SET_INTR_TX(interruptMask)
#define comm_RS485_UART_GetTxInterruptSource()                (comm_RS485_UART_INTR_TX_REG)
#define comm_RS485_UART_GetTxInterruptMode()                  (comm_RS485_UART_INTR_TX_MASK_REG)
#define comm_RS485_UART_GetTxInterruptSourceMasked()          (comm_RS485_UART_INTR_TX_MASKED_REG)
void comm_RS485_UART_SetTxFifoLevel(uint32 level);

/* APIs to service INTR_MASTER register */
#define comm_RS485_UART_SetMasterInterruptMode(interruptMask)     comm_RS485_UART_WRITE_INTR_MASTER_MASK(interruptMask)
#define comm_RS485_UART_ClearMasterInterruptSource(interruptMask) comm_RS485_UART_CLEAR_INTR_MASTER(interruptMask)
#define comm_RS485_UART_SetMasterInterrupt(interruptMask)         comm_RS485_UART_SET_INTR_MASTER(interruptMask)
#define comm_RS485_UART_GetMasterInterruptSource()                (comm_RS485_UART_INTR_MASTER_REG)
#define comm_RS485_UART_GetMasterInterruptMode()                  (comm_RS485_UART_INTR_MASTER_MASK_REG)
#define comm_RS485_UART_GetMasterInterruptSourceMasked()          (comm_RS485_UART_INTR_MASTER_MASKED_REG)

/* APIs to service INTR_SLAVE register */
#define comm_RS485_UART_SetSlaveInterruptMode(interruptMask)     comm_RS485_UART_WRITE_INTR_SLAVE_MASK(interruptMask)
#define comm_RS485_UART_ClearSlaveInterruptSource(interruptMask) comm_RS485_UART_CLEAR_INTR_SLAVE(interruptMask)
#define comm_RS485_UART_SetSlaveInterrupt(interruptMask)         comm_RS485_UART_SET_INTR_SLAVE(interruptMask)
#define comm_RS485_UART_GetSlaveInterruptSource()                (comm_RS485_UART_INTR_SLAVE_REG)
#define comm_RS485_UART_GetSlaveInterruptMode()                  (comm_RS485_UART_INTR_SLAVE_MASK_REG)
#define comm_RS485_UART_GetSlaveInterruptSourceMasked()          (comm_RS485_UART_INTR_SLAVE_MASKED_REG)


/***************************************
*     Vars with External Linkage
***************************************/

extern uint8 comm_RS485_UART_initVar;


/***************************************
*              Registers
***************************************/

#define comm_RS485_UART_CTRL_REG               (*(reg32 *) comm_RS485_UART_SCB__CTRL)
#define comm_RS485_UART_CTRL_PTR               ( (reg32 *) comm_RS485_UART_SCB__CTRL)

#define comm_RS485_UART_STATUS_REG             (*(reg32 *) comm_RS485_UART_SCB__STATUS)
#define comm_RS485_UART_STATUS_PTR             ( (reg32 *) comm_RS485_UART_SCB__STATUS)

#if (!comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_SPI_CTRL_REG           (*(reg32 *) comm_RS485_UART_SCB__SPI_CTRL)
    #define comm_RS485_UART_SPI_CTRL_PTR           ( (reg32 *) comm_RS485_UART_SCB__SPI_CTRL)

    #define comm_RS485_UART_SPI_STATUS_REG         (*(reg32 *) comm_RS485_UART_SCB__SPI_STATUS)
    #define comm_RS485_UART_SPI_STATUS_PTR         ( (reg32 *) comm_RS485_UART_SCB__SPI_STATUS)

    #define comm_RS485_UART_UART_CTRL_REG          (*(reg32 *) comm_RS485_UART_SCB__UART_CTRL)
    #define comm_RS485_UART_UART_CTRL_PTR          ( (reg32 *) comm_RS485_UART_SCB__UART_CTRL)

    #define comm_RS485_UART_UART_TX_CTRL_REG       (*(reg32 *) comm_RS485_UART_SCB__UART_TX_CTRL)
    #define comm_RS485_UART_UART_TX_CTRL_PTR       ( (reg32 *) comm_RS485_UART_SCB__UART_RX_CTRL)

    #define comm_RS485_UART_UART_RX_CTRL_REG       (*(reg32 *) comm_RS485_UART_SCB__UART_RX_CTRL)
    #define comm_RS485_UART_UART_RX_CTRL_PTR       ( (reg32 *) comm_RS485_UART_SCB__UART_RX_CTRL)

    #define comm_RS485_UART_UART_RX_STATUS_REG     (*(reg32 *) comm_RS485_UART_SCB__UART_RX_STATUS)
    #define comm_RS485_UART_UART_RX_STATUS_PTR     ( (reg32 *) comm_RS485_UART_SCB__UART_RX_STATUS)
#endif /* (!comm_RS485_UART_CY_SCBIP_V1) */

#if !(comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_UART_FLOW_CTRL_REG     (*(reg32 *) comm_RS485_UART_SCB__UART_FLOW_CTRL)
    #define comm_RS485_UART_UART_FLOW_CTRL_PTR     ( (reg32 *) comm_RS485_UART_SCB__UART_FLOW_CTRL)
#endif /* !(comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1) */

#define comm_RS485_UART_I2C_CTRL_REG           (*(reg32 *) comm_RS485_UART_SCB__I2C_CTRL)
#define comm_RS485_UART_I2C_CTRL_PTR           ( (reg32 *) comm_RS485_UART_SCB__I2C_CTRL)

#define comm_RS485_UART_I2C_STATUS_REG         (*(reg32 *) comm_RS485_UART_SCB__I2C_STATUS)
#define comm_RS485_UART_I2C_STATUS_PTR         ( (reg32 *) comm_RS485_UART_SCB__I2C_STATUS)

#define comm_RS485_UART_I2C_MASTER_CMD_REG     (*(reg32 *) comm_RS485_UART_SCB__I2C_M_CMD)
#define comm_RS485_UART_I2C_MASTER_CMD_PTR     ( (reg32 *) comm_RS485_UART_SCB__I2C_M_CMD)

#define comm_RS485_UART_I2C_SLAVE_CMD_REG      (*(reg32 *) comm_RS485_UART_SCB__I2C_S_CMD)
#define comm_RS485_UART_I2C_SLAVE_CMD_PTR      ( (reg32 *) comm_RS485_UART_SCB__I2C_S_CMD)

#define comm_RS485_UART_I2C_CFG_REG            (*(reg32 *) comm_RS485_UART_SCB__I2C_CFG)
#define comm_RS485_UART_I2C_CFG_PTR            ( (reg32 *) comm_RS485_UART_SCB__I2C_CFG)

#define comm_RS485_UART_TX_CTRL_REG            (*(reg32 *) comm_RS485_UART_SCB__TX_CTRL)
#define comm_RS485_UART_TX_CTRL_PTR            ( (reg32 *) comm_RS485_UART_SCB__TX_CTRL)

#define comm_RS485_UART_TX_FIFO_CTRL_REG       (*(reg32 *) comm_RS485_UART_SCB__TX_FIFO_CTRL)
#define comm_RS485_UART_TX_FIFO_CTRL_PTR       ( (reg32 *) comm_RS485_UART_SCB__TX_FIFO_CTRL)

#define comm_RS485_UART_TX_FIFO_STATUS_REG     (*(reg32 *) comm_RS485_UART_SCB__TX_FIFO_STATUS)
#define comm_RS485_UART_TX_FIFO_STATUS_PTR     ( (reg32 *) comm_RS485_UART_SCB__TX_FIFO_STATUS)

#define comm_RS485_UART_TX_FIFO_WR_REG         (*(reg32 *) comm_RS485_UART_SCB__TX_FIFO_WR)
#define comm_RS485_UART_TX_FIFO_WR_PTR         ( (reg32 *) comm_RS485_UART_SCB__TX_FIFO_WR)

#define comm_RS485_UART_RX_CTRL_REG            (*(reg32 *) comm_RS485_UART_SCB__RX_CTRL)
#define comm_RS485_UART_RX_CTRL_PTR            ( (reg32 *) comm_RS485_UART_SCB__RX_CTRL)

#define comm_RS485_UART_RX_FIFO_CTRL_REG       (*(reg32 *) comm_RS485_UART_SCB__RX_FIFO_CTRL)
#define comm_RS485_UART_RX_FIFO_CTRL_PTR       ( (reg32 *) comm_RS485_UART_SCB__RX_FIFO_CTRL)

#define comm_RS485_UART_RX_FIFO_STATUS_REG     (*(reg32 *) comm_RS485_UART_SCB__RX_FIFO_STATUS)
#define comm_RS485_UART_RX_FIFO_STATUS_PTR     ( (reg32 *) comm_RS485_UART_SCB__RX_FIFO_STATUS)

#define comm_RS485_UART_RX_MATCH_REG           (*(reg32 *) comm_RS485_UART_SCB__RX_MATCH)
#define comm_RS485_UART_RX_MATCH_PTR           ( (reg32 *) comm_RS485_UART_SCB__RX_MATCH)

#define comm_RS485_UART_RX_FIFO_RD_REG         (*(reg32 *) comm_RS485_UART_SCB__RX_FIFO_RD)
#define comm_RS485_UART_RX_FIFO_RD_PTR         ( (reg32 *) comm_RS485_UART_SCB__RX_FIFO_RD)

#define comm_RS485_UART_RX_FIFO_RD_SILENT_REG  (*(reg32 *) comm_RS485_UART_SCB__RX_FIFO_RD_SILENT)
#define comm_RS485_UART_RX_FIFO_RD_SILENT_PTR  ( (reg32 *) comm_RS485_UART_SCB__RX_FIFO_RD_SILENT)

#define comm_RS485_UART_EZBUF_DATA00_REG       (*(reg32 *) comm_RS485_UART_SCB__EZ_DATA00)
#define comm_RS485_UART_EZBUF_DATA00_PTR       ( (reg32 *) comm_RS485_UART_SCB__EZ_DATA00)

#define comm_RS485_UART_INTR_CAUSE_REG         (*(reg32 *) comm_RS485_UART_SCB__INTR_CAUSE)
#define comm_RS485_UART_INTR_CAUSE_PTR         ( (reg32 *) comm_RS485_UART_SCB__INTR_CAUSE)

#define comm_RS485_UART_INTR_I2C_EC_REG        (*(reg32 *) comm_RS485_UART_SCB__INTR_I2C_EC)
#define comm_RS485_UART_INTR_I2C_EC_PTR        ( (reg32 *) comm_RS485_UART_SCB__INTR_I2C_EC)

#define comm_RS485_UART_INTR_I2C_EC_MASK_REG   (*(reg32 *) comm_RS485_UART_SCB__INTR_I2C_EC_MASK)
#define comm_RS485_UART_INTR_I2C_EC_MASK_PTR   ( (reg32 *) comm_RS485_UART_SCB__INTR_I2C_EC_MASK)

#define comm_RS485_UART_INTR_I2C_EC_MASKED_REG (*(reg32 *) comm_RS485_UART_SCB__INTR_I2C_EC_MASKED)
#define comm_RS485_UART_INTR_I2C_EC_MASKED_PTR ( (reg32 *) comm_RS485_UART_SCB__INTR_I2C_EC_MASKED)

#if (!comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_INTR_SPI_EC_REG        (*(reg32 *) comm_RS485_UART_SCB__INTR_SPI_EC)
    #define comm_RS485_UART_INTR_SPI_EC_PTR        ( (reg32 *) comm_RS485_UART_SCB__INTR_SPI_EC)

    #define comm_RS485_UART_INTR_SPI_EC_MASK_REG   (*(reg32 *) comm_RS485_UART_SCB__INTR_SPI_EC_MASK)
    #define comm_RS485_UART_INTR_SPI_EC_MASK_PTR   ( (reg32 *) comm_RS485_UART_SCB__INTR_SPI_EC_MASK)

    #define comm_RS485_UART_INTR_SPI_EC_MASKED_REG (*(reg32 *) comm_RS485_UART_SCB__INTR_SPI_EC_MASKED)
    #define comm_RS485_UART_INTR_SPI_EC_MASKED_PTR ( (reg32 *) comm_RS485_UART_SCB__INTR_SPI_EC_MASKED)
#endif /* (!comm_RS485_UART_CY_SCBIP_V1) */

#define comm_RS485_UART_INTR_MASTER_REG        (*(reg32 *) comm_RS485_UART_SCB__INTR_M)
#define comm_RS485_UART_INTR_MASTER_PTR        ( (reg32 *) comm_RS485_UART_SCB__INTR_M)

#define comm_RS485_UART_INTR_MASTER_SET_REG    (*(reg32 *) comm_RS485_UART_SCB__INTR_M_SET)
#define comm_RS485_UART_INTR_MASTER_SET_PTR    ( (reg32 *) comm_RS485_UART_SCB__INTR_M_SET)

#define comm_RS485_UART_INTR_MASTER_MASK_REG   (*(reg32 *) comm_RS485_UART_SCB__INTR_M_MASK)
#define comm_RS485_UART_INTR_MASTER_MASK_PTR   ( (reg32 *) comm_RS485_UART_SCB__INTR_M_MASK)

#define comm_RS485_UART_INTR_MASTER_MASKED_REG (*(reg32 *) comm_RS485_UART_SCB__INTR_M_MASKED)
#define comm_RS485_UART_INTR_MASTER_MASKED_PTR ( (reg32 *) comm_RS485_UART_SCB__INTR_M_MASKED)

#define comm_RS485_UART_INTR_SLAVE_REG         (*(reg32 *) comm_RS485_UART_SCB__INTR_S)
#define comm_RS485_UART_INTR_SLAVE_PTR         ( (reg32 *) comm_RS485_UART_SCB__INTR_S)

#define comm_RS485_UART_INTR_SLAVE_SET_REG     (*(reg32 *) comm_RS485_UART_SCB__INTR_S_SET)
#define comm_RS485_UART_INTR_SLAVE_SET_PTR     ( (reg32 *) comm_RS485_UART_SCB__INTR_S_SET)

#define comm_RS485_UART_INTR_SLAVE_MASK_REG    (*(reg32 *) comm_RS485_UART_SCB__INTR_S_MASK)
#define comm_RS485_UART_INTR_SLAVE_MASK_PTR    ( (reg32 *) comm_RS485_UART_SCB__INTR_S_MASK)

#define comm_RS485_UART_INTR_SLAVE_MASKED_REG  (*(reg32 *) comm_RS485_UART_SCB__INTR_S_MASKED)
#define comm_RS485_UART_INTR_SLAVE_MASKED_PTR  ( (reg32 *) comm_RS485_UART_SCB__INTR_S_MASKED)

#define comm_RS485_UART_INTR_TX_REG            (*(reg32 *) comm_RS485_UART_SCB__INTR_TX)
#define comm_RS485_UART_INTR_TX_PTR            ( (reg32 *) comm_RS485_UART_SCB__INTR_TX)

#define comm_RS485_UART_INTR_TX_SET_REG        (*(reg32 *) comm_RS485_UART_SCB__INTR_TX_SET)
#define comm_RS485_UART_INTR_TX_SET_PTR        ( (reg32 *) comm_RS485_UART_SCB__INTR_TX_SET)

#define comm_RS485_UART_INTR_TX_MASK_REG       (*(reg32 *) comm_RS485_UART_SCB__INTR_TX_MASK)
#define comm_RS485_UART_INTR_TX_MASK_PTR       ( (reg32 *) comm_RS485_UART_SCB__INTR_TX_MASK)

#define comm_RS485_UART_INTR_TX_MASKED_REG     (*(reg32 *) comm_RS485_UART_SCB__INTR_TX_MASKED)
#define comm_RS485_UART_INTR_TX_MASKED_PTR     ( (reg32 *) comm_RS485_UART_SCB__INTR_TX_MASKED)

#define comm_RS485_UART_INTR_RX_REG            (*(reg32 *) comm_RS485_UART_SCB__INTR_RX)
#define comm_RS485_UART_INTR_RX_PTR            ( (reg32 *) comm_RS485_UART_SCB__INTR_RX)

#define comm_RS485_UART_INTR_RX_SET_REG        (*(reg32 *) comm_RS485_UART_SCB__INTR_RX_SET)
#define comm_RS485_UART_INTR_RX_SET_PTR        ( (reg32 *) comm_RS485_UART_SCB__INTR_RX_SET)

#define comm_RS485_UART_INTR_RX_MASK_REG       (*(reg32 *) comm_RS485_UART_SCB__INTR_RX_MASK)
#define comm_RS485_UART_INTR_RX_MASK_PTR       ( (reg32 *) comm_RS485_UART_SCB__INTR_RX_MASK)

#define comm_RS485_UART_INTR_RX_MASKED_REG     (*(reg32 *) comm_RS485_UART_SCB__INTR_RX_MASKED)
#define comm_RS485_UART_INTR_RX_MASKED_PTR     ( (reg32 *) comm_RS485_UART_SCB__INTR_RX_MASKED)

#if (comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_FF_DATA_NR_LOG2_PLUS1_MASK (0x0Fu) /* FF_DATA_NR_LOG2_PLUS1 = 4, MASK = 2^4 - 1 = 15 */
    #define comm_RS485_UART_FF_DATA_NR_LOG2_MASK       (0x07u) /* FF_DATA_NR_LOG2 = 3, MASK = 2^3 - 1 = 7 */
#else
    #define comm_RS485_UART_FF_DATA_NR_LOG2_PLUS1_MASK (0x1Fu) /* FF_DATA_NR_LOG2_PLUS1 = 5, MASK = 2^5 - 1 = 31 */
    #define comm_RS485_UART_FF_DATA_NR_LOG2_MASK       (0x0Fu) /* FF_DATA_NR_LOG2 = 4, MASK = 2^4 - 1 = 15 */
#endif /* (comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1) */


/***************************************
*        Registers Constants
***************************************/

#if(comm_RS485_UART_SCB_IRQ_INTERNAL)
    #define comm_RS485_UART_ISR_NUMBER     ((uint8) comm_RS485_UART_SCB_IRQ__INTC_NUMBER)
    #define comm_RS485_UART_ISR_PRIORITY   ((uint8) comm_RS485_UART_SCB_IRQ__INTC_PRIOR_NUM)
#endif /* (comm_RS485_UART_SCB_IRQ_INTERNAL) */

#if(comm_RS485_UART_UART_RX_WAKEUP_IRQ)
    #define comm_RS485_UART_RX_WAKE_ISR_NUMBER     ((uint8) comm_RS485_UART_RX_WAKEUP_IRQ__INTC_NUMBER)
    #define comm_RS485_UART_RX_WAKE_ISR_PRIORITY   ((uint8) comm_RS485_UART_RX_WAKEUP_IRQ__INTC_PRIOR_NUM)
#endif /* (comm_RS485_UART_UART_RX_WAKEUP_IRQ) */

/* comm_RS485_UART_CTRL_REG */
#define comm_RS485_UART_CTRL_OVS_POS           (0u)  /* [3:0]   Oversampling factor                 */
#define comm_RS485_UART_CTRL_EC_AM_MODE_POS    (8u)  /* [8]     Externally clocked address match    */
#define comm_RS485_UART_CTRL_EC_OP_MODE_POS    (9u)  /* [9]     Externally clocked operation mode   */
#define comm_RS485_UART_CTRL_EZBUF_MODE_POS    (10u) /* [10]    EZ buffer is enabled                */
#if !(comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_CTRL_BYTE_MODE_POS (11u) /* [11]    Determines the number of bits per FIFO data element */
#endif /* !(comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1) */
#define comm_RS485_UART_CTRL_ADDR_ACCEPT_POS   (16u) /* [16]    Put matched address in RX FIFO       */
#define comm_RS485_UART_CTRL_BLOCK_POS         (17u) /* [17]    Ext and Int logic to resolve collide */
#define comm_RS485_UART_CTRL_MODE_POS          (24u) /* [25:24] Operation mode                       */
#define comm_RS485_UART_CTRL_ENABLED_POS       (31u) /* [31]    Enable SCB block                     */
#define comm_RS485_UART_CTRL_OVS_MASK          ((uint32) 0x0Fu)
#define comm_RS485_UART_CTRL_EC_AM_MODE        ((uint32) 0x01u << comm_RS485_UART_CTRL_EC_AM_MODE_POS)
#define comm_RS485_UART_CTRL_EC_OP_MODE        ((uint32) 0x01u << comm_RS485_UART_CTRL_EC_OP_MODE_POS)
#define comm_RS485_UART_CTRL_EZBUF_MODE        ((uint32) 0x01u << comm_RS485_UART_CTRL_EZBUF_MODE_POS)
#if !(comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_CTRL_BYTE_MODE ((uint32) 0x01u << comm_RS485_UART_CTRL_BYTE_MODE_POS)
#endif /* !(comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1) */
#define comm_RS485_UART_CTRL_ADDR_ACCEPT       ((uint32) 0x01u << comm_RS485_UART_CTRL_ADDR_ACCEPT_POS)
#define comm_RS485_UART_CTRL_BLOCK             ((uint32) 0x01u << comm_RS485_UART_CTRL_BLOCK_POS)
#define comm_RS485_UART_CTRL_MODE_MASK         ((uint32) 0x03u << comm_RS485_UART_CTRL_MODE_POS)
#define comm_RS485_UART_CTRL_MODE_I2C          ((uint32) 0x00u)
#define comm_RS485_UART_CTRL_MODE_SPI          ((uint32) 0x01u << comm_RS485_UART_CTRL_MODE_POS)
#define comm_RS485_UART_CTRL_MODE_UART         ((uint32) 0x02u << comm_RS485_UART_CTRL_MODE_POS)
#define comm_RS485_UART_CTRL_ENABLED           ((uint32) 0x01u << comm_RS485_UART_CTRL_ENABLED_POS)

/* comm_RS485_UART_STATUS_REG */
#define comm_RS485_UART_STATUS_EC_BUSY_POS     (0u)  /* [0] Bus busy. Externally clocked logic access to EZ memory */
#define comm_RS485_UART_STATUS_EC_BUSY         ((uint32) 0x0Fu)

/* comm_RS485_UART_SPI_CTRL_REG  */
#define comm_RS485_UART_SPI_CTRL_CONTINUOUS_POS        (0u)  /* [0]     Continuous or Separated SPI data transfers */
#define comm_RS485_UART_SPI_CTRL_SELECT_PRECEDE_POS    (1u)  /* [1]     Precedes or coincides start of data frame  */
#define comm_RS485_UART_SPI_CTRL_CPHA_POS              (2u)  /* [2]     SCLK phase                                 */
#define comm_RS485_UART_SPI_CTRL_CPOL_POS              (3u)  /* [3]     SCLK polarity                              */
#define comm_RS485_UART_SPI_CTRL_LATE_MISO_SAMPLE_POS  (4u)  /* [4]     Late MISO sample enabled                   */
#if !(comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_SPI_CTRL_SCLK_CONTINUOUS_POS   (5u)  /* [5]     Enable continuous SCLK generation */
    #define comm_RS485_UART_SPI_CTRL_SSEL0_POLARITY_POS    (8u)  /* [8]     SS0 polarity                      */
    #define comm_RS485_UART_SPI_CTRL_SSEL1_POLARITY_POS    (9u)  /* [9]     SS1 polarity                      */
    #define comm_RS485_UART_SPI_CTRL_SSEL2_POLARITY_POS    (10u) /* [10]    SS2 polarity                      */
    #define comm_RS485_UART_SPI_CTRL_SSEL3_POLARITY_POS    (11u) /* [11]    SS3 polarity                      */
#endif /* !(comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1) */
#define comm_RS485_UART_SPI_CTRL_LOOPBACK_POS          (16u) /* [16]    Local loop-back control enabled            */
#define comm_RS485_UART_SPI_CTRL_MODE_POS              (24u) /* [25:24] Submode of SPI operation                   */
#define comm_RS485_UART_SPI_CTRL_SLAVE_SELECT_POS      (26u) /* [27:26] Selects SPI SS signal                      */
#define comm_RS485_UART_SPI_CTRL_MASTER_MODE_POS       (31u) /* [31]    Master mode enabled                        */
#define comm_RS485_UART_SPI_CTRL_CONTINUOUS            ((uint32) 0x01u)
#define comm_RS485_UART_SPI_CTRL_SELECT_PRECEDE        ((uint32) 0x01u << comm_RS485_UART_SPI_CTRL_SELECT_PRECEDE_POS)
#define comm_RS485_UART_SPI_CTRL_SCLK_MODE_MASK        ((uint32) 0x03u << comm_RS485_UART_SPI_CTRL_CPHA_POS)
#define comm_RS485_UART_SPI_CTRL_CPHA                  ((uint32) 0x01u << comm_RS485_UART_SPI_CTRL_CPHA_POS)
#define comm_RS485_UART_SPI_CTRL_CPOL                  ((uint32) 0x01u << comm_RS485_UART_SPI_CTRL_CPOL_POS)
#define comm_RS485_UART_SPI_CTRL_LATE_MISO_SAMPLE      ((uint32) 0x01u << \
                                                                    comm_RS485_UART_SPI_CTRL_LATE_MISO_SAMPLE_POS)
#if !(comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_SPI_CTRL_SCLK_CONTINUOUS  ((uint32) 0x01u << comm_RS485_UART_SPI_CTRL_SCLK_CONTINUOUS_POS)
    #define comm_RS485_UART_SPI_CTRL_SSEL0_POLARITY   ((uint32) 0x01u << comm_RS485_UART_SPI_CTRL_SSEL_POLARITY0_POS)
    #define comm_RS485_UART_SPI_CTRL_SSEL1_POLARITY   ((uint32) 0x01u << comm_RS485_UART_SPI_CTRL_SSEL_POLARITY1_POS)
    #define comm_RS485_UART_SPI_CTRL_SSEL2_POLARITY   ((uint32) 0x01u << comm_RS485_UART_SPI_CTRL_SSEL_POLARITY2_POS)
    #define comm_RS485_UART_SPI_CTRL_SSEL3_POLARITY   ((uint32) 0x01u << comm_RS485_UART_SPI_CTRL_SSEL_POLARITY3_POS)
    #define comm_RS485_UART_SPI_CTRL_SSEL_POLARITY_MASK ((uint32)0x0Fu << comm_RS485_UART_SPI_CTRL_SSEL0_POLARITY_POS)
#endif /* !(comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1) */

#define comm_RS485_UART_SPI_CTRL_LOOPBACK              ((uint32) 0x01u << comm_RS485_UART_SPI_CTRL_LOOPBACK_POS)
#define comm_RS485_UART_SPI_CTRL_MODE_MASK             ((uint32) 0x03u << comm_RS485_UART_SPI_CTRL_MODE_POS)
#define comm_RS485_UART_SPI_CTRL_MODE_MOTOROLA         ((uint32) 0x00u)
#define comm_RS485_UART_SPI_CTRL_MODE_TI               ((uint32) 0x01u << comm_RS485_UART_CTRL_MODE_POS)
#define comm_RS485_UART_SPI_CTRL_MODE_NS               ((uint32) 0x02u << comm_RS485_UART_CTRL_MODE_POS)
#define comm_RS485_UART_SPI_CTRL_SLAVE_SELECT_MASK     ((uint32) 0x03u << comm_RS485_UART_SPI_CTRL_SLAVE_SELECT_POS)
#define comm_RS485_UART_SPI_CTRL_SLAVE_SELECT0         ((uint32) 0x00u)
#define comm_RS485_UART_SPI_CTRL_SLAVE_SELECT1         ((uint32) 0x01u << comm_RS485_UART_SPI_CTRL_SLAVE_SELECT_POS)
#define comm_RS485_UART_SPI_CTRL_SLAVE_SELECT2         ((uint32) 0x02u << comm_RS485_UART_SPI_CTRL_SLAVE_SELECT_POS)
#define comm_RS485_UART_SPI_CTRL_SLAVE_SELECT3         ((uint32) 0x03u << comm_RS485_UART_SPI_CTRL_SLAVE_SELECT_POS)
#define comm_RS485_UART_SPI_CTRL_MASTER                ((uint32) 0x01u << comm_RS485_UART_SPI_CTRL_MASTER_MODE_POS)
#define comm_RS485_UART_SPI_CTRL_SLAVE                 ((uint32) 0x00u)

/* comm_RS485_UART_SPI_STATUS_REG  */
#define comm_RS485_UART_SPI_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy - slave selected */
#define comm_RS485_UART_SPI_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EzAddress                 */
#define comm_RS485_UART_SPI_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define comm_RS485_UART_SPI_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << comm_RS485_UART_I2C_STATUS_EZBUF_ADDR_POS)

/* comm_RS485_UART_UART_CTRL */
#define comm_RS485_UART_UART_CTRL_LOOPBACK_POS         (16u) /* [16] Loop-back    */
#define comm_RS485_UART_UART_CTRL_MODE_POS             (24u) /* [24] UART subMode */
#define comm_RS485_UART_UART_CTRL_LOOPBACK             ((uint32) 0x01u << comm_RS485_UART_UART_CTRL_LOOPBACK_POS)
#define comm_RS485_UART_UART_CTRL_MODE_UART_STD        ((uint32) 0x00u)
#define comm_RS485_UART_UART_CTRL_MODE_UART_SMARTCARD  ((uint32) 0x01u << comm_RS485_UART_UART_CTRL_MODE_POS)
#define comm_RS485_UART_UART_CTRL_MODE_UART_IRDA       ((uint32) 0x02u << comm_RS485_UART_UART_CTRL_MODE_POS)
#define comm_RS485_UART_UART_CTRL_MODE_MASK            ((uint32) 0x03u << comm_RS485_UART_UART_CTRL_MODE_POS)

/* comm_RS485_UART_UART_TX_CTRL */
#define comm_RS485_UART_UART_TX_CTRL_STOP_BITS_POS         (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period */
#define comm_RS485_UART_UART_TX_CTRL_PARITY_POS            (4u)  /* [4]   Parity bit                              */
#define comm_RS485_UART_UART_TX_CTRL_PARITY_ENABLED_POS    (5u)  /* [5]   Parity enable                           */
#define comm_RS485_UART_UART_TX_CTRL_RETRY_ON_NACK_POS     (8u)  /* [8]   Smart Card: re-send frame on NACK       */
#define comm_RS485_UART_UART_TX_CTRL_ONE_STOP_BIT          ((uint32) 0x01u)
#define comm_RS485_UART_UART_TX_CTRL_ONE_HALF_STOP_BITS    ((uint32) 0x02u)
#define comm_RS485_UART_UART_TX_CTRL_TWO_STOP_BITS         ((uint32) 0x03u)
#define comm_RS485_UART_UART_TX_CTRL_STOP_BITS_MASK        ((uint32) 0x07u)
#define comm_RS485_UART_UART_TX_CTRL_PARITY                ((uint32) 0x01u << \
                                                                    comm_RS485_UART_UART_TX_CTRL_PARITY_POS)
#define comm_RS485_UART_UART_TX_CTRL_PARITY_ENABLED        ((uint32) 0x01u << \
                                                                    comm_RS485_UART_UART_TX_CTRL_PARITY_ENABLED_POS)
#define comm_RS485_UART_UART_TX_CTRL_RETRY_ON_NACK         ((uint32) 0x01u << \
                                                                    comm_RS485_UART_UART_TX_CTRL_RETRY_ON_NACK_POS)

/* comm_RS485_UART_UART_RX_CTRL */
#define comm_RS485_UART_UART_RX_CTRL_STOP_BITS_POS             (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period*/
#define comm_RS485_UART_UART_RX_CTRL_PARITY_POS                (4u)  /* [4]   Parity bit                             */
#define comm_RS485_UART_UART_RX_CTRL_PARITY_ENABLED_POS        (5u)  /* [5]   Parity enable                          */
#define comm_RS485_UART_UART_RX_CTRL_POLARITY_POS              (6u)  /* [6]   IrDA: inverts polarity of RX signal    */
#define comm_RS485_UART_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS    (8u)  /* [8]   Drop and lost RX FIFO on parity error  */
#define comm_RS485_UART_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS     (9u)  /* [9]   Drop and lost RX FIFO on frame error   */
#define comm_RS485_UART_UART_RX_CTRL_MP_MODE_POS               (10u) /* [10]  Multi-processor mode                   */
#define comm_RS485_UART_UART_RX_CTRL_LIN_MODE_POS              (12u) /* [12]  Lin mode: applicable for UART Standard */
#define comm_RS485_UART_UART_RX_CTRL_SKIP_START_POS            (13u) /* [13]  Skip start not: only for UART Standard */
#define comm_RS485_UART_UART_RX_CTRL_BREAK_WIDTH_POS           (16u) /* [19:16]  Break width: (Break width + 1)      */
#define comm_RS485_UART_UART_TX_CTRL_ONE_STOP_BIT              ((uint32) 0x01u)
#define comm_RS485_UART_UART_TX_CTRL_ONE_HALF_STOP_BITS        ((uint32) 0x02u)
#define comm_RS485_UART_UART_TX_CTRL_TWO_STOP_BITS             ((uint32) 0x03u)
#define comm_RS485_UART_UART_RX_CTRL_STOP_BITS_MASK            ((uint32) 0x07u)
#define comm_RS485_UART_UART_RX_CTRL_PARITY                    ((uint32) 0x01u << \
                                                                    comm_RS485_UART_UART_RX_CTRL_PARITY_POS)
#define comm_RS485_UART_UART_RX_CTRL_PARITY_ENABLED            ((uint32) 0x01u << \
                                                                    comm_RS485_UART_UART_RX_CTRL_PARITY_ENABLED_POS)
#define comm_RS485_UART_UART_RX_CTRL_POLARITY                  ((uint32) 0x01u << \
                                                                    comm_RS485_UART_UART_RX_CTRL_POLARITY_POS)
#define comm_RS485_UART_UART_RX_CTRL_DROP_ON_PARITY_ERR        ((uint32) 0x01u << \
                                                                   comm_RS485_UART_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS)
#define comm_RS485_UART_UART_RX_CTRL_DROP_ON_FRAME_ERR         ((uint32) 0x01u << \
                                                                    comm_RS485_UART_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS)
#define comm_RS485_UART_UART_RX_CTRL_MP_MODE                   ((uint32) 0x01u << \
                                                                    comm_RS485_UART_UART_RX_CTRL_MP_MODE_POS)
#define comm_RS485_UART_UART_RX_CTRL_LIN_MODE                  ((uint32) 0x01u << \
                                                                    comm_RS485_UART_UART_RX_CTRL_LIN_MODE_POS)
#define comm_RS485_UART_UART_RX_CTRL_SKIP_START                ((uint32) 0x01u << \
                                                                    comm_RS485_UART_UART_RX_CTRL_SKIP_START_POS)
#define comm_RS485_UART_UART_RX_CTRL_BREAK_WIDTH_MASK          ((uint32) 0x0Fu << \
                                                                    comm_RS485_UART_UART_RX_CTRL_BREAK_WIDTH_POS)
/* comm_RS485_UART_UART_RX_STATUS_REG */
#define comm_RS485_UART_UART_RX_STATUS_BR_COUNTER_POS     (0u)  /* [11:0] Baud Rate counter */
#define comm_RS485_UART_UART_RX_STATUS_BR_COUNTER_MASK    ((uint32) 0xFFFu)

#if !(comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1)
    /* comm_RS485_UART_UART_FLOW_CTRL_REG */
    #define comm_RS485_UART_UART_FLOW_CTRL_TRIGGER_LEVEL_POS    (0u)  /* [7:0] RTS RX FIFO trigger level         */
    #define comm_RS485_UART_UART_FLOW_CTRL_RTS_POLARITY_POS     (16u) /* [16]  Polarity of the RTS output signal */
    #define comm_RS485_UART_UART_FLOW_CTRL_CTS_POLARITY_POS     (24u) /* [24]  Polarity of the CTS input signal  */
    #define comm_RS485_UART_UART_FLOW_CTRL_CTS_ENABLED_POS      (25u) /* [25]  Enable CTS signal                 */
    #define comm_RS485_UART_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK   ((uint32) comm_RS485_UART_FF_DATA_NR_LOG2_MASK)
    #define comm_RS485_UART_UART_FLOW_CTRL_RTS_POLARITY         ((uint32) 0x01u << \
                                                                       comm_RS485_UART_UART_FLOW_CTRL_RTS_POLARITY_POS)
    #define comm_RS485_UART_UART_FLOW_CTRL_CTS_POLARITY         ((uint32) 0x01u << \
                                                                       comm_RS485_UART_UART_FLOW_CTRL_CTS_POLARITY_POS)
    #define comm_RS485_UART_UART_FLOW_CTRL_CTS_ENABLE           ((uint32) 0x01u << \
                                                                       comm_RS485_UART_UART_FLOW_CTRL_CTS_ENABLED_POS)
#endif /* !(comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1) */

/* comm_RS485_UART_I2C_CTRL */
#define comm_RS485_UART_I2C_CTRL_HIGH_PHASE_OVS_POS           (0u)   /* [3:0] Oversampling factor high: master only */
#define comm_RS485_UART_I2C_CTRL_LOW_PHASE_OVS_POS            (4u)   /* [7:4] Oversampling factor low:  master only */
#define comm_RS485_UART_I2C_CTRL_M_READY_DATA_ACK_POS         (8u)   /* [8]   Master ACKs data while RX FIFO != FULL*/
#define comm_RS485_UART_I2C_CTRL_M_NOT_READY_DATA_NACK_POS    (9u)   /* [9]   Master NACKs data if RX FIFO ==  FULL */
#define comm_RS485_UART_I2C_CTRL_S_GENERAL_IGNORE_POS         (11u)  /* [11]  Slave ignores General call            */
#define comm_RS485_UART_I2C_CTRL_S_READY_ADDR_ACK_POS         (12u)  /* [12]  Slave ACKs Address if RX FIFO != FULL */
#define comm_RS485_UART_I2C_CTRL_S_READY_DATA_ACK_POS         (13u)  /* [13]  Slave ACKs data while RX FIFO == FULL */
#define comm_RS485_UART_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS    (14u)  /* [14]  Slave NACKs address if RX FIFO == FULL*/
#define comm_RS485_UART_I2C_CTRL_S_NOT_READY_DATA_NACK_POS    (15u)  /* [15]  Slave NACKs data if RX FIFO is  FULL  */
#define comm_RS485_UART_I2C_CTRL_LOOPBACK_POS                 (16u)  /* [16]  Loop-back                             */
#define comm_RS485_UART_I2C_CTRL_SLAVE_MODE_POS               (30u)  /* [30]  Slave mode enabled                    */
#define comm_RS485_UART_I2C_CTRL_MASTER_MODE_POS              (31u)  /* [31]  Master mode enabled                   */
#define comm_RS485_UART_I2C_CTRL_HIGH_PHASE_OVS_MASK  ((uint32) 0x0Fu)
#define comm_RS485_UART_I2C_CTRL_LOW_PHASE_OVS_MASK   ((uint32) 0x0Fu << \
                                                                comm_RS485_UART_I2C_CTRL_LOW_PHASE_OVS_POS)
#define comm_RS485_UART_I2C_CTRL_M_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                comm_RS485_UART_I2C_CTRL_M_READY_DATA_ACK_POS)
#define comm_RS485_UART_I2C_CTRL_M_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                comm_RS485_UART_I2C_CTRL_M_NOT_READY_DATA_NACK_POS)
#define comm_RS485_UART_I2C_CTRL_S_GENERAL_IGNORE      ((uint32) 0x01u << \
                                                                comm_RS485_UART_I2C_CTRL_S_GENERAL_IGNORE_POS)
#define comm_RS485_UART_I2C_CTRL_S_READY_ADDR_ACK      ((uint32) 0x01u << \
                                                                comm_RS485_UART_I2C_CTRL_S_READY_ADDR_ACK_POS)
#define comm_RS485_UART_I2C_CTRL_S_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                comm_RS485_UART_I2C_CTRL_S_READY_DATA_ACK_POS)
#define comm_RS485_UART_I2C_CTRL_S_NOT_READY_ADDR_NACK ((uint32) 0x01u << \
                                                                comm_RS485_UART_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS)
#define comm_RS485_UART_I2C_CTRL_S_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                comm_RS485_UART_I2C_CTRL_S_NOT_READY_DATA_NACK_POS)
#define comm_RS485_UART_I2C_CTRL_LOOPBACK              ((uint32) 0x01u << \
                                                                comm_RS485_UART_I2C_CTRL_LOOPBACK_POS)
#define comm_RS485_UART_I2C_CTRL_SLAVE_MODE            ((uint32) 0x01u << \
                                                                comm_RS485_UART_I2C_CTRL_SLAVE_MODE_POS)
#define comm_RS485_UART_I2C_CTRL_MASTER_MODE           ((uint32) 0x01u << \
                                                                comm_RS485_UART_I2C_CTRL_MASTER_MODE_POS)
#define comm_RS485_UART_I2C_CTRL_SLAVE_MASTER_MODE_MASK    ((uint32) 0x03u << \
                                                                comm_RS485_UART_I2C_CTRL_SLAVE_MODE_POS)

/* comm_RS485_UART_I2C_STATUS_REG  */
#define comm_RS485_UART_I2C_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy: internally clocked */
#define comm_RS485_UART_I2C_STATUS_S_READ_POS      (4u)  /* [4]    Slave is read by master      */
#define comm_RS485_UART_I2C_STATUS_M_READ_POS      (5u)  /* [5]    Master reads Slave           */
#define comm_RS485_UART_I2C_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EZAddress                    */
#define comm_RS485_UART_I2C_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define comm_RS485_UART_I2C_STATUS_S_READ          ((uint32) 0x01u << comm_RS485_UART_I2C_STATUS_S_READ_POS)
#define comm_RS485_UART_I2C_STATUS_M_READ          ((uint32) 0x01u << comm_RS485_UART_I2C_STATUS_M_READ_POS)
#define comm_RS485_UART_I2C_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << comm_RS485_UART_I2C_STATUS_EZBUF_ADDR_POS)

/* comm_RS485_UART_I2C_MASTER_CMD_REG */
#define comm_RS485_UART_I2C_MASTER_CMD_M_START_POS             (0u)  /* [0] Master generate Start                */
#define comm_RS485_UART_I2C_MASTER_CMD_M_START_ON_IDLE_POS     (1u)  /* [1] Master generate Start if bus is free */
#define comm_RS485_UART_I2C_MASTER_CMD_M_ACK_POS               (2u)  /* [2] Master generate ACK                  */
#define comm_RS485_UART_I2C_MASTER_CMD_M_NACK_POS              (3u)  /* [3] Master generate NACK                 */
#define comm_RS485_UART_I2C_MASTER_CMD_M_STOP_POS              (4u)  /* [4] Master generate Stop                 */
#define comm_RS485_UART_I2C_MASTER_CMD_M_START         ((uint32) 0x01u)
#define comm_RS485_UART_I2C_MASTER_CMD_M_START_ON_IDLE ((uint32) 0x01u << \
                                                                   comm_RS485_UART_I2C_MASTER_CMD_M_START_ON_IDLE_POS)
#define comm_RS485_UART_I2C_MASTER_CMD_M_ACK           ((uint32) 0x01u << \
                                                                   comm_RS485_UART_I2C_MASTER_CMD_M_ACK_POS)
#define comm_RS485_UART_I2C_MASTER_CMD_M_NACK          ((uint32) 0x01u << \
                                                                    comm_RS485_UART_I2C_MASTER_CMD_M_NACK_POS)
#define comm_RS485_UART_I2C_MASTER_CMD_M_STOP          ((uint32) 0x01u << \
                                                                    comm_RS485_UART_I2C_MASTER_CMD_M_STOP_POS)

/* comm_RS485_UART_I2C_SLAVE_CMD_REG  */
#define comm_RS485_UART_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define comm_RS485_UART_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define comm_RS485_UART_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define comm_RS485_UART_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << comm_RS485_UART_I2C_SLAVE_CMD_S_NACK_POS)

#define comm_RS485_UART_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define comm_RS485_UART_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define comm_RS485_UART_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define comm_RS485_UART_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << comm_RS485_UART_I2C_SLAVE_CMD_S_NACK_POS)

/* comm_RS485_UART_I2C_CFG_REG */
#if (comm_RS485_UART_CY_SCBIP_V0)
#define comm_RS485_UART_I2C_CFG_SDA_FILT_HYS_POS           (0u)  /* [1:0]   Trim bits for the I2C SDA filter         */
#define comm_RS485_UART_I2C_CFG_SDA_FILT_TRIM_POS          (2u)  /* [3:2]   Trim bits for the I2C SDA filter         */
#define comm_RS485_UART_I2C_CFG_SCL_FILT_HYS_POS           (4u)  /* [5:4]   Trim bits for the I2C SCL filter         */
#define comm_RS485_UART_I2C_CFG_SCL_FILT_TRIM_POS          (6u)  /* [7:6]   Trim bits for the I2C SCL filter         */
#define comm_RS485_UART_I2C_CFG_SDA_FILT_OUT_HYS_POS       (8u)  /* [9:8]   Trim bits for I2C SDA filter output path */
#define comm_RS485_UART_I2C_CFG_SDA_FILT_OUT_TRIM_POS      (10u) /* [11:10] Trim bits for I2C SDA filter output path */
#define comm_RS485_UART_I2C_CFG_SDA_FILT_HS_POS            (16u) /* [16]    '0': 50 ns filter, '1': 10 ns filter     */
#define comm_RS485_UART_I2C_CFG_SDA_FILT_ENABLED_POS       (17u) /* [17]    I2C SDA filter enabled                   */
#define comm_RS485_UART_I2C_CFG_SCL_FILT_HS_POS            (24u) /* [24]    '0': 50 ns filter, '1': 10 ns filter     */
#define comm_RS485_UART_I2C_CFG_SCL_FILT_ENABLED_POS       (25u) /* [25]    I2C SCL filter enabled                   */
#define comm_RS485_UART_I2C_CFG_SDA_FILT_OUT_HS_POS        (26u) /* [26]    '0': 50 ns filter, '1': 10 ns filter     */
#define comm_RS485_UART_I2C_CFG_SDA_FILT_OUT_ENABLED_POS   (27u) /* [27]    I2C SDA output delay filter enabled      */
#define comm_RS485_UART_I2C_CFG_SDA_FILT_HYS_MASK          ((uint32) 0x03u)
#define comm_RS485_UART_I2C_CFG_SDA_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                comm_RS485_UART_I2C_CFG_SDA_FILT_TRIM_POS)
#define comm_RS485_UART_I2C_CFG_SCL_FILT_HYS_MASK          ((uint32) 0x03u << \
                                                                comm_RS485_UART_I2C_CFG_SCL_FILT_HYS_POS)
#define comm_RS485_UART_I2C_CFG_SCL_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                comm_RS485_UART_I2C_CFG_SCL_FILT_TRIM_POS)
#define comm_RS485_UART_I2C_CFG_SDA_FILT_OUT_HYS_MASK      ((uint32) 0x03u << \
                                                                comm_RS485_UART_I2C_CFG_SDA_FILT_OUT_HYS_POS)
#define comm_RS485_UART_I2C_CFG_SDA_FILT_OUT_TRIM_MASK     ((uint32) 0x03u << \
                                                                comm_RS485_UART_I2C_CFG_SDA_FILT_OUT_TRIM_POS)
#define comm_RS485_UART_I2C_CFG_SDA_FILT_HS                ((uint32) 0x01u << \
                                                                comm_RS485_UART_I2C_CFG_SDA_FILT_HS_POS)
#define comm_RS485_UART_I2C_CFG_SDA_FILT_ENABLED           ((uint32) 0x01u << \
                                                                comm_RS485_UART_I2C_CFG_SDA_FILT_ENABLED_POS)
#define comm_RS485_UART_I2C_CFG_SCL_FILT_HS                ((uint32) 0x01u << \
                                                                comm_RS485_UART_I2C_CFG_SCL_FILT_HS_POS)
#define comm_RS485_UART_I2C_CFG_SCL_FILT_ENABLED           ((uint32) 0x01u << \
                                                                comm_RS485_UART_I2C_CFG_SCL_FILT_ENABLED_POS)
#define comm_RS485_UART_I2C_CFG_SDA_FILT_OUT_HS            ((uint32) 0x01u << \
                                                                comm_RS485_UART_I2C_CFG_SDA_FILT_OUT_HS_POS)
#define comm_RS485_UART_I2C_CFG_SDA_FILT_OUT_ENABLED       ((uint32) 0x01u << \
                                                                comm_RS485_UART_I2C_CFG_SDA_FILT_OUT_ENABLED_POS)
#else
#define comm_RS485_UART_I2C_CFG_SDA_IN_FILT_TRIM_POS   (0u)  /* [1:0] Trim bits for "i2c_sda_in" 50 ns filter */
#define comm_RS485_UART_I2C_CFG_SDA_IN_FILT_SEL_POS    (4u)  /* [4]   "i2c_sda_in" filter delay: 0 ns and 50 ns */
#define comm_RS485_UART_I2C_CFG_SCL_IN_FILT_TRIM_POS   (8u)  /* [9:8] Trim bits for "i2c_scl_in" 50 ns filter */
#define comm_RS485_UART_I2C_CFG_SCL_IN_FILT_SEL_POS    (12u) /* [12]  "i2c_scl_in" filter delay: 0 ns and 50 ns */
#define comm_RS485_UART_I2C_CFG_SDA_OUT_FILT0_TRIM_POS (16u) /* [17:16] Trim bits for "i2c_sda_out" 50 ns filter 0 */
#define comm_RS485_UART_I2C_CFG_SDA_OUT_FILT1_TRIM_POS (18u) /* [19:18] Trim bits for "i2c_sda_out" 50 ns filter 1 */
#define comm_RS485_UART_I2C_CFG_SDA_OUT_FILT2_TRIM_POS (20u) /* [21:20] Trim bits for "i2c_sda_out" 50 ns filter 2 */
#define comm_RS485_UART_I2C_CFG_SDA_OUT_FILT_SEL_POS   (28u) /* [29:28] Cumulative "i2c_sda_out" filter delay: */

#define comm_RS485_UART_I2C_CFG_SDA_IN_FILT_TRIM_MASK  ((uint32) 0x03u)
#define comm_RS485_UART_I2C_CFG_SDA_IN_FILT_SEL        ((uint32) 0x01u << comm_RS485_UART_I2C_CFG_SDA_IN_FILT_SEL_POS)
#define comm_RS485_UART_I2C_CFG_SCL_IN_FILT_TRIM_MASK  ((uint32) 0x03u << \
                                                            comm_RS485_UART_I2C_CFG_SCL_IN_FILT_TRIM_POS)
#define comm_RS485_UART_I2C_CFG_SCL_IN_FILT_SEL        ((uint32) 0x01u << comm_RS485_UART_I2C_CFG_SCL_IN_FILT_SEL_POS)
#define comm_RS485_UART_I2C_CFG_SDA_OUT_FILT0_TRIM_MASK ((uint32) 0x03u << \
                                                            comm_RS485_UART_I2C_CFG_SDA_OUT_FILT0_TRIM_POS)
#define comm_RS485_UART_I2C_CFG_SDA_OUT_FILT1_TRIM_MASK ((uint32) 0x03u << \
                                                            comm_RS485_UART_I2C_CFG_SDA_OUT_FILT1_TRIM_POS)
#define comm_RS485_UART_I2C_CFG_SDA_OUT_FILT2_TRIM_MASK ((uint32) 0x03u << \
                                                            comm_RS485_UART_I2C_CFG_SDA_OUT_FILT2_TRIM_POS)
#define comm_RS485_UART_I2C_CFG_SDA_OUT_FILT_SEL_MASK   ((uint32) 0x03u << \
                                                            comm_RS485_UART_I2C_CFG_SDA_OUT_FILT_SEL_POS)
#endif /* (comm_RS485_UART_CY_SCBIP_V0) */


/* comm_RS485_UART_TX_CTRL_REG */
#define comm_RS485_UART_TX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Data frame width: (Data width - 1) */
#define comm_RS485_UART_TX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define comm_RS485_UART_TX_CTRL_ENABLED_POS        (31u) /* [31]  Transmitter enabled               */
#define comm_RS485_UART_TX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define comm_RS485_UART_TX_CTRL_MSB_FIRST          ((uint32) 0x01u << comm_RS485_UART_TX_CTRL_MSB_FIRST_POS)
#define comm_RS485_UART_TX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define comm_RS485_UART_TX_CTRL_ENABLED            ((uint32) 0x01u << comm_RS485_UART_TX_CTRL_ENABLED_POS)

/* comm_RS485_UART_TX_CTRL_FIFO_REG */
#define comm_RS485_UART_TX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)  /* [2:0] Trigger level                              */
#define comm_RS485_UART_TX_FIFO_CTRL_CLEAR_POS             (16u) /* [16]  Clear TX FIFO: cleared after set           */
#define comm_RS485_UART_TX_FIFO_CTRL_FREEZE_POS            (17u) /* [17]  Freeze TX FIFO: HW do not inc read pointer */
#define comm_RS485_UART_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) comm_RS485_UART_FF_DATA_NR_LOG2_MASK)
#define comm_RS485_UART_TX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << comm_RS485_UART_TX_FIFO_CTRL_CLEAR_POS)
#define comm_RS485_UART_TX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << comm_RS485_UART_TX_FIFO_CTRL_FREEZE_POS)

/* comm_RS485_UART_TX_FIFO_STATUS_REG */
#define comm_RS485_UART_TX_FIFO_STATUS_USED_POS    (0u)  /* [3:0]   Amount of entries in TX FIFO */
#define comm_RS485_UART_TX_FIFO_SR_VALID_POS       (15u) /* [15]    Shifter status of TX FIFO    */
#define comm_RS485_UART_TX_FIFO_STATUS_RD_PTR_POS  (16u) /* [18:16] TX FIFO read pointer         */
#define comm_RS485_UART_TX_FIFO_STATUS_WR_PTR_POS  (24u) /* [26:24] TX FIFO write pointer        */
#define comm_RS485_UART_TX_FIFO_STATUS_USED_MASK   ((uint32) comm_RS485_UART_FF_DATA_NR_LOG2_PLUS1_MASK)
#define comm_RS485_UART_TX_FIFO_SR_VALID           ((uint32) 0x01u << comm_RS485_UART_TX_FIFO_SR_VALID_POS)
#define comm_RS485_UART_TX_FIFO_STATUS_RD_PTR_MASK ((uint32) comm_RS485_UART_FF_DATA_NR_LOG2_MASK << \
                                                                    comm_RS485_UART_TX_FIFO_STATUS_RD_PTR_POS)
#define comm_RS485_UART_TX_FIFO_STATUS_WR_PTR_MASK ((uint32) comm_RS485_UART_FF_DATA_NR_LOG2_MASK << \
                                                                    comm_RS485_UART_TX_FIFO_STATUS_WR_PTR_POS)

/* comm_RS485_UART_TX_FIFO_WR_REG */
#define comm_RS485_UART_TX_FIFO_WR_POS    (0u)  /* [15:0] Data written into TX FIFO */
#define comm_RS485_UART_TX_FIFO_WR_MASK   ((uint32) 0xFFu)

/* comm_RS485_UART_RX_CTRL_REG */
#define comm_RS485_UART_RX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Data frame width: (Data width - 1) */
#define comm_RS485_UART_RX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define comm_RS485_UART_RX_CTRL_MEDIAN_POS         (9u)  /* [9]   Median filter                     */
#define comm_RS485_UART_RX_CTRL_ENABLED_POS        (31u) /* [31]  Receiver enabled                  */
#define comm_RS485_UART_RX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define comm_RS485_UART_RX_CTRL_MSB_FIRST          ((uint32) 0x01u << comm_RS485_UART_RX_CTRL_MSB_FIRST_POS)
#define comm_RS485_UART_RX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define comm_RS485_UART_RX_CTRL_MEDIAN             ((uint32) 0x01u << comm_RS485_UART_RX_CTRL_MEDIAN_POS)
#define comm_RS485_UART_RX_CTRL_ENABLED            ((uint32) 0x01u << comm_RS485_UART_RX_CTRL_ENABLED_POS)


/* comm_RS485_UART_RX_FIFO_CTRL_REG */
#define comm_RS485_UART_RX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)   /* [2:0] Trigger level                            */
#define comm_RS485_UART_RX_FIFO_CTRL_CLEAR_POS             (16u)  /* [16]  Clear RX FIFO: clear after set           */
#define comm_RS485_UART_RX_FIFO_CTRL_FREEZE_POS            (17u)  /* [17]  Freeze RX FIFO: HW writes has not effect */
#define comm_RS485_UART_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) comm_RS485_UART_FF_DATA_NR_LOG2_MASK)
#define comm_RS485_UART_RX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << comm_RS485_UART_RX_FIFO_CTRL_CLEAR_POS)
#define comm_RS485_UART_RX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << comm_RS485_UART_RX_FIFO_CTRL_FREEZE_POS)

/* comm_RS485_UART_RX_FIFO_STATUS_REG */
#define comm_RS485_UART_RX_FIFO_STATUS_USED_POS    (0u)   /* [3:0]   Amount of entries in RX FIFO */
#define comm_RS485_UART_RX_FIFO_SR_VALID_POS       (15u)  /* [15]    Shifter status of RX FIFO    */
#define comm_RS485_UART_RX_FIFO_STATUS_RD_PTR_POS  (16u)  /* [18:16] RX FIFO read pointer         */
#define comm_RS485_UART_RX_FIFO_STATUS_WR_PTR_POS  (24u)  /* [26:24] RX FIFO write pointer        */
#define comm_RS485_UART_RX_FIFO_STATUS_USED_MASK   ((uint32) comm_RS485_UART_FF_DATA_NR_LOG2_PLUS1_MASK)
#define comm_RS485_UART_RX_FIFO_SR_VALID           ((uint32) 0x01u << comm_RS485_UART_RX_FIFO_SR_VALID_POS)
#define comm_RS485_UART_RX_FIFO_STATUS_RD_PTR_MASK ((uint32) comm_RS485_UART_FF_DATA_NR_LOG2_MASK << \
                                                                    comm_RS485_UART_RX_FIFO_STATUS_RD_PTR_POS)
#define comm_RS485_UART_RX_FIFO_STATUS_WR_PTR_MASK ((uint32) comm_RS485_UART_FF_DATA_NR_LOG2_MASK << \
                                                                    comm_RS485_UART_RX_FIFO_STATUS_WR_PTR_POS)

/* comm_RS485_UART_RX_MATCH_REG */
#define comm_RS485_UART_RX_MATCH_ADDR_POS     (0u)  /* [7:0]   Slave address                        */
#define comm_RS485_UART_RX_MATCH_MASK_POS     (16u) /* [23:16] Slave address mask: 0 - doesn't care */
#define comm_RS485_UART_RX_MATCH_ADDR_MASK    ((uint32) 0xFFu)
#define comm_RS485_UART_RX_MATCH_MASK_MASK    ((uint32) 0xFFu << comm_RS485_UART_RX_MATCH_MASK_POS)

/* comm_RS485_UART_RX_FIFO_WR_REG */
#define comm_RS485_UART_RX_FIFO_RD_POS    (0u)  /* [15:0] Data read from RX FIFO */
#define comm_RS485_UART_RX_FIFO_RD_MASK   ((uint32) 0xFFu)

/* comm_RS485_UART_RX_FIFO_RD_SILENT_REG */
#define comm_RS485_UART_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define comm_RS485_UART_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* comm_RS485_UART_RX_FIFO_RD_SILENT_REG */
#define comm_RS485_UART_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define comm_RS485_UART_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* comm_RS485_UART_EZBUF_DATA_REG */
#define comm_RS485_UART_EZBUF_DATA_POS   (0u)  /* [7:0] Data from EZ Memory */
#define comm_RS485_UART_EZBUF_DATA_MASK  ((uint32) 0xFFu)

/*  comm_RS485_UART_INTR_CAUSE_REG */
#define comm_RS485_UART_INTR_CAUSE_MASTER_POS  (0u)  /* [0] Master interrupt active                 */
#define comm_RS485_UART_INTR_CAUSE_SLAVE_POS   (1u)  /* [1] Slave interrupt active                  */
#define comm_RS485_UART_INTR_CAUSE_TX_POS      (2u)  /* [2] Transmitter interrupt active            */
#define comm_RS485_UART_INTR_CAUSE_RX_POS      (3u)  /* [3] Receiver interrupt active               */
#define comm_RS485_UART_INTR_CAUSE_I2C_EC_POS  (4u)  /* [4] Externally clock I2C interrupt active   */
#define comm_RS485_UART_INTR_CAUSE_SPI_EC_POS  (5u)  /* [5] Externally clocked SPI interrupt active */
#define comm_RS485_UART_INTR_CAUSE_MASTER      ((uint32) 0x01u)
#define comm_RS485_UART_INTR_CAUSE_SLAVE       ((uint32) 0x01u << comm_RS485_UART_INTR_CAUSE_SLAVE_POS)
#define comm_RS485_UART_INTR_CAUSE_TX          ((uint32) 0x01u << comm_RS485_UART_INTR_CAUSE_TX_POS)
#define comm_RS485_UART_INTR_CAUSE_RX          ((uint32) 0x01u << comm_RS485_UART_INTR_CAUSE_RX_POS)
#define comm_RS485_UART_INTR_CAUSE_I2C_EC      ((uint32) 0x01u << comm_RS485_UART_INTR_CAUSE_I2C_EC_POS)
#define comm_RS485_UART_INTR_CAUSE_SPI_EC      ((uint32) 0x01u << comm_RS485_UART_INTR_CAUSE_SPI_EC_POS)

/* comm_RS485_UART_INTR_SPI_EC_REG, comm_RS485_UART_INTR_SPI_EC_MASK_REG, comm_RS485_UART_INTR_SPI_EC_MASKED_REG */
#define comm_RS485_UART_INTR_SPI_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define comm_RS485_UART_INTR_SPI_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define comm_RS485_UART_INTR_SPI_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define comm_RS485_UART_INTR_SPI_EC_WAKE_UP              ((uint32) 0x01u)
#define comm_RS485_UART_INTR_SPI_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    comm_RS485_UART_INTR_SPI_EC_EZBUF_STOP_POS)
#define comm_RS485_UART_INTR_SPI_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    comm_RS485_UART_INTR_SPI_EC_EZBUF_WRITE_STOP_POS)

/* comm_RS485_UART_INTR_I2C_EC, comm_RS485_UART_INTR_I2C_EC_MASK, comm_RS485_UART_INTR_I2C_EC_MASKED */
#define comm_RS485_UART_INTR_I2C_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define comm_RS485_UART_INTR_I2C_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define comm_RS485_UART_INTR_I2C_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define comm_RS485_UART_INTR_I2C_EC_WAKE_UP              ((uint32) 0x01u)
#define comm_RS485_UART_INTR_I2C_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    comm_RS485_UART_INTR_I2C_EC_EZBUF_STOP_POS)
#define comm_RS485_UART_INTR_I2C_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    comm_RS485_UART_INTR_I2C_EC_EZBUF_WRITE_STOP_POS)

/* comm_RS485_UART_INTR_MASTER, comm_RS485_UART_INTR_MASTER_SET,
   comm_RS485_UART_INTR_MASTER_MASK, comm_RS485_UART_INTR_MASTER_MASKED */
#define comm_RS485_UART_INTR_MASTER_I2C_ARB_LOST_POS   (0u)  /* [0] Master lost arbitration                          */
#define comm_RS485_UART_INTR_MASTER_I2C_NACK_POS       (1u)  /* [1] Master receives NACK: address or write to slave  */
#define comm_RS485_UART_INTR_MASTER_I2C_ACK_POS        (2u)  /* [2] Master receives NACK: address or write to slave  */
#define comm_RS485_UART_INTR_MASTER_I2C_STOP_POS       (4u)  /* [4] Master detects the Stop: only self generated Stop*/
#define comm_RS485_UART_INTR_MASTER_I2C_BUS_ERROR_POS  (8u)  /* [8] Master detects bus error: misplaced Start or Stop*/
#define comm_RS485_UART_INTR_MASTER_SPI_DONE_POS       (9u)  /* [9] Master complete transfer: Only for SPI           */
#define comm_RS485_UART_INTR_MASTER_I2C_ARB_LOST       ((uint32) 0x01u)
#define comm_RS485_UART_INTR_MASTER_I2C_NACK           ((uint32) 0x01u << comm_RS485_UART_INTR_MASTER_I2C_NACK_POS)
#define comm_RS485_UART_INTR_MASTER_I2C_ACK            ((uint32) 0x01u << comm_RS485_UART_INTR_MASTER_I2C_ACK_POS)
#define comm_RS485_UART_INTR_MASTER_I2C_STOP           ((uint32) 0x01u << comm_RS485_UART_INTR_MASTER_I2C_STOP_POS)
#define comm_RS485_UART_INTR_MASTER_I2C_BUS_ERROR      ((uint32) 0x01u << \
                                                                    comm_RS485_UART_INTR_MASTER_I2C_BUS_ERROR_POS)
#define comm_RS485_UART_INTR_MASTER_SPI_DONE           ((uint32) 0x01u << comm_RS485_UART_INTR_MASTER_SPI_DONE_POS)

/*
* comm_RS485_UART_INTR_SLAVE, comm_RS485_UART_INTR_SLAVE_SET,
* comm_RS485_UART_INTR_SLAVE_MASK, comm_RS485_UART_INTR_SLAVE_MASKED
*/
#define comm_RS485_UART_INTR_SLAVE_I2C_ARB_LOST_POS         (0u)  /* [0]  Slave lost arbitration                   */
#define comm_RS485_UART_INTR_SLAVE_I2C_NACK_POS             (1u)  /* [1]  Slave receives NACK: master reads data   */
#define comm_RS485_UART_INTR_SLAVE_I2C_ACK_POS              (2u)  /* [2]  Slave receives ACK: master reads data    */
#define comm_RS485_UART_INTR_SLAVE_I2C_WRITE_STOP_POS       (3u)  /* [3]  Slave detects end of write transaction   */
#define comm_RS485_UART_INTR_SLAVE_I2C_STOP_POS             (4u)  /* [4]  Slave detects end of transaction intended */
#define comm_RS485_UART_INTR_SLAVE_I2C_START_POS            (5u)  /* [5]  Slave detects Start                      */
#define comm_RS485_UART_INTR_SLAVE_I2C_ADDR_MATCH_POS       (6u)  /* [6]  Slave address matches                    */
#define comm_RS485_UART_INTR_SLAVE_I2C_GENERAL_POS          (7u)  /* [7]  General call received                    */
#define comm_RS485_UART_INTR_SLAVE_I2C_BUS_ERROR_POS        (8u)  /* [8]  Slave detects bus error                  */
#define comm_RS485_UART_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS (9u)  /* [9]  Slave write complete: Only for SPI       */
#define comm_RS485_UART_INTR_SLAVE_SPI_EZBUF_STOP_POS       (10u) /* [10] Slave end of transaction: Only for SPI   */
#define comm_RS485_UART_INTR_SLAVE_SPI_BUS_ERROR_POS        (11u) /* [11] Slave detects bus error: Only for SPI    */
#define comm_RS485_UART_INTR_SLAVE_I2C_ARB_LOST             ((uint32) 0x01u)
#define comm_RS485_UART_INTR_SLAVE_I2C_NACK                 ((uint32) 0x01u << \
                                                                    comm_RS485_UART_INTR_SLAVE_I2C_NACK_POS)
#define comm_RS485_UART_INTR_SLAVE_I2C_ACK                  ((uint32) 0x01u << \
                                                                    comm_RS485_UART_INTR_SLAVE_I2C_ACK_POS)
#define comm_RS485_UART_INTR_SLAVE_I2C_WRITE_STOP           ((uint32) 0x01u << \
                                                                    comm_RS485_UART_INTR_SLAVE_I2C_WRITE_STOP_POS)
#define comm_RS485_UART_INTR_SLAVE_I2C_STOP                 ((uint32) 0x01u << \
                                                                    comm_RS485_UART_INTR_SLAVE_I2C_STOP_POS)
#define comm_RS485_UART_INTR_SLAVE_I2C_START                ((uint32) 0x01u << \
                                                                    comm_RS485_UART_INTR_SLAVE_I2C_START_POS)
#define comm_RS485_UART_INTR_SLAVE_I2C_ADDR_MATCH           ((uint32) 0x01u << \
                                                                    comm_RS485_UART_INTR_SLAVE_I2C_ADDR_MATCH_POS)
#define comm_RS485_UART_INTR_SLAVE_I2C_GENERAL              ((uint32) 0x01u << \
                                                                    comm_RS485_UART_INTR_SLAVE_I2C_GENERAL_POS)
#define comm_RS485_UART_INTR_SLAVE_I2C_BUS_ERROR            ((uint32) 0x01u << \
                                                                    comm_RS485_UART_INTR_SLAVE_I2C_BUS_ERROR_POS)
#define comm_RS485_UART_INTR_SLAVE_SPI_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                   comm_RS485_UART_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS)
#define comm_RS485_UART_INTR_SLAVE_SPI_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    comm_RS485_UART_INTR_SLAVE_SPI_EZBUF_STOP_POS)
#define comm_RS485_UART_INTR_SLAVE_SPI_BUS_ERROR           ((uint32) 0x01u << \
                                                                    comm_RS485_UART_INTR_SLAVE_SPI_BUS_ERROR_POS)

/*
* comm_RS485_UART_INTR_TX, comm_RS485_UART_INTR_TX_SET,
* comm_RS485_UART_INTR_TX_MASK, comm_RS485_UART_INTR_TX_MASKED
*/
#define comm_RS485_UART_INTR_TX_TRIGGER_POS        (0u)  /* [0]  Trigger on TX FIFO entires                       */
#define comm_RS485_UART_INTR_TX_NOT_FULL_POS       (1u)  /* [1]  TX FIFO is not full                              */
#define comm_RS485_UART_INTR_TX_EMPTY_POS          (4u)  /* [4]  TX FIFO is empty                                 */
#define comm_RS485_UART_INTR_TX_OVERFLOW_POS       (5u)  /* [5]  Attempt to write to a full TX FIFO               */
#define comm_RS485_UART_INTR_TX_UNDERFLOW_POS      (6u)  /* [6]  Attempt to read from an empty TX FIFO            */
#define comm_RS485_UART_INTR_TX_BLOCKED_POS        (7u)  /* [7]  No access to the EZ memory                       */
#define comm_RS485_UART_INTR_TX_UART_NACK_POS      (8u)  /* [8]  UART transmitter received a NACK: SmartCard mode */
#define comm_RS485_UART_INTR_TX_UART_DONE_POS      (9u)  /* [9]  UART transmitter done even                       */
#define comm_RS485_UART_INTR_TX_UART_ARB_LOST_POS  (10u) /* [10] UART lost arbitration: LIN or SmartCard          */
#define comm_RS485_UART_INTR_TX_TRIGGER            ((uint32) 0x01u)
#define comm_RS485_UART_INTR_TX_FIFO_LEVEL         (comm_RS485_UART_INTR_TX_TRIGGER)
#define comm_RS485_UART_INTR_TX_NOT_FULL           ((uint32) 0x01u << comm_RS485_UART_INTR_TX_NOT_FULL_POS)
#define comm_RS485_UART_INTR_TX_EMPTY              ((uint32) 0x01u << comm_RS485_UART_INTR_TX_EMPTY_POS)
#define comm_RS485_UART_INTR_TX_OVERFLOW           ((uint32) 0x01u << comm_RS485_UART_INTR_TX_OVERFLOW_POS)
#define comm_RS485_UART_INTR_TX_UNDERFLOW          ((uint32) 0x01u << comm_RS485_UART_INTR_TX_UNDERFLOW_POS)
#define comm_RS485_UART_INTR_TX_BLOCKED            ((uint32) 0x01u << comm_RS485_UART_INTR_TX_BLOCKED_POS)
#define comm_RS485_UART_INTR_TX_UART_NACK          ((uint32) 0x01u << comm_RS485_UART_INTR_TX_UART_NACK_POS)
#define comm_RS485_UART_INTR_TX_UART_DONE          ((uint32) 0x01u << comm_RS485_UART_INTR_TX_UART_DONE_POS)
#define comm_RS485_UART_INTR_TX_UART_ARB_LOST      ((uint32) 0x01u << comm_RS485_UART_INTR_TX_UART_ARB_LOST_POS)

/*
* comm_RS485_UART_INTR_RX, comm_RS485_UART_INTR_RX_SET,
* comm_RS485_UART_INTR_RX_MASK, comm_RS485_UART_INTR_RX_MASKED
*/
#define comm_RS485_UART_INTR_RX_TRIGGER_POS        (0u)   /* [0]  Trigger on RX FIFO entires            */
#define comm_RS485_UART_INTR_RX_NOT_EMPTY_POS      (2u)   /* [2]  RX FIFO is not empty                  */
#define comm_RS485_UART_INTR_RX_FULL_POS           (3u)   /* [3]  RX FIFO is full                       */
#define comm_RS485_UART_INTR_RX_OVERFLOW_POS       (5u)   /* [5]  Attempt to write to a full RX FIFO    */
#define comm_RS485_UART_INTR_RX_UNDERFLOW_POS      (6u)   /* [6]  Attempt to read from an empty RX FIFO */
#define comm_RS485_UART_INTR_RX_BLOCKED_POS        (7u)   /* [7]  No access to the EZ memory            */
#define comm_RS485_UART_INTR_RX_FRAME_ERROR_POS    (8u)   /* [8]  Frame error in received data frame    */
#define comm_RS485_UART_INTR_RX_PARITY_ERROR_POS   (9u)   /* [9]  Parity error in received data frame   */
#define comm_RS485_UART_INTR_RX_BAUD_DETECT_POS    (10u)  /* [10] LIN baud rate detection is completed   */
#define comm_RS485_UART_INTR_RX_BREAK_DETECT_POS   (11u)  /* [11] Break detection is successful         */
#define comm_RS485_UART_INTR_RX_TRIGGER            ((uint32) 0x01u)
#define comm_RS485_UART_INTR_RX_FIFO_LEVEL         (comm_RS485_UART_INTR_RX_TRIGGER)
#define comm_RS485_UART_INTR_RX_NOT_EMPTY          ((uint32) 0x01u << comm_RS485_UART_INTR_RX_NOT_EMPTY_POS)
#define comm_RS485_UART_INTR_RX_FULL               ((uint32) 0x01u << comm_RS485_UART_INTR_RX_FULL_POS)
#define comm_RS485_UART_INTR_RX_OVERFLOW           ((uint32) 0x01u << comm_RS485_UART_INTR_RX_OVERFLOW_POS)
#define comm_RS485_UART_INTR_RX_UNDERFLOW          ((uint32) 0x01u << comm_RS485_UART_INTR_RX_UNDERFLOW_POS)
#define comm_RS485_UART_INTR_RX_BLOCKED            ((uint32) 0x01u << comm_RS485_UART_INTR_RX_BLOCKED_POS)
#define comm_RS485_UART_INTR_RX_FRAME_ERROR        ((uint32) 0x01u << comm_RS485_UART_INTR_RX_FRAME_ERROR_POS)
#define comm_RS485_UART_INTR_RX_PARITY_ERROR       ((uint32) 0x01u << comm_RS485_UART_INTR_RX_PARITY_ERROR_POS)
#define comm_RS485_UART_INTR_RX_BAUD_DETECT        ((uint32) 0x01u << comm_RS485_UART_INTR_RX_BAUD_DETECT_POS)
#define comm_RS485_UART_INTR_RX_BREAK_DETECT       ((uint32) 0x01u << comm_RS485_UART_INTR_RX_BREAK_DETECT_POS)

/* Define all interrupt sources */
#define comm_RS485_UART_INTR_I2C_EC_ALL    (comm_RS485_UART_INTR_I2C_EC_WAKE_UP    | \
                                             comm_RS485_UART_INTR_I2C_EC_EZBUF_STOP | \
                                             comm_RS485_UART_INTR_I2C_EC_EZBUF_WRITE_STOP)

#define comm_RS485_UART_INTR_SPI_EC_ALL    (comm_RS485_UART_INTR_SPI_EC_WAKE_UP    | \
                                             comm_RS485_UART_INTR_SPI_EC_EZBUF_STOP | \
                                             comm_RS485_UART_INTR_SPI_EC_EZBUF_WRITE_STOP)

#define comm_RS485_UART_INTR_MASTER_ALL    (comm_RS485_UART_INTR_MASTER_I2C_ARB_LOST  | \
                                             comm_RS485_UART_INTR_MASTER_I2C_NACK      | \
                                             comm_RS485_UART_INTR_MASTER_I2C_ACK       | \
                                             comm_RS485_UART_INTR_MASTER_I2C_STOP      | \
                                             comm_RS485_UART_INTR_MASTER_I2C_BUS_ERROR | \
                                             comm_RS485_UART_INTR_MASTER_SPI_DONE)

#define comm_RS485_UART_INTR_SLAVE_ALL     (comm_RS485_UART_INTR_SLAVE_I2C_ARB_LOST      | \
                                             comm_RS485_UART_INTR_SLAVE_I2C_NACK          | \
                                             comm_RS485_UART_INTR_SLAVE_I2C_ACK           | \
                                             comm_RS485_UART_INTR_SLAVE_I2C_WRITE_STOP    | \
                                             comm_RS485_UART_INTR_SLAVE_I2C_STOP          | \
                                             comm_RS485_UART_INTR_SLAVE_I2C_START         | \
                                             comm_RS485_UART_INTR_SLAVE_I2C_ADDR_MATCH    | \
                                             comm_RS485_UART_INTR_SLAVE_I2C_GENERAL       | \
                                             comm_RS485_UART_INTR_SLAVE_I2C_BUS_ERROR     | \
                                             comm_RS485_UART_INTR_SLAVE_SPI_EZBUF_WRITE_STOP | \
                                             comm_RS485_UART_INTR_SLAVE_SPI_EZBUF_STOP       | \
                                             comm_RS485_UART_INTR_SLAVE_SPI_BUS_ERROR)

#define comm_RS485_UART_INTR_TX_ALL        (comm_RS485_UART_INTR_TX_TRIGGER   | \
                                             comm_RS485_UART_INTR_TX_NOT_FULL  | \
                                             comm_RS485_UART_INTR_TX_EMPTY     | \
                                             comm_RS485_UART_INTR_TX_OVERFLOW  | \
                                             comm_RS485_UART_INTR_TX_UNDERFLOW | \
                                             comm_RS485_UART_INTR_TX_BLOCKED   | \
                                             comm_RS485_UART_INTR_TX_UART_NACK | \
                                             comm_RS485_UART_INTR_TX_UART_DONE | \
                                             comm_RS485_UART_INTR_TX_UART_ARB_LOST)

#define comm_RS485_UART_INTR_RX_ALL        (comm_RS485_UART_INTR_RX_TRIGGER      | \
                                             comm_RS485_UART_INTR_RX_NOT_EMPTY    | \
                                             comm_RS485_UART_INTR_RX_FULL         | \
                                             comm_RS485_UART_INTR_RX_OVERFLOW     | \
                                             comm_RS485_UART_INTR_RX_UNDERFLOW    | \
                                             comm_RS485_UART_INTR_RX_BLOCKED      | \
                                             comm_RS485_UART_INTR_RX_FRAME_ERROR  | \
                                             comm_RS485_UART_INTR_RX_PARITY_ERROR | \
                                             comm_RS485_UART_INTR_RX_BAUD_DETECT  | \
                                             comm_RS485_UART_INTR_RX_BREAK_DETECT)

/* General usage HW definitions */
#define comm_RS485_UART_ONE_BYTE_WIDTH (8u)   /* Number of bits in one byte           */
#define comm_RS485_UART_FIFO_SIZE      (8u)   /* Size of TX or RX FIFO: defined by HW */
#define comm_RS485_UART_EZBUFFER_SIZE  (32u)  /* EZ Buffer size: defined by HW        */

/* I2C and EZI2C slave address defines */
#define comm_RS485_UART_I2C_SLAVE_ADDR_POS    (0x01u)    /* 7-bit address shift */
#define comm_RS485_UART_I2C_SLAVE_ADDR_MASK   (0xFEu)    /* 8-bit address mask */

/* OVS constants for IrDA Low Power operation */
#define comm_RS485_UART_CTRL_OVS_IRDA_LP_OVS16     (0x00u)
#define comm_RS485_UART_CTRL_OVS_IRDA_LP_OVS32     (0x01u)
#define comm_RS485_UART_CTRL_OVS_IRDA_LP_OVS48     (0x02u)
#define comm_RS485_UART_CTRL_OVS_IRDA_LP_OVS96     (0x03u)
#define comm_RS485_UART_CTRL_OVS_IRDA_LP_OVS192    (0x04u)
#define comm_RS485_UART_CTRL_OVS_IRDA_LP_OVS768    (0x05u)
#define comm_RS485_UART_CTRL_OVS_IRDA_LP_OVS1536   (0x06u)

/* OVS constant for IrDA */
#define comm_RS485_UART_CTRL_OVS_IRDA_OVS16        (comm_RS485_UART_UART_IRDA_LP_OVS16)


/***************************************
*    Common Macro Definitions
***************************************/

/* Re-enables the SCB IP. A clear enable bit has a different effect
* on the scb IP depending on the version:
*  CY_SCBIP_V0: resets state, status, TX and RX FIFOs.
*  CY_SCBIP_V1 or later: resets state, status, TX and RX FIFOs and interrupt sources.
*/
#define comm_RS485_UART_SCB_SW_RESET \
                        do{           \
                            comm_RS485_UART_CTRL_REG &= ((uint32) ~comm_RS485_UART_CTRL_ENABLED); \
                            comm_RS485_UART_CTRL_REG |= ((uint32)  comm_RS485_UART_CTRL_ENABLED); \
                        }while(0)

/* TX FIFO macro */
#define comm_RS485_UART_CLEAR_TX_FIFO \
                            do{        \
                                comm_RS485_UART_TX_FIFO_CTRL_REG |= ((uint32)  comm_RS485_UART_TX_FIFO_CTRL_CLEAR); \
                                comm_RS485_UART_TX_FIFO_CTRL_REG &= ((uint32) ~comm_RS485_UART_TX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define comm_RS485_UART_GET_TX_FIFO_ENTRIES    (comm_RS485_UART_TX_FIFO_STATUS_REG & \
                                                 comm_RS485_UART_TX_FIFO_STATUS_USED_MASK)

#define comm_RS485_UART_GET_TX_FIFO_SR_VALID   ((0u != (comm_RS485_UART_TX_FIFO_STATUS_REG & \
                                                         comm_RS485_UART_TX_FIFO_SR_VALID)) ? (1u) : (0u))

/* RX FIFO macro */
#define comm_RS485_UART_CLEAR_RX_FIFO \
                            do{        \
                                comm_RS485_UART_RX_FIFO_CTRL_REG |= ((uint32)  comm_RS485_UART_RX_FIFO_CTRL_CLEAR); \
                                comm_RS485_UART_RX_FIFO_CTRL_REG &= ((uint32) ~comm_RS485_UART_RX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define comm_RS485_UART_GET_RX_FIFO_ENTRIES    (comm_RS485_UART_RX_FIFO_STATUS_REG & \
                                                    comm_RS485_UART_RX_FIFO_STATUS_USED_MASK)

#define comm_RS485_UART_GET_RX_FIFO_SR_VALID   ((0u != (comm_RS485_UART_RX_FIFO_STATUS_REG & \
                                                         comm_RS485_UART_RX_FIFO_SR_VALID)) ? (1u) : (0u))

/* Write interrupt source: set sourceMask bits in comm_RS485_UART_INTR_X_MASK_REG */
#define comm_RS485_UART_WRITE_INTR_I2C_EC_MASK(sourceMask) \
                                                do{         \
                                                    comm_RS485_UART_INTR_I2C_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#if (!comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_WRITE_INTR_SPI_EC_MASK(sourceMask) \
                                                do{         \
                                                    comm_RS485_UART_INTR_SPI_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!comm_RS485_UART_CY_SCBIP_V1) */

#define comm_RS485_UART_WRITE_INTR_MASTER_MASK(sourceMask) \
                                                do{         \
                                                    comm_RS485_UART_INTR_MASTER_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define comm_RS485_UART_WRITE_INTR_SLAVE_MASK(sourceMask)  \
                                                do{         \
                                                    comm_RS485_UART_INTR_SLAVE_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define comm_RS485_UART_WRITE_INTR_TX_MASK(sourceMask)     \
                                                do{         \
                                                    comm_RS485_UART_INTR_TX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define comm_RS485_UART_WRITE_INTR_RX_MASK(sourceMask)     \
                                                do{         \
                                                    comm_RS485_UART_INTR_RX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Enable interrupt source: set sourceMask bits in comm_RS485_UART_INTR_X_MASK_REG */
#define comm_RS485_UART_ENABLE_INTR_I2C_EC(sourceMask) \
                                                do{     \
                                                    comm_RS485_UART_INTR_I2C_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)
#if (!comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_ENABLE_INTR_SPI_EC(sourceMask) \
                                                do{     \
                                                    comm_RS485_UART_INTR_SPI_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!comm_RS485_UART_CY_SCBIP_V1) */

#define comm_RS485_UART_ENABLE_INTR_MASTER(sourceMask) \
                                                do{     \
                                                    comm_RS485_UART_INTR_MASTER_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define comm_RS485_UART_ENABLE_INTR_SLAVE(sourceMask)  \
                                                do{     \
                                                    comm_RS485_UART_INTR_SLAVE_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define comm_RS485_UART_ENABLE_INTR_TX(sourceMask)     \
                                                do{     \
                                                    comm_RS485_UART_INTR_TX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define comm_RS485_UART_ENABLE_INTR_RX(sourceMask)     \
                                                do{     \
                                                    comm_RS485_UART_INTR_RX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

/* Disable interrupt source: clear sourceMask bits in comm_RS485_UART_INTR_X_MASK_REG */
#define comm_RS485_UART_DISABLE_INTR_I2C_EC(sourceMask) \
                                do{                      \
                                    comm_RS485_UART_INTR_I2C_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#if (!comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_DISABLE_INTR_SPI_EC(sourceMask) \
                                do{                      \
                                    comm_RS485_UART_INTR_SPI_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)
#endif /* (!comm_RS485_UART_CY_SCBIP_V1) */

#define comm_RS485_UART_DISABLE_INTR_MASTER(sourceMask) \
                                do{                      \
                                comm_RS485_UART_INTR_MASTER_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define comm_RS485_UART_DISABLE_INTR_SLAVE(sourceMask) \
                                do{                     \
                                    comm_RS485_UART_INTR_SLAVE_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define comm_RS485_UART_DISABLE_INTR_TX(sourceMask)    \
                                do{                     \
                                    comm_RS485_UART_INTR_TX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)

#define comm_RS485_UART_DISABLE_INTR_RX(sourceMask)    \
                                do{                     \
                                    comm_RS485_UART_INTR_RX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

/* Set interrupt sources: write sourceMask bits in comm_RS485_UART_INTR_X_SET_REG */
#define comm_RS485_UART_SET_INTR_MASTER(sourceMask)    \
                                                do{     \
                                                    comm_RS485_UART_INTR_MASTER_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define comm_RS485_UART_SET_INTR_SLAVE(sourceMask) \
                                                do{ \
                                                    comm_RS485_UART_INTR_SLAVE_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define comm_RS485_UART_SET_INTR_TX(sourceMask)    \
                                                do{ \
                                                    comm_RS485_UART_INTR_TX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define comm_RS485_UART_SET_INTR_RX(sourceMask)    \
                                                do{ \
                                                    comm_RS485_UART_INTR_RX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Clear interrupt sources: write sourceMask bits in comm_RS485_UART_INTR_X_REG */
#define comm_RS485_UART_CLEAR_INTR_I2C_EC(sourceMask)  \
                                                do{     \
                                                    comm_RS485_UART_INTR_I2C_EC_REG = (uint32) (sourceMask); \
                                                }while(0)

#if (!comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_CLEAR_INTR_SPI_EC(sourceMask)  \
                                                do{     \
                                                    comm_RS485_UART_INTR_SPI_EC_REG = (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!comm_RS485_UART_CY_SCBIP_V1) */

#define comm_RS485_UART_CLEAR_INTR_MASTER(sourceMask)  \
                                                do{     \
                                                    comm_RS485_UART_INTR_MASTER_REG = (uint32) (sourceMask); \
                                                }while(0)

#define comm_RS485_UART_CLEAR_INTR_SLAVE(sourceMask)   \
                                                do{     \
                                                    comm_RS485_UART_INTR_SLAVE_REG  = (uint32) (sourceMask); \
                                                }while(0)

#define comm_RS485_UART_CLEAR_INTR_TX(sourceMask)      \
                                                do{     \
                                                    comm_RS485_UART_INTR_TX_REG     = (uint32) (sourceMask); \
                                                }while(0)

#define comm_RS485_UART_CLEAR_INTR_RX(sourceMask)      \
                                                do{     \
                                                    comm_RS485_UART_INTR_RX_REG     = (uint32) (sourceMask); \
                                                }while(0)

/* Return true if sourceMask is set in comm_RS485_UART_INTR_CAUSE_REG */
#define comm_RS485_UART_CHECK_CAUSE_INTR(sourceMask)    (0u != (comm_RS485_UART_INTR_CAUSE_REG & (sourceMask)))

/* Return true if sourceMask is set in INTR_X_MASKED_REG */
#define comm_RS485_UART_CHECK_INTR_I2C_EC(sourceMask)  (0u != (comm_RS485_UART_INTR_I2C_EC_REG & (sourceMask)))
#if (!comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_CHECK_INTR_SPI_EC(sourceMask)  (0u != (comm_RS485_UART_INTR_SPI_EC_REG & (sourceMask)))
#endif /* (!comm_RS485_UART_CY_SCBIP_V1) */
#define comm_RS485_UART_CHECK_INTR_MASTER(sourceMask)  (0u != (comm_RS485_UART_INTR_MASTER_REG & (sourceMask)))
#define comm_RS485_UART_CHECK_INTR_SLAVE(sourceMask)   (0u != (comm_RS485_UART_INTR_SLAVE_REG  & (sourceMask)))
#define comm_RS485_UART_CHECK_INTR_TX(sourceMask)      (0u != (comm_RS485_UART_INTR_TX_REG     & (sourceMask)))
#define comm_RS485_UART_CHECK_INTR_RX(sourceMask)      (0u != (comm_RS485_UART_INTR_RX_REG     & (sourceMask)))

/* Return true if sourceMask is set in comm_RS485_UART_INTR_X_MASKED_REG */
#define comm_RS485_UART_CHECK_INTR_I2C_EC_MASKED(sourceMask)   (0u != (comm_RS485_UART_INTR_I2C_EC_MASKED_REG & \
                                                                       (sourceMask)))
#if (!comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_CHECK_INTR_SPI_EC_MASKED(sourceMask)   (0u != (comm_RS485_UART_INTR_SPI_EC_MASKED_REG & \
                                                                       (sourceMask)))
#endif /* (!comm_RS485_UART_CY_SCBIP_V1) */
#define comm_RS485_UART_CHECK_INTR_MASTER_MASKED(sourceMask)   (0u != (comm_RS485_UART_INTR_MASTER_MASKED_REG & \
                                                                       (sourceMask)))
#define comm_RS485_UART_CHECK_INTR_SLAVE_MASKED(sourceMask)    (0u != (comm_RS485_UART_INTR_SLAVE_MASKED_REG  & \
                                                                       (sourceMask)))
#define comm_RS485_UART_CHECK_INTR_TX_MASKED(sourceMask)       (0u != (comm_RS485_UART_INTR_TX_MASKED_REG     & \
                                                                       (sourceMask)))
#define comm_RS485_UART_CHECK_INTR_RX_MASKED(sourceMask)       (0u != (comm_RS485_UART_INTR_RX_MASKED_REG     & \
                                                                       (sourceMask)))

/* Return true if sourceMask is set in comm_RS485_UART_CTRL_REG: generally is used to check enable bit */
#define comm_RS485_UART_GET_CTRL_ENABLED    (0u != (comm_RS485_UART_CTRL_REG & comm_RS485_UART_CTRL_ENABLED))

#define comm_RS485_UART_CHECK_SLAVE_AUTO_ADDR_NACK     (0u != (comm_RS485_UART_I2C_CTRL_REG & \
                                                                comm_RS485_UART_I2C_CTRL_S_NOT_READY_DATA_NACK))


/***************************************
*      I2C Macro Definitions
***************************************/

/* Enable auto ACK/NACK */
#define comm_RS485_UART_ENABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                      \
                                comm_RS485_UART_I2C_CTRL_REG |= comm_RS485_UART_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define comm_RS485_UART_ENABLE_SLAVE_AUTO_DATA_ACK \
                            do{                     \
                                comm_RS485_UART_I2C_CTRL_REG |= comm_RS485_UART_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define comm_RS485_UART_ENABLE_SLAVE_AUTO_DATA_NACK \
                            do{                      \
                                comm_RS485_UART_I2C_CTRL_REG |= comm_RS485_UART_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define comm_RS485_UART_ENABLE_MASTER_AUTO_DATA_ACK \
                            do{                      \
                                comm_RS485_UART_I2C_CTRL_REG |= comm_RS485_UART_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define comm_RS485_UART_ENABLE_MASTER_AUTO_DATA_NACK \
                            do{                       \
                                comm_RS485_UART_I2C_CTRL_REG |= comm_RS485_UART_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Disable auto ACK/NACK */
#define comm_RS485_UART_DISABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                       \
                                comm_RS485_UART_I2C_CTRL_REG &= ~comm_RS485_UART_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define comm_RS485_UART_DISABLE_SLAVE_AUTO_DATA_ACK \
                            do{                      \
                                comm_RS485_UART_I2C_CTRL_REG &= ~comm_RS485_UART_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define comm_RS485_UART_DISABLE_SLAVE_AUTO_DATA_NACK \
                            do{                       \
                                comm_RS485_UART_I2C_CTRL_REG &= ~comm_RS485_UART_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define comm_RS485_UART_DISABLE_MASTER_AUTO_DATA_ACK \
                            do{                       \
                                comm_RS485_UART_I2C_CTRL_REG &= ~comm_RS485_UART_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define comm_RS485_UART_DISABLE_MASTER_AUTO_DATA_NACK \
                            do{                        \
                                comm_RS485_UART_I2C_CTRL_REG &= ~comm_RS485_UART_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Enable Slave autoACK/NACK Data */
#define comm_RS485_UART_ENABLE_SLAVE_AUTO_DATA \
                            do{                 \
                                comm_RS485_UART_I2C_CTRL_REG |= (comm_RS485_UART_I2C_CTRL_S_READY_DATA_ACK |      \
                                                                  comm_RS485_UART_I2C_CTRL_S_NOT_READY_DATA_NACK); \
                            }while(0)

/* Disable Slave autoACK/NACK Data */
#define comm_RS485_UART_DISABLE_SLAVE_AUTO_DATA \
                            do{                  \
                                comm_RS485_UART_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(comm_RS485_UART_I2C_CTRL_S_READY_DATA_ACK |       \
                                                                    comm_RS485_UART_I2C_CTRL_S_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Disable Master autoACK/NACK Data */
#define comm_RS485_UART_DISABLE_MASTER_AUTO_DATA \
                            do{                   \
                                comm_RS485_UART_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(comm_RS485_UART_I2C_CTRL_M_READY_DATA_ACK |       \
                                                                    comm_RS485_UART_I2C_CTRL_M_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Master commands */
#define comm_RS485_UART_I2C_MASTER_GENERATE_START \
                            do{                    \
                                comm_RS485_UART_I2C_MASTER_CMD_REG = comm_RS485_UART_I2C_MASTER_CMD_M_START_ON_IDLE; \
                            }while(0)

#define comm_RS485_UART_I2C_MASTER_CLEAR_START \
                            do{                 \
                                comm_RS485_UART_I2C_MASTER_CMD_REG =  ((uint32) 0u); \
                            }while(0)

#define comm_RS485_UART_I2C_MASTER_GENERATE_RESTART comm_RS485_UART_I2CReStartGeneration()

#define comm_RS485_UART_I2C_MASTER_GENERATE_STOP \
                            do{                   \
                                comm_RS485_UART_I2C_MASTER_CMD_REG =                                            \
                                    (comm_RS485_UART_I2C_MASTER_CMD_M_STOP |                                    \
                                        (comm_RS485_UART_CHECK_I2C_STATUS(comm_RS485_UART_I2C_STATUS_M_READ) ? \
                                            (comm_RS485_UART_I2C_MASTER_CMD_M_NACK) : (0u)));                   \
                            }while(0)

#define comm_RS485_UART_I2C_MASTER_GENERATE_ACK \
                            do{                  \
                                comm_RS485_UART_I2C_MASTER_CMD_REG = comm_RS485_UART_I2C_MASTER_CMD_M_ACK; \
                            }while(0)

#define comm_RS485_UART_I2C_MASTER_GENERATE_NACK \
                            do{                   \
                                comm_RS485_UART_I2C_MASTER_CMD_REG = comm_RS485_UART_I2C_MASTER_CMD_M_NACK; \
                            }while(0)

/* Slave commands */
#define comm_RS485_UART_I2C_SLAVE_GENERATE_ACK \
                            do{                 \
                                comm_RS485_UART_I2C_SLAVE_CMD_REG = comm_RS485_UART_I2C_SLAVE_CMD_S_ACK; \
                            }while(0)

#if (comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1)
    /* Slave NACK generation for EC_AM logic on address phase. Ticket ID #183902 */
    void comm_RS485_UART_I2CSlaveNackGeneration(void);
    #define comm_RS485_UART_I2C_SLAVE_GENERATE_NACK comm_RS485_UART_I2CSlaveNackGeneration()

#else
    #define comm_RS485_UART_I2C_SLAVE_GENERATE_NACK \
                            do{                      \
                                comm_RS485_UART_I2C_SLAVE_CMD_REG = comm_RS485_UART_I2C_SLAVE_CMD_S_NACK; \
                            }while(0)
#endif /* (comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1) */

#define comm_RS485_UART_I2C_SLAVE_CLEAR_NACK \
                            do{               \
                                comm_RS485_UART_I2C_SLAVE_CMD_REG = 0u; \
                            }while(0)

/* Return 8-bit address. The input address should be 7-bits */
#define comm_RS485_UART_GET_I2C_8BIT_ADDRESS(addr) (((uint32) ((uint32) (addr) << \
                                                                    comm_RS485_UART_I2C_SLAVE_ADDR_POS)) & \
                                                                        comm_RS485_UART_I2C_SLAVE_ADDR_MASK)

#define comm_RS485_UART_GET_I2C_7BIT_ADDRESS(addr) ((uint32) (addr) >> comm_RS485_UART_I2C_SLAVE_ADDR_POS)

/* Adjust SDA filter Trim settings */
#define comm_RS485_UART_DEFAULT_I2C_CFG_SDA_FILT_TRIM  (0x02u)
#define comm_RS485_UART_EC_AM_I2C_CFG_SDA_FILT_TRIM    (0x03u)

#if (comm_RS485_UART_CY_SCBIP_V0)
    #define comm_RS485_UART_SET_I2C_CFG_SDA_FILT_TRIM(sdaTrim) \
        do{                                                 \
            comm_RS485_UART_I2C_CFG_REG =                  \
                            ((comm_RS485_UART_I2C_CFG_REG & (uint32) ~comm_RS485_UART_I2C_CFG_SDA_FILT_TRIM_MASK) | \
                             ((uint32) ((uint32) (sdaTrim) <<comm_RS485_UART_I2C_CFG_SDA_FILT_TRIM_POS)));           \
        }while(0)
#endif /* (comm_RS485_UART_CY_SCBIP_V0) */

/* Enable/Disable analog and digital filter */
#define comm_RS485_UART_DIGITAL_FILTER_DISABLE    (0u)
#define comm_RS485_UART_DIGITAL_FILTER_ENABLE     (1u)
#define comm_RS485_UART_I2C_DATA_RATE_FS_MODE_MAX (400u)
#if (comm_RS485_UART_CY_SCBIP_V0)
    /* comm_RS485_UART_I2C_CFG_SDA_FILT_OUT_ENABLED is disabled by default */
    #define comm_RS485_UART_I2C_CFG_FILT_MASK  (comm_RS485_UART_I2C_CFG_SDA_FILT_ENABLED | \
                                                 comm_RS485_UART_I2C_CFG_SCL_FILT_ENABLED)
#else
    /* comm_RS485_UART_I2C_CFG_SDA_OUT_FILT_SEL_MASK is disabled by default */
    #define comm_RS485_UART_I2C_CFG_FILT_MASK  (comm_RS485_UART_I2C_CFG_SDA_IN_FILT_SEL | \
                                                 comm_RS485_UART_I2C_CFG_SCL_IN_FILT_SEL)
#endif /* (comm_RS485_UART_CY_SCBIP_V0) */

#define comm_RS485_UART_I2C_CFG_ANALOG_FITER_DISABLE \
        do{                                           \
            comm_RS485_UART_I2C_CFG_REG &= (uint32) ~comm_RS485_UART_I2C_CFG_FILT_MASK; \
        }while(0)

#define comm_RS485_UART_I2C_CFG_ANALOG_FITER_ENABLE \
        do{                                          \
            comm_RS485_UART_I2C_CFG_REG |= (uint32)  comm_RS485_UART_I2C_CFG_FILT_MASK; \
        }while(0)

/* Return slave select number from SPI_CTRL register */
#define comm_RS485_UART_GET_SPI_CTRL_SS(activeSelect) (((uint32) ((uint32) (activeSelect) << \
                                                                    comm_RS485_UART_SPI_CTRL_SLAVE_SELECT_POS)) & \
                                                                        comm_RS485_UART_SPI_CTRL_SLAVE_SELECT_MASK)

/* Return true if bit is set in comm_RS485_UART_I2C_STATUS_REG */
#define comm_RS485_UART_CHECK_I2C_STATUS(sourceMask)   (0u != (comm_RS485_UART_I2C_STATUS_REG & (sourceMask)))

/* Return true if bit is set in comm_RS485_UART_SPI_STATUS_REG */
#define comm_RS485_UART_CHECK_SPI_STATUS(sourceMask)   (0u != (comm_RS485_UART_SPI_STATUS_REG & (sourceMask)))

/* Return FIFO size depends on comm_RS485_UART_CTRL_BYTE_MODE bit */
#define comm_RS485_UART_GET_FIFO_SIZE(condition) ((0u != (condition)) ? \
                                                    (2u * comm_RS485_UART_FIFO_SIZE) : (comm_RS485_UART_FIFO_SIZE))


/***************************************
*       Get Macros Definitions
***************************************/

/* comm_RS485_UART_CTRL */
#define comm_RS485_UART_GET_CTRL_OVS(oversample)       (((uint32) (oversample) - 1u) & comm_RS485_UART_CTRL_OVS_MASK)

#define comm_RS485_UART_GET_CTRL_EC_OP_MODE(opMode)        ((0u != (opMode)) ? \
                                                                (comm_RS485_UART_CTRL_EC_OP_MODE)  : (0u))

#define comm_RS485_UART_GET_CTRL_EC_AM_MODE(amMode)        ((0u != (amMode)) ? \
                                                                (comm_RS485_UART_CTRL_EC_AM_MODE)  : (0u))

#define comm_RS485_UART_GET_CTRL_BLOCK(block)              ((0u != (block))  ? \
                                                                (comm_RS485_UART_CTRL_BLOCK)       : (0u))

#define comm_RS485_UART_GET_CTRL_ADDR_ACCEPT(acceptAddr)   ((0u != (acceptAddr)) ? \
                                                                (comm_RS485_UART_CTRL_ADDR_ACCEPT) : (0u))

#if (comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_GET_CTRL_BYTE_MODE(mode)   (0u)
#else
    #define comm_RS485_UART_GET_CTRL_BYTE_MODE(mode)   ((0u != (mode)) ? \
                                                            (comm_RS485_UART_CTRL_BYTE_MODE) : (0u))
#endif /* (comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1) */

/* comm_RS485_UART_I2C_CTRL */
#define comm_RS485_UART_GET_I2C_CTRL_HIGH_PHASE_OVS(oversampleHigh) (((uint32) (oversampleHigh) - 1u) & \
                                                                        comm_RS485_UART_I2C_CTRL_HIGH_PHASE_OVS_MASK)

#define comm_RS485_UART_GET_I2C_CTRL_LOW_PHASE_OVS(oversampleLow)  ((((uint32) (oversampleLow) - 1u) << \
                                                                    comm_RS485_UART_I2C_CTRL_LOW_PHASE_OVS_POS) &  \
                                                                    comm_RS485_UART_I2C_CTRL_LOW_PHASE_OVS_MASK)

#define comm_RS485_UART_GET_I2C_CTRL_S_NOT_READY_ADDR_NACK(wakeNack) ((0u != (wakeNack)) ? \
                                                            (comm_RS485_UART_I2C_CTRL_S_NOT_READY_ADDR_NACK) : (0u))

#define comm_RS485_UART_GET_I2C_CTRL_SL_MSTR_MODE(mode)    ((uint32)(mode) << comm_RS485_UART_I2C_CTRL_SLAVE_MODE_POS)

/* comm_RS485_UART_SPI_CTRL */
#define comm_RS485_UART_GET_SPI_CTRL_CONTINUOUS(separate)  ((0u != (separate)) ? \
                                                                (comm_RS485_UART_SPI_CTRL_CONTINUOUS) : (0u))

#define comm_RS485_UART_GET_SPI_CTRL_SELECT_PRECEDE(mode)  ((0u != (mode)) ? \
                                                                      (comm_RS485_UART_SPI_CTRL_SELECT_PRECEDE) : (0u))

#define comm_RS485_UART_GET_SPI_CTRL_SCLK_MODE(mode)       (((uint32) (mode) << \
                                                                        comm_RS485_UART_SPI_CTRL_CPHA_POS) & \
                                                                        comm_RS485_UART_SPI_CTRL_SCLK_MODE_MASK)

#define comm_RS485_UART_GET_SPI_CTRL_LATE_MISO_SAMPLE(lateMiso) ((0u != (lateMiso)) ? \
                                                                    (comm_RS485_UART_SPI_CTRL_LATE_MISO_SAMPLE) : (0u))

#if (comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_GET_SPI_CTRL_SCLK_CONTINUOUS(sclkType) (0u)
    #define comm_RS485_UART_GET_SPI_CTRL_SSEL_POLARITY(polarity)   (0u)
#else
    #define comm_RS485_UART_GET_SPI_CTRL_SCLK_CONTINUOUS(sclkType) ((0u != (sclkType)) ? \
                                                                    (comm_RS485_UART_SPI_CTRL_SCLK_CONTINUOUS) : (0u))

    #define comm_RS485_UART_GET_SPI_CTRL_SSEL_POLARITY(polarity)   (((uint32) (polarity) << \
                                                                     comm_RS485_UART_SPI_CTRL_SSEL0_POLARITY_POS) & \
                                                                     comm_RS485_UART_SPI_CTRL_SSEL_POLARITY_MASK)
#endif /* ((comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1) */

#define comm_RS485_UART_GET_SPI_CTRL_SUB_MODE(mode)        (((uint32) (mode) << comm_RS485_UART_SPI_CTRL_MODE_POS) & \
                                                                                 comm_RS485_UART_SPI_CTRL_MODE_MASK)

#define comm_RS485_UART_GET_SPI_CTRL_SLAVE_SELECT(select)  (((uint32) (select) << \
                                                                      comm_RS485_UART_SPI_CTRL_SLAVE_SELECT_POS) & \
                                                                      comm_RS485_UART_SPI_CTRL_SLAVE_SELECT_MASK)

#define comm_RS485_UART_GET_SPI_CTRL_MASTER_MODE(mode)     ((0u != (mode)) ? \
                                                                (comm_RS485_UART_SPI_CTRL_MASTER) : (0u))

/* comm_RS485_UART_UART_CTRL */
#define comm_RS485_UART_GET_UART_CTRL_MODE(mode)           (((uint32) (mode) << \
                                                                            comm_RS485_UART_UART_CTRL_MODE_POS) & \
                                                                            comm_RS485_UART_UART_CTRL_MODE_MASK)

/* comm_RS485_UART_UART_RX_CTRL */
#define comm_RS485_UART_GET_UART_RX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                        comm_RS485_UART_UART_RX_CTRL_STOP_BITS_MASK)

#define comm_RS485_UART_GET_UART_RX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                                    (comm_RS485_UART_UART_RX_CTRL_PARITY) : (0u))

#define comm_RS485_UART_GET_UART_RX_CTRL_POLARITY(polarity)    ((0u != (polarity)) ? \
                                                                    (comm_RS485_UART_UART_RX_CTRL_POLARITY) : (0u))

#define comm_RS485_UART_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (comm_RS485_UART_UART_RX_CTRL_DROP_ON_PARITY_ERR) : (0u))

#define comm_RS485_UART_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (comm_RS485_UART_UART_RX_CTRL_DROP_ON_FRAME_ERR) : (0u))

#define comm_RS485_UART_GET_UART_RX_CTRL_MP_MODE(mpMode)   ((0u != (mpMode)) ? \
                                                        (comm_RS485_UART_UART_RX_CTRL_MP_MODE) : (0u))

/* comm_RS485_UART_UART_TX_CTRL */
#define comm_RS485_UART_GET_UART_TX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                comm_RS485_UART_UART_RX_CTRL_STOP_BITS_MASK)

#define comm_RS485_UART_GET_UART_TX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                               (comm_RS485_UART_UART_TX_CTRL_PARITY) : (0u))

#define comm_RS485_UART_GET_UART_TX_CTRL_RETRY_NACK(nack)  ((0u != (nack)) ? \
                                                               (comm_RS485_UART_UART_TX_CTRL_RETRY_ON_NACK) : (0u))

/* comm_RS485_UART_UART_FLOW_CTRL */
#if !(comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(level)   ( (uint32) (level) & \
                                                                 comm_RS485_UART_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK)

    #define comm_RS485_UART_GET_UART_FLOW_CTRL_RTS_POLARITY(polarity) ((0u != (polarity)) ? \
                                                                (comm_RS485_UART_UART_FLOW_CTRL_RTS_POLARITY) : (0u))

    #define comm_RS485_UART_GET_UART_FLOW_CTRL_CTS_POLARITY(polarity) ((0u != (polarity)) ? \
                                                                (comm_RS485_UART_UART_FLOW_CTRL_CTS_POLARITY) : (0u))

    #define comm_RS485_UART_GET_UART_FLOW_CTRL_CTS_ENABLE(ctsEn)      ((0u != (ctsEn)) ? \
                                                                (comm_RS485_UART_UART_FLOW_CTRL_CTS_ENABLE) : (0u))
#endif /* !(comm_RS485_UART_CY_SCBIP_V0 || comm_RS485_UART_CY_SCBIP_V1) */

/* comm_RS485_UART_RX_CTRL */
#define comm_RS485_UART_GET_RX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                comm_RS485_UART_RX_CTRL_DATA_WIDTH_MASK)

#define comm_RS485_UART_GET_RX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (comm_RS485_UART_RX_CTRL_MSB_FIRST) : (0u))

#define comm_RS485_UART_GET_RX_CTRL_MEDIAN(filterEn)       ((0u != (filterEn)) ? \
                                                                (comm_RS485_UART_RX_CTRL_MEDIAN) : (0u))

/* comm_RS485_UART_RX_MATCH */
#define comm_RS485_UART_GET_RX_MATCH_ADDR(addr)    ((uint32) (addr) & comm_RS485_UART_RX_MATCH_ADDR_MASK)
#define comm_RS485_UART_GET_RX_MATCH_MASK(mask)    (((uint32) (mask) << \
                                                            comm_RS485_UART_RX_MATCH_MASK_POS) & \
                                                            comm_RS485_UART_RX_MATCH_MASK_MASK)

/* comm_RS485_UART_RX_FIFO_CTRL */
#define comm_RS485_UART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    comm_RS485_UART_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* comm_RS485_UART_TX_CTRL */
#define comm_RS485_UART_GET_TX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                comm_RS485_UART_RX_CTRL_DATA_WIDTH_MASK)

#define comm_RS485_UART_GET_TX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (comm_RS485_UART_TX_CTRL_MSB_FIRST) : (0u))

/* comm_RS485_UART_TX_FIFO_CTRL */
#define comm_RS485_UART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    comm_RS485_UART_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* Clear register constants for configuration and interrupt mask */
#define comm_RS485_UART_CLEAR_REG          ((uint32) (0u))
#define comm_RS485_UART_NO_INTR_SOURCES    ((uint32) (0u))
#define comm_RS485_UART_DUMMY_PARAM        ((uint32) (0u))
#define comm_RS485_UART_SUBMODE_SPI_SLAVE  ((uint32) (0u))

/* Return in case of I2C read error */
#define comm_RS485_UART_I2C_INVALID_BYTE   ((uint32) 0xFFFFFFFFu)
#define comm_RS485_UART_CHECK_VALID_BYTE   ((uint32) 0x80000000u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define comm_RS485_UART_CHECK_INTR_EC_I2C(sourceMask)  comm_RS485_UART_CHECK_INTR_I2C_EC(sourceMask)
#if (!comm_RS485_UART_CY_SCBIP_V1)
    #define comm_RS485_UART_CHECK_INTR_EC_SPI(sourceMask)  comm_RS485_UART_CHECK_INTR_SPI_EC(sourceMask)
#endif /* (!comm_RS485_UART_CY_SCBIP_V1) */

#define comm_RS485_UART_CY_SCBIP_V1_I2C_ONLY   (comm_RS485_UART_CY_SCBIP_V1)

#endif /* (CY_SCB_comm_RS485_UART_H) */


/* [] END OF FILE */
