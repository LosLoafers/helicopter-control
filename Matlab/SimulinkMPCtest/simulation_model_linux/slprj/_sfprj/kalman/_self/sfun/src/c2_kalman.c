/* Include files */

#include "blascompat32.h"
#include "kalman_sfun.h"
#include "c2_kalman.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "kalman_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[10] = { "nargin", "nargout", "u", "y",
  "x_0", "P_0", "stop_angle", "x", "x_hat", "P" };

/* Function Declarations */
static void initialize_c2_kalman(SFc2_kalmanInstanceStruct *chartInstance);
static void initialize_params_c2_kalman(SFc2_kalmanInstanceStruct *chartInstance);
static void enable_c2_kalman(SFc2_kalmanInstanceStruct *chartInstance);
static void disable_c2_kalman(SFc2_kalmanInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_kalman(SFc2_kalmanInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_kalman(SFc2_kalmanInstanceStruct
  *chartInstance);
static void set_sim_state_c2_kalman(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_st);
static void finalize_c2_kalman(SFc2_kalmanInstanceStruct *chartInstance);
static void sf_c2_kalman(SFc2_kalmanInstanceStruct *chartInstance);
static void initSimStructsc2_kalman(SFc2_kalmanInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance, const
  mxArray *c2_b_P, const char_T *c2_identifier, real_T c2_y[64]);
static void c2_b_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[64]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_c_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_b_x_hat, const char_T *c2_identifier, real_T c2_y[8]);
static void c2_d_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[8]);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_e_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_f_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_b_x_hat, const char_T *c2_identifier, real_T c2_y[8]);
static void c2_g_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[8]);
static void c2_h_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_b_P, const char_T *c2_identifier, real_T c2_y[64]);
static void c2_i_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[64]);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_j_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_k_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_kalman, const char_T *c2_identifier);
static uint8_T c2_l_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_kalmanInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_kalman(SFc2_kalmanInstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_x_hat_not_empty = FALSE;
  chartInstance->c2_P_not_empty = FALSE;
  chartInstance->c2_is_active_c2_kalman = 0U;
}

static void initialize_params_c2_kalman(SFc2_kalmanInstanceStruct *chartInstance)
{
}

