#ifndef __c2_LinuxMPC_h__
#define __c2_LinuxMPC_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_LinuxMPC;
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  real_T c2_x_hat[8];
  boolean_T c2_x_hat_not_empty;
  real_T c2_P[64];
  boolean_T c2_P_not_empty;
} SFc2_LinuxMPCInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_LinuxMPC_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_LinuxMPC_get_check_sum(mxArray *plhs[]);
extern void c2_LinuxMPC_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
