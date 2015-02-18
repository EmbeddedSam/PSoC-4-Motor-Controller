/*******************************************************************************
* File Name: MotorPWM.h
* Version 3.10
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_MotorPWM_H)
#define CY_PWM_MotorPWM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 MotorPWM_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define MotorPWM_Resolution                     (8u)
#define MotorPWM_UsingFixedFunction             (0u)
#define MotorPWM_DeadBandMode                   (0u)
#define MotorPWM_KillModeMinTime                (0u)
#define MotorPWM_KillMode                       (0u)
#define MotorPWM_PWMMode                        (0u)
#define MotorPWM_PWMModeIsCenterAligned         (0u)
#define MotorPWM_DeadBandUsed                   (0u)
#define MotorPWM_DeadBand2_4                    (0u)

#if !defined(MotorPWM_PWMUDB_genblk8_stsreg__REMOVED)
    #define MotorPWM_UseStatus                  (1u)
#else
    #define MotorPWM_UseStatus                  (0u)
#endif /* !defined(MotorPWM_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(MotorPWM_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define MotorPWM_UseControl                 (1u)
#else
    #define MotorPWM_UseControl                 (0u)
#endif /* !defined(MotorPWM_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define MotorPWM_UseOneCompareMode              (1u)
#define MotorPWM_MinimumKillTime                (1u)
#define MotorPWM_EnableMode                     (0u)

#define MotorPWM_CompareMode1SW                 (0u)
#define MotorPWM_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_10 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define MotorPWM__B_PWM__DISABLED 0
#define MotorPWM__B_PWM__ASYNCHRONOUS 1
#define MotorPWM__B_PWM__SINGLECYCLE 2
#define MotorPWM__B_PWM__LATCHED 3
#define MotorPWM__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define MotorPWM__B_PWM__DBMDISABLED 0
#define MotorPWM__B_PWM__DBM_2_4_CLOCKS 1
#define MotorPWM__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define MotorPWM__B_PWM__ONE_OUTPUT 0
#define MotorPWM__B_PWM__TWO_OUTPUTS 1
#define MotorPWM__B_PWM__DUAL_EDGE 2
#define MotorPWM__B_PWM__CENTER_ALIGN 3
#define MotorPWM__B_PWM__DITHER 5
#define MotorPWM__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define MotorPWM__B_PWM__LESS_THAN 1
#define MotorPWM__B_PWM__LESS_THAN_OR_EQUAL 2
#define MotorPWM__B_PWM__GREATER_THAN 3
#define MotorPWM__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define MotorPWM__B_PWM__EQUAL 0
#define MotorPWM__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!MotorPWM_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!MotorPWM_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!MotorPWM_PWMModeIsCenterAligned) */
        #if (MotorPWM_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (MotorPWM_UseStatus) */

        /* Backup for Deadband parameters */
        #if(MotorPWM_DeadBandMode == MotorPWM__B_PWM__DBM_256_CLOCKS || \
            MotorPWM_DeadBandMode == MotorPWM__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(MotorPWM_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (MotorPWM_KillModeMinTime) */

        /* Backup control register */
        #if(MotorPWM_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (MotorPWM_UseControl) */

    #endif /* (!MotorPWM_UsingFixedFunction) */

}MotorPWM_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    MotorPWM_Start(void) ;
void    MotorPWM_Stop(void) ;

#if (MotorPWM_UseStatus || MotorPWM_UsingFixedFunction)
    void  MotorPWM_SetInterruptMode(uint8 interruptMode) ;
    uint8 MotorPWM_ReadStatusRegister(void) ;
#endif /* (MotorPWM_UseStatus || MotorPWM_UsingFixedFunction) */

#define MotorPWM_GetInterruptSource() MotorPWM_ReadStatusRegister()

#if (MotorPWM_UseControl)
    uint8 MotorPWM_ReadControlRegister(void) ;
    void  MotorPWM_WriteControlRegister(uint8 control)
          ;
#endif /* (MotorPWM_UseControl) */

#if (MotorPWM_UseOneCompareMode)
   #if (MotorPWM_CompareMode1SW)
       void    MotorPWM_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (MotorPWM_CompareMode1SW) */
#else
    #if (MotorPWM_CompareMode1SW)
        void    MotorPWM_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (MotorPWM_CompareMode1SW) */
    #if (MotorPWM_CompareMode2SW)
        void    MotorPWM_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (MotorPWM_CompareMode2SW) */
