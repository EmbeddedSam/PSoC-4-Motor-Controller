/*******************************************************************************
* File Name: SpeedTimer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "SpeedTimer.h"

static SpeedTimer_backupStruct SpeedTimer_backup;


/*******************************************************************************
* Function Name: SpeedTimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SpeedTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void SpeedTimer_SaveConfig(void) 
{
    #if (!SpeedTimer_UsingFixedFunction)
        SpeedTimer_backup.TimerUdb = SpeedTimer_ReadCounter();
        SpeedTimer_backup.InterruptMaskValue = SpeedTimer_STATUS_MASK;
        #if (SpeedTimer_UsingHWCaptureCounter)
            SpeedTimer_backup.TimerCaptureCounter = SpeedTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!SpeedTimer_UDB_CONTROL_REG_REMOVED)
            SpeedTimer_backup.TimerControlRegister = SpeedTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: SpeedTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SpeedTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void SpeedTimer_RestoreConfig(void) 
{   
    #if (!SpeedTimer_UsingFixedFunction)

        SpeedTimer_WriteCounter(SpeedTimer_backup.TimerUdb);
        SpeedTimer_STATUS_MASK =SpeedTimer_backup.InterruptMaskValue;
        #if (SpeedTimer_UsingHWCaptureCounter)
            SpeedTimer_SetCaptureCount(SpeedTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!SpeedTimer_UDB_CONTROL_REG_REMOVED)
            SpeedTimer_WriteControlRegister(SpeedTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: SpeedTimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SpeedTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void SpeedTimer_Sleep(void) 
{
    #if(!SpeedTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(SpeedTimer_CTRL_ENABLE == (SpeedTimer_CONTROL & SpeedTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            SpeedTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            SpeedTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    SpeedTimer_Stop();
    SpeedTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: SpeedTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SpeedTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void SpeedTimer_Wakeup(void) 
{
    SpeedTimer_RestoreConfig();
    #if(!SpeedTimer_UDB_CONTROL_REG_REMOVED)
        if(SpeedTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                SpeedTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
