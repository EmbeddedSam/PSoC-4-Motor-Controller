/*******************************************************************************
* File Name: MotorCurrentADC.h
* Version 2.0
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Sequencing Successive Approximation ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_ADC_SAR_SEQ_MotorCurrentADC_H)
#define CY_ADC_SAR_SEQ_MotorCurrentADC_H

#include "cytypes.h"
#include "CyLib.h"


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} MotorCurrentADC_BACKUP_STRUCT;


/**************************************
*    Enumerated Types and Parameters
**************************************/

/*  Clock Source setting constants */
#define MotorCurrentADC__EXTERNAL 0
#define MotorCurrentADC__INTERNAL 1

/*  Sample Mode setting constants */
#define MotorCurrentADC__FREERUNNING 0
#define MotorCurrentADC__HARDWARESOC 1

/*  Reference type setting constants */
#define MotorCurrentADC__VDDA_2 0
#define MotorCurrentADC__VDDA 1
#define MotorCurrentADC__INTERNAL1024 2
#define MotorCurrentADC__INTERNAL1024BYPASSED 3
#define MotorCurrentADC__INTERNALVREF 4
#define MotorCurrentADC__INTERNALVREFBYPASSED 5
#define MotorCurrentADC__VDDA_2BYPASSED 6
#define MotorCurrentADC__EXTERNALVREF 7

/* Input buffer gain setting constants */
#define MotorCurrentADC__DISABLED 0
#define MotorCurrentADC__ONE 1
#define MotorCurrentADC__TWO 2
#define MotorCurrentADC__FOUR 3
#define MotorCurrentADC__EIGHT 4
#define MotorCurrentADC__SIXTEEN 5

/* Negative input setting sonstants in single ended mode */
#define MotorCurrentADC__VSS 0
#define MotorCurrentADC__VREF 1
#define MotorCurrentADC__OTHER 2

/* Compare mode setting constants:
*    Mode0 - Disable
*    Mode1 - Result < Low_Limit
*    Mode2 - Low_Limit <= Result < High_Limit
*    Mode3 - High_Limit <= Result
*    Mode4 - (Result < Low_Limit) or (High_Limit <= Result)
*/
#define MotorCurrentADC__MODE0 0
#define MotorCurrentADC__MODE1 1
#define MotorCurrentADC__MODE2 2
#define MotorCurrentADC__MODE3 3

#define MotorCurrentADC__RES8 0
#define MotorCurrentADC__RES10 1

#define MotorCurrentADC__RIGHT 0
#define MotorCurrentADC__LEFT 1

#define MotorCurrentADC__FSIGNED 1
#define MotorCurrentADC__FUNSIGNED 0

#define MotorCurrentADC__ACCUMULATE 0
#define MotorCurrentADC__FIXEDRESOLUTION 1



/***************************************
*   Conditional Compilation Parameters
****************************************/ 

#ifdef CYIPBLOCK_s8pass4al_VERSION
    #define MotorCurrentADC_CY_SAR_IP_VER              (CYIPBLOCK_s8pass4al_VERSION)
#else
    #define MotorCurrentADC_CY_SAR_IP_VER              (0u)
#endif  /* CYIPBLOCK_s8pass4al_VERSION */

#define MotorCurrentADC_CY_SAR_IP_PSOC4                (0u)
#define MotorCurrentADC_CY_SAR_IP_BLE                  (1u)


/***************************************
*    Initial Parameter Constants
***************************************/
#define MotorCurrentADC_DEFAULT_SAMPLE_MODE_SEL        (0u)
#define MotorCurrentADC_DEFAULT_VREF_SEL               (1u)
#define MotorCurrentADC_DEFAULT_NEG_INPUT_SEL          (0u)
#define MotorCurrentADC_DEFAULT_ALT_RESOLUTION_SEL     (0u)
#define MotorCurrentADC_DEFAULT_JUSTIFICATION_SEL      (0u)
#define MotorCurrentADC_DEFAULT_DIFF_RESULT_FORMAT_SEL (1u)
#define MotorCurrentADC_DEFAULT_SE_RESULT_FORMAT_SEL   (1u)
#define MotorCurrentADC_DEFAULT_CLOCK_SOURCE           (1u)
#define MotorCurrentADC_DEFAULT_VREF_MV_VALUE          (5000)
#define MotorCurrentADC_DEFAULT_BUFFER_GAIN            (0u)
#define MotorCurrentADC_DEFAULT_AVG_SAMPLES_NUM        (2u)
#define MotorCurrentADC_DEFAULT_AVG_SAMPLES_DIV        (int16)(0x100u >> (7u - 2u))
#define MotorCurrentADC_DEFAULT_AVG_MODE               (1u)
#define MotorCurrentADC_MAX_RESOLUTION                 (12u)
#define MotorCurrentADC_DEFAULT_LOW_LIMIT              (0u)
#define MotorCurrentADC_DEFAULT_HIGH_LIMIT             (2047u)
#define MotorCurrentADC_DEFAULT_COMPARE_MODE           (0u)
#define MotorCurrentADC_DEFAULT_ACLKS_NUM              (4u)
#define MotorCurrentADC_DEFAULT_BCLKS_NUM              (4u)
#define MotorCurrentADC_DEFAULT_CCLKS_NUM              (4u)
#define MotorCurrentADC_DEFAULT_DCLKS_NUM              (4u)
#define MotorCurrentADC_TOTAL_CHANNELS_NUM             (1u)
#define MotorCurrentADC_SEQUENCED_CHANNELS_NUM         (1u)
#define MotorCurrentADC_DEFAULT_EN_CHANNELS            (1u)
#define MotorCurrentADC_NOMINAL_CLOCK_FREQ             (1000000)
#define MotorCurrentADC_INJ_CHANNEL_ENABLED            (0u)
#define MotorCurrentADC_IRQ_REMOVE                     (0u)

