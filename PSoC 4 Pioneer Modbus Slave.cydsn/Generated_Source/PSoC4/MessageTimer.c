/*******************************************************************************
* File Name: MessageTimer.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the MessageTimer
*  component
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

#include "MessageTimer.h"
#include "CyLib.h"

uint8 MessageTimer_initVar = 0u;


/*******************************************************************************
* Function Name: MessageTimer_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default MessageTimer configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (MessageTimer__QUAD == MessageTimer_CONFIG)
        MessageTimer_CONTROL_REG =
        (((uint32)(MessageTimer_QUAD_ENCODING_MODES     << MessageTimer_QUAD_MODE_SHIFT))       |
         ((uint32)(MessageTimer_CONFIG                  << MessageTimer_MODE_SHIFT)));
    #endif  /* (MessageTimer__QUAD == MessageTimer_CONFIG) */

    #if (MessageTimer__PWM_SEL == MessageTimer_CONFIG)
        MessageTimer_CONTROL_REG =
        (((uint32)(MessageTimer_PWM_STOP_EVENT          << MessageTimer_PWM_STOP_KILL_SHIFT))    |
         ((uint32)(MessageTimer_PWM_OUT_INVERT          << MessageTimer_INV_OUT_SHIFT))         |
         ((uint32)(MessageTimer_PWM_OUT_N_INVERT        << MessageTimer_INV_COMPL_OUT_SHIFT))     |
         ((uint32)(MessageTimer_PWM_MODE                << MessageTimer_MODE_SHIFT)));

        #if (MessageTimer__PWM_PR == MessageTimer_PWM_MODE)
            MessageTimer_CONTROL_REG |=
            ((uint32)(MessageTimer_PWM_RUN_MODE         << MessageTimer_ONESHOT_SHIFT));

            MessageTimer_WriteCounter(MessageTimer_PWM_PR_INIT_VALUE);
        #else
            MessageTimer_CONTROL_REG |=
            (((uint32)(MessageTimer_PWM_ALIGN           << MessageTimer_UPDOWN_SHIFT))          |
             ((uint32)(MessageTimer_PWM_KILL_EVENT      << MessageTimer_PWM_SYNC_KILL_SHIFT)));
        #endif  /* (MessageTimer__PWM_PR == MessageTimer_PWM_MODE) */

        #if (MessageTimer__PWM_DT == MessageTimer_PWM_MODE)
            MessageTimer_CONTROL_REG |=
            ((uint32)(MessageTimer_PWM_DEAD_TIME_CYCLE  << MessageTimer_PRESCALER_SHIFT));
        #endif  /* (MessageTimer__PWM_DT == MessageTimer_PWM_MODE) */

        #if (MessageTimer__PWM == MessageTimer_PWM_MODE)
            MessageTimer_CONTROL_REG |=
            ((uint32)MessageTimer_PWM_PRESCALER         << MessageTimer_PRESCALER_SHIFT);
        #endif  /* (MessageTimer__PWM == MessageTimer_PWM_MODE) */
    #endif  /* (MessageTimer__PWM_SEL == MessageTimer_CONFIG) */

    #if (MessageTimer__TIMER == MessageTimer_CONFIG)
        MessageTimer_CONTROL_REG =
        (((uint32)(MessageTimer_TC_PRESCALER            << MessageTimer_PRESCALER_SHIFT))   |
         ((uint32)(MessageTimer_TC_COUNTER_MODE         << MessageTimer_UPDOWN_SHIFT))      |
         ((uint32)(MessageTimer_TC_RUN_MODE             << MessageTimer_ONESHOT_SHIFT))     |
         ((uint32)(MessageTimer_TC_COMP_CAP_MODE        << MessageTimer_MODE_SHIFT)));
    #endif  /* (MessageTimer__TIMER == MessageTimer_CONFIG) */

    /* Set values from customizer to CTRL1 */
    #if (MessageTimer__QUAD == MessageTimer_CONFIG)
        MessageTimer_TRIG_CONTROL1_REG  =
        (((uint32)(MessageTimer_QUAD_PHIA_SIGNAL_MODE   << MessageTimer_COUNT_SHIFT))       |
         ((uint32)(MessageTimer_QUAD_INDEX_SIGNAL_MODE  << MessageTimer_RELOAD_SHIFT))      |
         ((uint32)(MessageTimer_QUAD_STOP_SIGNAL_MODE   << MessageTimer_STOP_SHIFT))        |
         ((uint32)(MessageTimer_QUAD_PHIB_SIGNAL_MODE   << MessageTimer_START_SHIFT)));
    #endif  /* (MessageTimer__QUAD == MessageTimer_CONFIG) */

    #if (MessageTimer__PWM_SEL == MessageTimer_CONFIG)
        MessageTimer_TRIG_CONTROL1_REG  =
        (((uint32)(MessageTimer_PWM_SWITCH_SIGNAL_MODE  << MessageTimer_CAPTURE_SHIFT))     |
         ((uint32)(MessageTimer_PWM_COUNT_SIGNAL_MODE   << MessageTimer_COUNT_SHIFT))       |
         ((uint32)(MessageTimer_PWM_RELOAD_SIGNAL_MODE  << MessageTimer_RELOAD_SHIFT))      |
         ((uint32)(MessageTimer_PWM_STOP_SIGNAL_MODE    << MessageTimer_STOP_SHIFT))        |
         ((uint32)(MessageTimer_PWM_START_SIGNAL_MODE   << MessageTimer_START_SHIFT)));
    #endif  /* (MessageTimer__PWM_SEL == MessageTimer_CONFIG) */

    #if (MessageTimer__TIMER == MessageTimer_CONFIG)
        MessageTimer_TRIG_CONTROL1_REG  =
        (((uint32)(MessageTimer_TC_CAPTURE_SIGNAL_MODE  << MessageTimer_CAPTURE_SHIFT))     |
         ((uint32)(MessageTimer_TC_COUNT_SIGNAL_MODE    << MessageTimer_COUNT_SHIFT))       |
         ((uint32)(MessageTimer_TC_RELOAD_SIGNAL_MODE   << MessageTimer_RELOAD_SHIFT))      |
         ((uint32)(MessageTimer_TC_STOP_SIGNAL_MODE     << MessageTimer_STOP_SHIFT))        |
         ((uint32)(MessageTimer_TC_START_SIGNAL_MODE    << MessageTimer_START_SHIFT)));
    #endif  /* (MessageTimer__TIMER == MessageTimer_CONFIG) */

    /* Set values from customizer to INTR */
    #if (MessageTimer__QUAD == MessageTimer_CONFIG)
        MessageTimer_SetInterruptMode(MessageTimer_QUAD_INTERRUPT_MASK);
    #endif  /* (MessageTimer__QUAD == MessageTimer_CONFIG) */

    #if (MessageTimer__PWM_SEL == MessageTimer_CONFIG)
        MessageTimer_SetInterruptMode(MessageTimer_PWM_INTERRUPT_MASK);
    #endif  /* (MessageTimer__PWM_SEL == MessageTimer_CONFIG) */

    #if (MessageTimer__TIMER == MessageTimer_CONFIG)
        MessageTimer_SetInterruptMode(MessageTimer_TC_INTERRUPT_MASK);
    #endif  /* (MessageTimer__TIMER == MessageTimer_CONFIG) */

    /* Set other values from customizer */
    #if (MessageTimer__TIMER == MessageTimer_CONFIG)
        MessageTimer_WritePeriod(MessageTimer_TC_PERIOD_VALUE );
        #if (MessageTimer__COMPARE == MessageTimer_TC_COMP_CAP_MODE)
            MessageTimer_WriteCompare(MessageTimer_TC_COMPARE_VALUE);

            #if (1u == MessageTimer_TC_COMPARE_SWAP)
                MessageTimer_SetCompareSwap(1u);
                MessageTimer_WriteCompareBuf(MessageTimer_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == MessageTimer_TC_COMPARE_SWAP) */
        #endif  /* (MessageTimer__COMPARE == MessageTimer_TC_COMP_CAP_MODE) */
    #endif  /* (MessageTimer__TIMER == MessageTimer_CONFIG) */

    #if (MessageTimer__PWM_SEL == MessageTimer_CONFIG)
        MessageTimer_WritePeriod(MessageTimer_PWM_PERIOD_VALUE );
        MessageTimer_WriteCompare(MessageTimer_PWM_COMPARE_VALUE);

        #if (1u == MessageTimer_PWM_COMPARE_SWAP)
            MessageTimer_SetCompareSwap(1u);
            MessageTimer_WriteCompareBuf(MessageTimer_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == MessageTimer_PWM_COMPARE_SWAP) */

        #if (1u == MessageTimer_PWM_PERIOD_SWAP)
            MessageTimer_SetPeriodSwap(1u);
            MessageTimer_WritePeriodBuf(MessageTimer_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == MessageTimer_PWM_PERIOD_SWAP) */

        /* Set values from customizer to CTRL2 */
        #if (MessageTimer__PWM_PR == MessageTimer_PWM_MODE)
            MessageTimer_TRIG_CONTROL2_REG =
                    (MessageTimer_CC_MATCH_NO_CHANGE    |
                    MessageTimer_OVERLOW_NO_CHANGE      |
                    MessageTimer_UNDERFLOW_NO_CHANGE);
        #else
            #if (MessageTimer__LEFT == MessageTimer_PWM_ALIGN)
                MessageTimer_TRIG_CONTROL2_REG = MessageTimer_PWM_MODE_LEFT;
            #endif  /* ( MessageTimer_PWM_LEFT == MessageTimer_PWM_ALIGN) */

            #if (MessageTimer__RIGHT == MessageTimer_PWM_ALIGN)
                MessageTimer_TRIG_CONTROL2_REG = MessageTimer_PWM_MODE_RIGHT;
            #endif  /* ( MessageTimer_PWM_RIGHT == MessageTimer_PWM_ALIGN) */

            #if (MessageTimer__CENTER == MessageTimer_PWM_ALIGN)
                MessageTimer_TRIG_CONTROL2_REG = MessageTimer_PWM_MODE_CENTER;
            #endif  /* ( MessageTimer_PWM_CENTER == MessageTimer_PWM_ALIGN) */

            #if (MessageTimer__ASYMMETRIC == MessageTimer_PWM_ALIGN)
                MessageTimer_TRIG_CONTROL2_REG = MessageTimer_PWM_MODE_ASYM;
            #endif  /* (MessageTimer__ASYMMETRIC == MessageTimer_PWM_ALIGN) */
        #endif  /* (MessageTimer__PWM_PR == MessageTimer_PWM_MODE) */
    #endif  /* (MessageTimer__PWM_SEL == MessageTimer_CONFIG) */
}


