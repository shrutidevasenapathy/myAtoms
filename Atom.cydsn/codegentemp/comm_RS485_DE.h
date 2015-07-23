/*******************************************************************************
* File Name: comm_RS485_DE.h  
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

#if !defined(CY_PINS_comm_RS485_DE_H) /* Pins comm_RS485_DE_H */
#define CY_PINS_comm_RS485_DE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "comm_RS485_DE_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    comm_RS485_DE_Write(uint8 value) ;
void    comm_RS485_DE_SetDriveMode(uint8 mode) ;
uint8   comm_RS485_DE_ReadDataReg(void) ;
uint8   comm_RS485_DE_Read(void) ;
uint8   comm_RS485_DE_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define comm_RS485_DE_DRIVE_MODE_BITS        (3)
#define comm_RS485_DE_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - comm_RS485_DE_DRIVE_MODE_BITS))

#define comm_RS485_DE_DM_ALG_HIZ         (0x00u)
#define comm_RS485_DE_DM_DIG_HIZ         (0x01u)
#define comm_RS485_DE_DM_RES_UP          (0x02u)
#define comm_RS485_DE_DM_RES_DWN         (0x03u)
#define comm_RS485_DE_DM_OD_LO           (0x04u)
#define comm_RS485_DE_DM_OD_HI           (0x05u)
#define comm_RS485_DE_DM_STRONG          (0x06u)
#define comm_RS485_DE_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define comm_RS485_DE_MASK               comm_RS485_DE__MASK
#define comm_RS485_DE_SHIFT              comm_RS485_DE__SHIFT
#define comm_RS485_DE_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define comm_RS485_DE_PS                     (* (reg32 *) comm_RS485_DE__PS)
/* Port Configuration */
#define comm_RS485_DE_PC                     (* (reg32 *) comm_RS485_DE__PC)
/* Data Register */
#define comm_RS485_DE_DR                     (* (reg32 *) comm_RS485_DE__DR)
/* Input Buffer Disable Override */
#define comm_RS485_DE_INP_DIS                (* (reg32 *) comm_RS485_DE__PC2)


#if defined(comm_RS485_DE__INTSTAT)  /* Interrupt Registers */

    #define comm_RS485_DE_INTSTAT                (* (reg32 *) comm_RS485_DE__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define comm_RS485_DE_DRIVE_MODE_SHIFT       (0x00u)
#define comm_RS485_DE_DRIVE_MODE_MASK        (0x07u << comm_RS485_DE_DRIVE_MODE_SHIFT)


#endif /* End Pins comm_RS485_DE_H */


/* [] END OF FILE */
