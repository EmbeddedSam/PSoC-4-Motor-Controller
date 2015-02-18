/*******************************************************************************
* File Name: MotorCurrentADC_IRQ.h
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
#if !defined(CY_ISR_MotorCurrentADC_IRQ_H)
#define CY_ISR_MotorCurrentADC_IRQ_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void MotorCurrentADC_IRQ_Start(void);
void MotorCurrentADC_IRQ_StartEx(cyisraddress address);
void MotorCurrentADC_IRQ_Stop(void);

CY_ISR_PROTO(MotorCurrentADC_IRQ_Interrupt);

void MotorCurrentADC_IRQ_SetVector(cyisraddress address);
cyisraddress MotorCurrentADC_IRQ_GetVector(void);

void MotorCurrentADC_IRQ_SetPriority(uint8 priority);
uint8 MotorCurrentADC_IRQ_GetPriority(void);

void MotorCurrentADC_IRQ_Enable(void);
uint8 MotorCurrentADC_IRQ_GetState(void);
void MotorCurrentADC_IRQ_Disable(void);

void MotorCurrentADC_IRQ_SetPending(void);
void MotorCurrentADC_IRQ_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the MotorCurrentADC_IRQ ISR. */
#define MotorCurrentADC_IRQ_INTC_VECTOR            ((reg32 *) MotorCurrentADC_IRQ__INTC_VECT)

/* Address of the MotorCurrentADC_IRQ ISR priority. */
#define MotorCurrentADC_IRQ_INTC_PRIOR             ((reg32 *) MotorCurrentADC_IRQ__INTC_PRIOR_REG)

/* Priority of the MotorCurrentADC_IRQ interrupt. */
#define MotorCurrentADC_IRQ_INTC_PRIOR_NUMBER      MotorCurrentADC_IRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable MotorCurrentADC_IRQ interrupt. */
#define MotorCurrentADC_IRQ_INTC_SET_EN            ((reg32 *) MotorCurrentADC_IRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the MotorCurrentADC_IRQ interrupt. */
#define MotorCurrentADC_IRQ_INTC_CLR_EN            ((reg32 *) MotorCurrentADC_IRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the MotorCurrentADC_IRQ interrupt state to pending. */
#define MotorCurrentADC_IRQ_INTC_SET_PD            ((reg32 *) MotorCurrentADC_IRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the MotorCurrentADC_IRQ interrupt. */
#define MotorCurrentADC_IRQ_INTC_CLR_PD            ((reg32 *) MotorCurrentADC_IRQ__INTC_CLR_PD_REG)



#endif /* CY_ISR_MotorCurrentADC_IRQ_H */


/* [] END OF FILE */
