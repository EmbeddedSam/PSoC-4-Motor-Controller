/*******************************************************************************
* File Name: SpeedInterrupt.c  
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
#include <SpeedInterrupt.h>

#if !defined(SpeedInterrupt__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START SpeedInterrupt_intc` */

/* `#END` */

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: SpeedInterrupt_Start
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
void SpeedInterrupt_Start(void)
{
    /* For all we know the interrupt is active. */
    SpeedInterrupt_Disable();

    /* Set the ISR to point to the SpeedInterrupt Interrupt. */
    SpeedInterrupt_SetVector(&SpeedInterrupt_Interrupt);

    /* Set the priority. */
    SpeedInterrupt_SetPriority((uint8)SpeedInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    SpeedInterrupt_Enable();
}


/*******************************************************************************
* Function Name: SpeedInterrupt_StartEx
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
void SpeedInterrupt_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    SpeedInterrupt_Disable();

    /* Set the ISR to point to the SpeedInterrupt Interrupt. */
    SpeedInterrupt_SetVector(address);

    /* Set the priority. */
    SpeedInterrupt_SetPriority((uint8)SpeedInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    SpeedInterrupt_Enable();
}


/*******************************************************************************
* Function Name: SpeedInterrupt_Stop
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
void SpeedInterrupt_Stop(void)
{
    /* Disable this interrupt. */
    SpeedInterrupt_Disable();

    /* Set the ISR to point to the passive one. */
    SpeedInterrupt_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: SpeedInterrupt_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for SpeedInterrupt.
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
CY_ISR(SpeedInterrupt_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START SpeedInterrupt_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: SpeedInterrupt_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling SpeedInterrupt_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use SpeedInterrupt_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void SpeedInterrupt_SetVector(cyisraddress address)
{
    CyRamVectors[CYINT_IRQ_BASE + SpeedInterrupt__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: SpeedInterrupt_GetVector
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
cyisraddress SpeedInterrupt_GetVector(void)
{
    return CyRamVectors[CYINT_IRQ_BASE + SpeedInterrupt__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: SpeedInterrupt_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling SpeedInterrupt_Start
*   or SpeedInterrupt_StartEx will override any effect this method would 
*   have had. This method should only be called after SpeedInterrupt_Start or 
*   SpeedInterrupt_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void SpeedInterrupt_SetPriority(uint8 priority)
{
	uint8 interruptState;
    uint32 priorityOffset = ((SpeedInterrupt__INTC_NUMBER % 4u) * 8u) + 6u;
    
	interruptState = CyEnterCriticalSection();
    *SpeedInterrupt_INTC_PRIOR = (*SpeedInterrupt_INTC_PRIOR & (uint32)(~SpeedInterrupt__INTC_PRIOR_MASK)) |
                                    ((uint32)priority << priorityOffset);
	CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: SpeedInterrupt_GetPriority
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
uint8 SpeedInterrupt_GetPriority(void)
{
    uint32 priority;
	uint32 priorityOffset = ((SpeedInterrupt__INTC_NUMBER % 4u) * 8u) + 6u;

    priority = (*SpeedInterrupt_INTC_PRIOR & SpeedInterrupt__INTC_PRIOR_MASK) >> priorityOffset;

    return (uint8)priority;
}


/*******************************************************************************
* Function Name: SpeedInterrupt_Enable
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
void SpeedInterrupt_Enable(void)
{
    /* Enable the general interrupt. */
    *SpeedInterrupt_INTC_SET_EN = SpeedInterrupt__INTC_MASK;
}


/*******************************************************************************
* Function Name: SpeedInterrupt_GetState
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
uint8 SpeedInterrupt_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*SpeedInterrupt_INTC_SET_EN & (uint32)SpeedInterrupt__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: SpeedInterrupt_Disable
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
void SpeedInterrupt_Disable(void)
{
    /* Disable the general interrupt. */
    *SpeedInterrupt_INTC_CLR_EN = SpeedInterrupt__INTC_MASK;
}


/*******************************************************************************
* Function Name: SpeedInterrupt_SetPending
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
void SpeedInterrupt_SetPending(void)
{
    *SpeedInterrupt_INTC_SET_PD = SpeedInterrupt__INTC_MASK;
}


/*******************************************************************************
* Function Name: SpeedInterrupt_ClearPending
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
void SpeedInterrupt_ClearPending(void)
{
    *SpeedInterrupt_INTC_CLR_PD = SpeedInterrupt__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
