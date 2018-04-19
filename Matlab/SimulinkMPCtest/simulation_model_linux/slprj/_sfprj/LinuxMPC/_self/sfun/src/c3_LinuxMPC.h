#ifndef __c3_LinuxMPC_h__
#define __c3_LinuxMPC_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  const char * context;
  const char * name;
  const char * dominantType;
  const char * resolved;
  uint32_T fileTimeLo;
  uint32_T fileTimeHi;
  uint32_T mFileTimeLo;
  uint32_T mFileTimeHi;
} c3_ResolvedFunctionInfo;

typedef struct {
  int32_T c3_sfEvent;
  boolean_T c3_isStable;
  boolean_T c3_doneDoubleBufferReInit;
  uint8_T c3_is_active_c3_LinuxMPC;
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  real_T c3_i;
  boolean_T c3_i_not_empty;
  real_T c3_x_;
  boolean_T c3_x__not_empty;
} SFc3_LinuxMPCInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_LinuxMPC_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c3_LinuxMPC_get_check_sum(mxArray *plhs[]);
extern void c3_LinuxMPC_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
