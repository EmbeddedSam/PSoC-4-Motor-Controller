/*******************************************************************************
* File Name: MotorPWM.c
* Version 3.10
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "MotorPWM.h"

/* Error message for removed <resource> through optimization */
#ifdef MotorPWM_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_10 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* MotorPWM_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 MotorPWM_initVar = 0u;


/*******************************************************************************
* Function Name: MotorPWM_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  MotorPWM_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void MotorPWM_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(MotorPWM_initVar == 0u)
    {
        MotorPWM_Init();
        MotorPWM_initVar = 1u;
    }
    MotorPWM_Enable();

}


/*******************************************************************************
* Function Name: MotorPWM_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  MotorPWM_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MotorPWM_Init(void) 
{
    #if (MotorPWM_UsingFixedFunction || MotorPWM_UseControl)
        uint8 ctrl;
    #endif /* (MotorPWM_UsingFixedFunction || MotorPWM_UseControl) */

    #if(!MotorPWM_UsingFixedFunction)
        #if(MotorPWM_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 MotorPWM_interruptState;
        #endif /* (MotorPWM_UseStatus) */
    #endif /* (!MotorPWM_UsingFixedFunction) */

    #if (MotorPWM_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        MotorPWM_CONTROL |= MotorPWM_CFG0_MODE;
        #if (MotorPWM_DeadBand2_4)
            MotorPWM_CONTROL |= MotorPWM_CFG0_DB;
        #endif /* (MotorPWM_DeadBand2_4) */

        ctrl = MotorPWM_CONTROL3 & ((uint8 )(~MotorPWM_CTRL_CMPMODE1_MASK));
        MotorPWM_CONTROL3 = ctrl | MotorPWM_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        MotorPWM_RT1 &= ((uint8)(~MotorPWM_RT1_MASK));
        MotorPWM_RT1 |= MotorPWM_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        MotorPWM_RT1 &= ((uint8)(~MotorPWM_SYNCDSI_MASK));
        MotorPWM_RT1 |= MotorPWM_SYNCDSI_EN;

    #elif (MotorPWM_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = MotorPWM_CONTROL & ((uint8)(~MotorPWM_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~MotorPWM_CTRL_CMPMODE1_MASK));
        MotorPWM_CONTROL = ctrl | MotorPWM_DEFAULT_COMPARE2_MODE |
                                   MotorPWM_DEFAULT_COMPARE1_MODE;
    #endif /* (MotorPWM_UsingFixedFunction) */

    #if (!MotorPWM_UsingFixedFunction)
        #if (MotorPWM_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            MotorPWM_AUX_CONTROLDP0 |= (MotorPWM_AUX_CTRL_FIFO0_CLR);
        #else /* (MotorPWM_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            MotorPWM_AUX_CONTROLDP0 |= (MotorPWM_AUX_CTRL_FIFO0_CLR);
            MotorPWM_AUX_CONTROLDP1 |= (MotorPWM_AUX_CTRL_FIFO0_CLR);
        #endif /* (MotorPWM_Resolution == 8) */

        MotorPWM_WriteCounter(MotorPWM_INIT_PERIOD_VALUE);
    #endif /* (!MotorPWM_UsingFixedFunction) */

    MotorPWM_WritePeriod(MotorPWM_INIT_PERIOD_VALUE);

        #if (MotorPWM_UseOneCompareMode)
            MotorPWM_WriteCompare(MotorPWM_INIT_COMPARE_VALUE1);
        #else
            MotorPWM_WriteCompare1(MotorPWM_INIT_COMPARE_VALUE1);
            MotorPWM_WriteCompare2(MotorPWM_INIT_COMPARE_VALUE2);
        #endif /* (MotorPWM_UseOneCompareMode) */

        #if (MotorPWM_KillModeMinTime)
            MotorPWM_WriteKillTime(MotorPWM_MinimumKillTime);
        #endif /* (MotorPWM_KillModeMinTime) */

        #if (MotorPWM_DeadBandUsed)
            MotorPWM_WriteDeadTime(MotorPWM_INIT_DEAD_TIME);
        #endif /* (MotorPWM_DeadBandUsed) */

    #if (MotorPWM_UseStatus || MotorPWM_UsingFixedFunction)
        MotorPWM_SetInterruptMode(MotorPWM_INIT_INTERRUPTS_MODE);
    #endif /* (MotorPWM_UseStatus || MotorPWM_UsingFixedFunction) */

    #if (MotorPWM_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        MotorPWM_GLOBAL_ENABLE |= MotorPWM_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        MotorPWM_CONTROL2 |= MotorPWM_CTRL2_IRQ_SEL;
    #else
        #if(MotorPWM_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            MotorPWM_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            MotorPWM_STATUS_AUX_CTRL |= MotorPWM_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(MotorPWM_interruptState);

            /* Clear the FIFO to enable the MotorPWM_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            MotorPWM_ClearFIFO();
        #endif /* (MotorPWM_UseStatus) */
    #endif /* (MotorPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorPWM_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void MotorPWM_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (MotorPWM_UsingFixedFunction)
        MotorPWM_GLOBAL_ENABLE |= MotorPWM_BLOCK_EN_MASK;
        MotorPWM_GLOBAL_STBY_ENABLE |= MotorPWM_BLOCK_STBY_EN_MASK;
    #endif /* (MotorPWM_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (MotorPWM_UseControl || MotorPWM_UsingFixedFunction)
        MotorPWM_CONTROL |= MotorPWM_CTRL_ENABLE;
    #endif /* (MotorPWM_UseControl || MotorPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorPWM_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void MotorPWM_Stop(void) 
{
    #if (MotorPWM_UseControl || MotorPWM_UsingFixedFunction)
        MotorPWM_CONTROL &= ((uint8)(~MotorPWM_CTRL_ENABLE));
    #endif /* (MotorPWM_UseControl || MotorPWM_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (MotorPWM_UsingFixedFunction)
        MotorPWM_GLOBAL_ENABLE &= ((uint8)(~MotorPWM_BLOCK_EN_MASK));
        MotorPWM_GLOBAL_STBY_ENABLE &= ((uint8)(~MotorPWM_BLOCK_STBY_EN_MASK));
    #endif /* (MotorPWM_UsingFixedFunction) */
}