#endif /* (MotorPWM_UseOneCompareMode) */

#if (!MotorPWM_UsingFixedFunction)
    uint8   MotorPWM_ReadCounter(void) ;
    uint8 MotorPWM_ReadCapture(void) ;

    #if (MotorPWM_UseStatus)
            void MotorPWM_ClearFIFO(void) ;
    #endif /* (MotorPWM_UseStatus) */

    void    MotorPWM_WriteCounter(uint8 counter)
            ;
#endif /* (!MotorPWM_UsingFixedFunction) */

void    MotorPWM_WritePeriod(uint8 period)
        ;
uint8 MotorPWM_ReadPeriod(void) ;

#if (MotorPWM_UseOneCompareMode)
    void    MotorPWM_WriteCompare(uint8 compare)
            ;
    uint8 MotorPWM_ReadCompare(void) ;
#else
    void    MotorPWM_WriteCompare1(uint8 compare)
            ;
    uint8 MotorPWM_ReadCompare1(void) ;
    void    MotorPWM_WriteCompare2(uint8 compare)
            ;
    uint8 MotorPWM_ReadCompare2(void) ;
#endif /* (MotorPWM_UseOneCompareMode) */


#if (MotorPWM_DeadBandUsed)
    void    MotorPWM_WriteDeadTime(uint8 deadtime) ;
    uint8   MotorPWM_ReadDeadTime(void) ;
#endif /* (MotorPWM_DeadBandUsed) */

#if ( MotorPWM_KillModeMinTime)
    void MotorPWM_WriteKillTime(uint8 killtime) ;
    uint8 MotorPWM_ReadKillTime(void) ;
#endif /* ( MotorPWM_KillModeMinTime) */

void MotorPWM_Init(void) ;
void MotorPWM_Enable(void) ;
void MotorPWM_Sleep(void) ;
void MotorPWM_Wakeup(void) ;
void MotorPWM_SaveConfig(void) ;
void MotorPWM_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define MotorPWM_INIT_PERIOD_VALUE          (255u)
#define MotorPWM_INIT_COMPARE_VALUE1        (0u)
#define MotorPWM_INIT_COMPARE_VALUE2        (129u)
#define MotorPWM_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    MotorPWM_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    MotorPWM_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    MotorPWM_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    MotorPWM_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define MotorPWM_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  MotorPWM_CTRL_CMPMODE2_SHIFT)
#define MotorPWM_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  MotorPWM_CTRL_CMPMODE1_SHIFT)
#define MotorPWM_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (MotorPWM_UsingFixedFunction)
   #define MotorPWM_PERIOD_LSB              (*(reg16 *) MotorPWM_PWMHW__PER0)
   #define MotorPWM_PERIOD_LSB_PTR          ( (reg16 *) MotorPWM_PWMHW__PER0)
   #define MotorPWM_COMPARE1_LSB            (*(reg16 *) MotorPWM_PWMHW__CNT_CMP0)
   #define MotorPWM_COMPARE1_LSB_PTR        ( (reg16 *) MotorPWM_PWMHW__CNT_CMP0)
   #define MotorPWM_COMPARE2_LSB            (0x00u)
   #define MotorPWM_COMPARE2_LSB_PTR        (0x00u)
   #define MotorPWM_COUNTER_LSB             (*(reg16 *) MotorPWM_PWMHW__CNT_CMP0)
   #define MotorPWM_COUNTER_LSB_PTR         ( (reg16 *) MotorPWM_PWMHW__CNT_CMP0)
   #define MotorPWM_CAPTURE_LSB             (*(reg16 *) MotorPWM_PWMHW__CAP0)
   #define MotorPWM_CAPTURE_LSB_PTR         ( (reg16 *) MotorPWM_PWMHW__CAP0)
   #define MotorPWM_RT1                     (*(reg8 *)  MotorPWM_PWMHW__RT1)
   #define MotorPWM_RT1_PTR                 ( (reg8 *)  MotorPWM_PWMHW__RT1)

