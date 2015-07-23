/*******************************************************************************
* File Name: Pressure1.c  
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
#include "Pressure1.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Pressure1_PC =   (Pressure1_PC & \
                                (uint32)(~(uint32)(Pressure1_DRIVE_MODE_IND_MASK << (Pressure1_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Pressure1_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Pressure1_Write
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
void Pressure1_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Pressure1_DR & (uint8)(~Pressure1_MASK));
    drVal = (drVal | ((uint8)(value << Pressure1_SHIFT) & Pressure1_MASK));
    Pressure1_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Pressure1_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Pressure1_DM_STRONG     Strong Drive 
*  Pressure1_DM_OD_HI      Open Drain, Drives High 
*  Pressure1_DM_OD_LO      Open Drain, Drives Low 
*  Pressure1_DM_RES_UP     Resistive Pull Up 
*  Pressure1_DM_RES_DWN    Resistive Pull Down 
*  Pressure1_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Pressure1_DM_DIG_HIZ    High Impedance Digital 
*  Pressure1_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Pressure1_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Pressure1__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Pressure1_Read
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
*  Macro Pressure1_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pressure1_Read(void) 
{
    return (uint8)((Pressure1_PS & Pressure1_MASK) >> Pressure1_SHIFT);
}


/*******************************************************************************
* Function Name: Pressure1_ReadDataReg
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
uint8 Pressure1_ReadDataReg(void) 
{
    return (uint8)((Pressure1_DR & Pressure1_MASK) >> Pressure1_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pressure1_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pressure1_ClearInterrupt
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
    uint8 Pressure1_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Pressure1_INTSTAT & Pressure1_MASK);
		Pressure1_INTSTAT = maskedStatus;
        return maskedStatus >> Pressure1_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