#if (MotorPWM_UseOneCompareMode)
    #if (MotorPWM_CompareMode1SW)


        /*******************************************************************************
        * Function Name: MotorPWM_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void MotorPWM_SetCompareMode(uint8 comparemode) 
        {
            #if(MotorPWM_UsingFixedFunction)

                #if(0 != MotorPWM_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << MotorPWM_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != MotorPWM_CTRL_CMPMODE1_SHIFT) */

                MotorPWM_CONTROL3 &= ((uint8)(~MotorPWM_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                MotorPWM_CONTROL3 |= comparemodemasked;

            #elif (MotorPWM_UseControl)

                #if(0 != MotorPWM_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << MotorPWM_CTRL_CMPMODE1_SHIFT)) &
                                                MotorPWM_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & MotorPWM_CTRL_CMPMODE1_MASK;
                #endif /* (0 != MotorPWM_CTRL_CMPMODE1_SHIFT) */

                #if(0 != MotorPWM_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << MotorPWM_CTRL_CMPMODE2_SHIFT)) &
                                               MotorPWM_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & MotorPWM_CTRL_CMPMODE2_MASK;
                #endif /* (0 != MotorPWM_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                MotorPWM_CONTROL &= ((uint8)(~(MotorPWM_CTRL_CMPMODE1_MASK |
                                            MotorPWM_CTRL_CMPMODE2_MASK)));
                MotorPWM_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (MotorPWM_UsingFixedFunction) */
        }
    #endif /* MotorPWM_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (MotorPWM_CompareMode1SW)


        /*******************************************************************************
        * Function Name: MotorPWM_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void MotorPWM_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != MotorPWM_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << MotorPWM_CTRL_CMPMODE1_SHIFT)) &
                                           MotorPWM_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & MotorPWM_CTRL_CMPMODE1_MASK;
            #endif /* (0 != MotorPWM_CTRL_CMPMODE1_SHIFT) */

            #if (MotorPWM_UseControl)
                MotorPWM_CONTROL &= ((uint8)(~MotorPWM_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                MotorPWM_CONTROL |= comparemodemasked;
            #endif /* (MotorPWM_UseControl) */
        }
    #endif /* MotorPWM_CompareMode1SW */

#if (MotorPWM_CompareMode2SW)


    /*******************************************************************************
    * Function Name: MotorPWM_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void MotorPWM_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != MotorPWM_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << MotorPWM_CTRL_CMPMODE2_SHIFT)) &
                                                 MotorPWM_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & MotorPWM_CTRL_CMPMODE2_MASK;
        #endif /* (0 != MotorPWM_CTRL_CMPMODE2_SHIFT) */

        #if (MotorPWM_UseControl)
            MotorPWM_CONTROL &= ((uint8)(~MotorPWM_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            MotorPWM_CONTROL |= comparemodemasked;
        #endif /* (MotorPWM_UseControl) */
    }
    #endif /*MotorPWM_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!MotorPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: MotorPWM_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void MotorPWM_WriteCounter(uint8 counter) \
                                       
    {
        CY_SET_REG8(MotorPWM_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: MotorPWM_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint8 MotorPWM_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(MotorPWM_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG8(MotorPWM_CAPTURE_LSB_PTR));
    }

    #if (MotorPWM_UseStatus)


        /*******************************************************************************
        * Function Name: MotorPWM_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void MotorPWM_ClearFIFO(void) 
        {
            while(0u != (MotorPWM_ReadStatusRegister() & MotorPWM_STATUS_FIFONEMPTY))
            {
                (void)MotorPWM_ReadCapture();
            }
        }

    #endif /* MotorPWM_UseStatus */

#endif /* !MotorPWM_UsingFixedFunction */


/*******************************************************************************
* Function Name: MotorPWM_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void MotorPWM_WritePeriod(uint8 period) 
{
    #if(MotorPWM_UsingFixedFunction)
        CY_SET_REG16(MotorPWM_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(MotorPWM_PERIOD_LSB_PTR, period);
    #endif /* (MotorPWM_UsingFixedFunction) */
}

#if (MotorPWM_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: MotorPWM_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void MotorPWM_WriteCompare(uint8 compare) \
                                       
    {
        #if(MotorPWM_UsingFixedFunction)
            CY_SET_REG16(MotorPWM_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(MotorPWM_COMPARE1_LSB_PTR, compare);
        #endif /* (MotorPWM_UsingFixedFunction) */

        #if (MotorPWM_PWMMode == MotorPWM__B_PWM__DITHER)
            #if(MotorPWM_UsingFixedFunction)
                CY_SET_REG16(MotorPWM_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG8(MotorPWM_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (MotorPWM_UsingFixedFunction) */
        #endif /* (MotorPWM_PWMMode == MotorPWM__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: MotorPWM_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void MotorPWM_WriteCompare1(uint8 compare) \
                                        
    {
        #if(MotorPWM_UsingFixedFunction)
            CY_SET_REG16(MotorPWM_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(MotorPWM_COMPARE1_LSB_PTR, compare);
        #endif /* (MotorPWM_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: MotorPWM_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void MotorPWM_WriteCompare2(uint8 compare) \
                                        
    {
        #if(MotorPWM_UsingFixedFunction)
            CY_SET_REG16(MotorPWM_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG8(MotorPWM_COMPARE2_LSB_PTR, compare);
        #endif /* (MotorPWM_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (MotorPWM_DeadBandUsed)


    /*******************************************************************************
    * Function Name: MotorPWM_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void MotorPWM_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!MotorPWM_DeadBand2_4)
            CY_SET_REG8(MotorPWM_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            MotorPWM_DEADBAND_COUNT &= ((uint8)(~MotorPWM_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(MotorPWM_DEADBAND_COUNT_SHIFT)
                MotorPWM_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << MotorPWM_DEADBAND_COUNT_SHIFT)) &
                                                    MotorPWM_DEADBAND_COUNT_MASK;
            #else
                MotorPWM_DEADBAND_COUNT |= deadtime & MotorPWM_DEADBAND_COUNT_MASK;
            #endif /* (MotorPWM_DEADBAND_COUNT_SHIFT) */

        #endif /* (!MotorPWM_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: MotorPWM_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 MotorPWM_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!MotorPWM_DeadBand2_4)
            return (CY_GET_REG8(MotorPWM_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(MotorPWM_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(MotorPWM_DEADBAND_COUNT & MotorPWM_DEADBAND_COUNT_MASK)) >>
                                                                           MotorPWM_DEADBAND_COUNT_SHIFT));
            #else
                return (MotorPWM_DEADBAND_COUNT & MotorPWM_DEADBAND_COUNT_MASK);
            #endif /* (MotorPWM_DEADBAND_COUNT_SHIFT) */
        #endif /* (!MotorPWM_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (MotorPWM_UseStatus || MotorPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: MotorPWM_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void MotorPWM_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(MotorPWM_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: MotorPWM_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 MotorPWM_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(MotorPWM_STATUS_PTR));
    }

#endif /* (MotorPWM_UseStatus || MotorPWM_UsingFixedFunction) */


#if (MotorPWM_UseControl)


    /*******************************************************************************
    * Function Name: MotorPWM_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 MotorPWM_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(MotorPWM_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: MotorPWM_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void MotorPWM_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(MotorPWM_CONTROL_PTR, control);
    }

#endif /* (MotorPWM_UseControl) */


#if (!MotorPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: MotorPWM_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint8 MotorPWM_ReadCapture(void) 
    {
        return (CY_GET_REG8(MotorPWM_CAPTURE_LSB_PTR));
    }

#endif /* (!MotorPWM_UsingFixedFunction) */


#if (MotorPWM_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: MotorPWM_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint8 MotorPWM_ReadCompare(void) 
    {
        #if(MotorPWM_UsingFixedFunction)
            return ((uint8)CY_GET_REG16(MotorPWM_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG8(MotorPWM_COMPARE1_LSB_PTR));
        #endif /* (MotorPWM_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: MotorPWM_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint8 MotorPWM_ReadCompare1(void) 
    {
        return (CY_GET_REG8(MotorPWM_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: MotorPWM_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint8 MotorPWM_ReadCompare2(void) 
    {
        return (CY_GET_REG8(MotorPWM_COMPARE2_LSB_PTR));
    }

#endif /* (MotorPWM_UseOneCompareMode) */


/*******************************************************************************
* Function Name: MotorPWM_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint8 MotorPWM_ReadPeriod(void) 
{
    #if(MotorPWM_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(MotorPWM_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(MotorPWM_PERIOD_LSB_PTR));
    #endif /* (MotorPWM_UsingFixedFunction) */
}

#if ( MotorPWM_KillModeMinTime)


    /*******************************************************************************
    * Function Name: MotorPWM_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void MotorPWM_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(MotorPWM_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: MotorPWM_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 MotorPWM_ReadKillTime(void) 
    {
        return (CY_GET_REG8(MotorPWM_KILLMODEMINTIME_PTR));
    }

#endif /* ( MotorPWM_KillModeMinTime) */

/* [] END OF FILE */
