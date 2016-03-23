/*
 * autopilot.c
 *
 * Real-Time Workshop code generation for Simulink model "autopilot.mdl".
 *
 * Model version              : 1.184
 * Real-Time Workshop version : 7.5  (R2010a)  25-Jan-2010
 * C source code generated on : Tue Jul 19 19:43:27 2011
 *
 * Target selection: rtwin.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "autopilot.h"
#include "autopilot_private.h"
#include <stdio.h>
#include "autopilot_dt.h"

/* options for Real-Time Windows Target board 0 */
static double RTWinBoardOptions0[] = {
  2.130706433E+009,
  12000.0,
};

/* options for Real-Time Windows Target board 1 */
static double RTWinBoardOptions1[] = {
  2.130706433E+009,
  12003.0,
};

/* list of Real-Time Windows Target boards */
const int RTWinBoardCount = 2;
RTWINBOARD RTWinBoards[2] = {
  { "Standard_Devices/UDP_Protocol", 12001U, 2, RTWinBoardOptions0 },

  { "Standard_Devices/UDP_Protocol", 12002U, 2, RTWinBoardOptions1 },
};

/* Block signals (auto storage) */
BlockIO_autopilot autopilot_B;

/* Continuous states */
ContinuousStates_autopilot autopilot_X;

/* Block states (auto storage) */
D_Work_autopilot autopilot_DWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates_autopilot autopilot_PrevZCSigState;

