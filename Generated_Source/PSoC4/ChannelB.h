/*******************************************************************************
* File Name: ChannelB.h  
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

#if !defined(CY_PINS_ChannelB_H) /* Pins ChannelB_H */
#define CY_PINS_ChannelB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ChannelB_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ChannelB_Write(uint8 value) ;
void    ChannelB_SetDriveMode(uint8 mode) ;
uint8   ChannelB_ReadDataReg(void) ;
uint8   ChannelB_Read(void) ;
uint8   ChannelB_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ChannelB_DRIVE_MODE_BITS        (3)
#define ChannelB_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ChannelB_DRIVE_MODE_BITS))

#define ChannelB_DM_ALG_HIZ         (0x00u)
#define ChannelB_DM_DIG_HIZ         (0x01u)
#define ChannelB_DM_RES_UP          (0x02u)
#define ChannelB_DM_RES_DWN         (0x03u)
#define ChannelB_DM_OD_LO           (0x04u)
#define ChannelB_DM_OD_HI           (0x05u)
#define ChannelB_DM_STRONG          (0x06u)
#define ChannelB_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define ChannelB_MASK               ChannelB__MASK
#define ChannelB_SHIFT              ChannelB__SHIFT
#define ChannelB_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ChannelB_PS                     (* (reg32 *) ChannelB__PS)
/* Port Configuration */
#define ChannelB_PC                     (* (reg32 *) ChannelB__PC)
/* Data Register */
#define ChannelB_DR                     (* (reg32 *) ChannelB__DR)
/* Input Buffer Disable Override */
#define ChannelB_INP_DIS                (* (reg32 *) ChannelB__PC2)


#if defined(ChannelB__INTSTAT)  /* Interrupt Registers */

    #define ChannelB_INTSTAT                (* (reg32 *) ChannelB__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define ChannelB_DRIVE_MODE_SHIFT       (0x00u)
#define ChannelB_DRIVE_MODE_MASK        (0x07u << ChannelB_DRIVE_MODE_SHIFT)


#endif /* End Pins ChannelB_H */


/* [] END OF FILE */
