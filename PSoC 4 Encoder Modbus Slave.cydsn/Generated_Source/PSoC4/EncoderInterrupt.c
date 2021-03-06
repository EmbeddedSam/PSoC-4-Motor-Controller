/*******************************************************************************
* File Name: EncoderInterrupt.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <EncoderInterrupt.h>

#if !defined(EncoderInterrupt__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START EncoderInterrupt_intc` */

/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: EncoderInterrupt_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void EncoderInterrupt_Start(void)
{
    /* For all we know the interrupt is active. */
    EncoderInterrupt_Disable();

    /* Set the ISR to point to the EncoderInterrupt Interrupt. */
    EncoderInterrupt_SetVector(&EncoderInterrupt_Interrupt);

    /* Set the priority. */
    EncoderInterrupt_SetPriority((uint8)EncoderInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    EncoderInterrupt_Enable();
}


/*******************************************************************************
* Function Name: EncoderInterrupt_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void EncoderInterrupt_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    EncoderInterrupt_Disable();

    /* Set the ISR to point to the EncoderInterrupt Interrupt. */
    EncoderInterrupt_SetVector(address);

    /* Set the priority. */
    EncoderInterrupt_SetPriority((uint8)EncoderInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    EncoderInterrupt_Enable();
}


/*******************************************************************************
* Function Name: EncoderInterrupt_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
void EncoderInterrupt_Stop(void)
{
    /* Disable this interrupt. */
    EncoderInterrupt_Disable();

    /* Set the ISR to point to the passive one. */
    EncoderInterrupt_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: EncoderInterrupt_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for EncoderInterrupt.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(EncoderInterrupt_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START EncoderInterrupt_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: EncoderInterrupt_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling EncoderInterrupt_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use EncoderInterrupt_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void EncoderInterrupt_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + EncoderInterrupt__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: EncoderInterrupt_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress EncoderInterrupt_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + EncoderInterrupt__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: EncoderInterrupt_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling EncoderInterrupt_Start
*   or EncoderInterrupt_StartEx will override any effect this method would 
*   have had. This method should only be called after EncoderInterrupt_Start or 
*   EncoderInterrupt_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void EncoderInterrupt_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((EncoderInterrupt__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *EncoderInterrupt_INTC_PRIOR = (*EncoderInterrupt_INTC_PRIOR & (uint32)(~EncoderInterrupt__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: EncoderInterrupt_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 3, 0 being the highest.
*
*******************************************************************************/
uint8 EncoderInterrupt_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((EncoderInterrupt__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*EncoderInterrupt_INTC_PRIOR & EncoderInterrupt__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: EncoderInterrupt_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void EncoderInterrupt_Enable(void)
{
    /* Enable the general interrupt. */
    *EncoderInterrupt_INTC_SET_EN = EncoderInterrupt__INTC_MASK;
}


/*******************************************************************************
* Function Name: EncoderInterrupt_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 EncoderInterrupt_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*EncoderInterrupt_INTC_SET_EN & (uint32)EncoderInterrupt__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: EncoderInterrupt_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void EncoderInterrupt_Disable(void)
{
    /* Disable the general interrupt. */
    *EncoderInterrupt_INTC_CLR_EN = EncoderInterrupt__INTC_MASK;
}


/*******************************************************************************
* Function Name: EncoderInterrupt_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void EncoderInterrupt_SetPending(void)
{
    *EncoderInterrupt_INTC_SET_PD = EncoderInterrupt__INTC_MASK;
}


/*******************************************************************************
* Function Name: EncoderInterrupt_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void EncoderInterrupt_ClearPending(void)
{
    *EncoderInterrupt_INTC_CLR_PD = EncoderInterrupt__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