/*******************************************************************************
* Function Name: MessageTimer_Enable
********************************************************************************
*
* Summary:
*  Enables the MessageTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    MessageTimer_BLOCK_CONTROL_REG |= MessageTimer_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Statr Timer or PWM if start input is absent */
    #if (MessageTimer__PWM_SEL == MessageTimer_CONFIG)
        #if (0u == MessageTimer_PWM_START_SIGNAL_PRESENT)
            MessageTimer_TriggerCommand(MessageTimer_MASK, MessageTimer_CMD_START);
        #endif /* (0u == MessageTimer_PWM_START_SIGNAL_PRESENT) */
    #endif /* (MessageTimer__PWM_SEL == MessageTimer_CONFIG) */

    #if (MessageTimer__TIMER == MessageTimer_CONFIG)
        #if (0u == MessageTimer_TC_START_SIGNAL_PRESENT)
            MessageTimer_TriggerCommand(MessageTimer_MASK, MessageTimer_CMD_START);
        #endif /* (0u == MessageTimer_TC_START_SIGNAL_PRESENT) */
    #endif /* (MessageTimer__TIMER == MessageTimer_CONFIG) */
}


/*******************************************************************************
* Function Name: MessageTimer_Start
********************************************************************************
*
* Summary:
*  Initialize the MessageTimer with default customizer
*  values when called the first time and enables the MessageTimer.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  MessageTimer_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time MessageTimer_Start() is called. This allows
*  enable/disable component without re-initialization in all subsequent calls
*  to the MessageTimer_Start() routine.
*
*******************************************************************************/
void MessageTimer_Start(void)
{
    if (0u == MessageTimer_initVar)
    {
        MessageTimer_Init();
        MessageTimer_initVar = 1u;
    }

    MessageTimer_Enable();
}