static void enable_c2_kalman(SFc2_kalmanInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_kalman(SFc2_kalmanInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_kalman(SFc2_kalmanInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c2_kalman(SFc2_kalmanInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  real_T c2_u[8];
  const mxArray *c2_b_y = NULL;
  int32_T c2_i1;
  real_T c2_b_u[64];
  const mxArray *c2_c_y = NULL;
  int32_T c2_i2;
  real_T c2_c_u[8];
  const mxArray *c2_d_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_d_u;
  const mxArray *c2_e_y = NULL;
  real_T (*c2_x)[8];
  c2_x = (real_T (*)[8])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(4), FALSE);
  for (c2_i0 = 0; c2_i0 < 8; c2_i0++) {
    c2_u[c2_i0] = (*c2_x)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 8), FALSE);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  for (c2_i1 = 0; c2_i1 < 64; c2_i1++) {
    c2_b_u[c2_i1] = chartInstance->c2_P[c2_i1];
  }

  c2_c_y = NULL;
  if (!chartInstance->c2_P_not_empty) {
    sf_mex_assign(&c2_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 8, 8),
                  FALSE);
  }

  sf_mex_setcell(c2_y, 1, c2_c_y);
  for (c2_i2 = 0; c2_i2 < 8; c2_i2++) {
    c2_c_u[c2_i2] = chartInstance->c2_x_hat[c2_i2];
  }

  c2_d_y = NULL;
  if (!chartInstance->c2_x_hat_not_empty) {
    sf_mex_assign(&c2_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 1, 8),
                  FALSE);
  }

  sf_mex_setcell(c2_y, 2, c2_d_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_kalman;
  c2_d_u = c2_hoistedGlobal;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_d_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 3, c2_e_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_kalman(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[8];
  int32_T c2_i3;
  real_T c2_dv1[64];
  int32_T c2_i4;
  real_T c2_dv2[8];
  int32_T c2_i5;
  real_T (*c2_x)[8];
  c2_x = (real_T (*)[8])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)), "x",
                        c2_dv0);
  for (c2_i3 = 0; c2_i3 < 8; c2_i3++) {
    (*c2_x)[c2_i3] = c2_dv0[c2_i3];
  }

  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)), "P",
                      c2_dv1);
  for (c2_i4 = 0; c2_i4 < 64; c2_i4++) {
    chartInstance->c2_P[c2_i4] = c2_dv1[c2_i4];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 2)),
                        "x_hat", c2_dv2);
  for (c2_i5 = 0; c2_i5 < 8; c2_i5++) {
    chartInstance->c2_x_hat[c2_i5] = c2_dv2[c2_i5];
  }

  chartInstance->c2_is_active_c2_kalman = c2_k_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 3)), "is_active_c2_kalman");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_kalman(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_kalman(SFc2_kalmanInstanceStruct *chartInstance)
{
}

static void sf_c2_kalman(SFc2_kalmanInstanceStruct *chartInstance)
{
  int32_T c2_i6;
  int32_T c2_i7;
  int32_T c2_i8;
  int32_T c2_i9;
  int32_T c2_i10;
  real_T c2_hoistedGlobal;
  int32_T c2_i11;
  real_T c2_u[2];
  int32_T c2_i12;
  real_T c2_y[2];
  int32_T c2_i13;
  real_T c2_x_0[8];
  int32_T c2_i14;
  real_T c2_P_0[64];
  real_T c2_stop_angle;
  uint32_T c2_debug_family_var_map[10];
  real_T c2_nargin = 5.0;
  real_T c2_nargout = 1.0;
  real_T c2_x[8];
  int32_T c2_i15;
  int32_T c2_i16;
  int32_T c2_i17;
  real_T c2_b_hoistedGlobal[8];
  int32_T c2_i18;
  real_T c2_b_u[8];
  const mxArray *c2_b_y = NULL;
  int32_T c2_i19;
  real_T c2_c_u[2];
  const mxArray *c2_c_y = NULL;
  int32_T c2_i20;
  real_T c2_d_u[2];
  const mxArray *c2_d_y = NULL;
  int32_T c2_i21;
  real_T c2_c_hoistedGlobal[64];
  int32_T c2_i22;
  real_T c2_e_u[64];
  const mxArray *c2_e_y = NULL;
  real_T c2_f_u;
  const mxArray *c2_f_y = NULL;
  const mxArray *c2_m0 = NULL;
  const mxArray *c2_m1 = NULL;
  const mxArray *c2_b_x_hat = NULL;
  const mxArray *c2_b_P = NULL;
  real_T c2_dv3[8];
  int32_T c2_i23;
  real_T c2_dv4[64];
  int32_T c2_i24;
  int32_T c2_i25;
  int32_T c2_i26;
  real_T *c2_b_stop_angle;
  real_T (*c2_b_x)[8];
  real_T (*c2_b_P_0)[64];
  real_T (*c2_b_x_0)[8];
  real_T (*c2_g_y)[2];
  real_T (*c2_g_u)[2];
  c2_b_x = (real_T (*)[8])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_stop_angle = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c2_b_P_0 = (real_T (*)[64])ssGetInputPortSignal(chartInstance->S, 3);
  c2_b_x_0 = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S, 2);
  c2_g_y = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 1);
  c2_g_u = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i6 = 0; c2_i6 < 2; c2_i6++) {
    _SFD_DATA_RANGE_CHECK((*c2_g_u)[c2_i6], 0U);
  }

  for (c2_i7 = 0; c2_i7 < 2; c2_i7++) {
    _SFD_DATA_RANGE_CHECK((*c2_g_y)[c2_i7], 1U);
  }

  for (c2_i8 = 0; c2_i8 < 8; c2_i8++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_x_0)[c2_i8], 2U);
  }

  for (c2_i9 = 0; c2_i9 < 64; c2_i9++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_P_0)[c2_i9], 3U);
  }

  _SFD_DATA_RANGE_CHECK(*c2_b_stop_angle, 4U);
  for (c2_i10 = 0; c2_i10 < 8; c2_i10++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_x)[c2_i10], 5U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *c2_b_stop_angle;
  for (c2_i11 = 0; c2_i11 < 2; c2_i11++) {
    c2_u[c2_i11] = (*c2_g_u)[c2_i11];
  }

  for (c2_i12 = 0; c2_i12 < 2; c2_i12++) {
    c2_y[c2_i12] = (*c2_g_y)[c2_i12];
  }

  for (c2_i13 = 0; c2_i13 < 8; c2_i13++) {
    c2_x_0[c2_i13] = (*c2_b_x_0)[c2_i13];
  }

  for (c2_i14 = 0; c2_i14 < 64; c2_i14++) {
    c2_P_0[c2_i14] = (*c2_b_P_0)[c2_i14];
  }

  c2_stop_angle = c2_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 10U, 10U, c2_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 0U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 1U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c2_u, 2U, c2_f_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_y, 3U, c2_f_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_x_0, 4U, c2_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_P_0, 5U, c2_e_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_stop_angle, 6U, c2_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c2_x, 7U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(chartInstance->c2_x_hat, 8U,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(chartInstance->c2_P, 9U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 5);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c2_x_hat_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
    for (c2_i15 = 0; c2_i15 < 8; c2_i15++) {
      chartInstance->c2_x_hat[c2_i15] = c2_x_0[c2_i15];
    }

    chartInstance->c2_x_hat_not_empty = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 7);
    for (c2_i16 = 0; c2_i16 < 64; c2_i16++) {
      chartInstance->c2_P[c2_i16] = c2_P_0[c2_i16];
    }

    chartInstance->c2_P_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 9);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 11);
  for (c2_i17 = 0; c2_i17 < 8; c2_i17++) {
    c2_b_hoistedGlobal[c2_i17] = chartInstance->c2_x_hat[c2_i17];
  }

  for (c2_i18 = 0; c2_i18 < 8; c2_i18++) {
    c2_b_u[c2_i18] = c2_b_hoistedGlobal[c2_i18];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 1, 8), FALSE);
  for (c2_i19 = 0; c2_i19 < 2; c2_i19++) {
    c2_c_u[c2_i19] = c2_u[c2_i19];
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  for (c2_i20 = 0; c2_i20 < 2; c2_i20++) {
    c2_d_u[c2_i20] = c2_y[c2_i20];
  }

  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  for (c2_i21 = 0; c2_i21 < 64; c2_i21++) {
    c2_c_hoistedGlobal[c2_i21] = chartInstance->c2_P[c2_i21];
  }

  for (c2_i22 = 0; c2_i22 < 64; c2_i22++) {
    c2_e_u[c2_i22] = c2_c_hoistedGlobal[c2_i22];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 8, 8),
                FALSE);
  c2_f_u = c2_stop_angle;
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", &c2_f_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_call_debug("updateKalman", 2U, 5U, 14, c2_b_y, 14, c2_c_y, 14, c2_d_y,
                    14, c2_e_y, 14, c2_f_y, &c2_m1, &c2_m0);
  sf_mex_assign(&c2_b_x_hat, sf_mex_dup(c2_m1), FALSE);
  sf_mex_assign(&c2_b_P, sf_mex_dup(c2_m0), FALSE);
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_x_hat), "x_hat", c2_dv3);
  for (c2_i23 = 0; c2_i23 < 8; c2_i23++) {
    chartInstance->c2_x_hat[c2_i23] = c2_dv3[c2_i23];
  }

  c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_P), "P", c2_dv4);
  for (c2_i24 = 0; c2_i24 < 64; c2_i24++) {
    chartInstance->c2_P[c2_i24] = c2_dv4[c2_i24];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 13);
  for (c2_i25 = 0; c2_i25 < 8; c2_i25++) {
    c2_x[c2_i25] = chartInstance->c2_x_hat[c2_i25];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -13);
  sf_debug_symbol_scope_pop();
  sf_mex_destroy(&c2_b_x_hat);
  sf_mex_destroy(&c2_b_P);
  sf_mex_destroy(&c2_m0);
  sf_mex_destroy(&c2_m1);
  for (c2_i26 = 0; c2_i26 < 8; c2_i26++) {
    (*c2_b_x)[c2_i26] = c2_x[c2_i26];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  sf_debug_check_for_state_inconsistency(_kalmanMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc2_kalman(SFc2_kalmanInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i27;
  int32_T c2_i28;
  int32_T c2_i29;
  real_T c2_b_inData[64];
  int32_T c2_i30;
  int32_T c2_i31;
  int32_T c2_i32;
  real_T c2_u[64];
  const mxArray *c2_y = NULL;
  SFc2_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc2_kalmanInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i27 = 0;
  for (c2_i28 = 0; c2_i28 < 8; c2_i28++) {
    for (c2_i29 = 0; c2_i29 < 8; c2_i29++) {
      c2_b_inData[c2_i29 + c2_i27] = (*(real_T (*)[64])c2_inData)[c2_i29 +
        c2_i27];
    }

    c2_i27 += 8;
  }

  c2_i30 = 0;
  for (c2_i31 = 0; c2_i31 < 8; c2_i31++) {
    for (c2_i32 = 0; c2_i32 < 8; c2_i32++) {
      c2_u[c2_i32 + c2_i30] = c2_b_inData[c2_i32 + c2_i30];
    }

    c2_i30 += 8;
  }

  c2_y = NULL;
  if (!chartInstance->c2_P_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 8, 8), FALSE);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance, const
  mxArray *c2_b_P, const char_T *c2_identifier, real_T c2_y[64])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_P), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_P);
}

