/*******************************************************************************
* File Name: MotorCurrentADC_PM.c
* Version 2.0
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "MotorCurrentADC.h"


/***************************************
* Local data allocation
***************************************/

static MotorCurrentADC_BACKUP_STRUCT  MotorCurrentADC_backup =
{
    MotorCurrentADC_DISABLED
};


/*******************************************************************************
* Function Name: MotorCurrentADC_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MotorCurrentADC_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: MotorCurrentADC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MotorCurrentADC_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: MotorCurrentADC_Sleep
********************************************************************************
*
* Summary:
*  Stops the ADC operation and saves the configuration registers and component
*  enable state. Should be called just prior to entering sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  MotorCurrentADC_backup - modified.
*
*******************************************************************************/
void MotorCurrentADC_Sleep(void)
{
    /* During deepsleep/ hibernate mode keep SARMUX active, i.e. do not open
    *   all switches (disconnect), to be used for ADFT
    */
    MotorCurrentADC_SAR_DFT_CTRL_REG |= MotorCurrentADC_ADFT_OVERRIDE;
    if((MotorCurrentADC_SAR_CTRL_REG  & MotorCurrentADC_ENABLE) != 0u)
    {
        if((MotorCurrentADC_SAR_SAMPLE_CTRL_REG & MotorCurrentADC_CONTINUOUS_EN) != 0u)
        {
            MotorCurrentADC_backup.enableState = MotorCurrentADC_ENABLED | MotorCurrentADC_STARTED;
        }
        else
        {
            MotorCurrentADC_backup.enableState = MotorCurrentADC_ENABLED;
        }
        MotorCurrentADC_StopConvert();
        MotorCurrentADC_Stop();
    }
    else
    {
        MotorCurrentADC_backup.enableState = MotorCurrentADC_DISABLED;
    }
}


/*******************************************************************************
* Function Name: MotorCurrentADC_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component enable state and configuration registers.
*  This should be called just after awaking from sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  MotorCurrentADC_backup - used.
*
*******************************************************************************/
void MotorCurrentADC_Wakeup(void)
{
    MotorCurrentADC_SAR_DFT_CTRL_REG &= (uint32)~MotorCurrentADC_ADFT_OVERRIDE;
    if(MotorCurrentADC_backup.enableState != MotorCurrentADC_DISABLED)
    {
        MotorCurrentADC_Enable();
        if((MotorCurrentADC_backup.enableState & MotorCurrentADC_STARTED) != 0u)
        {
            MotorCurrentADC_StartConvert();
        }
    }
}
/* [] END OF FILE */
