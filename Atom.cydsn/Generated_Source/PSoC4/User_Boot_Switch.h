/*******************************************************************************
* File Name: User_Boot_Switch.h  
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

#if !defined(CY_PINS_User_Boot_Switch_H) /* Pins User_Boot_Switch_H */
#define CY_PINS_User_Boot_Switch_H

#include "cytypes.h"
#include "cyfitter.h"
#include "User_Boot_Switch_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    User_Boot_Switch_Write(uint8 value) ;
void    User_Boot_Switch_SetDriveMode(uint8 mode) ;
uint8   User_Boot_Switch_ReadDataReg(void) ;
uint8   User_Boot_Switch_Read(void) ;
uint8   User_Boot_Switch_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define User_Boot_Switch_DRIVE_MODE_BITS        (3)
#define User_Boot_Switch_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - User_Boot_Switch_DRIVE_MODE_BITS))

#define User_Boot_Switch_DM_ALG_HIZ         (0x00u)
#define User_Boot_Switch_DM_DIG_HIZ         (0x01u)
#define User_Boot_Switch_DM_RES_UP          (0x02u)
#define User_Boot_Switch_DM_RES_DWN         (0x03u)
#define User_Boot_Switch_DM_OD_LO           (0x04u)
#define User_Boot_Switch_DM_OD_HI           (0x05u)
#define User_Boot_Switch_DM_STRONG          (0x06u)
#define User_Boot_Switch_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define User_Boot_Switch_MASK               User_Boot_Switch__MASK
#define User_Boot_Switch_SHIFT              User_Boot_Switch__SHIFT
#define User_Boot_Switch_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define User_Boot_Switch_PS                     (* (reg32 *) User_Boot_Switch__PS)
/* Port Configuration */
#define User_Boot_Switch_PC                     (* (reg32 *) User_Boot_Switch__PC)
/* Data Register */
#define User_Boot_Switch_DR                     (* (reg32 *) User_Boot_Switch__DR)
/* Input Buffer Disable Override */
#define User_Boot_Switch_INP_DIS                (* (reg32 *) User_Boot_Switch__PC2)


#if defined(User_Boot_Switch__INTSTAT)  /* Interrupt Registers */

    #define User_Boot_Switch_INTSTAT                (* (reg32 *) User_Boot_Switch__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define User_Boot_Switch_DRIVE_MODE_SHIFT       (0x00u)
#define User_Boot_Switch_DRIVE_MODE_MASK        (0x07u << User_Boot_Switch_DRIVE_MODE_SHIFT)


#endif /* End Pins User_Boot_Switch_H */


/* [] END OF FILE */