/* Determines whether the configuration contains external negative input. */
#define MotorCurrentADC_SINGLE_PRESENT                 (0u)
#define MotorCurrentADC_CHANNELS_MODE                  (0u)
#define MotorCurrentADC_MAX_CHANNELS_EN_MASK           (0xffffu >> (16u - MotorCurrentADC_SEQUENCED_CHANNELS_NUM))


/***************************************
*        Function Prototypes
***************************************/

void MotorCurrentADC_Start(void);
void MotorCurrentADC_Stop(void);
void MotorCurrentADC_Init(void);
void MotorCurrentADC_Enable(void);
void MotorCurrentADC_StartConvert(void);
void MotorCurrentADC_StopConvert(void);
uint32 MotorCurrentADC_IsEndConversion(uint32 retMode);
int16 MotorCurrentADC_GetResult16(uint32 chan);
void MotorCurrentADC_SetChanMask(uint32 mask);
void MotorCurrentADC_SetLowLimit(uint32 lowLimit);
void MotorCurrentADC_SetHighLimit(uint32 highLimit);
void MotorCurrentADC_SetLimitMask(uint32 mask);
void MotorCurrentADC_SetSatMask(uint32 mask);
void MotorCurrentADC_SetOffset(uint32 chan, int16 offset);
void MotorCurrentADC_SetGain(uint32 chan, int32 adcGain);
#if(MotorCurrentADC_INJ_CHANNEL_ENABLED)
    void MotorCurrentADC_EnableInjection(void);
#endif /* MotorCurrentADC_INJ_CHANNEL_ENABLED */
#if(MotorCurrentADC_DEFAULT_JUSTIFICATION_SEL == MotorCurrentADC__RIGHT)
    int16 MotorCurrentADC_CountsTo_mVolts(uint32 chan, int16 adcCounts);
    int32 MotorCurrentADC_CountsTo_uVolts(uint32 chan, int16 adcCounts);
    float32 MotorCurrentADC_CountsTo_Volts(uint32 chan, int16 adcCounts);
#endif /* End MotorCurrentADC_DEFAULT_JUSTIFICATION_SEL == MotorCurrentADC__RIGHT */
void MotorCurrentADC_Sleep(void);
void MotorCurrentADC_Wakeup(void);
void MotorCurrentADC_SaveConfig(void);
void MotorCurrentADC_RestoreConfig(void);

CY_ISR_PROTO( MotorCurrentADC_ISR );


/**************************************
*           API Constants
**************************************/
/* Constants for Sleep mode states */
#define MotorCurrentADC_STARTED                    (0x02u)
#define MotorCurrentADC_ENABLED                    (0x01u)
#define MotorCurrentADC_DISABLED                   (0x00u)

/*   Constants for IsEndConversion() "retMode" parameter  */
#define MotorCurrentADC_RETURN_STATUS              (0x01u)
#define MotorCurrentADC_WAIT_FOR_RESULT            (0x02u)
#define MotorCurrentADC_RETURN_STATUS_INJ          (0x04u)
#define MotorCurrentADC_WAIT_FOR_RESULT_INJ        (0x08u)

#define MotorCurrentADC_MAX_FREQUENCY              (18000000)       /*18Mhz*/

#define MotorCurrentADC_RESOLUTION_12              (12u)
#define MotorCurrentADC_RESOLUTION_10              (10u)
#define MotorCurrentADC_RESOLUTION_8               (8u)

#define MotorCurrentADC_10US_DELAY                 (10u)

#define MotorCurrentADC_10V_COUNTS                 (10.0F)
#define MotorCurrentADC_10MV_COUNTS                (10000)
#define MotorCurrentADC_10UV_COUNTS                (10000000L)


/***************************************
* Global variables external identifier
***************************************/

extern uint8 MotorCurrentADC_initVar;
extern volatile int16 MotorCurrentADC_offset[MotorCurrentADC_TOTAL_CHANNELS_NUM];
extern volatile int32 MotorCurrentADC_countsPer10Volt[MotorCurrentADC_TOTAL_CHANNELS_NUM];


/***************************************
*              Registers
***************************************/

#define MotorCurrentADC_SAR_CTRL_REG                (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_CTRL )
#define MotorCurrentADC_SAR_CTRL_PTR                ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_CTRL )

#define MotorCurrentADC_SAR_SAMPLE_CTRL_REG         (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_SAMPLE_CTRL )
#define MotorCurrentADC_SAR_SAMPLE_CTRL_PTR         ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_SAMPLE_CTRL )

#define MotorCurrentADC_SAR_SAMPLE_TIME01_REG       (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_SAMPLE_TIME01 )
#define MotorCurrentADC_SAR_SAMPLE_TIME01_PTR       ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_SAMPLE_TIME01 )

#define MotorCurrentADC_SAR_SAMPLE_TIME23_REG       (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_SAMPLE_TIME23 )
#define MotorCurrentADC_SAR_SAMPLE_TIME23_PTR       ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_SAMPLE_TIME23 )

#define MotorCurrentADC_SAR_RANGE_THRES_REG         (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_RANGE_THRES )
#define MotorCurrentADC_SAR_RANGE_THRES_PTR         ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_RANGE_THRES )

#define MotorCurrentADC_SAR_RANGE_COND_REG          (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_RANGE_COND )
#define MotorCurrentADC_SAR_RANGE_COND_PTR          ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_RANGE_COND )

