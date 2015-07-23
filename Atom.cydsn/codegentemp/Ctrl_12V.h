/*******************************************************************************
* File Name: Ctrl_12V.h  
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

#if !defined(CY_PINS_Ctrl_12V_H) /* Pins Ctrl_12V_H */
#define CY_PINS_Ctrl_12V_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Ctrl_12V_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Ctrl_12V_Write(uint8 value) ;
void    Ctrl_12V_SetDriveMode(uint8 mode) ;
uint8   Ctrl_12V_ReadDataReg(void) ;
uint8   Ctrl_12V_Read(void) ;
uint8   Ctrl_12V_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Ctrl_12V_DRIVE_MODE_BITS        (3)
#define Ctrl_12V_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Ctrl_12V_DRIVE_MODE_BITS))

#define Ctrl_12V_DM_ALG_HIZ         (0x00u)
#define Ctrl_12V_DM_DIG_HIZ         (0x01u)
#define Ctrl_12V_DM_RES_UP          (0x02u)
#define Ctrl_12V_DM_RES_DWN         (0x03u)
#define Ctrl_12V_DM_OD_LO           (0x04u)
#define Ctrl_12V_DM_OD_HI           (0x05u)
#define Ctrl_12V_DM_STRONG          (0x06u)
#define Ctrl_12V_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Ctrl_12V_MASK               Ctrl_12V__MASK
#define Ctrl_12V_SHIFT              Ctrl_12V__SHIFT
#define Ctrl_12V_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Ctrl_12V_PS                     (* (reg32 *) Ctrl_12V__PS)
/* Port Configuration */
#define Ctrl_12V_PC                     (* (reg32 *) Ctrl_12V__PC)
/* Data Register */
#define Ctrl_12V_DR                     (* (reg32 *) Ctrl_12V__DR)
/* Input Buffer Disable Override */
#define Ctrl_12V_INP_DIS                (* (reg32 *) Ctrl_12V__PC2)


#if defined(Ctrl_12V__INTSTAT)  /* Interrupt Registers */

    #define Ctrl_12V_INTSTAT                (* (reg32 *) Ctrl_12V__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Ctrl_12V_DRIVE_MODE_SHIFT       (0x00u)
#define Ctrl_12V_DRIVE_MODE_MASK        (0x07u << Ctrl_12V_DRIVE_MODE_SHIFT)


#endif /* End Pins Ctrl_12V_H */


/* [] END OF FILE */
