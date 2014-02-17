/*******************************************************************************
* File Name: MessageTimer.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the MessageTimer
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_MessageTimer_H)
#define CY_TCPWM_MessageTimer_H

#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} MessageTimer_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  MessageTimer_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* TCPWM Configuration */
#define MessageTimer_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define MessageTimer_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define MessageTimer_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define MessageTimer_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define MessageTimer_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define MessageTimer_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define MessageTimer_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define MessageTimer_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define MessageTimer_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define MessageTimer_TC_RUN_MODE                    (0lu)
#define MessageTimer_TC_COUNTER_MODE                (0lu)
#define MessageTimer_TC_COMP_CAP_MODE               (2lu)
#define MessageTimer_TC_PRESCALER                   (0lu)

/* Signal modes */
#define MessageTimer_TC_RELOAD_SIGNAL_MODE          (0lu)
#define MessageTimer_TC_COUNT_SIGNAL_MODE           (3lu)
#define MessageTimer_TC_START_SIGNAL_MODE           (0lu)
#define MessageTimer_TC_STOP_SIGNAL_MODE            (0lu)
#define MessageTimer_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define MessageTimer_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define MessageTimer_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define MessageTimer_TC_START_SIGNAL_PRESENT        (0lu)
#define MessageTimer_TC_STOP_SIGNAL_PRESENT         (0lu)
#define MessageTimer_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define MessageTimer_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define MessageTimer_PWM_KILL_EVENT                 (0lu)
#define MessageTimer_PWM_STOP_EVENT                 (0lu)
#define MessageTimer_PWM_MODE                       (4lu)
#define MessageTimer_PWM_OUT_N_INVERT               (0lu)
#define MessageTimer_PWM_OUT_INVERT                 (0lu)
#define MessageTimer_PWM_ALIGN                      (0lu)
#define MessageTimer_PWM_RUN_MODE                   (0lu)
#define MessageTimer_PWM_DEAD_TIME_CYCLE            (0lu)
#define MessageTimer_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define MessageTimer_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define MessageTimer_PWM_COUNT_SIGNAL_MODE          (3lu)
#define MessageTimer_PWM_START_SIGNAL_MODE          (0lu)
#define MessageTimer_PWM_STOP_SIGNAL_MODE           (0lu)
#define MessageTimer_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define MessageTimer_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define MessageTimer_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define MessageTimer_PWM_START_SIGNAL_PRESENT       (0lu)
#define MessageTimer_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define MessageTimer_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define MessageTimer_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define MessageTimer_TC_PERIOD_VALUE                (65535lu)
#define MessageTimer_TC_COMPARE_VALUE               (65535lu)
#define MessageTimer_TC_COMPARE_BUF_VALUE           (65535lu)
#define MessageTimer_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define MessageTimer_PWM_PERIOD_VALUE               (65535lu)
#define MessageTimer_PWM_PERIOD_BUF_VALUE           (65535lu)
#define MessageTimer_PWM_PERIOD_SWAP                (0lu)
#define MessageTimer_PWM_COMPARE_VALUE              (65535lu)
#define MessageTimer_PWM_COMPARE_BUF_VALUE          (65535lu)
#define MessageTimer_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define MessageTimer__LEFT 0
#define MessageTimer__RIGHT 1
#define MessageTimer__CENTER 2
#define MessageTimer__ASYMMETRIC 3

#define MessageTimer__X1 0
#define MessageTimer__X2 1
#define MessageTimer__X4 2

#define MessageTimer__PWM 4
#define MessageTimer__PWM_DT 5
#define MessageTimer__PWM_PR 6

#define MessageTimer__INVERSE 1
#define MessageTimer__DIRECT 0

#define MessageTimer__CAPTURE 2
#define MessageTimer__COMPARE 0

#define MessageTimer__TRIG_LEVEL 3
#define MessageTimer__TRIG_RISING 0
#define MessageTimer__TRIG_FALLING 1
#define MessageTimer__TRIG_BOTH 2

#define MessageTimer__INTR_MASK_TC 1
#define MessageTimer__INTR_MASK_CC_MATCH 2
#define MessageTimer__INTR_MASK_NONE 0
#define MessageTimer__INTR_MASK_TC_CC 3

