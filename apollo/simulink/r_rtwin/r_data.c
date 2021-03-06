/*
 * r_data.c
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

/* Block parameters (auto storage) */
Parameters_r r_P = {
  0.07,                                /* Expression: D
                                        * Referenced by: '<S7>/Derivative Gain'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S7>/Filter'
                                        */
  10.0,                                /* Expression: N
                                        * Referenced by: '<S7>/Filter Coefficient'
                                        */
  1.0E-006,                            /* Expression: I
                                        * Referenced by: '<S7>/Integral Gain'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S7>/Integrator'
                                        */
  0.012,                               /* Expression: P
                                        * Referenced by: '<S7>/Proportional Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Switch'
                                        */
  0.07,                                /* Expression: D
                                        * Referenced by: '<S8>/Derivative Gain'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S8>/Filter'
                                        */
  10.0,                                /* Expression: N
                                        * Referenced by: '<S8>/Filter Coefficient'
                                        */
  1.0E-006,                            /* Expression: I
                                        * Referenced by: '<S8>/Integral Gain'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S8>/Integrator'
                                        */
  0.012,                               /* Expression: P
                                        * Referenced by: '<S8>/Proportional Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Switch'
                                        */
  0.5,                                 /* Expression: D
                                        * Referenced by: '<S9>/Derivative Gain'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S9>/Filter'
                                        */
  10.0,                                /* Expression: N
                                        * Referenced by: '<S9>/Filter Coefficient'
                                        */
  0.01,                                /* Expression: I
                                        * Referenced by: '<S9>/Integral Gain'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S9>/Integrator'
                                        */
  0.15,                                /* Expression: P
                                        * Referenced by: '<S9>/Proportional Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S5>/Switch'
                                        */
  0.07,                                /* Expression: D
                                        * Referenced by: '<S10>/Derivative Gain'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S10>/Filter'
                                        */
  10.0,                                /* Expression: N
                                        * Referenced by: '<S10>/Filter Coefficient'
                                        */
  1.0E-006,                            /* Expression: I
                                        * Referenced by: '<S10>/Integral Gain'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S10>/Integrator'
                                        */
  0.012,                               /* Expression: P
                                        * Referenced by: '<S10>/Proportional Gain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/Switch'
                                        */
  1,                                   /* Expression: PacketID
                                        * Referenced by: '<S1>/Packet Input'
                                        */
  1,                                   /* Expression: PacketID
                                        * Referenced by: '<S1>/Packet Output'
                                        */
  512,                                 /* Expression: BitMask
                                        * Referenced by: '<S3>/Bitwise Operator'
                                        */
  1024,                                /* Expression: BitMask
                                        * Referenced by: '<S4>/Bitwise Operator'
                                        */
  256,                                 /* Expression: BitMask
                                        * Referenced by: '<S5>/Bitwise Operator'
                                        */
  2048                                 /* Expression: BitMask
                                        * Referenced by: '<S6>/Bitwise Operator'
                                        */
};
