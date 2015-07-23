/*******************************************************************************
* File Name: ButtonClock.h
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

#if !defined(CY_CLOCK_ButtonClock_H)
#define CY_CLOCK_ButtonClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void ButtonClock_StartEx(uint32 alignClkDiv);
#define ButtonClock_Start() \
    ButtonClock_StartEx(ButtonClock__PA_DIV_ID)

#else

void ButtonClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void ButtonClock_Stop(void);

void ButtonClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 ButtonClock_GetDividerRegister(void);
uint8  ButtonClock_GetFractionalDividerRegister(void);

#define ButtonClock_Enable()                         ButtonClock_Start()
#define ButtonClock_Disable()                        ButtonClock_Stop()
#define ButtonClock_SetDividerRegister(clkDivider, reset)  \
    ButtonClock_SetFractionalDividerRegister((clkDivider), 0u)
#define ButtonClock_SetDivider(clkDivider)           ButtonClock_SetDividerRegister((clkDivider), 1u)
#define ButtonClock_SetDividerValue(clkDivider)      ButtonClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define ButtonClock_DIV_ID     ButtonClock__DIV_ID

#define ButtonClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define ButtonClock_CTRL_REG   (*(reg32 *)ButtonClock__CTRL_REGISTER)
#define ButtonClock_DIV_REG    (*(reg32 *)ButtonClock__DIV_REGISTER)

#define ButtonClock_CMD_DIV_SHIFT          (0u)
#define ButtonClock_CMD_PA_DIV_SHIFT       (8u)
#define ButtonClock_CMD_DISABLE_SHIFT      (30u)
#define ButtonClock_CMD_ENABLE_SHIFT       (31u)

#define ButtonClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << ButtonClock_CMD_DISABLE_SHIFT))
#define ButtonClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << ButtonClock_CMD_ENABLE_SHIFT))

#define ButtonClock_DIV_FRAC_MASK  (0x000000F8u)
#define ButtonClock_DIV_FRAC_SHIFT (3u)
#define ButtonClock_DIV_INT_MASK   (0xFFFFFF00u)
#define ButtonClock_DIV_INT_SHIFT  (8u)

#else 

#define ButtonClock_DIV_REG        (*(reg32 *)ButtonClock__REGISTER)
#define ButtonClock_ENABLE_REG     ButtonClock_DIV_REG
#define ButtonClock_DIV_FRAC_MASK  ButtonClock__FRAC_MASK
#define ButtonClock_DIV_FRAC_SHIFT (16u)
#define ButtonClock_DIV_INT_MASK   ButtonClock__DIVIDER_MASK
#define ButtonClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_ButtonClock_H) */

/* [] END OF FILE */
