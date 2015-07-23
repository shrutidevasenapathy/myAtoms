/*******************************************************************************
* File Name: comm_RS485_Timeout.h
* Version 1.0
*
* Description:
*  This header file contains registers and constants associated with the
*  Count7 component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_COUNT7_comm_RS485_Timeout_H)
#define CY_COUNT7_comm_RS485_Timeout_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
* Function Prototypes
***************************************/
void  comm_RS485_Timeout_Init(void) ;
void  comm_RS485_Timeout_Enable(void) ;
void  comm_RS485_Timeout_Start(void) ;
void  comm_RS485_Timeout_Stop(void) ;
void  comm_RS485_Timeout_WriteCounter(uint8 count) ;
uint8 comm_RS485_Timeout_ReadCounter(void) ;
void  comm_RS485_Timeout_WritePeriod(uint8 period) ;
uint8 comm_RS485_Timeout_ReadPeriod(void) ;
void  comm_RS485_Timeout_SaveConfig(void) ;
void  comm_RS485_Timeout_RestoreConfig(void) ;
void  comm_RS485_Timeout_Sleep(void) ;
void  comm_RS485_Timeout_Wakeup(void) ;


/***************************************
*     Data Struct Definitions
***************************************/
/* Structure to save registers before go to sleep */
typedef struct
{
    uint8 enableState;
    uint8 count;
} comm_RS485_Timeout_BACKUP_STRUCT;


/***************************************
*           Global Variables
***************************************/
extern comm_RS485_Timeout_BACKUP_STRUCT comm_RS485_Timeout_backup;
extern uint8 comm_RS485_Timeout_initVar;


/***************************************
* Initial Parameter
***************************************/
#define comm_RS485_Timeout_INITIAL_PERIOD               (100u)


/***************************************
* Registers
***************************************/
#define comm_RS485_Timeout_COUNT_REG                    (*(reg8 *) comm_RS485_Timeout_Counter7__COUNT_REG)
#define comm_RS485_Timeout_COUNT_PTR                    ( (reg8 *) comm_RS485_Timeout_Counter7__COUNT_REG)
#define comm_RS485_Timeout_PERIOD_REG                   (*(reg8 *) comm_RS485_Timeout_Counter7__PERIOD_REG)
#define comm_RS485_Timeout_PERIOD_PTR                   ( (reg8 *) comm_RS485_Timeout_Counter7__PERIOD_REG)
#define comm_RS485_Timeout_AUX_CONTROL_REG              (*(reg8 *) comm_RS485_Timeout_Counter7__CONTROL_AUX_CTL_REG)
#define comm_RS485_Timeout_AUX_CONTROL_PTR              ( (reg8 *) comm_RS485_Timeout_Counter7__CONTROL_AUX_CTL_REG)


/***************************************
* Register Constants
***************************************/
#define comm_RS485_Timeout_COUNTER_START                (0x20u)

/* This constant is used to mask the TC bit (bit#7) in the Count register */
#define comm_RS485_Timeout_COUNT_7BIT_MASK              (0x7Fu)


#endif /* CY_COUNT7_comm_RS485_Timeout_H */


/* [] END OF FILE */