#define MotorCurrentADC_SAR_CHAN_EN_REG             (*(reg32 *) CYREG_SAR_CHAN_EN )
#define MotorCurrentADC_SAR_CHAN_EN_PTR             ( (reg32 *) CYREG_SAR_CHAN_EN )

#define MotorCurrentADC_SAR_START_CTRL_REG          (*(reg32 *) CYREG_SAR_START_CTRL )
#define MotorCurrentADC_SAR_START_CTRL_PTR          ( (reg32 *) CYREG_SAR_START_CTRL )

#define MotorCurrentADC_SAR_DFT_CTRL_REG            (*(reg32 *) CYREG_SAR_DFT_CTRL )
#define MotorCurrentADC_SAR_DFT_CTRL_PTR            ( (reg32 *) CYREG_SAR_DFT_CTRL )

#define MotorCurrentADC_SAR_CHAN_CONFIG_REG         (*(reg32 *) CYREG_SAR_CHAN_CONFIG00 )
#define MotorCurrentADC_SAR_CHAN_CONFIG_PTR         ( (reg32 *) CYREG_SAR_CHAN_CONFIG00 )
#define MotorCurrentADC_SAR_CHAN_CONFIG_IND         CYREG_SAR_CHAN_CONFIG00

#define MotorCurrentADC_SAR_CHAN_WORK_REG           (*(reg32 *) CYREG_SAR_CHAN_WORK00 )
#define MotorCurrentADC_SAR_CHAN_WORK_PTR           ( (reg32 *) CYREG_SAR_CHAN_WORK00 )

#define MotorCurrentADC_SAR_CHAN_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT00 )
#define MotorCurrentADC_SAR_CHAN_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT00 )
#define MotorCurrentADC_SAR_CHAN_RESULT_IND         CYREG_SAR_CHAN_RESULT00

#define MotorCurrentADC_SAR_CHAN0_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT00 )
#define MotorCurrentADC_SAR_CHAN0_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT00 )

#define MotorCurrentADC_SAR_CHAN1_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT01 )
#define MotorCurrentADC_SAR_CHAN1_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT01 )

#define MotorCurrentADC_SAR_CHAN2_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT02 )
#define MotorCurrentADC_SAR_CHAN2_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT02 )

#define MotorCurrentADC_SAR_CHAN3_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT03 )
#define MotorCurrentADC_SAR_CHAN3_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT03 )

#define MotorCurrentADC_SAR_CHAN4_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT04 )
#define MotorCurrentADC_SAR_CHAN4_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT04 )

#define MotorCurrentADC_SAR_CHAN5_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT05 )
#define MotorCurrentADC_SAR_CHAN5_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT05 )

#define MotorCurrentADC_SAR_CHAN6_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT06 )
#define MotorCurrentADC_SAR_CHAN6_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT06 )

#define MotorCurrentADC_SAR_CHAN7_RESULT_REG         (*(reg32 *) CYREG_SAR_CHAN_RESULT07 )
#define MotorCurrentADC_SAR_CHAN7_RESULT_PTR         ( (reg32 *) CYREG_SAR_CHAN_RESULT07 )

#define MotorCurrentADC_SAR_CHAN_WORK_VALID_REG     (*(reg32 *) CYREG_SAR_CHAN_WORK_VALID)
#define MotorCurrentADC_SAR_CHAN_WORK_VALID_PTR     ( (reg32 *) CYREG_SAR_CHAN_WORK_VALID)

#define MotorCurrentADC_SAR_CHAN_RESULT_VALID_REG   ( *(reg32 *) CYREG_SAR_CHAN_RESULT_VALID )
#define MotorCurrentADC_SAR_CHAN_RESULT_VALID_PTR   ( (reg32 *) CYREG_SAR_CHAN_RESULT_VALID )

#define MotorCurrentADC_SAR_STATUS_REG              (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_STATUS )
#define MotorCurrentADC_SAR_STATUS_PTR              ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_STATUS )

#define MotorCurrentADC_SAR_AVG_START_REG           (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_AVG_STAT )
#define MotorCurrentADC_SAR_AVG_START_PTR           ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_AVG_STAT )

#define MotorCurrentADC_SAR_INTR_REG                (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_INTR )
#define MotorCurrentADC_SAR_INTR_PTR                ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_INTR )

#define MotorCurrentADC_SAR_INTR_SET_REG            (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_INTR_SET )
#define MotorCurrentADC_SAR_INTR_SET_PTR            ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_INTR_SET )

#define MotorCurrentADC_SAR_INTR_MASK_REG           (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_INTR_MASK )
#define MotorCurrentADC_SAR_INTR_MASK_PTR           ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_INTR_MASK )

#define MotorCurrentADC_SAR_INTR_MASKED_REG         (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_INTR_MASKED )
#define MotorCurrentADC_SAR_INTR_MASKED_PTR         ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_INTR_MASKED )

#define MotorCurrentADC_SAR_SATURATE_INTR_REG       (*(reg32 *) CYREG_SAR_SATURATE_INTR )
#define MotorCurrentADC_SAR_SATURATE_INTR_PTR       ( (reg32 *) CYREG_SAR_SATURATE_INTR )

#define MotorCurrentADC_SAR_SATURATE_INTR_SET_REG   (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_SATURATE_INTR_SET )
#define MotorCurrentADC_SAR_SATURATE_INTR_SET_PTR   ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_SATURATE_INTR_SET )

#define MotorCurrentADC_SAR_SATURATE_INTR_MASK_REG  (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_SATURATE_INTR_MASK )
#define MotorCurrentADC_SAR_SATURATE_INTR_MASK_PTR  ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_SATURATE_INTR_MASK )