static void c2_b_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[64])
{
  real_T c2_dv5[64];
  int32_T c2_i33;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_P_not_empty = FALSE;
  } else {
    chartInstance->c2_P_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv5, 1, 0, 0U, 1, 0U, 2, 8,
                  8);
    for (c2_i33 = 0; c2_i33 < 64; c2_i33++) {
      c2_y[c2_i33] = c2_dv5[c2_i33];
    }
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_P;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[64];
  int32_T c2_i34;
  int32_T c2_i35;
  int32_T c2_i36;
  SFc2_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc2_kalmanInstanceStruct *)chartInstanceVoid;
  c2_b_P = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_P), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_P);
  c2_i34 = 0;
  for (c2_i35 = 0; c2_i35 < 8; c2_i35++) {
    for (c2_i36 = 0; c2_i36 < 8; c2_i36++) {
      (*(real_T (*)[64])c2_outData)[c2_i36 + c2_i34] = c2_y[c2_i36 + c2_i34];
    }

    c2_i34 += 8;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i37;
  real_T c2_b_inData[8];
  int32_T c2_i38;
  real_T c2_u[8];
  const mxArray *c2_y = NULL;
  SFc2_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc2_kalmanInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i37 = 0; c2_i37 < 8; c2_i37++) {
    c2_b_inData[c2_i37] = (*(real_T (*)[8])c2_inData)[c2_i37];
  }

  for (c2_i38 = 0; c2_i38 < 8; c2_i38++) {
    c2_u[c2_i38] = c2_b_inData[c2_i38];
  }

  c2_y = NULL;
  if (!chartInstance->c2_x_hat_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 8), FALSE);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_c_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_b_x_hat, const char_T *c2_identifier, real_T c2_y[8])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_x_hat), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_x_hat);
}

