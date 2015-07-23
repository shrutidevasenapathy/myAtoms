/*******************************************************************************
* File Name: comm_RS485_WAKE.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "comm_RS485_WAKE.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        comm_RS485_WAKE_PC =   (comm_RS485_WAKE_PC & \
                                (uint32)(~(uint32)(comm_RS485_WAKE_DRIVE_MODE_IND_MASK << (comm_RS485_WAKE_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (comm_RS485_WAKE_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: comm_RS485_WAKE_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void comm_RS485_WAKE_Write(uint8 value) 
{
    uint8 drVal = (uint8)(comm_RS485_WAKE_DR & (uint8)(~comm_RS485_WAKE_MASK));
    drVal = (drVal | ((uint8)(value << comm_RS485_WAKE_SHIFT) & comm_RS485_WAKE_MASK));
    comm_RS485_WAKE_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: comm_RS485_WAKE_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  comm_RS485_WAKE_DM_STRONG     Strong Drive 
*  comm_RS485_WAKE_DM_OD_HI      Open Drain, Drives High 
*  comm_RS485_WAKE_DM_OD_LO      Open Drain, Drives Low 
*  comm_RS485_WAKE_DM_RES_UP     Resistive Pull Up 
*  comm_RS485_WAKE_DM_RES_DWN    Resistive Pull Down 
*  comm_RS485_WAKE_DM_RES_UPDWN  Resistive Pull Up/Down 
*  comm_RS485_WAKE_DM_DIG_HIZ    High Impedance Digital 
*  comm_RS485_WAKE_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void comm_RS485_WAKE_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(comm_RS485_WAKE__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: comm_RS485_WAKE_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro comm_RS485_WAKE_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 comm_RS485_WAKE_Read(void) 
{
    return (uint8)((comm_RS485_WAKE_PS & comm_RS485_WAKE_MASK) >> comm_RS485_WAKE_SHIFT);
}


/*******************************************************************************
* Function Name: comm_RS485_WAKE_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 comm_RS485_WAKE_ReadDataReg(void) 
{
    return (uint8)((comm_RS485_WAKE_DR & comm_RS485_WAKE_MASK) >> comm_RS485_WAKE_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(comm_RS485_WAKE_INTSTAT) 

    /*******************************************************************************
    * Function Name: comm_RS485_WAKE_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 comm_RS485_WAKE_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(comm_RS485_WAKE_INTSTAT & comm_RS485_WAKE_MASK);
		comm_RS485_WAKE_INTSTAT = maskedStatus;
        return maskedStatus >> comm_RS485_WAKE_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