#define MotorCurrentADC_SAR_SATURATE_INTR_MASKED_REG \
                                                 (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_SATURATE_INTR_MASKED )
#define MotorCurrentADC_SAR_SATURATE_INTR_MASKED_PTR \
                                                 ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_SATURATE_INTR_MASKED )

#define MotorCurrentADC_SAR_RANGE_INTR_REG          (*(reg32 *) CYREG_SAR_RANGE_INTR )
#define MotorCurrentADC_SAR_RANGE_INTR_PTR          ( (reg32 *) CYREG_SAR_RANGE_INTR )

#define MotorCurrentADC_SAR_RANGE_INTR_SET_REG      (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_RANGE_INTR_SET )
#define MotorCurrentADC_SAR_RANGE_INTR_SET_PTR      ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_RANGE_INTR_SET )

#define MotorCurrentADC_SAR_RANGE_INTR_MASK_REG     (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_RANGE_INTR_MASK )
#define MotorCurrentADC_SAR_RANGE_INTR_MASK_PTR     ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_RANGE_INTR_MASK )

#define MotorCurrentADC_SAR_RANGE_INTR_MASKED_REG   (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_RANGE_INTR_MASKED )
#define MotorCurrentADC_SAR_RANGE_INTR_MASKED_PTR   ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_RANGE_INTR_MASKED )

#define MotorCurrentADC_SAR_INTR_CAUSE_REG          (*(reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_INTR_CAUSE )
#define MotorCurrentADC_SAR_INTR_CAUSE_PTR          ( (reg32 *) MotorCurrentADC_cy_psoc4_sar__SAR_INTR_CAUSE )

#define MotorCurrentADC_SAR_INJ_CHAN_CONFIG_REG     (*(reg32 *) CYREG_SAR_INJ_CHAN_CONFIG)
#define MotorCurrentADC_SAR_INJ_CHAN_CONFIG_PTR     ( (reg32 *) CYREG_SAR_INJ_CHAN_CONFIG)

#define MotorCurrentADC_SAR_INJ_RESULT_REG          (*(reg32 *) CYREG_SAR_INJ_RESULT )
#define MotorCurrentADC_SAR_INJ_RESULT_PTR          ( (reg32 *) CYREG_SAR_INJ_RESULT )

#define MotorCurrentADC_MUX_SWITCH0_REG             (*(reg32 *)  CYREG_SAR_MUX_SWITCH0 )
#define MotorCurrentADC_MUX_SWITCH0_PTR             ( (reg32 *)  CYREG_SAR_MUX_SWITCH0 )

#define MotorCurrentADC_MUX_SWITCH_HW_CTRL_REG      (*(reg32 *)  CYREG_SAR_MUX_SWITCH_HW_CTRL )
#define MotorCurrentADC_MUX_SWITCH_HW_CTRL_PTR      ( (reg32 *)  CYREG_SAR_MUX_SWITCH_HW_CTRL )

#define MotorCurrentADC_PUMP_CTRL_REG               (*(reg32 *)  CYREG_SAR_PUMP_CTRL )
#define MotorCurrentADC_PUMP_CTRL_PTR               ( (reg32 *)  CYREG_SAR_PUMP_CTRL )

#define MotorCurrentADC_ANA_TRIM_REG                (*(reg32 *)  CYREG_SAR_ANA_TRIM )
#define MotorCurrentADC_ANA_TRIM_PTR                ( (reg32 *)  CYREG_SAR_ANA_TRIM )

#define MotorCurrentADC_WOUNDING_REG                (*(reg32 *)  CYREG_SAR_WOUNDING )
#define MotorCurrentADC_WOUNDING_PTR                ( (reg32 *)  CYREG_SAR_WOUNDING )


/**************************************
*       Register Constants
**************************************/
#define MotorCurrentADC_INTC_NUMBER                (MotorCurrentADC_IRQ__INTC_NUMBER)
#define MotorCurrentADC_INTC_PRIOR_NUMBER          (MotorCurrentADC_IRQ__INTC_PRIOR_NUM)

/* defines for CTRL register */
#define MotorCurrentADC_VREF_INTERNAL1024          (0x00000040Lu)
#define MotorCurrentADC_VREF_EXTERNAL              (0x00000050Lu)
#define MotorCurrentADC_VREF_VDDA_2                (0x00000060Lu)
#define MotorCurrentADC_VREF_VDDA                  (0x00000070Lu)
#define MotorCurrentADC_VREF_INTERNAL1024BYPASSED  (0x000000C0Lu)
#define MotorCurrentADC_VREF_VDDA_2BYPASSED        (0x000000E0Lu)
#define MotorCurrentADC_VREF_INTERNALVREF          (0x00000000Lu)
#define MotorCurrentADC_VREF_INTERNALVREFBYPASSED  (0x00000000Lu)

#define MotorCurrentADC_NEG_VSSA_KELVIN            (0x00000000Lu)
#define MotorCurrentADC_NEG_VSSA                   (0x00000200Lu)
#define MotorCurrentADC_NEG_VREF                   (0x00000E00Lu)
#if(MotorCurrentADC_TOTAL_CHANNELS_NUM > 1u)
    #define MotorCurrentADC_NEG_OTHER              (uint16)((uint16)MotorCurrentADC_cy_psoc4_sarmux_8__VNEG << 9u)
#else
    #define MotorCurrentADC_NEG_OTHER              (0)
#endif /* MotorCurrentADC_TOTAL_CHANNELS_NUM > 1u */

#define MotorCurrentADC_SAR_HW_CTRL_NEGVREF        (0x00002000Lu)

