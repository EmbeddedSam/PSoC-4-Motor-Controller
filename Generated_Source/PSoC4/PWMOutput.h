/*******************************************************************************
* File Name: PWMOutput.h  
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

#if !defined(CY_PINS_PWMOutput_H) /* Pins PWMOutput_H */
#define CY_PINS_PWMOutput_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PWMOutput_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PWMOutput_Write(uint8 value) ;
void    PWMOutput_SetDriveMode(uint8 mode) ;
uint8   PWMOutput_ReadDataReg(void) ;
uint8   PWMOutput_Read(void) ;
uint8   PWMOutput_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PWMOutput_DRIVE_MODE_BITS        (3)
#define PWMOutput_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PWMOutput_DRIVE_MODE_BITS))

#define PWMOutput_DM_ALG_HIZ         (0x00u)
#define PWMOutput_DM_DIG_HIZ         (0x01u)
#define PWMOutput_DM_RES_UP          (0x02u)
#define PWMOutput_DM_RES_DWN         (0x03u)
#define PWMOutput_DM_OD_LO           (0x04u)
#define PWMOutput_DM_OD_HI           (0x05u)
#define PWMOutput_DM_STRONG          (0x06u)
#define PWMOutput_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PWMOutput_MASK               PWMOutput__MASK
#define PWMOutput_SHIFT              PWMOutput__SHIFT
#define PWMOutput_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWMOutput_PS                     (* (reg32 *) PWMOutput__PS)
/* Port Configuration */
#define PWMOutput_PC                     (* (reg32 *) PWMOutput__PC)
/* Data Register */
#define PWMOutput_DR                     (* (reg32 *) PWMOutput__DR)
/* Input Buffer Disable Override */
#define PWMOutput_INP_DIS                (* (reg32 *) PWMOutput__PC2)


#if defined(PWMOutput__INTSTAT)  /* Interrupt Registers */

    #define PWMOutput_INTSTAT                (* (reg32 *) PWMOutput__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PWMOutput_DRIVE_MODE_SHIFT       (0x00u)
#define PWMOutput_DRIVE_MODE_MASK        (0x07u << PWMOutput_DRIVE_MODE_SHIFT)


#endif /* End Pins PWMOutput_H */


/* [] END OF FILE */
