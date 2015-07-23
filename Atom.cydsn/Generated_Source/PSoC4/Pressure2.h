/*******************************************************************************
* File Name: Pressure2.h  
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

#if !defined(CY_PINS_Pressure2_H) /* Pins Pressure2_H */
#define CY_PINS_Pressure2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pressure2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pressure2_Write(uint8 value) ;
void    Pressure2_SetDriveMode(uint8 mode) ;
uint8   Pressure2_ReadDataReg(void) ;
uint8   Pressure2_Read(void) ;
uint8   Pressure2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pressure2_DRIVE_MODE_BITS        (3)
#define Pressure2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pressure2_DRIVE_MODE_BITS))

#define Pressure2_DM_ALG_HIZ         (0x00u)
#define Pressure2_DM_DIG_HIZ         (0x01u)
#define Pressure2_DM_RES_UP          (0x02u)
#define Pressure2_DM_RES_DWN         (0x03u)
#define Pressure2_DM_OD_LO           (0x04u)
#define Pressure2_DM_OD_HI           (0x05u)
#define Pressure2_DM_STRONG          (0x06u)
#define Pressure2_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Pressure2_MASK               Pressure2__MASK
#define Pressure2_SHIFT              Pressure2__SHIFT
#define Pressure2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pressure2_PS                     (* (reg32 *) Pressure2__PS)
/* Port Configuration */
#define Pressure2_PC                     (* (reg32 *) Pressure2__PC)
/* Data Register */
#define Pressure2_DR                     (* (reg32 *) Pressure2__DR)
/* Input Buffer Disable Override */
#define Pressure2_INP_DIS                (* (reg32 *) Pressure2__PC2)


#if defined(Pressure2__INTSTAT)  /* Interrupt Registers */

    #define Pressure2_INTSTAT                (* (reg32 *) Pressure2__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Pressure2_DRIVE_MODE_SHIFT       (0x00u)
#define Pressure2_DRIVE_MODE_MASK        (0x07u << Pressure2_DRIVE_MODE_SHIFT)


#endif /* End Pins Pressure2_H */


/* [] END OF FILE */