#else
   #if (MotorPWM_Resolution == 8u) /* 8bit - PWM */

       #if(MotorPWM_PWMModeIsCenterAligned)
           #define MotorPWM_PERIOD_LSB      (*(reg8 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
           #define MotorPWM_PERIOD_LSB_PTR  ((reg8 *)   MotorPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #else
           #define MotorPWM_PERIOD_LSB      (*(reg8 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
           #define MotorPWM_PERIOD_LSB_PTR  ((reg8 *)   MotorPWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
       #endif /* (MotorPWM_PWMModeIsCenterAligned) */

       #define MotorPWM_COMPARE1_LSB        (*(reg8 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define MotorPWM_COMPARE1_LSB_PTR    ((reg8 *)   MotorPWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define MotorPWM_COMPARE2_LSB        (*(reg8 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define MotorPWM_COMPARE2_LSB_PTR    ((reg8 *)   MotorPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define MotorPWM_COUNTERCAP_LSB      (*(reg8 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define MotorPWM_COUNTERCAP_LSB_PTR  ((reg8 *)   MotorPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define MotorPWM_COUNTER_LSB         (*(reg8 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define MotorPWM_COUNTER_LSB_PTR     ((reg8 *)   MotorPWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define MotorPWM_CAPTURE_LSB         (*(reg8 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
       #define MotorPWM_CAPTURE_LSB_PTR     ((reg8 *)   MotorPWM_PWMUDB_sP8_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(MotorPWM_PWMModeIsCenterAligned)
               #define MotorPWM_PERIOD_LSB      (*(reg16 *) MotorPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
               #define MotorPWM_PERIOD_LSB_PTR  ((reg16 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #else
               #define MotorPWM_PERIOD_LSB      (*(reg16 *) MotorPWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
               #define MotorPWM_PERIOD_LSB_PTR  ((reg16 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
            #endif /* (MotorPWM_PWMModeIsCenterAligned) */

            #define MotorPWM_COMPARE1_LSB       (*(reg16 *) MotorPWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define MotorPWM_COMPARE1_LSB_PTR   ((reg16 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define MotorPWM_COMPARE2_LSB       (*(reg16 *) MotorPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define MotorPWM_COMPARE2_LSB_PTR   ((reg16 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define MotorPWM_COUNTERCAP_LSB     (*(reg16 *) MotorPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define MotorPWM_COUNTERCAP_LSB_PTR ((reg16 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define MotorPWM_COUNTER_LSB        (*(reg16 *) MotorPWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define MotorPWM_COUNTER_LSB_PTR    ((reg16 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define MotorPWM_CAPTURE_LSB        (*(reg16 *) MotorPWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
            #define MotorPWM_CAPTURE_LSB_PTR    ((reg16 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
        #else
            #if(MotorPWM_PWMModeIsCenterAligned)
               #define MotorPWM_PERIOD_LSB      (*(reg16 *) MotorPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
               #define MotorPWM_PERIOD_LSB_PTR  ((reg16 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #else
               #define MotorPWM_PERIOD_LSB      (*(reg16 *) MotorPWM_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
               #define MotorPWM_PERIOD_LSB_PTR  ((reg16 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
            #endif /* (MotorPWM_PWMModeIsCenterAligned) */

            #define MotorPWM_COMPARE1_LSB       (*(reg16 *) MotorPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define MotorPWM_COMPARE1_LSB_PTR   ((reg16 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define MotorPWM_COMPARE2_LSB       (*(reg16 *) MotorPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define MotorPWM_COMPARE2_LSB_PTR   ((reg16 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define MotorPWM_COUNTERCAP_LSB     (*(reg16 *) MotorPWM_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define MotorPWM_COUNTERCAP_LSB_PTR ((reg16 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define MotorPWM_COUNTER_LSB        (*(reg16 *) MotorPWM_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define MotorPWM_COUNTER_LSB_PTR    ((reg16 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define MotorPWM_CAPTURE_LSB        (*(reg16 *) MotorPWM_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
            #define MotorPWM_CAPTURE_LSB_PTR    ((reg16 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define MotorPWM_AUX_CONTROLDP1          (*(reg8 *)  MotorPWM_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define MotorPWM_AUX_CONTROLDP1_PTR      ((reg8 *)   MotorPWM_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (MotorPWM_Resolution == 8) */

   #define MotorPWM_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
   #define MotorPWM_AUX_CONTROLDP0          (*(reg8 *)  MotorPWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define MotorPWM_AUX_CONTROLDP0_PTR      ((reg8 *)   MotorPWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (MotorPWM_UsingFixedFunction) */

#if(MotorPWM_KillModeMinTime )
    #define MotorPWM_KILLMODEMINTIME        (*(reg8 *)  MotorPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define MotorPWM_KILLMODEMINTIME_PTR    ((reg8 *)   MotorPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (MotorPWM_KillModeMinTime ) */