static void c2_d_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[8])
{
  real_T c2_dv6[8];
  int32_T c2_i39;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_x_hat_not_empty = FALSE;
  } else {
    chartInstance->c2_x_hat_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv6, 1, 0, 0U, 1, 0U, 1, 8);
    for (c2_i39 = 0; c2_i39 < 8; c2_i39++) {
      c2_y[c2_i39] = c2_dv6[c2_i39];
    }
  }

  sf_mex_destroy(&c2_u);
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_x_hat;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[8];
  int32_T c2_i40;
  SFc2_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc2_kalmanInstanceStruct *)chartInstanceVoid;
  c2_b_x_hat = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_x_hat), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_x_hat);
  for (c2_i40 = 0; c2_i40 < 8; c2_i40++) {
    (*(real_T (*)[8])c2_outData)[c2_i40] = c2_y[c2_i40];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i41;
  real_T c2_b_inData[8];
  int32_T c2_i42;
  real_T c2_u[8];
  const mxArray *c2_y = NULL;
  SFc2_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc2_kalmanInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i41 = 0; c2_i41 < 8; c2_i41++) {
    c2_b_inData[c2_i41] = (*(real_T (*)[8])c2_inData)[c2_i41];
  }

  for (c2_i42 = 0; c2_i42 < 8; c2_i42++) {
    c2_u[c2_i42] = c2_b_inData[c2_i42];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 8), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_x_hat;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[8];
  int32_T c2_i43;
  SFc2_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc2_kalmanInstanceStruct *)chartInstanceVoid;
  c2_b_x_hat = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_x_hat), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_x_hat);
  for (c2_i43 = 0; c2_i43 < 8; c2_i43++) {
    (*(real_T (*)[8])c2_outData)[c2_i43] = c2_y[c2_i43];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc2_kalmanInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i44;
  int32_T c2_i45;
  int32_T c2_i46;
  real_T c2_b_inData[64];
  int32_T c2_i47;
  int32_T c2_i48;
  int32_T c2_i49;
  real_T c2_u[64];
  const mxArray *c2_y = NULL;
  SFc2_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc2_kalmanInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i44 = 0;
  for (c2_i45 = 0; c2_i45 < 8; c2_i45++) {
    for (c2_i46 = 0; c2_i46 < 8; c2_i46++) {
      c2_b_inData[c2_i46 + c2_i44] = (*(real_T (*)[64])c2_inData)[c2_i46 +
        c2_i44];
    }

    c2_i44 += 8;
  }

  c2_i47 = 0;
  for (c2_i48 = 0; c2_i48 < 8; c2_i48++) {
    for (c2_i49 = 0; c2_i49 < 8; c2_i49++) {
      c2_u[c2_i49 + c2_i47] = c2_b_inData[c2_i49 + c2_i47];
    }

    c2_i47 += 8;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 8, 8), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i50;
  real_T c2_b_inData[2];
  int32_T c2_i51;
  real_T c2_u[2];
  const mxArray *c2_y = NULL;
  SFc2_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc2_kalmanInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i50 = 0; c2_i50 < 2; c2_i50++) {
    c2_b_inData[c2_i50] = (*(real_T (*)[2])c2_inData)[c2_i50];
  }

  for (c2_i51 = 0; c2_i51 < 2; c2_i51++) {
    c2_u[c2_i51] = c2_b_inData[c2_i51];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_e_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc2_kalmanInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_kalman_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), FALSE);
  return c2_nameCaptureInfo;
}

