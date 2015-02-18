/*******************************************************************************
* File Name: SpeedInterrupt.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_SpeedInterrupt_H)
#define CY_ISR_SpeedInterrupt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void SpeedInterrupt_Start(void);
void SpeedInterrupt_StartEx(cyisraddress address);
void SpeedInterrupt_Stop(void);

CY_ISR_PROTO(SpeedInterrupt_Interrupt);

void SpeedInterrupt_SetVector(cyisraddress address);
cyisraddress SpeedInterrupt_GetVector(void);

void SpeedInterrupt_SetPriority(uint8 priority);
uint8 SpeedInterrupt_GetPriority(void);

void SpeedInterrupt_Enable(void);
uint8 SpeedInterrupt_GetState(void);
void SpeedInterrupt_Disable(void);

void SpeedInterrupt_SetPending(void);
void SpeedInterrupt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the SpeedInterrupt ISR. */
#define SpeedInterrupt_INTC_VECTOR            ((reg32 *) SpeedInterrupt__INTC_VECT)

/* Address of the SpeedInterrupt ISR priority. */
#define SpeedInterrupt_INTC_PRIOR             ((reg32 *) SpeedInterrupt__INTC_PRIOR_REG)

/* Priority of the SpeedInterrupt interrupt. */
#define SpeedInterrupt_INTC_PRIOR_NUMBER      SpeedInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable SpeedInterrupt interrupt. */
#define SpeedInterrupt_INTC_SET_EN            ((reg32 *) SpeedInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the SpeedInterrupt interrupt. */
#define SpeedInterrupt_INTC_CLR_EN            ((reg32 *) SpeedInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the SpeedInterrupt interrupt state to pending. */
#define SpeedInterrupt_INTC_SET_PD            ((reg32 *) SpeedInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the SpeedInterrupt interrupt. */
#define SpeedInterrupt_INTC_CLR_PD            ((reg32 *) SpeedInterrupt__INTC_CLR_PD_REG)



#endif /* CY_ISR_SpeedInterrupt_H */


/* [] END OF FILE */
