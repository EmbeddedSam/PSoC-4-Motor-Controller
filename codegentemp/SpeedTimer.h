/*******************************************************************************
* File Name: SpeedTimer.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_SpeedTimer_H)
#define CY_Timer_v2_60_SpeedTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 SpeedTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define SpeedTimer_Resolution                 8u
#define SpeedTimer_UsingFixedFunction         0u
#define SpeedTimer_UsingHWCaptureCounter      0u
#define SpeedTimer_SoftwareCaptureMode        0u
#define SpeedTimer_SoftwareTriggerMode        0u
#define SpeedTimer_UsingHWEnable              0u
#define SpeedTimer_EnableTriggerMode          0u
#define SpeedTimer_InterruptOnCaptureCount    0u
#define SpeedTimer_RunModeUsed                0u
#define SpeedTimer_ControlRegRemoved          0u

#if defined(SpeedTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define SpeedTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (SpeedTimer_UsingFixedFunction)
    #define SpeedTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define SpeedTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End SpeedTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!SpeedTimer_UsingFixedFunction)

        uint8 TimerUdb;
        uint8 InterruptMaskValue;
        #if (SpeedTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!SpeedTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}SpeedTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    SpeedTimer_Start(void) ;
void    SpeedTimer_Stop(void) ;

void    SpeedTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   SpeedTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define SpeedTimer_GetInterruptSource() SpeedTimer_ReadStatusRegister()

#if(!SpeedTimer_UDB_CONTROL_REG_REMOVED)
    uint8   SpeedTimer_ReadControlRegister(void) ;
    void    SpeedTimer_WriteControlRegister(uint8 control) ;
#endif /* (!SpeedTimer_UDB_CONTROL_REG_REMOVED) */

uint8  SpeedTimer_ReadPeriod(void) ;
void    SpeedTimer_WritePeriod(uint8 period) ;
uint8  SpeedTimer_ReadCounter(void) ;
void    SpeedTimer_WriteCounter(uint8 counter) ;
uint8  SpeedTimer_ReadCapture(void) ;
void    SpeedTimer_SoftwareCapture(void) ;

#if(!SpeedTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (SpeedTimer_SoftwareCaptureMode)
        void    SpeedTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!SpeedTimer_UsingFixedFunction) */

    #if (SpeedTimer_SoftwareTriggerMode)
        void    SpeedTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (SpeedTimer_SoftwareTriggerMode) */

    #if (SpeedTimer_EnableTriggerMode)
        void    SpeedTimer_EnableTrigger(void) ;
        void    SpeedTimer_DisableTrigger(void) ;
    #endif /* (SpeedTimer_EnableTriggerMode) */


    #if(SpeedTimer_InterruptOnCaptureCount)
        void    SpeedTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (SpeedTimer_InterruptOnCaptureCount) */

    #if (SpeedTimer_UsingHWCaptureCounter)
        void    SpeedTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   SpeedTimer_ReadCaptureCount(void) ;
    #endif /* (SpeedTimer_UsingHWCaptureCounter) */

    void SpeedTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void SpeedTimer_Init(void)          ;
void SpeedTimer_Enable(void)        ;
void SpeedTimer_SaveConfig(void)    ;
void SpeedTimer_RestoreConfig(void) ;
void SpeedTimer_Sleep(void)         ;
void SpeedTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define SpeedTimer__B_TIMER__CM_NONE 0
#define SpeedTimer__B_TIMER__CM_RISINGEDGE 1
#define SpeedTimer__B_TIMER__CM_FALLINGEDGE 2
#define SpeedTimer__B_TIMER__CM_EITHEREDGE 3
#define SpeedTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define SpeedTimer__B_TIMER__TM_NONE 0x00u
#define SpeedTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define SpeedTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define SpeedTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define SpeedTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define SpeedTimer_INIT_PERIOD             49u
#define SpeedTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << SpeedTimer_CTRL_CAP_MODE_SHIFT))
#define SpeedTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << SpeedTimer_CTRL_TRIG_MODE_SHIFT))
#if (SpeedTimer_UsingFixedFunction)
    #define SpeedTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << SpeedTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << SpeedTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define SpeedTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << SpeedTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << SpeedTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << SpeedTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (SpeedTimer_UsingFixedFunction) */