#define MessageTimer__UNCONFIG 8
#define MessageTimer__TIMER 1
#define MessageTimer__QUAD 3
#define MessageTimer__PWM_SEL 7

#define MessageTimer__COUNT_UP 0
#define MessageTimer__COUNT_DOWN 1
#define MessageTimer__COUNT_UPDOWN0 2
#define MessageTimer__COUNT_UPDOWN1 3


/* Prescaler */
#define MessageTimer_PRESCALE_DIVBY1                ((uint32)(0u << MessageTimer_PRESCALER_SHIFT))
#define MessageTimer_PRESCALE_DIVBY2                ((uint32)(1u << MessageTimer_PRESCALER_SHIFT))
#define MessageTimer_PRESCALE_DIVBY4                ((uint32)(2u << MessageTimer_PRESCALER_SHIFT))
#define MessageTimer_PRESCALE_DIVBY8                ((uint32)(3u << MessageTimer_PRESCALER_SHIFT))
#define MessageTimer_PRESCALE_DIVBY16               ((uint32)(4u << MessageTimer_PRESCALER_SHIFT))
#define MessageTimer_PRESCALE_DIVBY32               ((uint32)(5u << MessageTimer_PRESCALER_SHIFT))
#define MessageTimer_PRESCALE_DIVBY64               ((uint32)(6u << MessageTimer_PRESCALER_SHIFT))
#define MessageTimer_PRESCALE_DIVBY128              ((uint32)(7u << MessageTimer_PRESCALER_SHIFT))

/* TCPWM set modes */
#define MessageTimer_MODE_TIMER_COMPARE             ((uint32)(MessageTimer__COMPARE         <<  \
                                                                  MessageTimer_MODE_SHIFT))
#define MessageTimer_MODE_TIMER_CAPTURE             ((uint32)(MessageTimer__CAPTURE         <<  \
                                                                  MessageTimer_MODE_SHIFT))
#define MessageTimer_MODE_QUAD                      ((uint32)(MessageTimer__QUAD            <<  \
                                                                  MessageTimer_MODE_SHIFT))
#define MessageTimer_MODE_PWM                       ((uint32)(MessageTimer__PWM             <<  \
                                                                  MessageTimer_MODE_SHIFT))
#define MessageTimer_MODE_PWM_DT                    ((uint32)(MessageTimer__PWM_DT          <<  \
                                                                  MessageTimer_MODE_SHIFT))
#define MessageTimer_MODE_PWM_PR                    ((uint32)(MessageTimer__PWM_PR          <<  \
                                                                  MessageTimer_MODE_SHIFT))

/* Quad Modes */
#define MessageTimer_MODE_X1                        ((uint32)(MessageTimer__X1              <<  \
                                                                  MessageTimer_QUAD_MODE_SHIFT))
#define MessageTimer_MODE_X2                        ((uint32)(MessageTimer__X2              <<  \
                                                                  MessageTimer_QUAD_MODE_SHIFT))
#define MessageTimer_MODE_X4                        ((uint32)(MessageTimer__X4              <<  \
                                                                  MessageTimer_QUAD_MODE_SHIFT))

/* Counter modes */
#define MessageTimer_COUNT_UP                       ((uint32)(MessageTimer__COUNT_UP        <<  \
                                                                  MessageTimer_UPDOWN_SHIFT))
#define MessageTimer_COUNT_DOWN                     ((uint32)(MessageTimer__COUNT_DOWN      <<  \
                                                                  MessageTimer_UPDOWN_SHIFT))
#define MessageTimer_COUNT_UPDOWN0                  ((uint32)(MessageTimer__COUNT_UPDOWN0   <<  \
                                                                  MessageTimer_UPDOWN_SHIFT))
#define MessageTimer_COUNT_UPDOWN1                  ((uint32)(MessageTimer__COUNT_UPDOWN1   <<  \
                                                                  MessageTimer_UPDOWN_SHIFT))

/* PWM output invert */
#define MessageTimer_INVERT_LINE                    ((uint32)(MessageTimer__INVERSE         <<  \
                                                                  MessageTimer_INV_OUT_SHIFT))
