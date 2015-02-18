/*******************************************************************************
* File Name: MotorCurrentPin.h  
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

#if !defined(CY_PINS_MotorCurrentPin_H) /* Pins MotorCurrentPin_H */
#define CY_PINS_MotorCurrentPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MotorCurrentPin_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    MotorCurrentPin_Write(uint8 value) ;
void    MotorCurrentPin_SetDriveMode(uint8 mode) ;
uint8   MotorCurrentPin_ReadDataReg(void) ;
uint8   MotorCurrentPin_Read(void) ;
uint8   MotorCurrentPin_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MotorCurrentPin_DRIVE_MODE_BITS        (3)
#define MotorCurrentPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MotorCurrentPin_DRIVE_MODE_BITS))

#define MotorCurrentPin_DM_ALG_HIZ         (0x00u)
#define MotorCurrentPin_DM_DIG_HIZ         (0x01u)
#define MotorCurrentPin_DM_RES_UP          (0x02u)
#define MotorCurrentPin_DM_RES_DWN         (0x03u)
#define MotorCurrentPin_DM_OD_LO           (0x04u)
#define MotorCurrentPin_DM_OD_HI           (0x05u)
#define MotorCurrentPin_DM_STRONG          (0x06u)
#define MotorCurrentPin_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define MotorCurrentPin_MASK               MotorCurrentPin__MASK
#define MotorCurrentPin_SHIFT              MotorCurrentPin__SHIFT
#define MotorCurrentPin_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MotorCurrentPin_PS                     (* (reg32 *) MotorCurrentPin__PS)
/* Port Configuration */
#define MotorCurrentPin_PC                     (* (reg32 *) MotorCurrentPin__PC)
/* Data Register */
#define MotorCurrentPin_DR                     (* (reg32 *) MotorCurrentPin__DR)
/* Input Buffer Disable Override */
#define MotorCurrentPin_INP_DIS                (* (reg32 *) MotorCurrentPin__PC2)


#if defined(MotorCurrentPin__INTSTAT)  /* Interrupt Registers */

    #define MotorCurrentPin_INTSTAT                (* (reg32 *) MotorCurrentPin__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define MotorCurrentPin_DRIVE_MODE_SHIFT       (0x00u)
#define MotorCurrentPin_DRIVE_MODE_MASK        (0x07u << MotorCurrentPin_DRIVE_MODE_SHIFT)


#endif /* End Pins MotorCurrentPin_H */


/* [] END OF FILE */
