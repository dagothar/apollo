/*
 * r.c
 *
 * Real-Time Workshop code generation for Simulink model "r.mdl".
 *
 * Model version              : 1.180
 * Real-Time Workshop version : 7.5  (R2010a)  25-Jan-2010
 * C source code generated on : Sun Jul 17 16:28:22 2011
 *
 * Target selection: rtwin.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "r.h"
#include "r_private.h"
#include <stdio.h>
#include "r_dt.h"

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
BlockIO_r r_B;

/* Continuous states */
ContinuousStates_r r_X;

/* Block states (auto storage) */
D_Work_r r_DWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates_r r_PrevZCSigState;

/* Real-time model */
RT_MODEL_r r_M_;
RT_MODEL_r *r_M = &r_M_;

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
  r_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void r_output(int_T tid)
{
  /* local block i/o variables */
  real_T rtb_Integrator;
  real_T rtb_Integrator_n;
  real_T rtb_Integrator_o;
  real_T rtb_Integrator_g;
  real_T rtb_Filter;
  real_T rtb_Sum_p;
  int32_T i;
  if (rtmIsMajorTimeStep(r_M)) {
    /* set solver stop time */
    if (!(r_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&r_M->solverInfo, ((r_M->Timing.clockTickH0 + 1) *
        r_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&r_M->solverInfo, ((r_M->Timing.clockTick0 + 1) *
        r_M->Timing.stepSize0 + r_M->Timing.clockTickH0 * r_M->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(r_M)) {
    r_M->Timing.t[0] = rtsiGetT(&r_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(r_M)) {
    /* S-Function Block: <S1>/Packet Input */
    {
      uint8_T indata[192U];
      int status = RTBIO_DriverIO(0, STREAMINPUT, IOREAD, 192U,
        &r_P.PacketInput_PacketID, (double*) indata, NULL);
      if (status & 0x1) {
        RTWin_ANYTYPEPTR indp;
        indp.p_uint8_T = indata;
        r_B.PacketInput_o1 = *indp.p_int32_T++;
        r_B.PacketInput_o2 = *indp.p_int32_T++;
        r_B.PacketInput_o3[0] = *indp.p_real_T++;
        r_B.PacketInput_o3[1] = *indp.p_real_T++;
        r_B.PacketInput_o4[0] = *indp.p_real_T++;
        r_B.PacketInput_o4[1] = *indp.p_real_T++;
        r_B.PacketInput_o4[2] = *indp.p_real_T++;
        r_B.PacketInput_o4[3] = *indp.p_real_T++;
        r_B.PacketInput_o4[4] = *indp.p_real_T++;
        r_B.PacketInput_o4[5] = *indp.p_real_T++;
        r_B.PacketInput_o4[6] = *indp.p_real_T++;
        r_B.PacketInput_o5[0] = *indp.p_real_T++;
        r_B.PacketInput_o5[1] = *indp.p_real_T++;
        r_B.PacketInput_o5[2] = *indp.p_real_T++;
        r_B.PacketInput_o5[3] = *indp.p_real_T++;
        r_B.PacketInput_o5[4] = *indp.p_real_T++;
        r_B.PacketInput_o5[5] = *indp.p_real_T++;
        r_B.PacketInput_o6[0] = *indp.p_real_T++;
        r_B.PacketInput_o6[1] = *indp.p_real_T++;
        r_B.PacketInput_o6[2] = *indp.p_real_T++;
        r_B.PacketInput_o6[3] = *indp.p_real_T++;
        r_B.PacketInput_o6[4] = *indp.p_real_T++;
        r_B.PacketInput_o6[5] = *indp.p_real_T++;
        r_B.PacketInput_o6[6] = *indp.p_real_T++;
        r_B.PacketInput_o6[7] = *indp.p_real_T++;
      }
    }

    /* RateTransition: '<S1>/Rate Transition2' */
    if (rtmIsMajorTimeStep(r_M)) {
      r_B.RateTransition2 = r_B.PacketInput_o1;
    }

    /* RateTransition: '<S1>/Rate Transition3' */
    if (rtmIsMajorTimeStep(r_M)) {
      r_B.RateTransition3[0] = r_B.PacketInput_o3[0];
      r_B.RateTransition3[1] = r_B.PacketInput_o3[1];
    }

    /* RateTransition: '<S1>/Rate Transition4' */
    if (rtmIsMajorTimeStep(r_M)) {
      for (i = 0; i < 7; i++) {
        r_B.RateTransition4[i] = r_B.PacketInput_o4[i];
      }
    }

    /* RateTransition: '<S1>/Rate Transition5' */
    if (rtmIsMajorTimeStep(r_M)) {
      for (i = 0; i < 6; i++) {
        r_B.RateTransition5[i] = r_B.PacketInput_o5[i];
      }
    }

    /* RateTransition: '<S1>/Rate Transition6' */
    if (rtmIsMajorTimeStep(r_M)) {
      memcpy((void *)(&r_B.RateTransition6[0]), (void *)(&r_B.PacketInput_o6[0]),
             sizeof(real_T) << 3U);
    }

    /* DataTypeConversion: '<S3>/Data Type Conversion' incorporates:
     *  S-Function (sfix_bitop): '<S3>/Bitwise Operator'
     */
    r_B.DataTypeConversion = (real_T)(r_B.RateTransition2 &
      r_P.BitwiseOperator_BitMask);

    /* Logic: '<S3>/Logical Operator' */
    r_B.LogicalOperator = !(r_B.DataTypeConversion != 0.0);

    /* Sum: '<S3>/Sum' */
    rtb_Sum_p = r_B.RateTransition6[5] - r_B.RateTransition5[0];

    /* Gain: '<S7>/Derivative Gain' */
    r_B.DerivativeGain = r_P.DerivativeGain_Gain * rtb_Sum_p;
  }

  /* Integrator: '<S7>/Filter' */
  if (rtmIsMajorTimeStep(r_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((r_B.LogicalOperator !=
      (r_PrevZCSigState.Filter_Reset_ZCE == POS_ZCSIG)) &&
                (r_PrevZCSigState.Filter_Reset_ZCE != UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    r_PrevZCSigState.Filter_Reset_ZCE = (ZCSigState) r_B.LogicalOperator;
    if (zcEvent || r_B.LogicalOperator) {
      r_X.Filter_CSTATE = r_P.Filter_IC;
    }
  }

  rtb_Filter = r_X.Filter_CSTATE;

  /* Gain: '<S7>/Filter Coefficient' incorporates:
   *  Sum: '<S7>/SumD'
   */
  r_B.FilterCoefficient = (r_B.DerivativeGain - rtb_Filter) *
    r_P.FilterCoefficient_Gain;
  if (rtmIsMajorTimeStep(r_M)) {
    /* Gain: '<S7>/Integral Gain' */
    r_B.IntegralGain = r_P.IntegralGain_Gain * rtb_Sum_p;
  }

  /* Integrator: '<S7>/Integrator' */
  if (rtmIsMajorTimeStep(r_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((r_B.LogicalOperator !=
      (r_PrevZCSigState.Integrator_Reset_ZCE == POS_ZCSIG)) &&
                (r_PrevZCSigState.Integrator_Reset_ZCE != UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    r_PrevZCSigState.Integrator_Reset_ZCE = (ZCSigState) r_B.LogicalOperator;
    if (zcEvent || r_B.LogicalOperator) {
      r_X.Integrator_CSTATE = r_P.Integrator_IC;
    }
  }

  rtb_Integrator = r_X.Integrator_CSTATE;
  if (rtmIsMajorTimeStep(r_M)) {
    /* Gain: '<S7>/Proportional Gain' */
    r_B.ProportionalGain = r_P.ProportionalGain_Gain * rtb_Sum_p;
  }

  /* Switch: '<S3>/Switch' incorporates:
   *  Sum: '<S7>/Sum'
   */
  if (r_B.DataTypeConversion > r_P.Switch_Threshold) {
    r_B.Switch = (r_B.ProportionalGain + rtb_Integrator) + r_B.FilterCoefficient;
  } else {
    r_B.Switch = 0.0;
  }

  if (rtmIsMajorTimeStep(r_M)) {
    /* DataTypeConversion: '<S4>/Data Type Conversion' incorporates:
     *  S-Function (sfix_bitop): '<S4>/Bitwise Operator'
     */
    r_B.DataTypeConversion_f = (real_T)(r_B.RateTransition2 &
      r_P.BitwiseOperator_BitMask_m);

    /* Logic: '<S4>/Logical Operator' */
    r_B.LogicalOperator_d = !(r_B.DataTypeConversion_f != 0.0);

    /* Sum: '<S4>/Sum' */
    rtb_Sum_p = r_B.RateTransition6[6] - r_B.RateTransition5[2];

    /* Gain: '<S8>/Derivative Gain' */
    r_B.DerivativeGain_f = r_P.DerivativeGain_Gain_i * rtb_Sum_p;
  }

  /* Integrator: '<S8>/Filter' */
  if (rtmIsMajorTimeStep(r_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((r_B.LogicalOperator_d !=
      (r_PrevZCSigState.Filter_Reset_ZCE_d == POS_ZCSIG)) &&
                (r_PrevZCSigState.Filter_Reset_ZCE_d != UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    r_PrevZCSigState.Filter_Reset_ZCE_d = (ZCSigState) r_B.LogicalOperator_d;
    if (zcEvent || r_B.LogicalOperator_d) {
      r_X.Filter_CSTATE_k = r_P.Filter_IC_k;
    }
  }

  rtb_Filter = r_X.Filter_CSTATE_k;

  /* Gain: '<S8>/Filter Coefficient' incorporates:
   *  Sum: '<S8>/SumD'
   */
  r_B.FilterCoefficient_k = (r_B.DerivativeGain_f - rtb_Filter) *
    r_P.FilterCoefficient_Gain_c;
  if (rtmIsMajorTimeStep(r_M)) {
    /* Gain: '<S8>/Integral Gain' */
    r_B.IntegralGain_j = r_P.IntegralGain_Gain_e * rtb_Sum_p;
  }

  /* Integrator: '<S8>/Integrator' */
  if (rtmIsMajorTimeStep(r_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((r_B.LogicalOperator_d !=
      (r_PrevZCSigState.Integrator_Reset_ZCE_d == POS_ZCSIG)) &&
                (r_PrevZCSigState.Integrator_Reset_ZCE_d != UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    r_PrevZCSigState.Integrator_Reset_ZCE_d = (ZCSigState) r_B.LogicalOperator_d;
    if (zcEvent || r_B.LogicalOperator_d) {
      r_X.Integrator_CSTATE_p = r_P.Integrator_IC_d;
    }
  }

  rtb_Integrator_n = r_X.Integrator_CSTATE_p;
  if (rtmIsMajorTimeStep(r_M)) {
    /* Gain: '<S8>/Proportional Gain' */
    r_B.ProportionalGain_c = r_P.ProportionalGain_Gain_e * rtb_Sum_p;
  }

  /* Switch: '<S4>/Switch' incorporates:
   *  Sum: '<S8>/Sum'
   */
  if (r_B.DataTypeConversion_f > r_P.Switch_Threshold_n) {
    r_B.Switch_f = (r_B.ProportionalGain_c + rtb_Integrator_n) +
      r_B.FilterCoefficient_k;
  } else {
    r_B.Switch_f = 0.0;
  }

  if (rtmIsMajorTimeStep(r_M)) {
    /* Sum: '<S5>/Sum' */
    r_B.Sum = r_B.RateTransition6[4] - r_B.RateTransition4[3];

    /* DataTypeConversion: '<S5>/Data Type Conversion' incorporates:
     *  S-Function (sfix_bitop): '<S5>/Bitwise Operator'
     */
    r_B.DataTypeConversion_j = (real_T)(r_B.RateTransition2 &
      r_P.BitwiseOperator_BitMask_n);

    /* Logic: '<S5>/Logical Operator' */
    r_B.LogicalOperator_g = !(r_B.DataTypeConversion_j != 0.0);

    /* Gain: '<S9>/Derivative Gain' */
    r_B.DerivativeGain_j = r_P.DerivativeGain_Gain_j * r_B.Sum;
  }

  /* Integrator: '<S9>/Filter' */
  if (rtmIsMajorTimeStep(r_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((r_B.LogicalOperator_g !=
      (r_PrevZCSigState.Filter_Reset_ZCE_b == POS_ZCSIG)) &&
                (r_PrevZCSigState.Filter_Reset_ZCE_b != UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    r_PrevZCSigState.Filter_Reset_ZCE_b = (ZCSigState) r_B.LogicalOperator_g;
    if (zcEvent || r_B.LogicalOperator_g) {
      r_X.Filter_CSTATE_e = r_P.Filter_IC_a;
    }
  }

  rtb_Filter = r_X.Filter_CSTATE_e;

  /* Gain: '<S9>/Filter Coefficient' incorporates:
   *  Sum: '<S9>/SumD'
   */
  r_B.FilterCoefficient_j = (r_B.DerivativeGain_j - rtb_Filter) *
    r_P.FilterCoefficient_Gain_j;
  if (rtmIsMajorTimeStep(r_M)) {
    /* Gain: '<S9>/Integral Gain' */
    r_B.IntegralGain_d = r_P.IntegralGain_Gain_c * r_B.Sum;
  }

  /* Integrator: '<S9>/Integrator' */
  if (rtmIsMajorTimeStep(r_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((r_B.LogicalOperator_g !=
      (r_PrevZCSigState.Integrator_Reset_ZCE_b == POS_ZCSIG)) &&
                (r_PrevZCSigState.Integrator_Reset_ZCE_b != UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    r_PrevZCSigState.Integrator_Reset_ZCE_b = (ZCSigState) r_B.LogicalOperator_g;
    if (zcEvent || r_B.LogicalOperator_g) {
      r_X.Integrator_CSTATE_l = r_P.Integrator_IC_h;
    }
  }

  rtb_Integrator_o = r_X.Integrator_CSTATE_l;
  if (rtmIsMajorTimeStep(r_M)) {
    /* Gain: '<S9>/Proportional Gain' */
    r_B.ProportionalGain_l = r_P.ProportionalGain_Gain_f * r_B.Sum;
  }

  /* Switch: '<S5>/Switch' incorporates:
   *  Sum: '<S9>/Sum'
   */
  if (r_B.DataTypeConversion_j > r_P.Switch_Threshold_i) {
    r_B.Switch_n = (r_B.ProportionalGain_l + rtb_Integrator_o) +
      r_B.FilterCoefficient_j;
  } else {
    r_B.Switch_n = 0.0;
  }

  if (rtmIsMajorTimeStep(r_M)) {
    /* DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
     *  S-Function (sfix_bitop): '<S6>/Bitwise Operator'
     */
    r_B.DataTypeConversion_c = (real_T)(r_B.RateTransition2 &
      r_P.BitwiseOperator_BitMask_l);

    /* Logic: '<S6>/Logical Operator' */
    r_B.LogicalOperator_l = !(r_B.DataTypeConversion_c != 0.0);

    /* Sum: '<S6>/Sum' */
    rtb_Sum_p = r_B.RateTransition6[7] - r_B.RateTransition5[1];

    /* Gain: '<S10>/Derivative Gain' */
    r_B.DerivativeGain_ff = r_P.DerivativeGain_Gain_o * rtb_Sum_p;
  }

  /* Integrator: '<S10>/Filter' */
  if (rtmIsMajorTimeStep(r_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((r_B.LogicalOperator_l !=
      (r_PrevZCSigState.Filter_Reset_ZCE_j == POS_ZCSIG)) &&
                (r_PrevZCSigState.Filter_Reset_ZCE_j != UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    r_PrevZCSigState.Filter_Reset_ZCE_j = (ZCSigState) r_B.LogicalOperator_l;
    if (zcEvent || r_B.LogicalOperator_l) {
      r_X.Filter_CSTATE_g = r_P.Filter_IC_j;
    }
  }

  rtb_Filter = r_X.Filter_CSTATE_g;

  /* Gain: '<S10>/Filter Coefficient' incorporates:
   *  Sum: '<S10>/SumD'
   */
  r_B.FilterCoefficient_h = (r_B.DerivativeGain_ff - rtb_Filter) *
    r_P.FilterCoefficient_Gain_e;
  if (rtmIsMajorTimeStep(r_M)) {
    /* Gain: '<S10>/Integral Gain' */
    r_B.IntegralGain_o = r_P.IntegralGain_Gain_d * rtb_Sum_p;
  }

  /* Integrator: '<S10>/Integrator' */
  if (rtmIsMajorTimeStep(r_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((r_B.LogicalOperator_l !=
      (r_PrevZCSigState.Integrator_Reset_ZCE_h == POS_ZCSIG)) &&
                (r_PrevZCSigState.Integrator_Reset_ZCE_h != UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    r_PrevZCSigState.Integrator_Reset_ZCE_h = (ZCSigState) r_B.LogicalOperator_l;
    if (zcEvent || r_B.LogicalOperator_l) {
      r_X.Integrator_CSTATE_n = r_P.Integrator_IC_m;
    }
  }

  rtb_Integrator_g = r_X.Integrator_CSTATE_n;
  if (rtmIsMajorTimeStep(r_M)) {
    /* Gain: '<S10>/Proportional Gain' */
    r_B.ProportionalGain_g = r_P.ProportionalGain_Gain_h * rtb_Sum_p;
  }

  /* Switch: '<S6>/Switch' incorporates:
   *  Sum: '<S10>/Sum'
   */
  if (r_B.DataTypeConversion_c > r_P.Switch_Threshold_e) {
    r_B.Switch_m = (r_B.ProportionalGain_g + rtb_Integrator_g) +
      r_B.FilterCoefficient_h;
  } else {
    r_B.Switch_m = 0.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void r_update(int_T tid)
{
  if (rtmIsMajorTimeStep(r_M)) {
    /* S-Function Block: <S1>/Packet Output */
    {
      uint8_T outdata[40U];
      RTWin_ANYTYPEPTR outdp;
      outdp.p_uint8_T = outdata;
      *outdp.p_int32_T++ = (int32_T) 0.0;
      *outdp.p_int32_T++ = (int32_T) 0.0;
      *outdp.p_real_T++ = (real_T) r_B.Switch_n;
      *outdp.p_real_T++ = (real_T) r_B.Switch;
      *outdp.p_real_T++ = (real_T) r_B.Switch_m;
      *outdp.p_real_T++ = (real_T) r_B.Switch_f;
      RTBIO_DriverIO(1, STREAMOUTPUT, IOWRITE, 40U, &r_P.PacketOutput_PacketID,
                     (double*) outdata, NULL);
    }
  }

  if (rtmIsMajorTimeStep(r_M)) {
    rt_ertODEUpdateContinuousStates(&r_M->solverInfo);
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
  if (!(++r_M->Timing.clockTick0)) {
    ++r_M->Timing.clockTickH0;
  }

  r_M->Timing.t[0] = rtsiGetSolverStopTime(&r_M->solverInfo);
  if (rtmIsMajorTimeStep(r_M)) {
    /* Update absolute timer for sample time: [0.02s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++r_M->Timing.clockTick1)) {
      ++r_M->Timing.clockTickH1;
    }

    r_M->Timing.t[1] = r_M->Timing.clockTick1 * r_M->Timing.stepSize1 +
      r_M->Timing.clockTickH1 * r_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void r_derivatives(void)
{
  /* Derivatives for Integrator: '<S7>/Filter' */
  {
    if (!r_B.LogicalOperator) {
      ((StateDerivatives_r *) r_M->ModelData.derivs)->Filter_CSTATE =
        r_B.FilterCoefficient;
    } else {
      /* level reset is active*/
      ((StateDerivatives_r *) r_M->ModelData.derivs)->Filter_CSTATE = 0.0;
    }
  }

  /* Derivatives for Integrator: '<S7>/Integrator' */
  {
    if (!r_B.LogicalOperator) {
      ((StateDerivatives_r *) r_M->ModelData.derivs)->Integrator_CSTATE =
        r_B.IntegralGain;
    } else {
      /* level reset is active*/
      ((StateDerivatives_r *) r_M->ModelData.derivs)->Integrator_CSTATE = 0.0;
    }
  }

  /* Derivatives for Integrator: '<S8>/Filter' */
  {
    if (!r_B.LogicalOperator_d) {
      ((StateDerivatives_r *) r_M->ModelData.derivs)->Filter_CSTATE_k =
        r_B.FilterCoefficient_k;
    } else {
      /* level reset is active*/
      ((StateDerivatives_r *) r_M->ModelData.derivs)->Filter_CSTATE_k = 0.0;
    }
  }

  /* Derivatives for Integrator: '<S8>/Integrator' */
  {
    if (!r_B.LogicalOperator_d) {
      ((StateDerivatives_r *) r_M->ModelData.derivs)->Integrator_CSTATE_p =
        r_B.IntegralGain_j;
    } else {
      /* level reset is active*/
      ((StateDerivatives_r *) r_M->ModelData.derivs)->Integrator_CSTATE_p = 0.0;
    }
  }

  /* Derivatives for Integrator: '<S9>/Filter' */
  {
    if (!r_B.LogicalOperator_g) {
      ((StateDerivatives_r *) r_M->ModelData.derivs)->Filter_CSTATE_e =
        r_B.FilterCoefficient_j;
    } else {
      /* level reset is active*/
      ((StateDerivatives_r *) r_M->ModelData.derivs)->Filter_CSTATE_e = 0.0;
    }
  }

  /* Derivatives for Integrator: '<S9>/Integrator' */
  {
    if (!r_B.LogicalOperator_g) {
      ((StateDerivatives_r *) r_M->ModelData.derivs)->Integrator_CSTATE_l =
        r_B.IntegralGain_d;
    } else {
      /* level reset is active*/
      ((StateDerivatives_r *) r_M->ModelData.derivs)->Integrator_CSTATE_l = 0.0;
    }
  }

  /* Derivatives for Integrator: '<S10>/Filter' */
  {
    if (!r_B.LogicalOperator_l) {
      ((StateDerivatives_r *) r_M->ModelData.derivs)->Filter_CSTATE_g =
        r_B.FilterCoefficient_h;
    } else {
      /* level reset is active*/
      ((StateDerivatives_r *) r_M->ModelData.derivs)->Filter_CSTATE_g = 0.0;
    }
  }

  /* Derivatives for Integrator: '<S10>/Integrator' */
  {
    if (!r_B.LogicalOperator_l) {
      ((StateDerivatives_r *) r_M->ModelData.derivs)->Integrator_CSTATE_n =
        r_B.IntegralGain_o;
    } else {
      /* level reset is active*/
      ((StateDerivatives_r *) r_M->ModelData.derivs)->Integrator_CSTATE_n = 0.0;
    }
  }
}

/* Model initialize function */
void r_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)r_M, 0,
                sizeof(RT_MODEL_r));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&r_M->solverInfo, &r_M->Timing.simTimeStep);
    rtsiSetTPtr(&r_M->solverInfo, &rtmGetTPtr(r_M));
    rtsiSetStepSizePtr(&r_M->solverInfo, &r_M->Timing.stepSize0);
    rtsiSetdXPtr(&r_M->solverInfo, &r_M->ModelData.derivs);
    rtsiSetContStatesPtr(&r_M->solverInfo, &r_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&r_M->solverInfo, &r_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&r_M->solverInfo, (&rtmGetErrorStatus(r_M)));
    rtsiSetRTModelPtr(&r_M->solverInfo, r_M);
  }

  rtsiSetSimTimeStep(&r_M->solverInfo, MAJOR_TIME_STEP);
  r_M->ModelData.intgData.f[0] = r_M->ModelData.odeF[0];
  r_M->ModelData.contStates = ((real_T *) &r_X);
  rtsiSetSolverData(&r_M->solverInfo, (void *)&r_M->ModelData.intgData);
  rtsiSetSolverName(&r_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = r_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    r_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    r_M->Timing.sampleTimes = (&r_M->Timing.sampleTimesArray[0]);
    r_M->Timing.offsetTimes = (&r_M->Timing.offsetTimesArray[0]);

    /* task periods */
    r_M->Timing.sampleTimes[0] = (0.0);
    r_M->Timing.sampleTimes[1] = (0.02);

    /* task offsets */
    r_M->Timing.offsetTimes[0] = (0.0);
    r_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(r_M, &r_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = r_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    r_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(r_M, -1);
  r_M->Timing.stepSize0 = 0.02;
  r_M->Timing.stepSize1 = 0.02;

  /* external mode info */
  r_M->Sizes.checksums[0] = (2146525147U);
  r_M->Sizes.checksums[1] = (114594147U);
  r_M->Sizes.checksums[2] = (3439338169U);
  r_M->Sizes.checksums[3] = (2421275999U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[5];
    r_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(r_M->extModeInfo, &r_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(r_M->extModeInfo, r_M->Sizes.checksums);
    rteiSetTPtr(r_M->extModeInfo, rtmGetTPtr(r_M));
  }

  r_M->solverInfoPtr = (&r_M->solverInfo);
  r_M->Timing.stepSize = (0.02);
  rtsiSetFixedStepSize(&r_M->solverInfo, 0.02);
  rtsiSetSolverMode(&r_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  r_M->ModelData.blockIO = ((void *) &r_B);
  (void) memset(((void *) &r_B), 0,
                sizeof(BlockIO_r));

  /* parameters */
  r_M->ModelData.defaultParam = ((real_T *)&r_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &r_X;
    r_M->ModelData.contStates = (x);
    (void) memset((void *)&r_X, 0,
                  sizeof(ContinuousStates_r));
  }

  /* states (dwork) */
  r_M->Work.dwork = ((void *) &r_DWork);
  (void) memset((void *)&r_DWork, 0,
                sizeof(D_Work_r));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    r_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  r_PrevZCSigState.Filter_Reset_ZCE = UNINITIALIZED_ZCSIG;
  r_PrevZCSigState.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  r_PrevZCSigState.Filter_Reset_ZCE_d = UNINITIALIZED_ZCSIG;
  r_PrevZCSigState.Integrator_Reset_ZCE_d = UNINITIALIZED_ZCSIG;
  r_PrevZCSigState.Filter_Reset_ZCE_b = UNINITIALIZED_ZCSIG;
  r_PrevZCSigState.Integrator_Reset_ZCE_b = UNINITIALIZED_ZCSIG;
  r_PrevZCSigState.Filter_Reset_ZCE_j = UNINITIALIZED_ZCSIG;
  r_PrevZCSigState.Integrator_Reset_ZCE_h = UNINITIALIZED_ZCSIG;
}

/* Model terminate function */
void r_terminate(void)
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
  r_output(tid);
}

void MdlUpdate(int_T tid)
{
  r_update(tid);
}

void MdlInitializeSizes(void)
{
  r_M->Sizes.numContStates = (8);      /* Number of continuous states */
  r_M->Sizes.numY = (0);               /* Number of model outputs */
  r_M->Sizes.numU = (0);               /* Number of model inputs */
  r_M->Sizes.sysDirFeedThru = (0);     /* The model is not direct feedthrough */
  r_M->Sizes.numSampTimes = (2);       /* Number of sample times */
  r_M->Sizes.numBlocks = (76);         /* Number of blocks */
  r_M->Sizes.numBlockIO = (40);        /* Number of block outputs */
  r_M->Sizes.numBlockPrms = (34);      /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* InitializeConditions for Integrator: '<S7>/Filter' */
  r_X.Filter_CSTATE = r_P.Filter_IC;

  /* InitializeConditions for Integrator: '<S7>/Integrator' */
  r_X.Integrator_CSTATE = r_P.Integrator_IC;

  /* InitializeConditions for Integrator: '<S8>/Filter' */
  r_X.Filter_CSTATE_k = r_P.Filter_IC_k;

  /* InitializeConditions for Integrator: '<S8>/Integrator' */
  r_X.Integrator_CSTATE_p = r_P.Integrator_IC_d;

  /* InitializeConditions for Integrator: '<S9>/Filter' */
  r_X.Filter_CSTATE_e = r_P.Filter_IC_a;

  /* InitializeConditions for Integrator: '<S9>/Integrator' */
  r_X.Integrator_CSTATE_l = r_P.Integrator_IC_h;

  /* InitializeConditions for Integrator: '<S10>/Filter' */
  r_X.Filter_CSTATE_g = r_P.Filter_IC_j;

  /* InitializeConditions for Integrator: '<S10>/Integrator' */
  r_X.Integrator_CSTATE_n = r_P.Integrator_IC_m;
}

void MdlStart(void)
{
  /* S-Function Block: <S1>/Packet Output */

  /* no initial value should be set */
  MdlInitialize();
}

void MdlTerminate(void)
{
  r_terminate();
}

RT_MODEL_r *r(void)
{
  r_initialize(1);
  return r_M;
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/
