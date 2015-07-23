/*******************************************************************************
* File Name: BUTTON.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_BUTTON_H) /* Pins BUTTON_H */
#define CY_PINS_BUTTON_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BUTTON_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    BUTTON_Write(uint8 value) ;
void    BUTTON_SetDriveMode(uint8 mode) ;
uint8   BUTTON_ReadDataReg(void) ;
uint8   BUTTON_Read(void) ;
uint8   BUTTON_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define BUTTON_DRIVE_MODE_BITS        (3)
#define BUTTON_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BUTTON_DRIVE_MODE_BITS))

#define BUTTON_DM_ALG_HIZ         (0x00u)
#define BUTTON_DM_DIG_HIZ         (0x01u)
#define BUTTON_DM_RES_UP          (0x02u)
#define BUTTON_DM_RES_DWN         (0x03u)
#define BUTTON_DM_OD_LO           (0x04u)
#define BUTTON_DM_OD_HI           (0x05u)
#define BUTTON_DM_STRONG          (0x06u)
#define BUTTON_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define BUTTON_MASK               BUTTON__MASK
#define BUTTON_SHIFT              BUTTON__SHIFT
#define BUTTON_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BUTTON_PS                     (* (reg32 *) BUTTON__PS)
/* Port Configuration */
#define BUTTON_PC                     (* (reg32 *) BUTTON__PC)
/* Data Register */
#define BUTTON_DR                     (* (reg32 *) BUTTON__DR)
/* Input Buffer Disable Override */
#define BUTTON_INP_DIS                (* (reg32 *) BUTTON__PC2)


#if defined(BUTTON__INTSTAT)  /* Interrupt Registers */

    #define BUTTON_INTSTAT                (* (reg32 *) BUTTON__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define BUTTON_DRIVE_MODE_SHIFT       (0x00u)
#define BUTTON_DRIVE_MODE_MASK        (0x07u << BUTTON_DRIVE_MODE_SHIFT)


#endif /* End Pins BUTTON_H */


/* [] END OF FILE */