static void c2_f_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_b_x_hat, const char_T *c2_identifier, real_T c2_y[8])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_x_hat), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_x_hat);
}

static void c2_g_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[8])
{
  real_T c2_dv7[8];
  int32_T c2_i52;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv7, 1, 0, 0U, 1, 0U, 1, 8);
  for (c2_i52 = 0; c2_i52 < 8; c2_i52++) {
    c2_y[c2_i52] = c2_dv7[c2_i52];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_h_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_b_P, const char_T *c2_identifier, real_T c2_y[64])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_P), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_P);
}

static void c2_i_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[64])
{
  real_T c2_dv8[64];
  int32_T c2_i53;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv8, 1, 0, 0U, 1, 0U, 2, 8, 8);
  for (c2_i53 = 0; c2_i53 < 64; c2_i53++) {
    c2_y[c2_i53] = c2_dv8[c2_i53];
  }

  sf_mex_destroy(&c2_u);
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc2_kalmanInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_j_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i54;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i54, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i54;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc2_kalmanInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_k_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_kalman, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_kalman), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_kalman);
  return c2_y;
}

static uint8_T c2_l_emlrt_marshallIn(SFc2_kalmanInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_kalmanInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_kalman_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2039327878U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(618167363U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2750336043U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2192024163U);
}