/* Real-time model */
RT_MODEL_autopilot autopilot_M_;
RT_MODEL_autopilot *autopilot_M = &autopilot_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 8;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  autopilot_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void autopilot_output(int_T tid)
{
  /* local block i/o variables */
  real_T rtb_Integrator;
  real_T rtb_Integrator_i;
  real_T rtb_Integrator_n;
  real_T rtb_Integrator_j;
  real_T rtb_Filter;
  real_T rtb_Sum_l;
  int32_T i;
  if (rtmIsMajorTimeStep(autopilot_M)) {
    /* set solver stop time */
    if (!(autopilot_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&autopilot_M->solverInfo,
                            ((autopilot_M->Timing.clockTickH0 + 1) *
        autopilot_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&autopilot_M->solverInfo,
                            ((autopilot_M->Timing.clockTick0 + 1) *
        autopilot_M->Timing.stepSize0 + autopilot_M->Timing.clockTickH0 *
        autopilot_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(autopilot_M)) {
    autopilot_M->Timing.t[0] = rtsiGetT(&autopilot_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(autopilot_M)) {
    /* S-Function Block: <S1>/Packet Input */
    {
      uint8_T indata[192U];
      int status = RTBIO_DriverIO(0, STREAMINPUT, IOREAD, 192U,
        &autopilot_P.PacketInput_PacketID, (double*) indata, NULL);
      if (status & 0x1) {
        RTWin_ANYTYPEPTR indp;
        indp.p_uint8_T = indata;
        autopilot_B.PacketInput_o1 = *indp.p_int32_T++;
        autopilot_B.PacketInput_o2 = *indp.p_int32_T++;
        autopilot_B.PacketInput_o3[0] = *indp.p_real_T++;
        autopilot_B.PacketInput_o3[1] = *indp.p_real_T++;
        autopilot_B.PacketInput_o4[0] = *indp.p_real_T++;
        autopilot_B.PacketInput_o4[1] = *indp.p_real_T++;
        autopilot_B.PacketInput_o4[2] = *indp.p_real_T++;
        autopilot_B.PacketInput_o4[3] = *indp.p_real_T++;
        autopilot_B.PacketInput_o4[4] = *indp.p_real_T++;
        autopilot_B.PacketInput_o4[5] = *indp.p_real_T++;
        autopilot_B.PacketInput_o4[6] = *indp.p_real_T++;
        autopilot_B.PacketInput_o5[0] = *indp.p_real_T++;
        autopilot_B.PacketInput_o5[1] = *indp.p_real_T++;
        autopilot_B.PacketInput_o5[2] = *indp.p_real_T++;
        autopilot_B.PacketInput_o5[3] = *indp.p_real_T++;
        autopilot_B.PacketInput_o5[4] = *indp.p_real_T++;
        autopilot_B.PacketInput_o5[5] = *indp.p_real_T++;
        autopilot_B.PacketInput_o6[0] = *indp.p_real_T++;
        autopilot_B.PacketInput_o6[1] = *indp.p_real_T++;
        autopilot_B.PacketInput_o6[2] = *indp.p_real_T++;
        autopilot_B.PacketInput_o6[3] = *indp.p_real_T++;
        autopilot_B.PacketInput_o6[4] = *indp.p_real_T++;
        autopilot_B.PacketInput_o6[5] = *indp.p_real_T++;
        autopilot_B.PacketInput_o6[6] = *indp.p_real_T++;
        autopilot_B.PacketInput_o6[7] = *indp.p_real_T++;
      }
    }

    /* RateTransition: '<S1>/Rate Transition2' */
    if (rtmIsMajorTimeStep(autopilot_M)) {
      autopilot_B.RateTransition2 = autopilot_B.PacketInput_o1;
    }

    /* RateTransition: '<S1>/Rate Transition3' */
    if (rtmIsMajorTimeStep(autopilot_M)) {
      autopilot_B.RateTransition3[0] = autopilot_B.PacketInput_o3[0];
      autopilot_B.RateTransition3[1] = autopilot_B.PacketInput_o3[1];
    }

    /* RateTransition: '<S1>/Rate Transition4' */
    if (rtmIsMajorTimeStep(autopilot_M)) {
      for (i = 0; i < 7; i++) {
        autopilot_B.RateTransition4[i] = autopilot_B.PacketInput_o4[i];
      }
    }

    /* RateTransition: '<S1>/Rate Transition5' */
    if (rtmIsMajorTimeStep(autopilot_M)) {
      for (i = 0; i < 6; i++) {
        autopilot_B.RateTransition5[i] = autopilot_B.PacketInput_o5[i];
      }
    }

    /* RateTransition: '<S1>/Rate Transition6' */
    if (rtmIsMajorTimeStep(autopilot_M)) {
      memcpy((void *)(&autopilot_B.RateTransition6[0]), (void *)
             (&autopilot_B.PacketInput_o6[0]), sizeof(real_T) << 3U);
    }

    /* DataTypeConversion: '<S3>/Data Type Conversion' incorporates:
     *  S-Function (sfix_bitop): '<S3>/Bitwise Operator'
     */
    autopilot_B.DataTypeConversion = (real_T)(autopilot_B.RateTransition2 &
      autopilot_P.BitwiseOperator_BitMask);

    /* Logic: '<S3>/Logical Operator' */
    autopilot_B.LogicalOperator = !(autopilot_B.DataTypeConversion != 0.0);

    /* Sum: '<S3>/Sum' */
    rtb_Sum_l = autopilot_B.RateTransition6[5] - autopilot_B.RateTransition5[0];

    /* Gain: '<S7>/Derivative Gain' */
    autopilot_B.DerivativeGain = autopilot_P.DerivativeGain_Gain * rtb_Sum_l;
  }

  /* Integrator: '<S7>/Filter' */
  if (rtmIsMajorTimeStep(autopilot_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((autopilot_B.LogicalOperator !=
      (autopilot_PrevZCSigState.Filter_Reset_ZCE == POS_ZCSIG)) &&
                (autopilot_PrevZCSigState.Filter_Reset_ZCE !=
                 UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    autopilot_PrevZCSigState.Filter_Reset_ZCE = (ZCSigState)
      autopilot_B.LogicalOperator;
    if (zcEvent || autopilot_B.LogicalOperator) {
      autopilot_X.Filter_CSTATE = autopilot_P.Filter_IC;
    }
  }

  rtb_Filter = autopilot_X.Filter_CSTATE;

  /* Gain: '<S7>/Filter Coefficient' incorporates:
   *  Sum: '<S7>/SumD'
   */
  autopilot_B.FilterCoefficient = (autopilot_B.DerivativeGain - rtb_Filter) *
    autopilot_P.FilterCoefficient_Gain;
  if (rtmIsMajorTimeStep(autopilot_M)) {
    /* Gain: '<S7>/Integral Gain' */
    autopilot_B.IntegralGain = autopilot_P.IntegralGain_Gain * rtb_Sum_l;
  }

  /* Integrator: '<S7>/Integrator' */
  if (rtmIsMajorTimeStep(autopilot_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((autopilot_B.LogicalOperator !=
      (autopilot_PrevZCSigState.Integrator_Reset_ZCE == POS_ZCSIG)) &&
                (autopilot_PrevZCSigState.Integrator_Reset_ZCE !=
                 UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    autopilot_PrevZCSigState.Integrator_Reset_ZCE = (ZCSigState)
      autopilot_B.LogicalOperator;
    if (zcEvent || autopilot_B.LogicalOperator) {
      autopilot_X.Integrator_CSTATE = autopilot_P.Integrator_IC;
    }
  }

  rtb_Integrator = autopilot_X.Integrator_CSTATE;
  if (rtmIsMajorTimeStep(autopilot_M)) {
    /* Gain: '<S7>/Proportional Gain' */
    autopilot_B.ProportionalGain = autopilot_P.ProportionalGain_Gain * rtb_Sum_l;
  }

  /* Switch: '<S3>/Switch' incorporates:
   *  Sum: '<S7>/Sum'
   */
  if (autopilot_B.DataTypeConversion > autopilot_P.Switch_Threshold) {
    autopilot_B.Switch = (autopilot_B.ProportionalGain + rtb_Integrator) +
      autopilot_B.FilterCoefficient;
  } else {
    autopilot_B.Switch = 0.0;
  }

  if (rtmIsMajorTimeStep(autopilot_M)) {
    /* DataTypeConversion: '<S4>/Data Type Conversion' incorporates:
     *  S-Function (sfix_bitop): '<S4>/Bitwise Operator'
     */
    autopilot_B.DataTypeConversion_o = (real_T)(autopilot_B.RateTransition2 &
      autopilot_P.BitwiseOperator_BitMask_f);

    /* Logic: '<S4>/Logical Operator' */
    autopilot_B.LogicalOperator_n = !(autopilot_B.DataTypeConversion_o != 0.0);

    /* Sum: '<S4>/Sum' */
    rtb_Sum_l = autopilot_B.RateTransition6[6] - autopilot_B.RateTransition5[2];

    /* Gain: '<S8>/Derivative Gain' */
    autopilot_B.DerivativeGain_e = autopilot_P.DerivativeGain_Gain_m * rtb_Sum_l;
  }

  /* Integrator: '<S8>/Filter' */
  if (rtmIsMajorTimeStep(autopilot_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((autopilot_B.LogicalOperator_n !=
      (autopilot_PrevZCSigState.Filter_Reset_ZCE_k == POS_ZCSIG)) &&
                (autopilot_PrevZCSigState.Filter_Reset_ZCE_k !=
                 UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    autopilot_PrevZCSigState.Filter_Reset_ZCE_k = (ZCSigState)
      autopilot_B.LogicalOperator_n;
    if (zcEvent || autopilot_B.LogicalOperator_n) {
      autopilot_X.Filter_CSTATE_l = autopilot_P.Filter_IC_f;
    }
  }

  rtb_Filter = autopilot_X.Filter_CSTATE_l;

  /* Gain: '<S8>/Filter Coefficient' incorporates:
   *  Sum: '<S8>/SumD'
   */
  autopilot_B.FilterCoefficient_f = (autopilot_B.DerivativeGain_e - rtb_Filter) *
    autopilot_P.FilterCoefficient_Gain_h;
  if (rtmIsMajorTimeStep(autopilot_M)) {
    /* Gain: '<S8>/Integral Gain' */
    autopilot_B.IntegralGain_k = autopilot_P.IntegralGain_Gain_m * rtb_Sum_l;
  }

  /* Integrator: '<S8>/Integrator' */
  if (rtmIsMajorTimeStep(autopilot_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((autopilot_B.LogicalOperator_n !=
      (autopilot_PrevZCSigState.Integrator_Reset_ZCE_k == POS_ZCSIG)) &&
                (autopilot_PrevZCSigState.Integrator_Reset_ZCE_k !=
                 UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    autopilot_PrevZCSigState.Integrator_Reset_ZCE_k = (ZCSigState)
      autopilot_B.LogicalOperator_n;
    if (zcEvent || autopilot_B.LogicalOperator_n) {
      autopilot_X.Integrator_CSTATE_d = autopilot_P.Integrator_IC_m;
    }
  }

  rtb_Integrator_i = autopilot_X.Integrator_CSTATE_d;
  if (rtmIsMajorTimeStep(autopilot_M)) {
    /* Gain: '<S8>/Proportional Gain' */
    autopilot_B.ProportionalGain_i = autopilot_P.ProportionalGain_Gain_h *
      rtb_Sum_l;
  }

  /* Switch: '<S4>/Switch' incorporates:
   *  Sum: '<S8>/Sum'
   */
  if (autopilot_B.DataTypeConversion_o > autopilot_P.Switch_Threshold_a) {
    autopilot_B.Switch_l = (autopilot_B.ProportionalGain_i + rtb_Integrator_i) +
      autopilot_B.FilterCoefficient_f;
  } else {
    autopilot_B.Switch_l = 0.0;
  }

  if (rtmIsMajorTimeStep(autopilot_M)) {
    /* Sum: '<S5>/Sum' */
    autopilot_B.Sum = autopilot_B.RateTransition6[4] -
      autopilot_B.RateTransition4[3];

    /* DataTypeConversion: '<S5>/Data Type Conversion' incorporates:
     *  S-Function (sfix_bitop): '<S5>/Bitwise Operator'
     */
    autopilot_B.DataTypeConversion_c = (real_T)(autopilot_B.RateTransition2 &
      autopilot_P.BitwiseOperator_BitMask_k);

    /* Logic: '<S5>/Logical Operator' */
    autopilot_B.LogicalOperator_i = !(autopilot_B.DataTypeConversion_c != 0.0);

    /* Gain: '<S9>/Derivative Gain' */
    autopilot_B.DerivativeGain_i = autopilot_P.DerivativeGain_Gain_j *
      autopilot_B.Sum;
  }

  /* Integrator: '<S9>/Filter' */
  if (rtmIsMajorTimeStep(autopilot_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((autopilot_B.LogicalOperator_i !=
      (autopilot_PrevZCSigState.Filter_Reset_ZCE_a == POS_ZCSIG)) &&
                (autopilot_PrevZCSigState.Filter_Reset_ZCE_a !=
                 UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    autopilot_PrevZCSigState.Filter_Reset_ZCE_a = (ZCSigState)
      autopilot_B.LogicalOperator_i;
    if (zcEvent || autopilot_B.LogicalOperator_i) {
      autopilot_X.Filter_CSTATE_i = autopilot_P.Filter_IC_a;
    }
  }

  rtb_Filter = autopilot_X.Filter_CSTATE_i;

  /* Gain: '<S9>/Filter Coefficient' incorporates:
   *  Sum: '<S9>/SumD'
   */
  autopilot_B.FilterCoefficient_c = (autopilot_B.DerivativeGain_i - rtb_Filter) *
    autopilot_P.FilterCoefficient_Gain_o;
  if (rtmIsMajorTimeStep(autopilot_M)) {
    /* Gain: '<S9>/Integral Gain' */
    autopilot_B.IntegralGain_a = autopilot_P.IntegralGain_Gain_i *
      autopilot_B.Sum;
  }

  /* Integrator: '<S9>/Integrator' */
  if (rtmIsMajorTimeStep(autopilot_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((autopilot_B.LogicalOperator_i !=
      (autopilot_PrevZCSigState.Integrator_Reset_ZCE_h == POS_ZCSIG)) &&
                (autopilot_PrevZCSigState.Integrator_Reset_ZCE_h !=
                 UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    autopilot_PrevZCSigState.Integrator_Reset_ZCE_h = (ZCSigState)
      autopilot_B.LogicalOperator_i;
    if (zcEvent || autopilot_B.LogicalOperator_i) {
      autopilot_X.Integrator_CSTATE_e = autopilot_P.Integrator_IC_n;
    }
  }

  rtb_Integrator_n = autopilot_X.Integrator_CSTATE_e;
  if (rtmIsMajorTimeStep(autopilot_M)) {
    /* Gain: '<S9>/Proportional Gain' */
    autopilot_B.ProportionalGain_o = autopilot_P.ProportionalGain_Gain_a *
      autopilot_B.Sum;
  }

  /* Switch: '<S5>/Switch' incorporates:
   *  Sum: '<S9>/Sum'
   */
  if (autopilot_B.DataTypeConversion_c > autopilot_P.Switch_Threshold_e) {
    autopilot_B.Switch_i = (autopilot_B.ProportionalGain_o + rtb_Integrator_n) +
      autopilot_B.FilterCoefficient_c;
  } else {
    autopilot_B.Switch_i = 0.0;
  }

  if (rtmIsMajorTimeStep(autopilot_M)) {
    /* DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
     *  S-Function (sfix_bitop): '<S6>/Bitwise Operator'
     */
    autopilot_B.DataTypeConversion_l = (real_T)(autopilot_B.RateTransition2 &
      autopilot_P.BitwiseOperator_BitMask_a);

    /* Logic: '<S6>/Logical Operator' */
    autopilot_B.LogicalOperator_d = !(autopilot_B.DataTypeConversion_l != 0.0);

    /* Sum: '<S6>/Sum' */
    rtb_Sum_l = autopilot_B.RateTransition6[7] - autopilot_B.RateTransition5[1];

    /* Gain: '<S10>/Derivative Gain' */
    autopilot_B.DerivativeGain_ei = autopilot_P.DerivativeGain_Gain_k *
      rtb_Sum_l;
  }

  /* Integrator: '<S10>/Filter' */
  if (rtmIsMajorTimeStep(autopilot_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((autopilot_B.LogicalOperator_d !=
      (autopilot_PrevZCSigState.Filter_Reset_ZCE_b == POS_ZCSIG)) &&
                (autopilot_PrevZCSigState.Filter_Reset_ZCE_b !=
                 UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    autopilot_PrevZCSigState.Filter_Reset_ZCE_b = (ZCSigState)
      autopilot_B.LogicalOperator_d;
    if (zcEvent || autopilot_B.LogicalOperator_d) {
      autopilot_X.Filter_CSTATE_p = autopilot_P.Filter_IC_d;
    }
  }

  rtb_Filter = autopilot_X.Filter_CSTATE_p;

  /* Gain: '<S10>/Filter Coefficient' incorporates:
   *  Sum: '<S10>/SumD'
   */
  autopilot_B.FilterCoefficient_e = (autopilot_B.DerivativeGain_ei - rtb_Filter)
    * autopilot_P.FilterCoefficient_Gain_b;
  if (rtmIsMajorTimeStep(autopilot_M)) {
    /* Gain: '<S10>/Integral Gain' */
    autopilot_B.IntegralGain_m = autopilot_P.IntegralGain_Gain_k * rtb_Sum_l;
  }

  /* Integrator: '<S10>/Integrator' */
  if (rtmIsMajorTimeStep(autopilot_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((autopilot_B.LogicalOperator_d !=
      (autopilot_PrevZCSigState.Integrator_Reset_ZCE_j == POS_ZCSIG)) &&
                (autopilot_PrevZCSigState.Integrator_Reset_ZCE_j !=
                 UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    autopilot_PrevZCSigState.Integrator_Reset_ZCE_j = (ZCSigState)
      autopilot_B.LogicalOperator_d;
    if (zcEvent || autopilot_B.LogicalOperator_d) {
      autopilot_X.Integrator_CSTATE_n = autopilot_P.Integrator_IC_l;
    }
  }

  rtb_Integrator_j = autopilot_X.Integrator_CSTATE_n;
  if (rtmIsMajorTimeStep(autopilot_M)) {
    /* Gain: '<S10>/Proportional Gain' */
    autopilot_B.ProportionalGain_l = autopilot_P.ProportionalGain_Gain_e *
      rtb_Sum_l;
  }

  /* Switch: '<S6>/Switch' incorporates:
   *  Sum: '<S10>/Sum'
   */
  if (autopilot_B.DataTypeConversion_l > autopilot_P.Switch_Threshold_b) {
    autopilot_B.Switch_e = (autopilot_B.ProportionalGain_l + rtb_Integrator_j) +
      autopilot_B.FilterCoefficient_e;
  } else {
    autopilot_B.Switch_e = 0.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void autopilot_update(int_T tid)
{
  if (rtmIsMajorTimeStep(autopilot_M)) {
    /* S-Function Block: <S1>/Packet Output */
    {
      uint8_T outdata[40U];
      RTWin_ANYTYPEPTR outdp;
      outdp.p_uint8_T = outdata;
      *outdp.p_int32_T++ = (int32_T) 0.0;
      *outdp.p_int32_T++ = (int32_T) 0.0;
      *outdp.p_real_T++ = (real_T) autopilot_B.Switch_i;
      *outdp.p_real_T++ = (real_T) autopilot_B.Switch;
      *outdp.p_real_T++ = (real_T) autopilot_B.Switch_e;
      *outdp.p_real_T++ = (real_T) autopilot_B.Switch_l;
      RTBIO_DriverIO(1, STREAMOUTPUT, IOWRITE, 40U,
                     &autopilot_P.PacketOutput_PacketID, (double*) outdata, NULL);
    }
  }

  if (rtmIsMajorTimeStep(autopilot_M)) {
    rt_ertODEUpdateContinuousStates(&autopilot_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++autopilot_M->Timing.clockTick0)) {
    ++autopilot_M->Timing.clockTickH0;
  }

  autopilot_M->Timing.t[0] = rtsiGetSolverStopTime(&autopilot_M->solverInfo);
  if (rtmIsMajorTimeStep(autopilot_M)) {
    /* Update absolute timer for sample time: [0.02s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++autopilot_M->Timing.clockTick1)) {
      ++autopilot_M->Timing.clockTickH1;
    }

    autopilot_M->Timing.t[1] = autopilot_M->Timing.clockTick1 *
      autopilot_M->Timing.stepSize1 + autopilot_M->Timing.clockTickH1 *
      autopilot_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void autopilot_derivatives(void)
{
  /* Derivatives for Integrator: '<S7>/Filter' */
  {
    if (!autopilot_B.LogicalOperator) {
      ((StateDerivatives_autopilot *) autopilot_M->ModelData.derivs)
        ->Filter_CSTATE = autopilot_B.FilterCoefficient;
    } else {
      /* level reset is active*/
      ((StateDerivatives_autopilot *) autopilot_M->ModelData.derivs)
        ->Filter_CSTATE = 0.0;
    }
  }

  /* Derivatives for Integrator: '<S7>/Integrator' */
  {
    if (!autopilot_B.LogicalOperator) {
      ((StateDerivatives_autopilot *) autopilot_M->ModelData.derivs)
        ->Integrator_CSTATE = autopilot_B.IntegralGain;
    } else {
      /* level reset is active*/
      ((StateDerivatives_autopilot *) autopilot_M->ModelData.derivs)
        ->Integrator_CSTATE = 0.0;
    }
  }

  /* Derivatives for Integrator: '<S8>/Filter' */
  {
    if (!autopilot_B.LogicalOperator_n) {
      ((StateDerivatives_autopilot *) autopilot_M->ModelData.derivs)
        ->Filter_CSTATE_l = autopilot_B.FilterCoefficient_f;
    } else {
      /* level reset is active*/
      ((StateDerivatives_autopilot *) autopilot_M->ModelData.derivs)
        ->Filter_CSTATE_l = 0.0;
    }
  }

  /* Derivatives for Integrator: '<S8>/Integrator' */
  {
    if (!autopilot_B.LogicalOperator_n) {
      ((StateDerivatives_autopilot *) autopilot_M->ModelData.derivs)
        ->Integrator_CSTATE_d = autopilot_B.IntegralGain_k;
    } else {
      /* level reset is active*/
      ((StateDerivatives_autopilot *) autopilot_M->ModelData.derivs)
        ->Integrator_CSTATE_d = 0.0;
    }
  }

  /* Derivatives for Integrator: '<S9>/Filter' */
  {
    if (!autopilot_B.LogicalOperator_i) {
      ((StateDerivatives_autopilot *) autopilot_M->ModelData.derivs)
        ->Filter_CSTATE_i = autopilot_B.FilterCoefficient_c;
    } else {
      /* level reset is active*/
      ((StateDerivatives_autopilot *) autopilot_M->ModelData.derivs)
        ->Filter_CSTATE_i = 0.0;
    }
  }

  /* Derivatives for Integrator: '<S9>/Integrator' */
  {
    if (!autopilot_B.LogicalOperator_i) {
      ((StateDerivatives_autopilot *) autopilot_M->ModelData.derivs)
        ->Integrator_CSTATE_e = autopilot_B.IntegralGain_a;
    } else {
      /* level reset is active*/
      ((StateDerivatives_autopilot *) autopilot_M->ModelData.derivs)
        ->Integrator_CSTATE_e = 0.0;
    }
  }

  /* Derivatives for Integrator: '<S10>/Filter' */
  {
    if (!autopilot_B.LogicalOperator_d) {
      ((StateDerivatives_autopilot *) autopilot_M->ModelData.derivs)
        ->Filter_CSTATE_p = autopilot_B.FilterCoefficient_e;
    } else {
      /* level reset is active*/
      ((StateDerivatives_autopilot *) autopilot_M->ModelData.derivs)
        ->Filter_CSTATE_p = 0.0;
    }
  }

  /* Derivatives for Integrator: '<S10>/Integrator' */
  {
    if (!autopilot_B.LogicalOperator_d) {
      ((StateDerivatives_autopilot *) autopilot_M->ModelData.derivs)
        ->Integrator_CSTATE_n = autopilot_B.IntegralGain_m;
    } else {
      /* level reset is active*/
      ((StateDerivatives_autopilot *) autopilot_M->ModelData.derivs)
        ->Integrator_CSTATE_n = 0.0;
    }
  }
}

/* Model initialize function */
void autopilot_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)autopilot_M, 0,
                sizeof(RT_MODEL_autopilot));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&autopilot_M->solverInfo,
                          &autopilot_M->Timing.simTimeStep);
    rtsiSetTPtr(&autopilot_M->solverInfo, &rtmGetTPtr(autopilot_M));
    rtsiSetStepSizePtr(&autopilot_M->solverInfo, &autopilot_M->Timing.stepSize0);
    rtsiSetdXPtr(&autopilot_M->solverInfo, &autopilot_M->ModelData.derivs);
    rtsiSetContStatesPtr(&autopilot_M->solverInfo,
                         &autopilot_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&autopilot_M->solverInfo,
      &autopilot_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&autopilot_M->solverInfo, (&rtmGetErrorStatus
      (autopilot_M)));
    rtsiSetRTModelPtr(&autopilot_M->solverInfo, autopilot_M);
  }

  rtsiSetSimTimeStep(&autopilot_M->solverInfo, MAJOR_TIME_STEP);
  autopilot_M->ModelData.intgData.f[0] = autopilot_M->ModelData.odeF[0];
  autopilot_M->ModelData.contStates = ((real_T *) &autopilot_X);
  rtsiSetSolverData(&autopilot_M->solverInfo, (void *)
                    &autopilot_M->ModelData.intgData);
  rtsiSetSolverName(&autopilot_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = autopilot_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    autopilot_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    autopilot_M->Timing.sampleTimes = (&autopilot_M->Timing.sampleTimesArray[0]);
    autopilot_M->Timing.offsetTimes = (&autopilot_M->Timing.offsetTimesArray[0]);

    /* task periods */
    autopilot_M->Timing.sampleTimes[0] = (0.0);
    autopilot_M->Timing.sampleTimes[1] = (0.02);

    /* task offsets */
    autopilot_M->Timing.offsetTimes[0] = (0.0);
    autopilot_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(autopilot_M, &autopilot_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = autopilot_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    autopilot_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(autopilot_M, -1);
  autopilot_M->Timing.stepSize0 = 0.02;
  autopilot_M->Timing.stepSize1 = 0.02;

  /* external mode info */
  autopilot_M->Sizes.checksums[0] = (3104530854U);
  autopilot_M->Sizes.checksums[1] = (3537910531U);
  autopilot_M->Sizes.checksums[2] = (3301480833U);
  autopilot_M->Sizes.checksums[3] = (2426685723U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[5];
    autopilot_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(autopilot_M->extModeInfo,
      &autopilot_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(autopilot_M->extModeInfo, autopilot_M->Sizes.checksums);
    rteiSetTPtr(autopilot_M->extModeInfo, rtmGetTPtr(autopilot_M));
  }

  autopilot_M->solverInfoPtr = (&autopilot_M->solverInfo);
  autopilot_M->Timing.stepSize = (0.02);
  rtsiSetFixedStepSize(&autopilot_M->solverInfo, 0.02);
  rtsiSetSolverMode(&autopilot_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  autopilot_M->ModelData.blockIO = ((void *) &autopilot_B);
  (void) memset(((void *) &autopilot_B), 0,
                sizeof(BlockIO_autopilot));

  /* parameters */
  autopilot_M->ModelData.defaultParam = ((real_T *)&autopilot_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &autopilot_X;
    autopilot_M->ModelData.contStates = (x);
    (void) memset((void *)&autopilot_X, 0,
                  sizeof(ContinuousStates_autopilot));
  }

  /* states (dwork) */
  autopilot_M->Work.dwork = ((void *) &autopilot_DWork);
  (void) memset((void *)&autopilot_DWork, 0,
                sizeof(D_Work_autopilot));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    autopilot_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  autopilot_PrevZCSigState.Filter_Reset_ZCE = UNINITIALIZED_ZCSIG;
  autopilot_PrevZCSigState.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  autopilot_PrevZCSigState.Filter_Reset_ZCE_k = UNINITIALIZED_ZCSIG;
  autopilot_PrevZCSigState.Integrator_Reset_ZCE_k = UNINITIALIZED_ZCSIG;
  autopilot_PrevZCSigState.Filter_Reset_ZCE_a = UNINITIALIZED_ZCSIG;
  autopilot_PrevZCSigState.Integrator_Reset_ZCE_h = UNINITIALIZED_ZCSIG;
  autopilot_PrevZCSigState.Filter_Reset_ZCE_b = UNINITIALIZED_ZCSIG;
  autopilot_PrevZCSigState.Integrator_Reset_ZCE_j = UNINITIALIZED_ZCSIG;
}

/* Model terminate function */
void autopilot_terminate(void)
{
  /* S-Function Block: <S1>/Packet Output */

  /* no final value should be set */
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  autopilot_output(tid);
}

void MdlUpdate(int_T tid)
{
  autopilot_update(tid);
}

void MdlInitializeSizes(void)
{
  autopilot_M->Sizes.numContStates = (8);/* Number of continuous states */
  autopilot_M->Sizes.numY = (0);       /* Number of model outputs */
  autopilot_M->Sizes.numU = (0);       /* Number of model inputs */
  autopilot_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  autopilot_M->Sizes.numSampTimes = (2);/* Number of sample times */
  autopilot_M->Sizes.numBlocks = (76); /* Number of blocks */
  autopilot_M->Sizes.numBlockIO = (40);/* Number of block outputs */
  autopilot_M->Sizes.numBlockPrms = (34);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* InitializeConditions for Integrator: '<S7>/Filter' */
  autopilot_X.Filter_CSTATE = autopilot_P.Filter_IC;

  /* InitializeConditions for Integrator: '<S7>/Integrator' */
  autopilot_X.Integrator_CSTATE = autopilot_P.Integrator_IC;

  /* InitializeConditions for Integrator: '<S8>/Filter' */
  autopilot_X.Filter_CSTATE_l = autopilot_P.Filter_IC_f;

  /* InitializeConditions for Integrator: '<S8>/Integrator' */
  autopilot_X.Integrator_CSTATE_d = autopilot_P.Integrator_IC_m;

  /* InitializeConditions for Integrator: '<S9>/Filter' */
  autopilot_X.Filter_CSTATE_i = autopilot_P.Filter_IC_a;

  /* InitializeConditions for Integrator: '<S9>/Integrator' */
  autopilot_X.Integrator_CSTATE_e = autopilot_P.Integrator_IC_n;

  /* InitializeConditions for Integrator: '<S10>/Filter' */
  autopilot_X.Filter_CSTATE_p = autopilot_P.Filter_IC_d;

  /* InitializeConditions for Integrator: '<S10>/Integrator' */
  autopilot_X.Integrator_CSTATE_n = autopilot_P.Integrator_IC_l;
}

void MdlStart(void)
{
  /* S-Function Block: <S1>/Packet Output */

  /* no initial value should be set */
  MdlInitialize();
}

void MdlTerminate(void)
{
  autopilot_terminate();
}

RT_MODEL_autopilot *autopilot(void)
{
  autopilot_initialize(1);
  return autopilot_M;
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/
