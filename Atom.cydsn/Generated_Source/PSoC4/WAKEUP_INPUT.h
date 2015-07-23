/*******************************************************************************
* File Name: WAKEUP_INPUT.h  
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

#if !defined(CY_PINS_WAKEUP_INPUT_H) /* Pins WAKEUP_INPUT_H */
#define CY_PINS_WAKEUP_INPUT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "WAKEUP_INPUT_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    WAKEUP_INPUT_Write(uint8 value) ;
void    WAKEUP_INPUT_SetDriveMode(uint8 mode) ;
uint8   WAKEUP_INPUT_ReadDataReg(void) ;
uint8   WAKEUP_INPUT_Read(void) ;
uint8   WAKEUP_INPUT_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define WAKEUP_INPUT_DRIVE_MODE_BITS        (3)
#define WAKEUP_INPUT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - WAKEUP_INPUT_DRIVE_MODE_BITS))

#define WAKEUP_INPUT_DM_ALG_HIZ         (0x00u)
#define WAKEUP_INPUT_DM_DIG_HIZ         (0x01u)
#define WAKEUP_INPUT_DM_RES_UP          (0x02u)
#define WAKEUP_INPUT_DM_RES_DWN         (0x03u)
#define WAKEUP_INPUT_DM_OD_LO           (0x04u)
#define WAKEUP_INPUT_DM_OD_HI           (0x05u)
#define WAKEUP_INPUT_DM_STRONG          (0x06u)
#define WAKEUP_INPUT_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define WAKEUP_INPUT_MASK               WAKEUP_INPUT__MASK
#define WAKEUP_INPUT_SHIFT              WAKEUP_INPUT__SHIFT
#define WAKEUP_INPUT_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WAKEUP_INPUT_PS                     (* (reg32 *) WAKEUP_INPUT__PS)
/* Port Configuration */
#define WAKEUP_INPUT_PC                     (* (reg32 *) WAKEUP_INPUT__PC)
/* Data Register */
#define WAKEUP_INPUT_DR                     (* (reg32 *) WAKEUP_INPUT__DR)
/* Input Buffer Disable Override */
#define WAKEUP_INPUT_INP_DIS                (* (reg32 *) WAKEUP_INPUT__PC2)


#if defined(WAKEUP_INPUT__INTSTAT)  /* Interrupt Registers */

    #define WAKEUP_INPUT_INTSTAT                (* (reg32 *) WAKEUP_INPUT__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define WAKEUP_INPUT_DRIVE_MODE_SHIFT       (0x00u)
#define WAKEUP_INPUT_DRIVE_MODE_MASK        (0x07u << WAKEUP_INPUT_DRIVE_MODE_SHIFT)


#endif /* End Pins WAKEUP_INPUT_H */


/* [] END OF FILE */
