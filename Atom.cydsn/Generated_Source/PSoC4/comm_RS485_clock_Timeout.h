/*******************************************************************************
* File Name: comm_RS485_clock_Timeout.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_comm_RS485_clock_Timeout_H)
#define CY_CLOCK_comm_RS485_clock_Timeout_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void comm_RS485_clock_Timeout_StartEx(uint32 alignClkDiv);
#define comm_RS485_clock_Timeout_Start() \
    comm_RS485_clock_Timeout_StartEx(comm_RS485_clock_Timeout__PA_DIV_ID)

#else

void comm_RS485_clock_Timeout_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void comm_RS485_clock_Timeout_Stop(void);

void comm_RS485_clock_Timeout_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 comm_RS485_clock_Timeout_GetDividerRegister(void);
uint8  comm_RS485_clock_Timeout_GetFractionalDividerRegister(void);

#define comm_RS485_clock_Timeout_Enable()                         comm_RS485_clock_Timeout_Start()
#define comm_RS485_clock_Timeout_Disable()                        comm_RS485_clock_Timeout_Stop()
#define comm_RS485_clock_Timeout_SetDividerRegister(clkDivider, reset)  \
    comm_RS485_clock_Timeout_SetFractionalDividerRegister((clkDivider), 0u)
#define comm_RS485_clock_Timeout_SetDivider(clkDivider)           comm_RS485_clock_Timeout_SetDividerRegister((clkDivider), 1u)
#define comm_RS485_clock_Timeout_SetDividerValue(clkDivider)      comm_RS485_clock_Timeout_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define comm_RS485_clock_Timeout_DIV_ID     comm_RS485_clock_Timeout__DIV_ID

#define comm_RS485_clock_Timeout_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define comm_RS485_clock_Timeout_CTRL_REG   (*(reg32 *)comm_RS485_clock_Timeout__CTRL_REGISTER)
#define comm_RS485_clock_Timeout_DIV_REG    (*(reg32 *)comm_RS485_clock_Timeout__DIV_REGISTER)

#define comm_RS485_clock_Timeout_CMD_DIV_SHIFT          (0u)
#define comm_RS485_clock_Timeout_CMD_PA_DIV_SHIFT       (8u)
#define comm_RS485_clock_Timeout_CMD_DISABLE_SHIFT      (30u)
#define comm_RS485_clock_Timeout_CMD_ENABLE_SHIFT       (31u)

#define comm_RS485_clock_Timeout_CMD_DISABLE_MASK       ((uint32)((uint32)1u << comm_RS485_clock_Timeout_CMD_DISABLE_SHIFT))
#define comm_RS485_clock_Timeout_CMD_ENABLE_MASK        ((uint32)((uint32)1u << comm_RS485_clock_Timeout_CMD_ENABLE_SHIFT))

#define comm_RS485_clock_Timeout_DIV_FRAC_MASK  (0x000000F8u)
#define comm_RS485_clock_Timeout_DIV_FRAC_SHIFT (3u)
#define comm_RS485_clock_Timeout_DIV_INT_MASK   (0xFFFFFF00u)
#define comm_RS485_clock_Timeout_DIV_INT_SHIFT  (8u)

#else 

#define comm_RS485_clock_Timeout_DIV_REG        (*(reg32 *)comm_RS485_clock_Timeout__REGISTER)
#define comm_RS485_clock_Timeout_ENABLE_REG     comm_RS485_clock_Timeout_DIV_REG
#define comm_RS485_clock_Timeout_DIV_FRAC_MASK  comm_RS485_clock_Timeout__FRAC_MASK
#define comm_RS485_clock_Timeout_DIV_FRAC_SHIFT (16u)
#define comm_RS485_clock_Timeout_DIV_INT_MASK   comm_RS485_clock_Timeout__DIVIDER_MASK
#define comm_RS485_clock_Timeout_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_comm_RS485_clock_Timeout_H) */

/* [] END OF FILE */
