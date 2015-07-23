/*******************************************************************************
* File Name: comm_RS485_Timeout_PM.c
* Version 1.0
*
* Description:
*  This file provides Low power mode APIs for Count7 component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "comm_RS485_Timeout.h"


comm_RS485_Timeout_BACKUP_STRUCT comm_RS485_Timeout_backup;


/*******************************************************************************
* Function Name: comm_RS485_Timeout_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component configuration and non-retention registers.
*  This function is called by the Count7_Sleep() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  comm_RS485_Timeout_backup - used to save component configuration and non-
*  retention registers before enter sleep mode.
*
*******************************************************************************/
void comm_RS485_Timeout_SaveConfig(void) 
{
    comm_RS485_Timeout_backup.count = comm_RS485_Timeout_COUNT_REG;
}


/*******************************************************************************
* Function Name: comm_RS485_Timeout_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for low power mode
*  operation. The Count7_Sleep() API saves the current component state using
*  Count7_SaveConfig() and disables the counter.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void comm_RS485_Timeout_Sleep(void) 
{
    if(0u != (comm_RS485_Timeout_AUX_CONTROL_REG & comm_RS485_Timeout_COUNTER_START))
    {
        comm_RS485_Timeout_backup.enableState = 1u;
        comm_RS485_Timeout_Stop();
    }
    else
    {
        comm_RS485_Timeout_backup.enableState = 0u;
    }

    comm_RS485_Timeout_SaveConfig();
}


/*******************************************************************************
* Function Name: comm_RS485_Timeout_RestoreConfig
********************************************************************************
*
* Summary:
*  This function restores the component configuration and non-retention
*  registers. This function is called by the Count7_Wakeup() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  comm_RS485_Timeout_backup - used to save component configuration and
*  non-retention registers before exit sleep mode.
*
*******************************************************************************/
void comm_RS485_Timeout_RestoreConfig(void) 
{
    comm_RS485_Timeout_COUNT_REG = comm_RS485_Timeout_backup.count;
}


/*******************************************************************************
* Function Name: comm_RS485_Timeout_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when
*  Count7_Sleep() was called. The Count7_Wakeup() function calls the
*  Count7_RestoreConfig() function to restore the configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void comm_RS485_Timeout_Wakeup(void) 
{
    comm_RS485_Timeout_RestoreConfig();

    /* Restore enable state */
    if (comm_RS485_Timeout_backup.enableState != 0u)
    {
        comm_RS485_Timeout_Enable();
    }
}


/* [] END OF FILE */