#define MessageTimer_INVERT_LINE_N                  ((uint32)(MessageTimer__INVERSE         <<  \
                                                                  MessageTimer_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define MessageTimer_TRIG_RISING                    (MessageTimer__TRIG_RISING)
#define MessageTimer_TRIG_FALLING                   (MessageTimer__TRIG_FALLING)
#define MessageTimer_TRIG_BOTH                      (MessageTimer__TRIG_BOTH)
#define MessageTimer_TRIG_LEVEL                     (MessageTimer__TRIG_LEVEL)

/* Interrupt mask */
#define MessageTimer_INTR_MASK_TC                   (MessageTimer__INTR_MASK_TC)
#define MessageTimer_INTR_MASK_CC_MATCH             (MessageTimer__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define MessageTimer_CC_MATCH_SET                   (0x00u)
#define MessageTimer_CC_MATCH_CLEAR                 (0x01u)
#define MessageTimer_CC_MATCH_INVERT                (0x02u)
#define MessageTimer_CC_MATCH_NO_CHANGE             (0x03u)
#define MessageTimer_OVERLOW_SET                    (0x00u)
#define MessageTimer_OVERLOW_CLEAR                  (0x04u)
#define MessageTimer_OVERLOW_INVERT                 (0x08u)
#define MessageTimer_OVERLOW_NO_CHANGE              (0x0Cu)
#define MessageTimer_UNDERFLOW_SET                  (0x00u)
#define MessageTimer_UNDERFLOW_CLEAR                (0x10u)
#define MessageTimer_UNDERFLOW_INVERT               (0x20u)
#define MessageTimer_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define MessageTimer_PWM_MODE_LEFT                  (MessageTimer_CC_MATCH_CLEAR        |   \
                                                         MessageTimer_OVERLOW_SET           |   \
                                                         MessageTimer_UNDERFLOW_NO_CHANGE)
#define MessageTimer_PWM_MODE_RIGHT                 (MessageTimer_CC_MATCH_SET          |   \
                                                         MessageTimer_OVERLOW_NO_CHANGE     |   \
                                                         MessageTimer_UNDERFLOW_CLEAR)
#define MessageTimer_PWM_MODE_CENTER                (MessageTimer_CC_MATCH_INVERT       |   \
                                                         MessageTimer_OVERLOW_NO_CHANGE     |   \
                                                         MessageTimer_UNDERFLOW_CLEAR)
#define MessageTimer_PWM_MODE_ASYM                  (MessageTimer_CC_MATCH_NO_CHANGE    |   \
                                                         MessageTimer_OVERLOW_SET           |   \
                                                         MessageTimer_UNDERFLOW_CLEAR )

/* Command operations without condition */
#define MessageTimer_CMD_CAPTURE                    (0u)
#define MessageTimer_CMD_RELOAD                     (8u)
#define MessageTimer_CMD_STOP                       (16u)
#define MessageTimer_CMD_START                      (24u)

/* Status */
#define MessageTimer_STATUS_DOWN                    (1u)
#define MessageTimer_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   MessageTimer_Init(void);
void   MessageTimer_Enable(void);
void   MessageTimer_Start(void);
void   MessageTimer_Stop(void);

void   MessageTimer_SetMode(uint32 mode);
void   MessageTimer_SetCounterMode(uint32 counterMode);
void   MessageTimer_SetPWMMode(uint32 modeMask);
void   MessageTimer_SetQDMode(uint32 qdMode);

void   MessageTimer_SetPrescaler(uint32 prescaler);
void   MessageTimer_TriggerCommand(uint32 mask, uint32 command);
void   MessageTimer_SetOneShot(uint32 oneShotEnable);
uint32 MessageTimer_ReadStatus(void);

void   MessageTimer_SetPWMSyncKill(uint32 syncKillEnable);
void   MessageTimer_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   MessageTimer_SetPWMDeadTime(uint32 deadTime);
void   MessageTimer_SetPWMInvert(uint32 mask);

void   MessageTimer_SetInterruptMode(uint32 interruptMask);
uint32 MessageTimer_GetInterruptSourceMasked(void);
uint32 MessageTimer_GetInterruptSource(void);
void   MessageTimer_ClearInterrupt(uint32 interruptMask);
void   MessageTimer_SetInterrupt(uint32 interruptMask);

