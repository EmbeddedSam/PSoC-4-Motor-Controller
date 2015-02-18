/*******************************************************************************
* File Name: EncoderInterruptPin.h  
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

#if !defined(CY_PINS_EncoderInterruptPin_H) /* Pins EncoderInterruptPin_H */
#define CY_PINS_EncoderInterruptPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "EncoderInterruptPin_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    EncoderInterruptPin_Write(uint8 value) ;
void    EncoderInterruptPin_SetDriveMode(uint8 mode) ;
uint8   EncoderInterruptPin_ReadDataReg(void) ;
uint8   EncoderInterruptPin_Read(void) ;
uint8   EncoderInterruptPin_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define EncoderInterruptPin_DRIVE_MODE_BITS        (3)
#define EncoderInterruptPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - EncoderInterruptPin_DRIVE_MODE_BITS))

#define EncoderInterruptPin_DM_ALG_HIZ         (0x00u)
#define EncoderInterruptPin_DM_DIG_HIZ         (0x01u)
#define EncoderInterruptPin_DM_RES_UP          (0x02u)
#define EncoderInterruptPin_DM_RES_DWN         (0x03u)
#define EncoderInterruptPin_DM_OD_LO           (0x04u)
#define EncoderInterruptPin_DM_OD_HI           (0x05u)
#define EncoderInterruptPin_DM_STRONG          (0x06u)
#define EncoderInterruptPin_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define EncoderInterruptPin_MASK               EncoderInterruptPin__MASK
#define EncoderInterruptPin_SHIFT              EncoderInterruptPin__SHIFT
#define EncoderInterruptPin_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define EncoderInterruptPin_PS                     (* (reg32 *) EncoderInterruptPin__PS)
/* Port Configuration */
#define EncoderInterruptPin_PC                     (* (reg32 *) EncoderInterruptPin__PC)
/* Data Register */
#define EncoderInterruptPin_DR                     (* (reg32 *) EncoderInterruptPin__DR)
/* Input Buffer Disable Override */
#define EncoderInterruptPin_INP_DIS                (* (reg32 *) EncoderInterruptPin__PC2)


#if defined(EncoderInterruptPin__INTSTAT)  /* Interrupt Registers */

    #define EncoderInterruptPin_INTSTAT                (* (reg32 *) EncoderInterruptPin__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define EncoderInterruptPin_DRIVE_MODE_SHIFT       (0x00u)
#define EncoderInterruptPin_DRIVE_MODE_MASK        (0x07u << EncoderInterruptPin_DRIVE_MODE_SHIFT)


#endif /* End Pins EncoderInterruptPin_H */


/* [] END OF FILE */