#define MotorCurrentADC_NORMAL_PWR                 (0x00000000Lu)
#define MotorCurrentADC_HALF_PWR                   (0x01000000Lu)
#define MotorCurrentADC_MORE_PWR                   (0x02000000Lu)
#define MotorCurrentADC_QUARTER_PWR                (0x03000000Lu)

#define MotorCurrentADC_DSI_SYNC_CONFIG            (0x10000000Lu)
#define MotorCurrentADC_DSI_MODE                   (0x20000000Lu)
#define MotorCurrentADC_SWITCH_DISABLE             (0x40000000Lu)
#define MotorCurrentADC_ENABLE                     (0x80000000Lu)

/* defines for STATUS register */
#define MotorCurrentADC_STATUS_BUSY                (0x80000000Lu)

/* defines for SAMPLE_CTRL register */
#define MotorCurrentADC_ALT_RESOLUTION_10BIT       (0x00000001Lu)
#define MotorCurrentADC_ALT_RESOLUTION_8BIT        (0x00000000Lu)

#define MotorCurrentADC_DATA_ALIGN_LEFT            (0x00000002Lu)
#define MotorCurrentADC_DATA_ALIGN_RIGHT           (0x00000000Lu)

#define MotorCurrentADC_SE_SIGNED_RESULT           (0x00000004Lu)
#define MotorCurrentADC_SE_UNSIGNED_RESULT         (0x00000000Lu)

#define MotorCurrentADC_DIFF_SIGNED_RESULT         (0x00000008Lu)
#define MotorCurrentADC_DIFF_UNSIGNED_RESULT       (0x00000000Lu)

#define MotorCurrentADC_AVG_CNT_OFFSET             (4u)
#define MotorCurrentADC_AVG_CNT_MASK               (0x00000070Lu)
#define MotorCurrentADC_AVG_SHIFT                  (0x00000080Lu)

#define MotorCurrentADC_CONTINUOUS_EN              (0x00010000Lu)
#define MotorCurrentADC_DSI_TRIGGER_EN             (0x00020000Lu)
#define MotorCurrentADC_DSI_TRIGGER_LEVEL          (0x00040000Lu)
#define MotorCurrentADC_DSI_SYNC_TRIGGER           (0x00080000Lu)
#define MotorCurrentADC_EOS_DSI_OUT_EN             (0x80000000Lu)

/* defines for SAMPLE_TIME01 / SAMPLE_TIME23 registers */
#define MotorCurrentADC_SAMPLE_TIME13_OFFSET       (16u)
#define MotorCurrentADC_SAMPLE_TIME02_MASK         (0x000003FFLu)
#define MotorCurrentADC_SAMPLE_TIME13_MASK         (0x03FF0000Lu)

/* defines for RANGE_THRES registers */
#define MotorCurrentADC_RANGE_HIGH_OFFSET          (16u)
#define MotorCurrentADC_RANGE_HIGH_MASK            (0xFFFF0000Lu)
#define MotorCurrentADC_RANGE_LOW_MASK             (0x0000FFFFLu)

/* defines for RANGE_COND register */
/* Compare mode setting constants:
*    BELOW   - Result < Low_Limit
*    INSIDE  - Low_Limit <= Result < High_Limit
*    ABOVE   - High_Limit <= Result
*    OUTSIDE - (Result < Low_Limit) or (High_Limit <= Result)
*/
#define MotorCurrentADC_CMP_MODE_BELOW             (0x00000000Lu)
#define MotorCurrentADC_CMP_MODE_INSIDE            (0x40000000Lu)
#define MotorCurrentADC_CMP_MODE_ABOVE             (0x80000000Lu)
#define MotorCurrentADC_CMP_MODE_OUTSIDE           (0xC0000000Lu)
#define MotorCurrentADC_CMP_OFFSET                 (30u)

/* defines for _START_CTRL register */
#define MotorCurrentADC_FW_TRIGGER                 (0x00000001Lu)

/* defines for DFT_CTRL register */
#define MotorCurrentADC_DLY_INC                    (0x00000001Lu)
#define MotorCurrentADC_HIZ                        (0x00000002Lu)
#define MotorCurrentADC_DFT_INC_MASK               (0x000F0000Lu)
#define MotorCurrentADC_DFT_OUTC_MASK              (0x00700000Lu)
#define MotorCurrentADC_SEL_CSEL_DFT_MASK          (0x0F000000Lu)

/* configuration for clock speed > 9 Mhz based on
* characterization results
*/
#define MotorCurrentADC_SEL_CSEL_DFT_CHAR          (0x03000000Lu)
#define MotorCurrentADC_EN_CSEL_DFT                (0x10000000Lu)
#define MotorCurrentADC_DCEN                       (0x20000000Lu)
#define MotorCurrentADC_ADFT_OVERRIDE              (0x80000000Lu)

/* defines for CHAN_CONFIG / DIE_CHAN_CONFIG register
*  and channelsConfig parameter
*/
#define MotorCurrentADC_SARMUX_VIRT_SELECT         (0x00000070Lu)
#define MotorCurrentADC_DIFFERENTIAL_EN            (0x00000100Lu)
#define MotorCurrentADC_ALT_RESOLUTION_ON          (0x00000200Lu)
#define MotorCurrentADC_AVERAGING_EN               (0x00000400Lu)

#define MotorCurrentADC_SAMPLE_TIME_SEL_SHIFT      (12u)
#define MotorCurrentADC_SAMPLE_TIME_SEL_MASK       (0x00003000Lu)

#define MotorCurrentADC_CHANNEL_CONFIG_MASK        (0x00003700Lu)

