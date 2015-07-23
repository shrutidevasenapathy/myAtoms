/*******************************************************************************
* File Name: ON1_DIR2.h  
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

#if !defined(CY_PINS_ON1_DIR2_H) /* Pins ON1_DIR2_H */
#define CY_PINS_ON1_DIR2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ON1_DIR2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ON1_DIR2_Write(uint8 value) ;
void    ON1_DIR2_SetDriveMode(uint8 mode) ;
uint8   ON1_DIR2_ReadDataReg(void) ;
uint8   ON1_DIR2_Read(void) ;
uint8   ON1_DIR2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ON1_DIR2_DRIVE_MODE_BITS        (3)
#define ON1_DIR2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ON1_DIR2_DRIVE_MODE_BITS))

#define ON1_DIR2_DM_ALG_HIZ         (0x00u)
#define ON1_DIR2_DM_DIG_HIZ         (0x01u)
#define ON1_DIR2_DM_RES_UP          (0x02u)
#define ON1_DIR2_DM_RES_DWN         (0x03u)
#define ON1_DIR2_DM_OD_LO           (0x04u)
#define ON1_DIR2_DM_OD_HI           (0x05u)
#define ON1_DIR2_DM_STRONG          (0x06u)
#define ON1_DIR2_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define ON1_DIR2_MASK               ON1_DIR2__MASK
#define ON1_DIR2_SHIFT              ON1_DIR2__SHIFT
#define ON1_DIR2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ON1_DIR2_PS                     (* (reg32 *) ON1_DIR2__PS)
/* Port Configuration */
#define ON1_DIR2_PC                     (* (reg32 *) ON1_DIR2__PC)
/* Data Register */
#define ON1_DIR2_DR                     (* (reg32 *) ON1_DIR2__DR)
/* Input Buffer Disable Override */
#define ON1_DIR2_INP_DIS                (* (reg32 *) ON1_DIR2__PC2)


#if defined(ON1_DIR2__INTSTAT)  /* Interrupt Registers */

    #define ON1_DIR2_INTSTAT                (* (reg32 *) ON1_DIR2__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define ON1_DIR2_DRIVE_MODE_SHIFT       (0x00u)
#define ON1_DIR2_DRIVE_MODE_MASK        (0x07u << ON1_DIR2_DRIVE_MODE_SHIFT)


#endif /* End Pins ON1_DIR2_H */


/* [] END OF FILE */
