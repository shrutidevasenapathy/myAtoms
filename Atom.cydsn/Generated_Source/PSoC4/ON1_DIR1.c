/*******************************************************************************
* File Name: ON1_DIR1.c  
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
#include "ON1_DIR1.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        ON1_DIR1_PC =   (ON1_DIR1_PC & \
                                (uint32)(~(uint32)(ON1_DIR1_DRIVE_MODE_IND_MASK << (ON1_DIR1_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (ON1_DIR1_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: ON1_DIR1_Write
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
void ON1_DIR1_Write(uint8 value) 
{
    uint8 drVal = (uint8)(ON1_DIR1_DR & (uint8)(~ON1_DIR1_MASK));
    drVal = (drVal | ((uint8)(value << ON1_DIR1_SHIFT) & ON1_DIR1_MASK));
    ON1_DIR1_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: ON1_DIR1_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  ON1_DIR1_DM_STRONG     Strong Drive 
*  ON1_DIR1_DM_OD_HI      Open Drain, Drives High 
*  ON1_DIR1_DM_OD_LO      Open Drain, Drives Low 
*  ON1_DIR1_DM_RES_UP     Resistive Pull Up 
*  ON1_DIR1_DM_RES_DWN    Resistive Pull Down 
*  ON1_DIR1_DM_RES_UPDWN  Resistive Pull Up/Down 
*  ON1_DIR1_DM_DIG_HIZ    High Impedance Digital 
*  ON1_DIR1_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void ON1_DIR1_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(ON1_DIR1__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: ON1_DIR1_Read
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
*  Macro ON1_DIR1_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ON1_DIR1_Read(void) 
{
    return (uint8)((ON1_DIR1_PS & ON1_DIR1_MASK) >> ON1_DIR1_SHIFT);
}


/*******************************************************************************
* Function Name: ON1_DIR1_ReadDataReg
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
uint8 ON1_DIR1_ReadDataReg(void) 
{
    return (uint8)((ON1_DIR1_DR & ON1_DIR1_MASK) >> ON1_DIR1_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ON1_DIR1_INTSTAT) 

    /*******************************************************************************
    * Function Name: ON1_DIR1_ClearInterrupt
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
    uint8 ON1_DIR1_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(ON1_DIR1_INTSTAT & ON1_DIR1_MASK);
		ON1_DIR1_INTSTAT = maskedStatus;
        return maskedStatus >> ON1_DIR1_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
