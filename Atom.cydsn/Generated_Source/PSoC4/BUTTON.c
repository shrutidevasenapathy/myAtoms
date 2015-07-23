/*******************************************************************************
* File Name: BUTTON.c  
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
#include "BUTTON.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        BUTTON_PC =   (BUTTON_PC & \
                                (uint32)(~(uint32)(BUTTON_DRIVE_MODE_IND_MASK << (BUTTON_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (BUTTON_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: BUTTON_Write
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
void BUTTON_Write(uint8 value) 
{
    uint8 drVal = (uint8)(BUTTON_DR & (uint8)(~BUTTON_MASK));
    drVal = (drVal | ((uint8)(value << BUTTON_SHIFT) & BUTTON_MASK));
    BUTTON_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: BUTTON_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  BUTTON_DM_STRONG     Strong Drive 
*  BUTTON_DM_OD_HI      Open Drain, Drives High 
*  BUTTON_DM_OD_LO      Open Drain, Drives Low 
*  BUTTON_DM_RES_UP     Resistive Pull Up 
*  BUTTON_DM_RES_DWN    Resistive Pull Down 
*  BUTTON_DM_RES_UPDWN  Resistive Pull Up/Down 
*  BUTTON_DM_DIG_HIZ    High Impedance Digital 
*  BUTTON_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void BUTTON_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(BUTTON__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: BUTTON_Read
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
*  Macro BUTTON_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 BUTTON_Read(void) 
{
    return (uint8)((BUTTON_PS & BUTTON_MASK) >> BUTTON_SHIFT);
}


/*******************************************************************************
* Function Name: BUTTON_ReadDataReg
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
uint8 BUTTON_ReadDataReg(void) 
{
    return (uint8)((BUTTON_DR & BUTTON_MASK) >> BUTTON_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(BUTTON_INTSTAT) 

    /*******************************************************************************
    * Function Name: BUTTON_ClearInterrupt
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
    uint8 BUTTON_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(BUTTON_INTSTAT & BUTTON_MASK);
		BUTTON_INTSTAT = maskedStatus;
        return maskedStatus >> BUTTON_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
