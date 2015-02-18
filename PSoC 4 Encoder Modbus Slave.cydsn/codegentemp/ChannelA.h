/*******************************************************************************
* File Name: ChannelA.h  
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

#if !defined(CY_PINS_ChannelA_H) /* Pins ChannelA_H */
#define CY_PINS_ChannelA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ChannelA_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ChannelA_Write(uint8 value) ;
void    ChannelA_SetDriveMode(uint8 mode) ;
uint8   ChannelA_ReadDataReg(void) ;
uint8   ChannelA_Read(void) ;
uint8   ChannelA_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ChannelA_DRIVE_MODE_BITS        (3)
#define ChannelA_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ChannelA_DRIVE_MODE_BITS))

#define ChannelA_DM_ALG_HIZ         (0x00u)
#define ChannelA_DM_DIG_HIZ         (0x01u)
#define ChannelA_DM_RES_UP          (0x02u)
#define ChannelA_DM_RES_DWN         (0x03u)
#define ChannelA_DM_OD_LO           (0x04u)
#define ChannelA_DM_OD_HI           (0x05u)
#define ChannelA_DM_STRONG          (0x06u)
#define ChannelA_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define ChannelA_MASK               ChannelA__MASK
#define ChannelA_SHIFT              ChannelA__SHIFT
#define ChannelA_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ChannelA_PS                     (* (reg32 *) ChannelA__PS)
/* Port Configuration */
#define ChannelA_PC                     (* (reg32 *) ChannelA__PC)
/* Data Register */
#define ChannelA_DR                     (* (reg32 *) ChannelA__DR)
/* Input Buffer Disable Override */
#define ChannelA_INP_DIS                (* (reg32 *) ChannelA__PC2)


#if defined(ChannelA__INTSTAT)  /* Interrupt Registers */

    #define ChannelA_INTSTAT                (* (reg32 *) ChannelA__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define ChannelA_DRIVE_MODE_SHIFT       (0x00u)
#define ChannelA_DRIVE_MODE_MASK        (0x07u << ChannelA_DRIVE_MODE_SHIFT)


#endif /* End Pins ChannelA_H */


/* [] END OF FILE */
