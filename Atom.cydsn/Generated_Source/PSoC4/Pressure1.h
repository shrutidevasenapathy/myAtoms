/*******************************************************************************
* File Name: Pressure1.h  
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

#if !defined(CY_PINS_Pressure1_H) /* Pins Pressure1_H */
#define CY_PINS_Pressure1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pressure1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pressure1_Write(uint8 value) ;
void    Pressure1_SetDriveMode(uint8 mode) ;
uint8   Pressure1_ReadDataReg(void) ;
uint8   Pressure1_Read(void) ;
uint8   Pressure1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pressure1_DRIVE_MODE_BITS        (3)
#define Pressure1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pressure1_DRIVE_MODE_BITS))

#define Pressure1_DM_ALG_HIZ         (0x00u)
#define Pressure1_DM_DIG_HIZ         (0x01u)
#define Pressure1_DM_RES_UP          (0x02u)
#define Pressure1_DM_RES_DWN         (0x03u)
#define Pressure1_DM_OD_LO           (0x04u)
#define Pressure1_DM_OD_HI           (0x05u)
#define Pressure1_DM_STRONG          (0x06u)
#define Pressure1_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Pressure1_MASK               Pressure1__MASK
#define Pressure1_SHIFT              Pressure1__SHIFT
#define Pressure1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pressure1_PS                     (* (reg32 *) Pressure1__PS)
/* Port Configuration */
#define Pressure1_PC                     (* (reg32 *) Pressure1__PC)
/* Data Register */
#define Pressure1_DR                     (* (reg32 *) Pressure1__DR)
/* Input Buffer Disable Override */
#define Pressure1_INP_DIS                (* (reg32 *) Pressure1__PC2)


#if defined(Pressure1__INTSTAT)  /* Interrupt Registers */

    #define Pressure1_INTSTAT                (* (reg32 *) Pressure1__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Pressure1_DRIVE_MODE_SHIFT       (0x00u)
#define Pressure1_DRIVE_MODE_MASK        (0x07u << Pressure1_DRIVE_MODE_SHIFT)


#endif /* End Pins Pressure1_H */


/* [] END OF FILE */
