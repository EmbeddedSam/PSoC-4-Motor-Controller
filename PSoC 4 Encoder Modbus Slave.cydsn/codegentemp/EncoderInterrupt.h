/*******************************************************************************
* File Name: EncoderInterrupt.h
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
#if !defined(CY_ISR_EncoderInterrupt_H)
#define CY_ISR_EncoderInterrupt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void EncoderInterrupt_Start(void);
void EncoderInterrupt_StartEx(cyisraddress address);
void EncoderInterrupt_Stop(void);

CY_ISR_PROTO(EncoderInterrupt_Interrupt);

void EncoderInterrupt_SetVector(cyisraddress address);
cyisraddress EncoderInterrupt_GetVector(void);

void EncoderInterrupt_SetPriority(uint8 priority);
uint8 EncoderInterrupt_GetPriority(void);

void EncoderInterrupt_Enable(void);
uint8 EncoderInterrupt_GetState(void);
void EncoderInterrupt_Disable(void);

void EncoderInterrupt_SetPending(void);
void EncoderInterrupt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the EncoderInterrupt ISR. */
#define EncoderInterrupt_INTC_VECTOR            ((reg32 *) EncoderInterrupt__INTC_VECT)

/* Address of the EncoderInterrupt ISR priority. */
#define EncoderInterrupt_INTC_PRIOR             ((reg32 *) EncoderInterrupt__INTC_PRIOR_REG)

/* Priority of the EncoderInterrupt interrupt. */
#define EncoderInterrupt_INTC_PRIOR_NUMBER      EncoderInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable EncoderInterrupt interrupt. */
#define EncoderInterrupt_INTC_SET_EN            ((reg32 *) EncoderInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the EncoderInterrupt interrupt. */
#define EncoderInterrupt_INTC_CLR_EN            ((reg32 *) EncoderInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the EncoderInterrupt interrupt state to pending. */
#define EncoderInterrupt_INTC_SET_PD            ((reg32 *) EncoderInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the EncoderInterrupt interrupt. */
#define EncoderInterrupt_INTC_CLR_PD            ((reg32 *) EncoderInterrupt__INTC_CLR_PD_REG)



#endif /* CY_ISR_EncoderInterrupt_H */


/* [] END OF FILE */
