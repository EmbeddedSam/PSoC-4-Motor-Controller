/*******************************************************************************
* File Name: MotorPWM_PM.c
* Version 3.10
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "MotorPWM.h"

static MotorPWM_backupStruct MotorPWM_backup;


/*******************************************************************************
* Function Name: MotorPWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  MotorPWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void MotorPWM_SaveConfig(void) 
{

    #if(!MotorPWM_UsingFixedFunction)
        #if(!MotorPWM_PWMModeIsCenterAligned)
            MotorPWM_backup.PWMPeriod = MotorPWM_ReadPeriod();
        #endif /* (!MotorPWM_PWMModeIsCenterAligned) */
        MotorPWM_backup.PWMUdb = MotorPWM_ReadCounter();
        #if (MotorPWM_UseStatus)
            MotorPWM_backup.InterruptMaskValue = MotorPWM_STATUS_MASK;
        #endif /* (MotorPWM_UseStatus) */

        #if(MotorPWM_DeadBandMode == MotorPWM__B_PWM__DBM_256_CLOCKS || \
            MotorPWM_DeadBandMode == MotorPWM__B_PWM__DBM_2_4_CLOCKS)
            MotorPWM_backup.PWMdeadBandValue = MotorPWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(MotorPWM_KillModeMinTime)
             MotorPWM_backup.PWMKillCounterPeriod = MotorPWM_ReadKillTime();
        #endif /* (MotorPWM_KillModeMinTime) */

        #if(MotorPWM_UseControl)
            MotorPWM_backup.PWMControlRegister = MotorPWM_ReadControlRegister();
        #endif /* (MotorPWM_UseControl) */
    #endif  /* (!MotorPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorPWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  MotorPWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MotorPWM_RestoreConfig(void) 
{
        #if(!MotorPWM_UsingFixedFunction)
            #if(!MotorPWM_PWMModeIsCenterAligned)
                MotorPWM_WritePeriod(MotorPWM_backup.PWMPeriod);
            #endif /* (!MotorPWM_PWMModeIsCenterAligned) */

            MotorPWM_WriteCounter(MotorPWM_backup.PWMUdb);

            #if (MotorPWM_UseStatus)
                MotorPWM_STATUS_MASK = MotorPWM_backup.InterruptMaskValue;
            #endif /* (MotorPWM_UseStatus) */

            #if(MotorPWM_DeadBandMode == MotorPWM__B_PWM__DBM_256_CLOCKS || \
                MotorPWM_DeadBandMode == MotorPWM__B_PWM__DBM_2_4_CLOCKS)
                MotorPWM_WriteDeadTime(MotorPWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(MotorPWM_KillModeMinTime)
                MotorPWM_WriteKillTime(MotorPWM_backup.PWMKillCounterPeriod);
            #endif /* (MotorPWM_KillModeMinTime) */

            #if(MotorPWM_UseControl)
                MotorPWM_WriteControlRegister(MotorPWM_backup.PWMControlRegister);
            #endif /* (MotorPWM_UseControl) */
        #endif  /* (!MotorPWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: MotorPWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  MotorPWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MotorPWM_Sleep(void) 
{
    #if(MotorPWM_UseControl)
        if(MotorPWM_CTRL_ENABLE == (MotorPWM_CONTROL & MotorPWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            MotorPWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            MotorPWM_backup.PWMEnableState = 0u;
        }
    #endif /* (MotorPWM_UseControl) */

    /* Stop component */
    MotorPWM_Stop();

    /* Save registers configuration */
    MotorPWM_SaveConfig();
}


/*******************************************************************************
* Function Name: MotorPWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  MotorPWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MotorPWM_Wakeup(void) 
{
     /* Restore registers values */
    MotorPWM_RestoreConfig();

    if(MotorPWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        MotorPWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
