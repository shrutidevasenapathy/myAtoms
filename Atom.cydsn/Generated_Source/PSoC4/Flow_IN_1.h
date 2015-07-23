/*******************************************************************************
* File Name: Flow_IN_1.h  
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

#if !defined(CY_PINS_Flow_IN_1_H) /* Pins Flow_IN_1_H */
#define CY_PINS_Flow_IN_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Flow_IN_1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Flow_IN_1_Write(uint8 value) ;
void    Flow_IN_1_SetDriveMode(uint8 mode) ;
uint8   Flow_IN_1_ReadDataReg(void) ;
uint8   Flow_IN_1_Read(void) ;
uint8   Flow_IN_1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Flow_IN_1_DRIVE_MODE_BITS        (3)
#define Flow_IN_1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Flow_IN_1_DRIVE_MODE_BITS))

#define Flow_IN_1_DM_ALG_HIZ         (0x00u)
#define Flow_IN_1_DM_DIG_HIZ         (0x01u)
#define Flow_IN_1_DM_RES_UP          (0x02u)
#define Flow_IN_1_DM_RES_DWN         (0x03u)
#define Flow_IN_1_DM_OD_LO           (0x04u)
#define Flow_IN_1_DM_OD_HI           (0x05u)
#define Flow_IN_1_DM_STRONG          (0x06u)
#define Flow_IN_1_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Flow_IN_1_MASK               Flow_IN_1__MASK
#define Flow_IN_1_SHIFT              Flow_IN_1__SHIFT
#define Flow_IN_1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Flow_IN_1_PS                     (* (reg32 *) Flow_IN_1__PS)
/* Port Configuration */
#define Flow_IN_1_PC                     (* (reg32 *) Flow_IN_1__PC)
/* Data Register */
#define Flow_IN_1_DR                     (* (reg32 *) Flow_IN_1__DR)
/* Input Buffer Disable Override */
#define Flow_IN_1_INP_DIS                (* (reg32 *) Flow_IN_1__PC2)


#if defined(Flow_IN_1__INTSTAT)  /* Interrupt Registers */

    #define Flow_IN_1_INTSTAT                (* (reg32 *) Flow_IN_1__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Flow_IN_1_DRIVE_MODE_SHIFT       (0x00u)
#define Flow_IN_1_DRIVE_MODE_MASK        (0x07u << Flow_IN_1_DRIVE_MODE_SHIFT)


#endif /* End Pins Flow_IN_1_H */


/* [] END OF FILE */