void   MessageTimer_WriteCounter(uint32 count);
uint32 MessageTimer_ReadCounter(void);

uint32 MessageTimer_ReadCapture(void);
uint32 MessageTimer_ReadCaptureBuf(void);

void   MessageTimer_WritePeriod(uint32 period);
uint32 MessageTimer_ReadPeriod(void);
void   MessageTimer_WritePeriodBuf(uint32 periodBuf);
uint32 MessageTimer_ReadPeriodBuf(void);

void   MessageTimer_WriteCompare(uint32 compare);
uint32 MessageTimer_ReadCompare(void);
void   MessageTimer_WriteCompareBuf(uint32 compareBuf);
uint32 MessageTimer_ReadCompareBuf(void);

void   MessageTimer_SetPeriodSwap(uint32 swapEnable);
void   MessageTimer_SetCompareSwap(uint32 swapEnable);

void   MessageTimer_SetCaptureMode(uint32 triggerMode);
void   MessageTimer_SetReloadMode(uint32 triggerMode);
void   MessageTimer_SetStartMode(uint32 triggerMode);
void   MessageTimer_SetStopMode(uint32 triggerMode);
void   MessageTimer_SetCountMode(uint32 triggerMode);

void   MessageTimer_SaveConfig(void);
void   MessageTimer_RestoreConfig(void);
void   MessageTimer_Sleep(void);
void   MessageTimer_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define MessageTimer_BLOCK_CONTROL_REG              (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define MessageTimer_BLOCK_CONTROL_PTR              ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define MessageTimer_COMMAND_REG                    (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define MessageTimer_COMMAND_PTR                    ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define MessageTimer_INTRRUPT_CAUSE_REG             (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define MessageTimer_INTRRUPT_CAUSE_PTR             ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define MessageTimer_CONTROL_REG                    (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__CTRL )
#define MessageTimer_CONTROL_PTR                    ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__CTRL )
#define MessageTimer_STATUS_REG                     (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__STATUS )
#define MessageTimer_STATUS_PTR                     ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__STATUS )
#define MessageTimer_COUNTER_REG                    (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__COUNTER )
#define MessageTimer_COUNTER_PTR                    ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__COUNTER )
#define MessageTimer_COMP_CAP_REG                   (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__CC )
#define MessageTimer_COMP_CAP_PTR                   ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__CC )
#define MessageTimer_COMP_CAP_BUF_REG               (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define MessageTimer_COMP_CAP_BUF_PTR               ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define MessageTimer_PERIOD_REG                     (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__PERIOD )
#define MessageTimer_PERIOD_PTR                     ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__PERIOD )
#define MessageTimer_PERIOD_BUF_REG                 (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define MessageTimer_PERIOD_BUF_PTR                 ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define MessageTimer_TRIG_CONTROL0_REG              (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define MessageTimer_TRIG_CONTROL0_PTR              ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define MessageTimer_TRIG_CONTROL1_REG              (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define MessageTimer_TRIG_CONTROL1_PTR              ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define MessageTimer_TRIG_CONTROL2_REG              (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define MessageTimer_TRIG_CONTROL2_PTR              ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define MessageTimer_INTERRUPT_REQ_REG              (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__INTR )
#define MessageTimer_INTERRUPT_REQ_PTR              ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__INTR )
#define MessageTimer_INTERRUPT_SET_REG              (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define MessageTimer_INTERRUPT_SET_PTR              ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define MessageTimer_INTERRUPT_MASK_REG             (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define MessageTimer_INTERRUPT_MASK_PTR             ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define MessageTimer_INTERRUPT_MASKED_REG           (*(reg32 *) MessageTimer_cy_m0s8_tcpwm_1__INTR_MASKED )
#define MessageTimer_INTERRUPT_MASKED_PTR           ( (reg32 *) MessageTimer_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define MessageTimer_MASK                           ((uint32)MessageTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define MessageTimer_RELOAD_CC_SHIFT                (0u)
#define MessageTimer_RELOAD_PERIOD_SHIFT            (1u)
#define MessageTimer_PWM_SYNC_KILL_SHIFT            (2u)
#define MessageTimer_PWM_STOP_KILL_SHIFT            (3u)
#define MessageTimer_PRESCALER_SHIFT                (8u)
#define MessageTimer_UPDOWN_SHIFT                   (16u)
#define MessageTimer_ONESHOT_SHIFT                  (18u)
#define MessageTimer_QUAD_MODE_SHIFT                (20u)
#define MessageTimer_INV_OUT_SHIFT                  (20u)
#define MessageTimer_INV_COMPL_OUT_SHIFT            (21u)
#define MessageTimer_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define MessageTimer_RELOAD_CC_MASK                 ((uint32)(MessageTimer_1BIT_MASK        <<  \
                                                                            MessageTimer_RELOAD_CC_SHIFT))
#define MessageTimer_RELOAD_PERIOD_MASK             ((uint32)(MessageTimer_1BIT_MASK        <<  \
                                                                            MessageTimer_RELOAD_PERIOD_SHIFT))
