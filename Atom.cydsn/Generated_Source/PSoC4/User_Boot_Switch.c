/*******************************************************************************
* File Name: User_Boot_Switch.c  
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
#include "User_Boot_Switch.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        User_Boot_Switch_PC =   (User_Boot_Switch_PC & \
                                (uint32)(~(uint32)(User_Boot_Switch_DRIVE_MODE_IND_MASK << (User_Boot_Switch_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (User_Boot_Switch_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: User_Boot_Switch_Write
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
void User_Boot_Switch_Write(uint8 value) 
{
    uint8 drVal = (uint8)(User_Boot_Switch_DR & (uint8)(~User_Boot_Switch_MASK));
    drVal = (drVal | ((uint8)(value << User_Boot_Switch_SHIFT) & User_Boot_Switch_MASK));
    User_Boot_Switch_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: User_Boot_Switch_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  User_Boot_Switch_DM_STRONG     Strong Drive 
*  User_Boot_Switch_DM_OD_HI      Open Drain, Drives High 
*  User_Boot_Switch_DM_OD_LO      Open Drain, Drives Low 
*  User_Boot_Switch_DM_RES_UP     Resistive Pull Up 
*  User_Boot_Switch_DM_RES_DWN    Resistive Pull Down 
*  User_Boot_Switch_DM_RES_UPDWN  Resistive Pull Up/Down 
*  User_Boot_Switch_DM_DIG_HIZ    High Impedance Digital 
*  User_Boot_Switch_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void User_Boot_Switch_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(User_Boot_Switch__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: User_Boot_Switch_Read
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
*  Macro User_Boot_Switch_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 User_Boot_Switch_Read(void) 
{
    return (uint8)((User_Boot_Switch_PS & User_Boot_Switch_MASK) >> User_Boot_Switch_SHIFT);
}


/*******************************************************************************
* Function Name: User_Boot_Switch_ReadDataReg
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
uint8 User_Boot_Switch_ReadDataReg(void) 
{
    return (uint8)((User_Boot_Switch_DR & User_Boot_Switch_MASK) >> User_Boot_Switch_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(User_Boot_Switch_INTSTAT) 

    /*******************************************************************************
    * Function Name: User_Boot_Switch_ClearInterrupt
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
    uint8 User_Boot_Switch_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(User_Boot_Switch_INTSTAT & User_Boot_Switch_MASK);
		User_Boot_Switch_INTSTAT = maskedStatus;
        return maskedStatus >> User_Boot_Switch_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
