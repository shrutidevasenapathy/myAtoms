/*******************************************************************************
* File Name: ON1_DIR1.h  
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

#if !defined(CY_PINS_ON1_DIR1_H) /* Pins ON1_DIR1_H */
#define CY_PINS_ON1_DIR1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ON1_DIR1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ON1_DIR1_Write(uint8 value) ;
void    ON1_DIR1_SetDriveMode(uint8 mode) ;
uint8   ON1_DIR1_ReadDataReg(void) ;
uint8   ON1_DIR1_Read(void) ;
uint8   ON1_DIR1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ON1_DIR1_DRIVE_MODE_BITS        (3)
#define ON1_DIR1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ON1_DIR1_DRIVE_MODE_BITS))

#define ON1_DIR1_DM_ALG_HIZ         (0x00u)
#define ON1_DIR1_DM_DIG_HIZ         (0x01u)
#define ON1_DIR1_DM_RES_UP          (0x02u)
#define ON1_DIR1_DM_RES_DWN         (0x03u)
#define ON1_DIR1_DM_OD_LO           (0x04u)
#define ON1_DIR1_DM_OD_HI           (0x05u)
#define ON1_DIR1_DM_STRONG          (0x06u)
#define ON1_DIR1_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define ON1_DIR1_MASK               ON1_DIR1__MASK
#define ON1_DIR1_SHIFT              ON1_DIR1__SHIFT
#define ON1_DIR1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ON1_DIR1_PS                     (* (reg32 *) ON1_DIR1__PS)
/* Port Configuration */
#define ON1_DIR1_PC                     (* (reg32 *) ON1_DIR1__PC)
/* Data Register */
#define ON1_DIR1_DR                     (* (reg32 *) ON1_DIR1__DR)
/* Input Buffer Disable Override */
#define ON1_DIR1_INP_DIS                (* (reg32 *) ON1_DIR1__PC2)


#if defined(ON1_DIR1__INTSTAT)  /* Interrupt Registers */

    #define ON1_DIR1_INTSTAT                (* (reg32 *) ON1_DIR1__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define ON1_DIR1_DRIVE_MODE_SHIFT       (0x00u)
#define ON1_DIR1_DRIVE_MODE_MASK        (0x07u << ON1_DIR1_DRIVE_MODE_SHIFT)


#endif /* End Pins ON1_DIR1_H */


/* [] END OF FILE */