#if(MotorPWM_DeadBandMode == MotorPWM__B_PWM__DBM_256_CLOCKS)
    #define MotorPWM_DEADBAND_COUNT         (*(reg8 *)  MotorPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define MotorPWM_DEADBAND_COUNT_PTR     ((reg8 *)   MotorPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define MotorPWM_DEADBAND_LSB_PTR       ((reg8 *)   MotorPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define MotorPWM_DEADBAND_LSB           (*(reg8 *)  MotorPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(MotorPWM_DeadBandMode == MotorPWM__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (MotorPWM_UsingFixedFunction)
        #define MotorPWM_DEADBAND_COUNT         (*(reg8 *)  MotorPWM_PWMHW__CFG0)
        #define MotorPWM_DEADBAND_COUNT_PTR     ((reg8 *)   MotorPWM_PWMHW__CFG0)
        #define MotorPWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << MotorPWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define MotorPWM_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define MotorPWM_DEADBAND_COUNT         (*(reg8 *)  MotorPWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define MotorPWM_DEADBAND_COUNT_PTR     ((reg8 *)   MotorPWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define MotorPWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << MotorPWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define MotorPWM_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (MotorPWM_UsingFixedFunction) */
#endif /* (MotorPWM_DeadBandMode == MotorPWM__B_PWM__DBM_256_CLOCKS) */



#if (MotorPWM_UsingFixedFunction)
    #define MotorPWM_STATUS                 (*(reg8 *) MotorPWM_PWMHW__SR0)
    #define MotorPWM_STATUS_PTR             ((reg8 *) MotorPWM_PWMHW__SR0)
    #define MotorPWM_STATUS_MASK            (*(reg8 *) MotorPWM_PWMHW__SR0)
    #define MotorPWM_STATUS_MASK_PTR        ((reg8 *) MotorPWM_PWMHW__SR0)
    #define MotorPWM_CONTROL                (*(reg8 *) MotorPWM_PWMHW__CFG0)
    #define MotorPWM_CONTROL_PTR            ((reg8 *) MotorPWM_PWMHW__CFG0)
    #define MotorPWM_CONTROL2               (*(reg8 *) MotorPWM_PWMHW__CFG1)
    #define MotorPWM_CONTROL3               (*(reg8 *) MotorPWM_PWMHW__CFG2)
    #define MotorPWM_GLOBAL_ENABLE          (*(reg8 *) MotorPWM_PWMHW__PM_ACT_CFG)
    #define MotorPWM_GLOBAL_ENABLE_PTR      ( (reg8 *) MotorPWM_PWMHW__PM_ACT_CFG)
    #define MotorPWM_GLOBAL_STBY_ENABLE     (*(reg8 *) MotorPWM_PWMHW__PM_STBY_CFG)
    #define MotorPWM_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) MotorPWM_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define MotorPWM_BLOCK_EN_MASK          (MotorPWM_PWMHW__PM_ACT_MSK)
    #define MotorPWM_BLOCK_STBY_EN_MASK     (MotorPWM_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define MotorPWM_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define MotorPWM_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define MotorPWM_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define MotorPWM_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define MotorPWM_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define MotorPWM_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define MotorPWM_CTRL_ENABLE            (uint8)((uint8)0x01u << MotorPWM_CTRL_ENABLE_SHIFT)
    #define MotorPWM_CTRL_RESET             (uint8)((uint8)0x01u << MotorPWM_CTRL_RESET_SHIFT)
    #define MotorPWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << MotorPWM_CTRL_CMPMODE2_SHIFT)
    #define MotorPWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << MotorPWM_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define MotorPWM_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define MotorPWM_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << MotorPWM_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define MotorPWM_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define MotorPWM_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define MotorPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define MotorPWM_STATUS_TC_INT_EN_MASK_SHIFT            (MotorPWM_STATUS_TC_SHIFT - 4u)
    #define MotorPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define MotorPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (MotorPWM_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define MotorPWM_STATUS_TC              (uint8)((uint8)0x01u << MotorPWM_STATUS_TC_SHIFT)
    #define MotorPWM_STATUS_CMP1            (uint8)((uint8)0x01u << MotorPWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define MotorPWM_STATUS_TC_INT_EN_MASK              (uint8)((uint8)MotorPWM_STATUS_TC >> 4u)
    #define MotorPWM_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)MotorPWM_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define MotorPWM_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define MotorPWM_RT1_MASK              (uint8)((uint8)0x03u << MotorPWM_RT1_SHIFT)
    #define MotorPWM_SYNC                  (uint8)((uint8)0x03u << MotorPWM_RT1_SHIFT)
    #define MotorPWM_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define MotorPWM_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << MotorPWM_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define MotorPWM_SYNCDSI_EN            (uint8)((uint8)0x0Fu << MotorPWM_SYNCDSI_SHIFT)