#define MessageTimer_PWM_SYNC_KILL_MASK             ((uint32)(MessageTimer_1BIT_MASK        <<  \
                                                                            MessageTimer_PWM_SYNC_KILL_SHIFT))
#define MessageTimer_PWM_STOP_KILL_MASK             ((uint32)(MessageTimer_1BIT_MASK        <<  \
                                                                            MessageTimer_PWM_STOP_KILL_SHIFT))
#define MessageTimer_PRESCALER_MASK                 ((uint32)(MessageTimer_8BIT_MASK        <<  \
                                                                            MessageTimer_PRESCALER_SHIFT))
#define MessageTimer_UPDOWN_MASK                    ((uint32)(MessageTimer_2BIT_MASK        <<  \
                                                                            MessageTimer_UPDOWN_SHIFT))
#define MessageTimer_ONESHOT_MASK                   ((uint32)(MessageTimer_1BIT_MASK        <<  \
                                                                            MessageTimer_ONESHOT_SHIFT))
#define MessageTimer_QUAD_MODE_MASK                 ((uint32)(MessageTimer_3BIT_MASK        <<  \
                                                                            MessageTimer_QUAD_MODE_SHIFT))
#define MessageTimer_INV_OUT_MASK                   ((uint32)(MessageTimer_2BIT_MASK        <<  \
                                                                            MessageTimer_INV_OUT_SHIFT))
#define MessageTimer_MODE_MASK                      ((uint32)(MessageTimer_3BIT_MASK        <<  \
                                                                            MessageTimer_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define MessageTimer_CAPTURE_SHIFT                  (0u)
#define MessageTimer_COUNT_SHIFT                    (2u)
#define MessageTimer_RELOAD_SHIFT                   (4u)
#define MessageTimer_STOP_SHIFT                     (6u)
#define MessageTimer_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define MessageTimer_CAPTURE_MASK                   ((uint32)(MessageTimer_2BIT_MASK        <<  \
                                                                  MessageTimer_CAPTURE_SHIFT))
#define MessageTimer_COUNT_MASK                     ((uint32)(MessageTimer_2BIT_MASK        <<  \
                                                                  MessageTimer_COUNT_SHIFT))
#define MessageTimer_RELOAD_MASK                    ((uint32)(MessageTimer_2BIT_MASK        <<  \
                                                                  MessageTimer_RELOAD_SHIFT))
#define MessageTimer_STOP_MASK                      ((uint32)(MessageTimer_2BIT_MASK        <<  \
                                                                  MessageTimer_STOP_SHIFT))
#define MessageTimer_START_MASK                     ((uint32)(MessageTimer_2BIT_MASK        <<  \
                                                                  MessageTimer_START_SHIFT))

/* MASK */
#define MessageTimer_1BIT_MASK                      ((uint32)0x01u)
#define MessageTimer_2BIT_MASK                      ((uint32)0x03u)
#define MessageTimer_3BIT_MASK                      ((uint32)0x07u)
#define MessageTimer_6BIT_MASK                      ((uint32)0x3Fu)
#define MessageTimer_8BIT_MASK                      ((uint32)0xFFu)
#define MessageTimer_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define MessageTimer_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define MessageTimer_PWM_PR_INIT_VALUE              (1u)

#endif /* End CY_TCPWM_MessageTimer_H */

/* [] END OF FILE */
