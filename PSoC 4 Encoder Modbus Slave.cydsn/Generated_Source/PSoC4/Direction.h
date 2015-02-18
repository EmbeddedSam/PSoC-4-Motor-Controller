/*******************************************************************************
* File Name: Direction.h  
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

#if !defined(CY_PINS_Direction_H) /* Pins Direction_H */
#define CY_PINS_Direction_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Direction_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Direction_Write(uint8 value) ;
void    Direction_SetDriveMode(uint8 mode) ;
uint8   Direction_ReadDataReg(void) ;
uint8   Direction_Read(void) ;
uint8   Direction_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Direction_DRIVE_MODE_BITS        (3)
#define Direction_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Direction_DRIVE_MODE_BITS))

#define Direction_DM_ALG_HIZ         (0x00u)
#define Direction_DM_DIG_HIZ         (0x01u)
#define Direction_DM_RES_UP          (0x02u)
#define Direction_DM_RES_DWN         (0x03u)
#define Direction_DM_OD_LO           (0x04u)
#define Direction_DM_OD_HI           (0x05u)
#define Direction_DM_STRONG          (0x06u)
#define Direction_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Direction_MASK               Direction__MASK
#define Direction_SHIFT              Direction__SHIFT
#define Direction_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Direction_PS                     (* (reg32 *) Direction__PS)
/* Port Configuration */
#define Direction_PC                     (* (reg32 *) Direction__PC)
/* Data Register */
#define Direction_DR                     (* (reg32 *) Direction__DR)
/* Input Buffer Disable Override */
#define Direction_INP_DIS                (* (reg32 *) Direction__PC2)


#if defined(Direction__INTSTAT)  /* Interrupt Registers */

    #define Direction_INTSTAT                (* (reg32 *) Direction__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Direction_DRIVE_MODE_SHIFT       (0x00u)
#define Direction_DRIVE_MODE_MASK        (0x07u << Direction_DRIVE_MODE_SHIFT)


#endif /* End Pins Direction_H */


/* [] END OF FILE */