#else
    #define MotorPWM_STATUS                (*(reg8 *)   MotorPWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define MotorPWM_STATUS_PTR            ((reg8 *)    MotorPWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define MotorPWM_STATUS_MASK           (*(reg8 *)   MotorPWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define MotorPWM_STATUS_MASK_PTR       ((reg8 *)    MotorPWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define MotorPWM_STATUS_AUX_CTRL       (*(reg8 *)   MotorPWM_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define MotorPWM_CONTROL               (*(reg8 *)   MotorPWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define MotorPWM_CONTROL_PTR           ((reg8 *)    MotorPWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define MotorPWM_CTRL_ENABLE_SHIFT      (0x07u)
    #define MotorPWM_CTRL_RESET_SHIFT       (0x06u)
    #define MotorPWM_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define MotorPWM_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define MotorPWM_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define MotorPWM_CTRL_ENABLE            (uint8)((uint8)0x01u << MotorPWM_CTRL_ENABLE_SHIFT)
    #define MotorPWM_CTRL_RESET             (uint8)((uint8)0x01u << MotorPWM_CTRL_RESET_SHIFT)
    #define MotorPWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << MotorPWM_CTRL_CMPMODE2_SHIFT)
    #define MotorPWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << MotorPWM_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define MotorPWM_STATUS_KILL_SHIFT          (0x05u)
    #define MotorPWM_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define MotorPWM_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define MotorPWM_STATUS_TC_SHIFT            (0x02u)
    #define MotorPWM_STATUS_CMP2_SHIFT          (0x01u)
    #define MotorPWM_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define MotorPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (MotorPWM_STATUS_KILL_SHIFT)
    #define MotorPWM_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (MotorPWM_STATUS_FIFONEMPTY_SHIFT)
    #define MotorPWM_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (MotorPWM_STATUS_FIFOFULL_SHIFT)
    #define MotorPWM_STATUS_TC_INT_EN_MASK_SHIFT            (MotorPWM_STATUS_TC_SHIFT)
    #define MotorPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (MotorPWM_STATUS_CMP2_SHIFT)
    #define MotorPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (MotorPWM_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define MotorPWM_STATUS_KILL            (uint8)((uint8)0x00u << MotorPWM_STATUS_KILL_SHIFT )
    #define MotorPWM_STATUS_FIFOFULL        (uint8)((uint8)0x01u << MotorPWM_STATUS_FIFOFULL_SHIFT)
    #define MotorPWM_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << MotorPWM_STATUS_FIFONEMPTY_SHIFT)
    #define MotorPWM_STATUS_TC              (uint8)((uint8)0x01u << MotorPWM_STATUS_TC_SHIFT)
    #define MotorPWM_STATUS_CMP2            (uint8)((uint8)0x01u << MotorPWM_STATUS_CMP2_SHIFT)
    #define MotorPWM_STATUS_CMP1            (uint8)((uint8)0x01u << MotorPWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define MotorPWM_STATUS_KILL_INT_EN_MASK            (MotorPWM_STATUS_KILL)
    #define MotorPWM_STATUS_FIFOFULL_INT_EN_MASK        (MotorPWM_STATUS_FIFOFULL)
    #define MotorPWM_STATUS_FIFONEMPTY_INT_EN_MASK      (MotorPWM_STATUS_FIFONEMPTY)
    #define MotorPWM_STATUS_TC_INT_EN_MASK              (MotorPWM_STATUS_TC)
    #define MotorPWM_STATUS_CMP2_INT_EN_MASK            (MotorPWM_STATUS_CMP2)
    #define MotorPWM_STATUS_CMP1_INT_EN_MASK            (MotorPWM_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define MotorPWM_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define MotorPWM_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define MotorPWM_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define MotorPWM_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define MotorPWM_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* MotorPWM_UsingFixedFunction */

#endif  /* CY_PWM_MotorPWM_H */


/* [] END OF FILE */