/*******************************************************************************
* Function Name: MessageTimer_Stop
********************************************************************************
*
* Summary:
*  Disables the MessageTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_BLOCK_CONTROL_REG &= (uint32)~MessageTimer_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the MessageTimer. This function is used when
*  configured as a generic MessageTimer and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the MessageTimer to operate in
*   Values:
*   - MessageTimer_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - MessageTimer_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - MessageTimer_MODE_QUAD - Quadrature decoder
*         - MessageTimer_MODE_PWM - PWM
*         - MessageTimer_MODE_PWM_DT - PWM with dead time
*         - MessageTimer_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_CONTROL_REG &= (uint32)~MessageTimer_MODE_MASK;
    MessageTimer_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of 3 supported modes.
*  Is functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - MessageTimer_MODE_X1 - Counts on phi 1 rising
*         - MessageTimer_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - MessageTimer_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_CONTROL_REG &= (uint32)~MessageTimer_QUAD_MODE_MASK;
    MessageTimer_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to PWM with dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - MessageTimer_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - MessageTimer_PRESCALE_DIVBY2    - Divide by 2
*         - MessageTimer_PRESCALE_DIVBY4    - Divide by 4
*         - MessageTimer_PRESCALE_DIVBY8    - Divide by 8
*         - MessageTimer_PRESCALE_DIVBY16   - Divide by 16
*         - MessageTimer_PRESCALE_DIVBY32   - Divide by 32
*         - MessageTimer_PRESCALE_DIVBY64   - Divide by 64
*         - MessageTimer_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_CONTROL_REG &= (uint32)~MessageTimer_PRESCALER_MASK;
    MessageTimer_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the MessageTimer runs
*  continuously or stops when terminal count is reached.  By default the
*  MessageTimer operates in continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_CONTROL_REG &= (uint32)~MessageTimer_ONESHOT_MASK;
    MessageTimer_CONTROL_REG |= ((uint32)((oneShotEnable & MessageTimer_1BIT_MASK) <<
                                                               MessageTimer_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the 3 must be ORed together to form the
*  mode.
*
* Parameters:
*  modeMask: Combination of the 3 mode settings.  Mask must include a value for
*  each of the 3 or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be 
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetPWMMode(uint32 modeMask)
{
    MessageTimer_TRIG_CONTROL2_REG = (modeMask & MessageTimer_6BIT_MASK);
}



/*******************************************************************************
* Function Name: MessageTimer_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes an asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to PWM and
*  PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_CONTROL_REG &= (uint32)~MessageTimer_PWM_SYNC_KILL_MASK;
    MessageTimer_CONTROL_REG |= ((uint32)((syncKillEnable & MessageTimer_1BIT_MASK)  <<
                                               MessageTimer_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_CONTROL_REG &= (uint32)~MessageTimer_PWM_STOP_KILL_MASK;
    MessageTimer_CONTROL_REG |= ((uint32)((stopOnKillEnable & MessageTimer_1BIT_MASK)  <<
                                                         MessageTimer_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_CONTROL_REG &= (uint32)~MessageTimer_PRESCALER_MASK;
    MessageTimer_CONTROL_REG |= ((uint32)((deadTime & MessageTimer_8BIT_MASK) <<
                                                          MessageTimer_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - MessageTimer_INVERT_LINE   - Inverts the line output
*         - MessageTimer_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_CONTROL_REG &= (uint32)~MessageTimer_INV_OUT_MASK;
    MessageTimer_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: MessageTimer_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_WriteCounter(uint32 count)
{
    MessageTimer_COUNTER_REG = (count & MessageTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: MessageTimer_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 MessageTimer_ReadCounter(void)
{
    return (MessageTimer_COUNTER_REG & MessageTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: MessageTimer_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and PWM with pseudo random output.
*
* Parameters:
*  counterMode: Enumerated couner type values
*   Values:
*     - MessageTimer_COUNT_UP       - Counts up
*     - MessageTimer_COUNT_DOWN     - Counts down
*     - MessageTimer_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - MessageTimer_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_CONTROL_REG &= (uint32)~MessageTimer_UPDOWN_MASK;
    MessageTimer_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_WritePeriod(uint32 period)
{
    MessageTimer_PERIOD_REG = (period & MessageTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: MessageTimer_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 MessageTimer_ReadPeriod(void)
{
    return (MessageTimer_PERIOD_REG & MessageTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: MessageTimer_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in Timer/Counter mode(without capture) the swap occurs
*  at a TC event. In PWM mode the swap occurs at the next TC event following
*  a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_CONTROL_REG &= (uint32)~MessageTimer_RELOAD_CC_MASK;
    MessageTimer_CONTROL_REG |= (swapEnable & MessageTimer_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_WritePeriodBuf(uint32 periodBuf)
{
    MessageTimer_PERIOD_BUF_REG = (periodBuf & MessageTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: MessageTimer_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 MessageTimer_ReadPeriodBuf(void)
{
    return (MessageTimer_PERIOD_BUF_REG & MessageTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: MessageTimer_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In PWM mode the swap occurs at the next TC event following a hardware switch
*  event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_CONTROL_REG &= (uint32)~MessageTimer_RELOAD_PERIOD_MASK;
    MessageTimer_CONTROL_REG |= ((uint32)((swapEnable & MessageTimer_1BIT_MASK) <<
                                                            MessageTimer_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_WriteCompare(uint32 compare)
{
    MessageTimer_COMP_CAP_REG = (compare & MessageTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: MessageTimer_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
*******************************************************************************/
uint32 MessageTimer_ReadCompare(void)
{
    return (MessageTimer_COMP_CAP_REG & MessageTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: MessageTimer_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_WriteCompareBuf(uint32 compareBuf)
{
   MessageTimer_COMP_CAP_BUF_REG = (compareBuf & MessageTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: MessageTimer_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
*******************************************************************************/
uint32 MessageTimer_ReadCompareBuf(void)
{
    return (MessageTimer_COMP_CAP_BUF_REG & MessageTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: MessageTimer_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 MessageTimer_ReadCapture(void)
{
    return (MessageTimer_COMP_CAP_REG & MessageTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: MessageTimer_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 MessageTimer_ReadCaptureBuf(void)
{
    return (MessageTimer_COMP_CAP_BUF_REG & MessageTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: MessageTimer_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - MessageTimer_TRIG_LEVEL     - Level
*     - MessageTimer_TRIG_RISING    - Rising edge
*     - MessageTimer_TRIG_FALLING   - Falling edge
*     - MessageTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_TRIG_CONTROL1_REG &= (uint32)~MessageTimer_CAPTURE_MASK;
    MessageTimer_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - MessageTimer_TRIG_LEVEL     - Level
*     - MessageTimer_TRIG_RISING    - Rising edge
*     - MessageTimer_TRIG_FALLING   - Falling edge
*     - MessageTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_TRIG_CONTROL1_REG &= (uint32)~MessageTimer_RELOAD_MASK;
    MessageTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << MessageTimer_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - MessageTimer_TRIG_LEVEL     - Level
*     - MessageTimer_TRIG_RISING    - Rising edge
*     - MessageTimer_TRIG_FALLING   - Falling edge
*     - MessageTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_TRIG_CONTROL1_REG &= (uint32)~MessageTimer_START_MASK;
    MessageTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << MessageTimer_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - MessageTimer_TRIG_LEVEL     - Level
*     - MessageTimer_TRIG_RISING    - Rising edge
*     - MessageTimer_TRIG_FALLING   - Falling edge
*     - MessageTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_TRIG_CONTROL1_REG &= (uint32)~MessageTimer_STOP_MASK;
    MessageTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << MessageTimer_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - MessageTimer_TRIG_LEVEL     - Level
*     - MessageTimer_TRIG_RISING    - Rising edge
*     - MessageTimer_TRIG_FALLING   - Falling edge
*     - MessageTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_TRIG_CONTROL1_REG &= (uint32)~MessageTimer_COUNT_MASK;
    MessageTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << MessageTimer_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: Combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - MessageTimer_CMD_CAPTURE    - Trigger Capture command
*     - MessageTimer_CMD_RELOAD     - Trigger Reload command
*     - MessageTimer_CMD_STOP       - Trigger Stop command
*     - MessageTimer_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    MessageTimer_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MessageTimer_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the MessageTimer.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - MessageTimer_STATUS_DOWN    - Set if counting down
*     - MessageTimer_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 MessageTimer_ReadStatus(void)
{
    return ((MessageTimer_STATUS_REG >> MessageTimer_RUNNING_STATUS_SHIFT) |
            (MessageTimer_STATUS_REG & MessageTimer_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: MessageTimer_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - MessageTimer_INTR_MASK_TC       - Terminal count mask
*     - MessageTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetInterruptMode(uint32 interruptMask)
{
    MessageTimer_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: MessageTimer_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - MessageTimer_INTR_MASK_TC       - Terminal count mask
*     - MessageTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 MessageTimer_GetInterruptSourceMasked(void)
{
    return (MessageTimer_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: MessageTimer_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - MessageTimer_INTR_MASK_TC       - Terminal count mask
*     - MessageTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 MessageTimer_GetInterruptSource(void)
{
    return (MessageTimer_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: MessageTimer_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - MessageTimer_INTR_MASK_TC       - Terminal count mask
*     - MessageTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_ClearInterrupt(uint32 interruptMask)
{
    MessageTimer_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: MessageTimer_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - MessageTimer_INTR_MASK_TC       - Terminal count mask
*     - MessageTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void MessageTimer_SetInterrupt(uint32 interruptMask)
{
    MessageTimer_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
