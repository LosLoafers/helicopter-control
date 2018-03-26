#ifndef __c1_MPC_regul_h__
#define __c1_MPC_regul_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc1_MPC_regulInstanceStruct
#define typedef_SFc1_MPC_regulInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_MPC_regul;
  void *c1_fEmlrtCtx;
  real_T (*c1_u)[2];
  real_T *c1_ddph;
  real_T *c1_ph;
  real_T *c1_th;
  real_T *c1_dph;
  real_T *c1_dth;
  real_T *c1_w1;
  real_T *c1_w2;
  real_T *c1_ddth;
  real_T *c1_dw1;
  real_T *c1_dw2;
  real_T (*c1_x_0)[6];
} SFc1_MPC_regulInstanceStruct;

#endif                                 /*typedef_SFc1_MPC_regulInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_MPC_regul_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_MPC_regul_get_check_sum(mxArray *plhs[]);
extern void c1_MPC_regul_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
