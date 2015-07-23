/*******************************************************************************
* File Name: Green_Led.h  
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

#if !defined(CY_PINS_Green_Led_H) /* Pins Green_Led_H */
#define CY_PINS_Green_Led_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Green_Led_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Green_Led_Write(uint8 value) ;
void    Green_Led_SetDriveMode(uint8 mode) ;
uint8   Green_Led_ReadDataReg(void) ;
uint8   Green_Led_Read(void) ;
uint8   Green_Led_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Green_Led_DRIVE_MODE_BITS        (3)
#define Green_Led_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Green_Led_DRIVE_MODE_BITS))

#define Green_Led_DM_ALG_HIZ         (0x00u)
#define Green_Led_DM_DIG_HIZ         (0x01u)
#define Green_Led_DM_RES_UP          (0x02u)
#define Green_Led_DM_RES_DWN         (0x03u)
#define Green_Led_DM_OD_LO           (0x04u)
#define Green_Led_DM_OD_HI           (0x05u)
#define Green_Led_DM_STRONG          (0x06u)
#define Green_Led_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Green_Led_MASK               Green_Led__MASK
#define Green_Led_SHIFT              Green_Led__SHIFT
#define Green_Led_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Green_Led_PS                     (* (reg32 *) Green_Led__PS)
/* Port Configuration */
#define Green_Led_PC                     (* (reg32 *) Green_Led__PC)
/* Data Register */
#define Green_Led_DR                     (* (reg32 *) Green_Led__DR)
/* Input Buffer Disable Override */
#define Green_Led_INP_DIS                (* (reg32 *) Green_Led__PC2)


#if defined(Green_Led__INTSTAT)  /* Interrupt Registers */

    #define Green_Led_INTSTAT                (* (reg32 *) Green_Led__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Green_Led_DRIVE_MODE_SHIFT       (0x00u)
#define Green_Led_DRIVE_MODE_MASK        (0x07u << Green_Led_DRIVE_MODE_SHIFT)


#endif /* End Pins Green_Led_H */


/* [] END OF FILE */