/* for CHAN_CONFIG only */
#define MotorCurrentADC_DSI_OUT_EN                 (0x80000000Lu)

/* for INJ_CHAN_CONFIG only */
#define MotorCurrentADC_INJ_TAILGATING             (0x40000000Lu)
#define MotorCurrentADC_INJ_CHAN_EN                (0x80000000Lu)

/* defines for CHAN_WORK register */
#define MotorCurrentADC_SAR_WRK_MAX_12BIT          (0x00001000Lu)
#define MotorCurrentADC_SAR_WRK_MAX_10BIT          (0x00000400Lu)
#define MotorCurrentADC_SAR_WRK_MAX_8BIT           (0x00000100Lu)

/* defines for CHAN_RESULT register */
#define MotorCurrentADC_RESULT_MASK                (0x0000FFFFLu)
#define MotorCurrentADC_SATURATE_INTR_MIR          (0x20000000Lu)
#define MotorCurrentADC_RANGE_INTR_MIR             (0x40000000Lu)
#define MotorCurrentADC_CHAN_RESULT_VALID_MIR      (0x80000000Lu)

/* defines for INTR_MASK register */
#define MotorCurrentADC_EOS_MASK                   (0x00000001Lu)
#define MotorCurrentADC_OVERFLOW_MASK              (0x00000002Lu)
#define MotorCurrentADC_FW_COLLISION_MASK          (0x00000004Lu)
#define MotorCurrentADC_DSI_COLLISION_MASK         (0x00000008Lu)
#define MotorCurrentADC_INJ_EOC_MASK               (0x00000010Lu)
#define MotorCurrentADC_INJ_SATURATE_MASK          (0x00000020Lu)
#define MotorCurrentADC_INJ_RANGE_MASK             (0x00000040Lu)
#define MotorCurrentADC_INJ_COLLISION_MASK         (0x00000080Lu)

/* defines for INJ_RESULT register */
#define MotorCurrentADC_INJ_COLLISION_INTR_MIR     (0x10000000Lu)
#define MotorCurrentADC_INJ_SATURATE_INTR_MIR      (0x20000000Lu)
#define MotorCurrentADC_INJ_RANGE_INTR_MIR         (0x40000000Lu)
#define MotorCurrentADC_INJ_EOC_INTR_MIR           (0x80000000Lu)

/* defines for MUX_SWITCH0 register */
#define MotorCurrentADC_MUX_FW_VSSA_VMINUS         (0x00010000Lu)

/* defines for PUMP_CTRL register */
#define MotorCurrentADC_PUMP_CTRL_ENABLED          (0x80000000Lu)

/* additional defines for channelsConfig parameter */
#define MotorCurrentADC_IS_SATURATE_EN_MASK        (0x00000001Lu)
#define MotorCurrentADC_IS_RANGE_CTRL_EN_MASK      (0x00000002Lu)

/* defines for WOUNDING register */
#define MotorCurrentADC_WOUNDING_12BIT             (0x00000000Lu)
#define MotorCurrentADC_WOUNDING_10BIT             (0x00000001Lu)
#define MotorCurrentADC_WOUNDING_8BIT              (0x00000002Lu)

/* Trim value based on characterization */
#define MotorCurrentADC_TRIM_COEF                  (2u)

#if(MotorCurrentADC_MAX_RESOLUTION == MotorCurrentADC_RESOLUTION_10)
    #define MotorCurrentADC_ALT_WOUNDING           MotorCurrentADC_WOUNDING_10BIT
#else
    #define MotorCurrentADC_ALT_WOUNDING           MotorCurrentADC_WOUNDING_8BIT
#endif /* MotorCurrentADC_MAX_RESOLUTION == MotorCurrentADC_RESOLUTION_10 */

#if(MotorCurrentADC_DEFAULT_VREF_SEL == MotorCurrentADC__VDDA_2)
    #define MotorCurrentADC_DEFAULT_VREF_SOURCE    MotorCurrentADC_VREF_VDDA_2
#elif(MotorCurrentADC_DEFAULT_VREF_SEL == MotorCurrentADC__VDDA)
    #define MotorCurrentADC_DEFAULT_VREF_SOURCE    MotorCurrentADC_VREF_VDDA
#elif(MotorCurrentADC_DEFAULT_VREF_SEL == MotorCurrentADC__INTERNAL1024)
    #define MotorCurrentADC_DEFAULT_VREF_SOURCE    MotorCurrentADC_VREF_INTERNAL1024
#elif(MotorCurrentADC_DEFAULT_VREF_SEL == MotorCurrentADC__INTERNAL1024BYPASSED)
    #define MotorCurrentADC_DEFAULT_VREF_SOURCE    MotorCurrentADC_VREF_INTERNAL1024BYPASSED
#elif(MotorCurrentADC_DEFAULT_VREF_SEL == MotorCurrentADC__INTERNALVREF)
    #define MotorCurrentADC_DEFAULT_VREF_SOURCE    MotorCurrentADC_VREF_INTERNALVREF
#elif(MotorCurrentADC_DEFAULT_VREF_SEL == MotorCurrentADC__INTERNALVREFBYPASSED)
    #define MotorCurrentADC_DEFAULT_VREF_SOURCE    MotorCurrentADC_VREF_INTERNALVREFBYPASSED
#elif(MotorCurrentADC_DEFAULT_VREF_SEL == MotorCurrentADC__VDDA_2BYPASSED)
    #define MotorCurrentADC_DEFAULT_VREF_SOURCE    MotorCurrentADC_VREF_VDDA_2BYPASSED