mxArray *sf_c2_kalman_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("3yHfxjW4hjnhhqq6gV1XTC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(8);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(8);
      pr[1] = (double)(8);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(8);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c2_kalman(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[9],T\"x\",},{M[4],M[0],T\"P\",S'l','i','p'{{M1x2[74 75],M[0],}}},{M[4],M[0],T\"x_hat\",S'l','i','p'{{M1x2[56 61],M[0],}}},{M[8],M[0],T\"is_active_c2_kalman\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_kalman_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_kalmanInstanceStruct *chartInstance;
    chartInstance = (SFc2_kalmanInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_kalmanMachineNumber_,
          2,
          1,
          1,
          6,
          0,
          0,
          0,
          0,
          0,
          &(chartInstance->chartNumber),
          &(chartInstance->instanceNumber),
          ssGetPath(S),
          (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_kalmanMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting(_kalmanMachineNumber_,
            chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_kalmanMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"u");
          _SFD_SET_DATA_PROPS(1,1,1,0,"y");
          _SFD_SET_DATA_PROPS(2,1,1,0,"x_0");
          _SFD_SET_DATA_PROPS(3,1,1,0,"P_0");
          _SFD_SET_DATA_PROPS(4,1,1,0,"stop_angle");
          _SFD_SET_DATA_PROPS(5,2,0,1,"x");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,1,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,217);
        _SFD_CV_INIT_EML_IF(0,1,0,77,95,-1,125);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 8;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 8;
          dimVector[1]= 8;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 8;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)
            c2_c_sf_marshallIn);
        }

        {
          real_T *c2_stop_angle;
          real_T (*c2_u)[2];
          real_T (*c2_y)[2];
          real_T (*c2_x_0)[8];
          real_T (*c2_P_0)[64];
          real_T (*c2_x)[8];
          c2_x = (real_T (*)[8])ssGetOutputPortSignal(chartInstance->S, 1);
          c2_stop_angle = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
          c2_P_0 = (real_T (*)[64])ssGetInputPortSignal(chartInstance->S, 3);
          c2_x_0 = (real_T (*)[8])ssGetInputPortSignal(chartInstance->S, 2);
          c2_y = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 1);
          c2_u = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_u);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_y);
          _SFD_SET_DATA_VALUE_PTR(2U, *c2_x_0);
          _SFD_SET_DATA_VALUE_PTR(3U, *c2_P_0);
          _SFD_SET_DATA_VALUE_PTR(4U, c2_stop_angle);
          _SFD_SET_DATA_VALUE_PTR(5U, *c2_x);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_kalmanMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization()
{
  return "c7tJsgSSkeN9LN2OsoAHsC";
}

static void sf_opaque_initialize_c2_kalman(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_kalmanInstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c2_kalman((SFc2_kalmanInstanceStruct*) chartInstanceVar);
  initialize_c2_kalman((SFc2_kalmanInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_kalman(void *chartInstanceVar)
{
  enable_c2_kalman((SFc2_kalmanInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_kalman(void *chartInstanceVar)
{
  disable_c2_kalman((SFc2_kalmanInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_kalman(void *chartInstanceVar)
{
  sf_c2_kalman((SFc2_kalmanInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_kalman(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_kalman((SFc2_kalmanInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_kalman();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c2_kalman(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_kalman();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_kalman((SFc2_kalmanInstanceStruct*)chartInfo->chartInstance,
    mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_kalman(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_kalman(S);
}

static void sf_opaque_set_sim_state_c2_kalman(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c2_kalman(S, st);
}

static void sf_opaque_terminate_c2_kalman(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_kalmanInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_kalman((SFc2_kalmanInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_kalman_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_kalman((SFc2_kalmanInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_kalman(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_kalman((SFc2_kalmanInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_kalman(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_kalman_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,2,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2270131019U));
  ssSetChecksum1(S,(1731166515U));
  ssSetChecksum2(S,(1232425445U));
  ssSetChecksum3(S,(3205412448U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_kalman(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_kalman(SimStruct *S)
{
  SFc2_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc2_kalmanInstanceStruct *)malloc(sizeof
    (SFc2_kalmanInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_kalmanInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_kalman;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_kalman;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_kalman;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_kalman;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_kalman;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_kalman;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_kalman;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_kalman;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_kalman;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_kalman;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_kalman;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_kalman_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_kalman(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_kalman(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_kalman(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_kalman_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
