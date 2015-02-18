/*******************************************************************************
* File Name: SpeedTimerPin.h  
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

#if !defined(CY_PINS_SpeedTimerPin_H) /* Pins SpeedTimerPin_H */
#define CY_PINS_SpeedTimerPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SpeedTimerPin_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SpeedTimerPin_Write(uint8 value) ;
void    SpeedTimerPin_SetDriveMode(uint8 mode) ;
uint8   SpeedTimerPin_ReadDataReg(void) ;
uint8   SpeedTimerPin_Read(void) ;
uint8   SpeedTimerPin_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SpeedTimerPin_DRIVE_MODE_BITS        (3)
#define SpeedTimerPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SpeedTimerPin_DRIVE_MODE_BITS))

#define SpeedTimerPin_DM_ALG_HIZ         (0x00u)
#define SpeedTimerPin_DM_DIG_HIZ         (0x01u)
#define SpeedTimerPin_DM_RES_UP          (0x02u)
#define SpeedTimerPin_DM_RES_DWN         (0x03u)
#define SpeedTimerPin_DM_OD_LO           (0x04u)
#define SpeedTimerPin_DM_OD_HI           (0x05u)
#define SpeedTimerPin_DM_STRONG          (0x06u)
#define SpeedTimerPin_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define SpeedTimerPin_MASK               SpeedTimerPin__MASK
#define SpeedTimerPin_SHIFT              SpeedTimerPin__SHIFT
#define SpeedTimerPin_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SpeedTimerPin_PS                     (* (reg32 *) SpeedTimerPin__PS)
/* Port Configuration */
#define SpeedTimerPin_PC                     (* (reg32 *) SpeedTimerPin__PC)
/* Data Register */
#define SpeedTimerPin_DR                     (* (reg32 *) SpeedTimerPin__DR)
/* Input Buffer Disable Override */
#define SpeedTimerPin_INP_DIS                (* (reg32 *) SpeedTimerPin__PC2)


#if defined(SpeedTimerPin__INTSTAT)  /* Interrupt Registers */

    #define SpeedTimerPin_INTSTAT                (* (reg32 *) SpeedTimerPin__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define SpeedTimerPin_DRIVE_MODE_SHIFT       (0x00u)
#define SpeedTimerPin_DRIVE_MODE_MASK        (0x07u << SpeedTimerPin_DRIVE_MODE_SHIFT)


#endif /* End Pins SpeedTimerPin_H */


/* [] END OF FILE */
