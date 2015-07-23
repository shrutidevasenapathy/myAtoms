/*******************************************************************************
* File Name: comm_RS485_isr_Timeout.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_comm_RS485_isr_Timeout_H)
#define CY_ISR_comm_RS485_isr_Timeout_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void comm_RS485_isr_Timeout_Start(void);
void comm_RS485_isr_Timeout_StartEx(cyisraddress address);
void comm_RS485_isr_Timeout_Stop(void);

CY_ISR_PROTO(comm_RS485_isr_Timeout_Interrupt);

void comm_RS485_isr_Timeout_SetVector(cyisraddress address);
cyisraddress comm_RS485_isr_Timeout_GetVector(void);

void comm_RS485_isr_Timeout_SetPriority(uint8 priority);
uint8 comm_RS485_isr_Timeout_GetPriority(void);

void comm_RS485_isr_Timeout_Enable(void);
uint8 comm_RS485_isr_Timeout_GetState(void);
void comm_RS485_isr_Timeout_Disable(void);

void comm_RS485_isr_Timeout_SetPending(void);
void comm_RS485_isr_Timeout_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the comm_RS485_isr_Timeout ISR. */
#define comm_RS485_isr_Timeout_INTC_VECTOR            ((reg32 *) comm_RS485_isr_Timeout__INTC_VECT)

/* Address of the comm_RS485_isr_Timeout ISR priority. */
#define comm_RS485_isr_Timeout_INTC_PRIOR             ((reg32 *) comm_RS485_isr_Timeout__INTC_PRIOR_REG)

/* Priority of the comm_RS485_isr_Timeout interrupt. */
#define comm_RS485_isr_Timeout_INTC_PRIOR_NUMBER      comm_RS485_isr_Timeout__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable comm_RS485_isr_Timeout interrupt. */
#define comm_RS485_isr_Timeout_INTC_SET_EN            ((reg32 *) comm_RS485_isr_Timeout__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the comm_RS485_isr_Timeout interrupt. */
#define comm_RS485_isr_Timeout_INTC_CLR_EN            ((reg32 *) comm_RS485_isr_Timeout__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the comm_RS485_isr_Timeout interrupt state to pending. */
#define comm_RS485_isr_Timeout_INTC_SET_PD            ((reg32 *) comm_RS485_isr_Timeout__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the comm_RS485_isr_Timeout interrupt. */
#define comm_RS485_isr_Timeout_INTC_CLR_PD            ((reg32 *) comm_RS485_isr_Timeout__INTC_CLR_PD_REG)



#endif /* CY_ISR_comm_RS485_isr_Timeout_H */


/* [] END OF FILE */