#define SpeedTimer_INIT_CAPTURE_COUNT      (2u)
#define SpeedTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << SpeedTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (SpeedTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define SpeedTimer_STATUS         (*(reg8 *) SpeedTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define SpeedTimer_STATUS_MASK    (*(reg8 *) SpeedTimer_TimerHW__SR0 )
    #define SpeedTimer_CONTROL        (*(reg8 *) SpeedTimer_TimerHW__CFG0)
    #define SpeedTimer_CONTROL2       (*(reg8 *) SpeedTimer_TimerHW__CFG1)
    #define SpeedTimer_CONTROL2_PTR   ( (reg8 *) SpeedTimer_TimerHW__CFG1)
    #define SpeedTimer_RT1            (*(reg8 *) SpeedTimer_TimerHW__RT1)
    #define SpeedTimer_RT1_PTR        ( (reg8 *) SpeedTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define SpeedTimer_CONTROL3       (*(reg8 *) SpeedTimer_TimerHW__CFG2)
        #define SpeedTimer_CONTROL3_PTR   ( (reg8 *) SpeedTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define SpeedTimer_GLOBAL_ENABLE  (*(reg8 *) SpeedTimer_TimerHW__PM_ACT_CFG)
    #define SpeedTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) SpeedTimer_TimerHW__PM_STBY_CFG)

    #define SpeedTimer_CAPTURE_LSB         (* (reg16 *) SpeedTimer_TimerHW__CAP0 )
    #define SpeedTimer_CAPTURE_LSB_PTR       ((reg16 *) SpeedTimer_TimerHW__CAP0 )
    #define SpeedTimer_PERIOD_LSB          (* (reg16 *) SpeedTimer_TimerHW__PER0 )
    #define SpeedTimer_PERIOD_LSB_PTR        ((reg16 *) SpeedTimer_TimerHW__PER0 )
    #define SpeedTimer_COUNTER_LSB         (* (reg16 *) SpeedTimer_TimerHW__CNT_CMP0 )
    #define SpeedTimer_COUNTER_LSB_PTR       ((reg16 *) SpeedTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define SpeedTimer_BLOCK_EN_MASK                     SpeedTimer_TimerHW__PM_ACT_MSK
    #define SpeedTimer_BLOCK_STBY_EN_MASK                SpeedTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define SpeedTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define SpeedTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define SpeedTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define SpeedTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define SpeedTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define SpeedTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << SpeedTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define SpeedTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define SpeedTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << SpeedTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define SpeedTimer_CTRL_MODE_SHIFT                 0x01u
        #define SpeedTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << SpeedTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define SpeedTimer_CTRL_RCOD_SHIFT        0x02u
        #define SpeedTimer_CTRL_ENBL_SHIFT        0x00u
        #define SpeedTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define SpeedTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << SpeedTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define SpeedTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << SpeedTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define SpeedTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << SpeedTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define SpeedTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << SpeedTimer_CTRL_RCOD_SHIFT))
        #define SpeedTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << SpeedTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define SpeedTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define SpeedTimer_RT1_MASK                        ((uint8)((uint8)0x03u << SpeedTimer_RT1_SHIFT))
    #define SpeedTimer_SYNC                            ((uint8)((uint8)0x03u << SpeedTimer_RT1_SHIFT))
    #define SpeedTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define SpeedTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << SpeedTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define SpeedTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << SpeedTimer_SYNCDSI_SHIFT))

    #define SpeedTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << SpeedTimer_CTRL_MODE_SHIFT))
    #define SpeedTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << SpeedTimer_CTRL_MODE_SHIFT))
    #define SpeedTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << SpeedTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define SpeedTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define SpeedTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define SpeedTimer_STATUS_TC_INT_MASK_SHIFT        (SpeedTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define SpeedTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (SpeedTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define SpeedTimer_STATUS_TC                       ((uint8)((uint8)0x01u << SpeedTimer_STATUS_TC_SHIFT))
    #define SpeedTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << SpeedTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define SpeedTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << SpeedTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define SpeedTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << SpeedTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define SpeedTimer_STATUS              (* (reg8 *) SpeedTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define SpeedTimer_STATUS_MASK         (* (reg8 *) SpeedTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define SpeedTimer_STATUS_AUX_CTRL     (* (reg8 *) SpeedTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define SpeedTimer_CONTROL             (* (reg8 *) SpeedTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(SpeedTimer_Resolution <= 8u) /* 8-bit Timer */
        #define SpeedTimer_CAPTURE_LSB         (* (reg8 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define SpeedTimer_CAPTURE_LSB_PTR       ((reg8 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define SpeedTimer_PERIOD_LSB          (* (reg8 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define SpeedTimer_PERIOD_LSB_PTR        ((reg8 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define SpeedTimer_COUNTER_LSB         (* (reg8 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define SpeedTimer_COUNTER_LSB_PTR       ((reg8 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
    #elif(SpeedTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define SpeedTimer_CAPTURE_LSB         (* (reg16 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define SpeedTimer_CAPTURE_LSB_PTR       ((reg16 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define SpeedTimer_PERIOD_LSB          (* (reg16 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define SpeedTimer_PERIOD_LSB_PTR        ((reg16 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define SpeedTimer_COUNTER_LSB         (* (reg16 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define SpeedTimer_COUNTER_LSB_PTR       ((reg16 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define SpeedTimer_CAPTURE_LSB         (* (reg16 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define SpeedTimer_CAPTURE_LSB_PTR       ((reg16 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define SpeedTimer_PERIOD_LSB          (* (reg16 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define SpeedTimer_PERIOD_LSB_PTR        ((reg16 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define SpeedTimer_COUNTER_LSB         (* (reg16 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
            #define SpeedTimer_COUNTER_LSB_PTR       ((reg16 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(SpeedTimer_Resolution <= 24u)/* 24-bit Timer */
        #define SpeedTimer_CAPTURE_LSB         (* (reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define SpeedTimer_CAPTURE_LSB_PTR       ((reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define SpeedTimer_PERIOD_LSB          (* (reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define SpeedTimer_PERIOD_LSB_PTR        ((reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define SpeedTimer_COUNTER_LSB         (* (reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define SpeedTimer_COUNTER_LSB_PTR       ((reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define SpeedTimer_CAPTURE_LSB         (* (reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define SpeedTimer_CAPTURE_LSB_PTR       ((reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define SpeedTimer_PERIOD_LSB          (* (reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define SpeedTimer_PERIOD_LSB_PTR        ((reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define SpeedTimer_COUNTER_LSB         (* (reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define SpeedTimer_COUNTER_LSB_PTR       ((reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define SpeedTimer_CAPTURE_LSB         (* (reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define SpeedTimer_CAPTURE_LSB_PTR       ((reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define SpeedTimer_PERIOD_LSB          (* (reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define SpeedTimer_PERIOD_LSB_PTR        ((reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define SpeedTimer_COUNTER_LSB         (* (reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
            #define SpeedTimer_COUNTER_LSB_PTR       ((reg32 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define SpeedTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) SpeedTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
    
    #if (SpeedTimer_UsingHWCaptureCounter)
        #define SpeedTimer_CAP_COUNT              (*(reg8 *) SpeedTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define SpeedTimer_CAP_COUNT_PTR          ( (reg8 *) SpeedTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define SpeedTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) SpeedTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define SpeedTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) SpeedTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (SpeedTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define SpeedTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define SpeedTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define SpeedTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define SpeedTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define SpeedTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define SpeedTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << SpeedTimer_CTRL_INTCNT_SHIFT))
    #define SpeedTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << SpeedTimer_CTRL_TRIG_MODE_SHIFT))
    #define SpeedTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << SpeedTimer_CTRL_TRIG_EN_SHIFT))
    #define SpeedTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << SpeedTimer_CTRL_CAP_MODE_SHIFT))
    #define SpeedTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << SpeedTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define SpeedTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define SpeedTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define SpeedTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define SpeedTimer_STATUS_TC_INT_MASK_SHIFT       SpeedTimer_STATUS_TC_SHIFT
    #define SpeedTimer_STATUS_CAPTURE_INT_MASK_SHIFT  SpeedTimer_STATUS_CAPTURE_SHIFT
    #define SpeedTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define SpeedTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define SpeedTimer_STATUS_FIFOFULL_INT_MASK_SHIFT SpeedTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define SpeedTimer_STATUS_TC                      ((uint8)((uint8)0x01u << SpeedTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define SpeedTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << SpeedTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define SpeedTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << SpeedTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define SpeedTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << SpeedTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define SpeedTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << SpeedTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define SpeedTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << SpeedTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define SpeedTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << SpeedTimer_STATUS_FIFOFULL_SHIFT))

    #define SpeedTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define SpeedTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define SpeedTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define SpeedTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define SpeedTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define SpeedTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_SpeedTimer_H */


/* [] END OF FILE */