#else
    #define MotorCurrentADC_DEFAULT_VREF_SOURCE    MotorCurrentADC_VREF_EXTERNAL
#endif /* MotorCurrentADC_DEFAULT_VREF_SEL == MotorCurrentADC__VDDA_2 */

#if(MotorCurrentADC_DEFAULT_NEG_INPUT_SEL == MotorCurrentADC__VSS)
    /* Connect NEG input of SARADC to VSSA close to the SARADC for single channel mode */
    #if(MotorCurrentADC_TOTAL_CHANNELS_NUM == 1u)
        #define MotorCurrentADC_DEFAULT_SE_NEG_INPUT    MotorCurrentADC_NEG_VSSA
    #else
        #define MotorCurrentADC_DEFAULT_SE_NEG_INPUT    MotorCurrentADC_NEG_VSSA_KELVIN
    #endif /* (MotorCurrentADC_TOTAL_CHANNELS_NUM == 1u) */
    /* Do not connect VSSA to VMINUS when one channel in differential mode used */
    #if((MotorCurrentADC_TOTAL_CHANNELS_NUM == 1u) && (MotorCurrentADC_CHANNELS_MODE != 0u))
        #define MotorCurrentADC_DEFAULT_MUX_SWITCH0     0u
    #else    /* miltiple channels or one single channel */
        #define MotorCurrentADC_DEFAULT_MUX_SWITCH0     MotorCurrentADC_MUX_FW_VSSA_VMINUS
    #endif /* (MotorCurrentADC_TOTAL_CHANNELS_NUM == 1u) */
#elif(MotorCurrentADC_DEFAULT_NEG_INPUT_SEL == MotorCurrentADC__VREF)
    /* Do not connect VNEG to VREF when one channel in differential mode used */
    #if((MotorCurrentADC_TOTAL_CHANNELS_NUM == 1u) && (MotorCurrentADC_CHANNELS_MODE != 0u))
        #define MotorCurrentADC_DEFAULT_SE_NEG_INPUT    0u
    #else    /* miltiple channels or one single channel */
        #define MotorCurrentADC_DEFAULT_SE_NEG_INPUT    MotorCurrentADC_NEG_VREF
    #endif /* (MotorCurrentADC_TOTAL_CHANNELS_NUM == 1u) */
    #define MotorCurrentADC_DEFAULT_MUX_SWITCH0     0u
#elif (MotorCurrentADC_SINGLE_PRESENT != 0u)
    #define MotorCurrentADC_DEFAULT_SE_NEG_INPUT    MotorCurrentADC_NEG_OTHER
    #define MotorCurrentADC_DEFAULT_MUX_SWITCH0     0u
#else
    #define MotorCurrentADC_DEFAULT_SE_NEG_INPUT    0u
    #define MotorCurrentADC_DEFAULT_MUX_SWITCH0     0u
#endif /* MotorCurrentADC_DEFAULT_NEG_INPUT_SEL == MotorCurrentADC__VREF */

/* If the SAR is configured for multiple channels, always set SAR_HW_CTRL_NEGVREF to 1 */
#if(MotorCurrentADC_TOTAL_CHANNELS_NUM == 1u)
    #define MotorCurrentADC_DEFAULT_HW_CTRL_NEGVREF 0u
#else
    #define MotorCurrentADC_DEFAULT_HW_CTRL_NEGVREF MotorCurrentADC_SAR_HW_CTRL_NEGVREF
#endif /* (MotorCurrentADC_TOTAL_CHANNELS_NUM == 1u) */


#if(MotorCurrentADC_DEFAULT_ALT_RESOLUTION_SEL == MotorCurrentADC__RES8)
    #define MotorCurrentADC_DEFAULT_ALT_RESOLUTION     (MotorCurrentADC_ALT_RESOLUTION_8BIT)
    #define MotorCurrentADC_DEFAULT_MAX_WRK_ALT        (MotorCurrentADC_SAR_WRK_MAX_8BIT)
#else
    #define MotorCurrentADC_DEFAULT_ALT_RESOLUTION     (MotorCurrentADC_ALT_RESOLUTION_10BIT)
    #define MotorCurrentADC_DEFAULT_MAX_WRK_ALT        (MotorCurrentADC_SAR_WRK_MAX_10BIT)
#endif /* End MotorCurrentADC_DEFAULT_ALT_RESOLUTION_SEL == MotorCurrentADC__RES8 */

#if(MotorCurrentADC_DEFAULT_JUSTIFICATION_SEL == MotorCurrentADC__RIGHT)
    #define MotorCurrentADC_DEFAULT_JUSTIFICATION  MotorCurrentADC_DATA_ALIGN_RIGHT
#else
    #define MotorCurrentADC_DEFAULT_JUSTIFICATION  MotorCurrentADC_DATA_ALIGN_LEFT
#endif /* MotorCurrentADC_DEFAULT_JUSTIFICATION_SEL == MotorCurrentADC__RIGHT */

#if(MotorCurrentADC_DEFAULT_DIFF_RESULT_FORMAT_SEL == MotorCurrentADC__FSIGNED)
    #define MotorCurrentADC_DEFAULT_DIFF_RESULT_FORMAT MotorCurrentADC_DIFF_SIGNED_RESULT
#else
    #define MotorCurrentADC_DEFAULT_DIFF_RESULT_FORMAT MotorCurrentADC_DIFF_UNSIGNED_RESULT
#endif /* MotorCurrentADC_DEFAULT_DIFF_RESULT_FORMAT_SEL == MotorCurrentADC__FSIGNED */

#if(MotorCurrentADC_DEFAULT_SE_RESULT_FORMAT_SEL == MotorCurrentADC__FSIGNED)
    #define MotorCurrentADC_DEFAULT_SE_RESULT_FORMAT MotorCurrentADC_SE_SIGNED_RESULT
#else
    #define MotorCurrentADC_DEFAULT_SE_RESULT_FORMAT MotorCurrentADC_SE_UNSIGNED_RESULT
#endif /* MotorCurrentADC_DEFAULT_SE_RESULT_FORMAT_SEL == MotorCurrentADC__FSIGNED */

#if(MotorCurrentADC_DEFAULT_SAMPLE_MODE_SEL == MotorCurrentADC__FREERUNNING)
    #define MotorCurrentADC_DSI_TRIGGER        0u
#else /* Firmware trigger */
    #define MotorCurrentADC_DSI_TRIGGER        (MotorCurrentADC_DSI_TRIGGER_EN | MotorCurrentADC_DSI_SYNC_TRIGGER)
#endif /* End MotorCurrentADC_DEFAULT_SAMPLE_MODE == MotorCurrentADC__FREERUNNING */

#if(MotorCurrentADC_INJ_CHANNEL_ENABLED)
    #define MotorCurrentADC_SAR_INTR_MASK      (MotorCurrentADC_EOS_MASK | MotorCurrentADC_INJ_EOC_MASK)
#else
    #define MotorCurrentADC_SAR_INTR_MASK      (MotorCurrentADC_EOS_MASK)
#endif /* MotorCurrentADC_INJ_CHANNEL_ENABLED*/

#if(MotorCurrentADC_DEFAULT_AVG_MODE == MotorCurrentADC__FIXEDRESOLUTION)
    #define MotorCurrentADC_AVG_SHIFT_MODE     MotorCurrentADC_AVG_SHIFT
#else
    #define MotorCurrentADC_AVG_SHIFT_MODE     0u
#endif /* End MotorCurrentADC_DEFAULT_AVG_MODE */

#define MotorCurrentADC_COMPARE_MODE           (uint32)((uint32)(MotorCurrentADC_DEFAULT_COMPARE_MODE) \
                                                << MotorCurrentADC_CMP_OFFSET)

#if(MotorCurrentADC_TOTAL_CHANNELS_NUM > 1u)
    #define MotorCurrentADC_DEFAULT_SWITCH_CONF    0u
#else /* Disable SAR sequencer from enabling routing switches in single channel mode */
    #define MotorCurrentADC_DEFAULT_SWITCH_CONF    MotorCurrentADC_SWITCH_DISABLE
#endif /* End MotorCurrentADC_TOTAL_CHANNELS_NUM > 1 */

#define MotorCurrentADC_DEFAULT_POWER \
       ((MotorCurrentADC_NOMINAL_CLOCK_FREQ > (MotorCurrentADC_MAX_FREQUENCY / 4)) ? MotorCurrentADC_NORMAL_PWR : \
       ((MotorCurrentADC_NOMINAL_CLOCK_FREQ > (MotorCurrentADC_MAX_FREQUENCY / 8)) ? MotorCurrentADC_HALF_PWR : \
                                                                                       MotorCurrentADC_QUARTER_PWR))

#define MotorCurrentADC_DEFAULT_CTRL_REG_CFG       (MotorCurrentADC_DEFAULT_VREF_SOURCE \
                                                   | MotorCurrentADC_DEFAULT_SE_NEG_INPUT \
                                                   | MotorCurrentADC_DEFAULT_HW_CTRL_NEGVREF \
                                                   | MotorCurrentADC_DEFAULT_POWER \
                                                   | MotorCurrentADC_DSI_SYNC_CONFIG \
                                                   | MotorCurrentADC_DEFAULT_SWITCH_CONF)

#define MotorCurrentADC_DEFAULT_SAMPLE_CTRL_REG_CFG (MotorCurrentADC_DEFAULT_DIFF_RESULT_FORMAT \
                                                    | MotorCurrentADC_DEFAULT_SE_RESULT_FORMAT \
                                                    | MotorCurrentADC_DEFAULT_JUSTIFICATION \
                                                    | MotorCurrentADC_DEFAULT_ALT_RESOLUTION \
                                           | (uint8)(MotorCurrentADC_DEFAULT_AVG_SAMPLES_NUM \
                                                   << MotorCurrentADC_AVG_CNT_OFFSET) \
                                                    | MotorCurrentADC_AVG_SHIFT_MODE \
                                                    | MotorCurrentADC_DSI_TRIGGER \
                                                    | MotorCurrentADC_EOS_DSI_OUT_EN)

#define MotorCurrentADC_DEFAULT_RANGE_THRES_REG_CFG (MotorCurrentADC_DEFAULT_LOW_LIMIT \
            | (uint32)((uint32)MotorCurrentADC_DEFAULT_HIGH_LIMIT << MotorCurrentADC_RANGE_HIGH_OFFSET))

#define MotorCurrentADC_DEFAULT_SAMPLE_TIME01_REG_CFG (MotorCurrentADC_DEFAULT_ACLKS_NUM \
            | (uint32)((uint32)MotorCurrentADC_DEFAULT_BCLKS_NUM << MotorCurrentADC_SAMPLE_TIME13_OFFSET))

#define MotorCurrentADC_DEFAULT_SAMPLE_TIME23_REG_CFG (MotorCurrentADC_DEFAULT_CCLKS_NUM \
            | (uint32)((uint32)MotorCurrentADC_DEFAULT_DCLKS_NUM << MotorCurrentADC_SAMPLE_TIME13_OFFSET))


#endif /* End CY_ADC_SAR_SEQ_MotorCurrentADC_H */


/* [] END OF FILE */
