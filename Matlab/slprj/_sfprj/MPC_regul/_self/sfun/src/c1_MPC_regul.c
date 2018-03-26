/* Include files */

#include "MPC_regul_sfun.h"
#include "c1_MPC_regul.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "MPC_regul_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c1_debug_family_names[39] = { "ml", "m1", "m2", "mw", "m",
  "l1", "l2", "lw", "h", "lc", "g", "Ja", "Jl", "k1", "k2", "C1", "C2", "D1",
  "D2", "T1", "T2", "cth", "sth", "u1", "u2", "nargin", "nargout", "u", "ph",
  "th", "dph", "dth", "w1", "w2", "x_0", "ddph", "ddth", "dw1", "dw2" };

/* Function Declarations */
static void initialize_c1_MPC_regul(SFc1_MPC_regulInstanceStruct *chartInstance);
static void initialize_params_c1_MPC_regul(SFc1_MPC_regulInstanceStruct
  *chartInstance);
static void enable_c1_MPC_regul(SFc1_MPC_regulInstanceStruct *chartInstance);
static void disable_c1_MPC_regul(SFc1_MPC_regulInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_MPC_regul(SFc1_MPC_regulInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_MPC_regul(SFc1_MPC_regulInstanceStruct
  *chartInstance);
static void set_sim_state_c1_MPC_regul(SFc1_MPC_regulInstanceStruct
  *chartInstance, const mxArray *c1_st);
static void finalize_c1_MPC_regul(SFc1_MPC_regulInstanceStruct *chartInstance);
static void sf_gateway_c1_MPC_regul(SFc1_MPC_regulInstanceStruct *chartInstance);
static void mdl_start_c1_MPC_regul(SFc1_MPC_regulInstanceStruct *chartInstance);
static void initSimStructsc1_MPC_regul(SFc1_MPC_regulInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static real_T c1_emlrt_marshallIn(SFc1_MPC_regulInstanceStruct *chartInstance,
  const mxArray *c1_b_dw2, const char_T *c1_identifier);
static real_T c1_b_emlrt_marshallIn(SFc1_MPC_regulInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_error(SFc1_MPC_regulInstanceStruct *chartInstance);
static real_T c1_mpower(SFc1_MPC_regulInstanceStruct *chartInstance, real_T c1_a);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_c_emlrt_marshallIn(SFc1_MPC_regulInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_d_emlrt_marshallIn(SFc1_MPC_regulInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_MPC_regul, const char_T *c1_identifier);
static uint8_T c1_e_emlrt_marshallIn(SFc1_MPC_regulInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_MPC_regulInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc1_MPC_regulInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_MPC_regul(SFc1_MPC_regulInstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc1_MPC_regul(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c1_is_active_c1_MPC_regul = 0U;
}

static void initialize_params_c1_MPC_regul(SFc1_MPC_regulInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c1_MPC_regul(SFc1_MPC_regulInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c1_MPC_regul(SFc1_MPC_regulInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c1_update_debugger_state_c1_MPC_regul(SFc1_MPC_regulInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c1_MPC_regul(SFc1_MPC_regulInstanceStruct
  *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  const mxArray *c1_b_y = NULL;
  real_T c1_b_hoistedGlobal;
  const mxArray *c1_c_y = NULL;
  real_T c1_c_hoistedGlobal;
  const mxArray *c1_d_y = NULL;
  real_T c1_d_hoistedGlobal;
  const mxArray *c1_e_y = NULL;
  uint8_T c1_e_hoistedGlobal;
  const mxArray *c1_f_y = NULL;
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellmatrix(5, 1), false);
  c1_hoistedGlobal = *chartInstance->c1_ddph;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_hoistedGlobal, 0, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = *chartInstance->c1_ddth;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_c_hoistedGlobal = *chartInstance->c1_dw1;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_d_hoistedGlobal = *chartInstance->c1_dw2;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_e_hoistedGlobal = chartInstance->c1_is_active_c1_MPC_regul;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_e_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 4, c1_f_y);
  sf_mex_assign(&c1_st, c1_y, false);
  return c1_st;
}

static void set_sim_state_c1_MPC_regul(SFc1_MPC_regulInstanceStruct
  *chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_b_u;
  chartInstance->c1_doneDoubleBufferReInit = true;
  c1_b_u = sf_mex_dup(c1_st);
  *chartInstance->c1_ddph = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("ddph", c1_b_u, 0)), "ddph");
  *chartInstance->c1_ddth = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("ddth", c1_b_u, 1)), "ddth");
  *chartInstance->c1_dw1 = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("dw1", c1_b_u, 2)), "dw1");
  *chartInstance->c1_dw2 = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("dw2", c1_b_u, 3)), "dw2");
  chartInstance->c1_is_active_c1_MPC_regul = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_active_c1_MPC_regul", c1_b_u, 4)),
    "is_active_c1_MPC_regul");
  sf_mex_destroy(&c1_b_u);
  c1_update_debugger_state_c1_MPC_regul(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_MPC_regul(SFc1_MPC_regulInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c1_MPC_regul(SFc1_MPC_regulInstanceStruct *chartInstance)
{
  int32_T c1_i0;
  int32_T c1_i1;
  real_T c1_hoistedGlobal;
  real_T c1_b_hoistedGlobal;
  real_T c1_c_hoistedGlobal;
  real_T c1_d_hoistedGlobal;
  real_T c1_e_hoistedGlobal;
  real_T c1_f_hoistedGlobal;
  int32_T c1_i2;
  real_T c1_b_ph;
  real_T c1_b_u[2];
  real_T c1_b_th;
  real_T c1_b_dph;
  real_T c1_b_dth;
  real_T c1_b_w1;
  real_T c1_b_w2;
  int32_T c1_i3;
  uint32_T c1_debug_family_var_map[39];
  real_T c1_b_x_0[6];
  real_T c1_ml;
  real_T c1_m1;
  real_T c1_m2;
  real_T c1_mw;
  real_T c1_m;
  real_T c1_l1;
  real_T c1_l2;
  real_T c1_lw;
  real_T c1_h;
  real_T c1_lc;
  real_T c1_g;
  real_T c1_Ja;
  real_T c1_Jl;
  real_T c1_k1;
  real_T c1_k2;
  real_T c1_C1;
  real_T c1_C2;
  real_T c1_D1;
  real_T c1_D2;
  real_T c1_T1;
  real_T c1_T2;
  real_T c1_cth;
  real_T c1_sth;
  real_T c1_u1;
  real_T c1_u2;
  real_T c1_nargin = 8.0;
  real_T c1_nargout = 4.0;
  real_T c1_b_ddph;
  real_T c1_b_ddth;
  real_T c1_b_dw1;
  real_T c1_b_dw2;
  real_T c1_x;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_d_x;
  real_T c1_e_x;
  real_T c1_f_x;
  real_T c1_g_x;
  real_T c1_h_x;
  real_T c1_i_x;
  real_T c1_y;
  real_T c1_j_x;
  real_T c1_k_x;
  real_T c1_l_x;
  real_T c1_b_y;
  real_T c1_A;
  real_T c1_B;
  real_T c1_m_x;
  real_T c1_c_y;
  real_T c1_n_x;
  real_T c1_d_y;
  real_T c1_o_x;
  real_T c1_p_x;
  real_T c1_q_x;
  real_T c1_e_y;
  real_T c1_r_x;
  real_T c1_s_x;
  real_T c1_t_x;
  real_T c1_f_y;
  real_T c1_b_B;
  real_T c1_u_x;
  real_T c1_v_x;
  real_T c1_b_A;
  real_T c1_w_x;
  real_T c1_x_x;
  real_T c1_g_y;
  real_T c1_c_A;
  real_T c1_y_x;
  real_T c1_ab_x;
  real_T c1_h_y;
  real_T c1_d_A;
  real_T c1_bb_x;
  real_T c1_cb_x;
  real_T c1_i_y;
  real_T c1_e_A;
  real_T c1_db_x;
  real_T c1_eb_x;
  real_T c1_j_y;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i0 = 0; c1_i0 < 6; c1_i0++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_x_0)[c1_i0], 7U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_w2, 6U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_w1, 5U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_dth, 4U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_dph, 3U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_th, 2U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_ph, 1U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  for (c1_i1 = 0; c1_i1 < 2; c1_i1++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_u)[c1_i1], 0U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_hoistedGlobal = *chartInstance->c1_ph;
  c1_b_hoistedGlobal = *chartInstance->c1_th;
  c1_c_hoistedGlobal = *chartInstance->c1_dph;
  c1_d_hoistedGlobal = *chartInstance->c1_dth;
  c1_e_hoistedGlobal = *chartInstance->c1_w1;
  c1_f_hoistedGlobal = *chartInstance->c1_w2;
  for (c1_i2 = 0; c1_i2 < 2; c1_i2++) {
    c1_b_u[c1_i2] = (*chartInstance->c1_u)[c1_i2];
  }

  c1_b_ph = c1_hoistedGlobal;
  c1_b_th = c1_b_hoistedGlobal;
  c1_b_dph = c1_c_hoistedGlobal;
  c1_b_dth = c1_d_hoistedGlobal;
  c1_b_w1 = c1_e_hoistedGlobal;
  c1_b_w2 = c1_f_hoistedGlobal;
  for (c1_i3 = 0; c1_i3 < 6; c1_i3++) {
    c1_b_x_0[c1_i3] = (*chartInstance->c1_x_0)[c1_i3];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 39U, 39U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_ml, 0U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_m1, 1U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_m2, 2U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_mw, 3U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_m, 4U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_l1, 5U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_l2, 6U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_lw, 7U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_h, 8U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_lc, 9U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_g, 10U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Ja, 11U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_Jl, 12U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_k1, 13U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_k2, 14U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_C1, 15U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_C2, 16U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_D1, 17U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_D2, 18U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_T1, 19U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_T2, 20U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_cth, 21U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_sth, 22U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_u1, 23U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_u2, 24U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 25U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 26U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_u, 27U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_ph, 28U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_th, 29U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_dph, 30U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_dth, 31U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_w1, 32U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b_w2, 33U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_x_0, 34U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_ddph, 35U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_ddth, 36U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_dw1, 37U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_dw2, 38U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 12);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
  c1_ml = 0.28;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 17);
  c1_m1 = 0.3792;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 18);
  c1_m2 = 0.1739;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 19);
  c1_mw = 0.158;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 20);
  c1_m = 0.9911;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 23);
  c1_l1 = 0.1995;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 24);
  c1_l2 = 0.1743;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 25);
  c1_lw = 0.09;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 26);
  c1_h = 0.0298;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 27);
  c1_lc = 0.038518444152961372;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 30);
  c1_g = 9.81;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 31);
  c1_Ja = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 32);
  c1_Jl = 0.024959958411000002;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 35);
  c1_k1 = 0.01;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 36);
  c1_k2 = 0.0139;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 37);
  c1_C1 = 2.5E-5;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 38);
  c1_C2 = 1.58E-6;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 39);
  c1_D1 = 2.9E-7;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 40);
  c1_D2 = 1.76E-7;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 41);
  c1_T1 = 1.1;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 42);
  c1_T2 = 0.33;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 56);
  c1_x = c1_b_th;
  c1_cth = c1_x;
  c1_b_x = c1_cth;
  c1_cth = c1_b_x;
  c1_c_x = c1_cth;
  c1_cth = c1_c_x;
  c1_cth = muDoubleScalarCos(c1_cth);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 57);
  c1_d_x = c1_b_th;
  c1_sth = c1_d_x;
  c1_e_x = c1_sth;
  c1_sth = c1_e_x;
  c1_f_x = c1_sth;
  c1_sth = c1_f_x;
  c1_sth = muDoubleScalarSin(c1_sth);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 58);
  c1_u1 = c1_b_u[0];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 59);
  c1_u2 = c1_b_u[1];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 62);
  c1_g_x = c1_b_w1;
  c1_h_x = c1_g_x;
  c1_i_x = c1_h_x;
  c1_y = muDoubleScalarAbs(c1_i_x);
  c1_j_x = c1_b_w2;
  c1_k_x = c1_j_x;
  c1_l_x = c1_k_x;
  c1_b_y = muDoubleScalarAbs(c1_l_x);
  c1_A = ((c1_mpower(chartInstance, c1_cth) * c1_Jl - 2.0 * c1_h * c1_cth *
           c1_sth * c1_m * c1_lc) + c1_mpower(chartInstance, 0.0298) * c1_mpower
          (chartInstance, c1_sth) * c1_m) + c1_Ja;
  c1_B = (((2.0 * c1_cth * c1_sth * c1_b_dph * c1_b_dth * c1_Jl - 2.0 * c1_h *
            (c1_mpower(chartInstance, c1_sth) - c1_mpower(chartInstance, c1_cth))
            * c1_b_dph * c1_b_dth * c1_m * c1_lc) - 2.0 * c1_mpower
           (chartInstance, 0.0298) * c1_sth * c1_cth * c1_b_dph * c1_b_dth *
           c1_m) + c1_D1 * c1_b_w1 * c1_y * c1_cth) + c1_l2 * c1_cth * c1_C2 *
    c1_b_w2 * c1_b_y;
  c1_m_x = c1_B;
  c1_c_y = c1_A;
  c1_n_x = c1_m_x;
  c1_d_y = c1_c_y;
  c1_b_ddph = c1_n_x / c1_d_y;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 65);
  c1_o_x = c1_b_w1;
  c1_p_x = c1_o_x;
  c1_q_x = c1_p_x;
  c1_e_y = muDoubleScalarAbs(c1_q_x);
  c1_r_x = c1_b_w2;
  c1_s_x = c1_r_x;
  c1_t_x = c1_s_x;
  c1_f_y = muDoubleScalarAbs(c1_t_x);
  c1_b_B = (((((-c1_cth * c1_sth * c1_mpower(chartInstance, c1_b_dph) * c1_Jl -
                c1_h * (-c1_mpower(chartInstance, c1_sth) + c1_mpower
                        (chartInstance, c1_cth)) * c1_mpower(chartInstance,
    c1_b_dph) * c1_m * c1_lc) - c1_g * c1_cth * c1_m * c1_lc) + c1_mpower
              (chartInstance, 0.0298) * c1_sth * c1_cth * c1_mpower
              (chartInstance, c1_b_dph) * c1_m) + c1_m * c1_g * c1_h * c1_sth) +
            c1_l1 * c1_C1 * c1_b_w1 * c1_e_y) + c1_D2 * c1_b_w2 * c1_f_y;
  c1_u_x = c1_b_B;
  c1_v_x = c1_u_x;
  c1_b_ddth = c1_v_x / 0.025840094855000002;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 68);
  c1_b_A = -c1_b_w1;
  c1_w_x = c1_b_A;
  c1_x_x = c1_w_x;
  c1_g_y = c1_x_x / 1.1;
  c1_c_A = c1_u1;
  c1_y_x = c1_c_A;
  c1_ab_x = c1_y_x;
  c1_h_y = c1_ab_x / 0.011000000000000001;
  c1_b_dw1 = c1_g_y + c1_h_y;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 69);
  c1_d_A = -c1_b_w2;
  c1_bb_x = c1_d_A;
  c1_cb_x = c1_bb_x;
  c1_i_y = c1_cb_x / 0.33;
  c1_e_A = c1_u2;
  c1_db_x = c1_e_A;
  c1_eb_x = c1_db_x;
  c1_j_y = c1_eb_x / 0.004587;
  c1_b_dw2 = c1_i_y + c1_j_y;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -69);
  _SFD_SYMBOL_SCOPE_POP();
  *chartInstance->c1_ddph = c1_b_ddph;
  *chartInstance->c1_ddth = c1_b_ddth;
  *chartInstance->c1_dw1 = c1_b_dw1;
  *chartInstance->c1_dw2 = c1_b_dw2;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_MPC_regulMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_ddph, 8U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_ddth, 9U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_dw1, 10U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_dw2, 11U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
}

static void mdl_start_c1_MPC_regul(SFc1_MPC_regulInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void initSimStructsc1_MPC_regul(SFc1_MPC_regulInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber)
{
  (void)(c1_machineNumber);
  (void)(c1_chartNumber);
  (void)(c1_instanceNumber);
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  real_T c1_b_u;
  const mxArray *c1_y = NULL;
  SFc1_MPC_regulInstanceStruct *chartInstance;
  chartInstance = (SFc1_MPC_regulInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_b_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_emlrt_marshallIn(SFc1_MPC_regulInstanceStruct *chartInstance,
  const mxArray *c1_b_dw2, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_dw2), &c1_thisId);
  sf_mex_destroy(&c1_b_dw2);
  return c1_y;
}

static real_T c1_b_emlrt_marshallIn(SFc1_MPC_regulInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_b_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_b_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_dw2;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_MPC_regulInstanceStruct *chartInstance;
  chartInstance = (SFc1_MPC_regulInstanceStruct *)chartInstanceVoid;
  c1_b_dw2 = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = (const char *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_dw2), &c1_thisId);
  sf_mex_destroy(&c1_b_dw2);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int32_T c1_i4;
  const mxArray *c1_y = NULL;
  real_T c1_b_u[6];
  SFc1_MPC_regulInstanceStruct *chartInstance;
  chartInstance = (SFc1_MPC_regulInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  for (c1_i4 = 0; c1_i4 < 6; c1_i4++) {
    c1_b_u[c1_i4] = (*(real_T (*)[6])c1_inData)[c1_i4];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 1, 6), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int32_T c1_i5;
  const mxArray *c1_y = NULL;
  real_T c1_b_u[2];
  SFc1_MPC_regulInstanceStruct *chartInstance;
  chartInstance = (SFc1_MPC_regulInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  for (c1_i5 = 0; c1_i5 < 2; c1_i5++) {
    c1_b_u[c1_i5] = (*(real_T (*)[2])c1_inData)[c1_i5];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

const mxArray *sf_c1_MPC_regul_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c1_nameCaptureInfo;
}

static void c1_error(SFc1_MPC_regulInstanceStruct *chartInstance)
{
  const mxArray *c1_y = NULL;
  static char_T c1_cv0[31] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'p', 'o', 'w', 'e', 'r', '_', 'd', 'o', 'm', 'a', 'i',
    'n', 'E', 'r', 'r', 'o', 'r' };

  (void)chartInstance;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_cv0, 10, 0U, 1U, 0U, 2, 1, 31),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c1_y));
}

static real_T c1_mpower(SFc1_MPC_regulInstanceStruct *chartInstance, real_T c1_a)
{
  real_T c1_c;
  real_T c1_b_a;
  real_T c1_c_a;
  real_T c1_x;
  real_T c1_d_a;
  boolean_T c1_p;
  c1_b_a = c1_a;
  c1_c_a = c1_b_a;
  c1_x = c1_c_a;
  c1_d_a = c1_x;
  c1_c = c1_d_a * c1_d_a;
  c1_p = false;
  if (c1_p) {
    c1_error(chartInstance);
  }

  return c1_c;
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int32_T c1_b_u;
  const mxArray *c1_y = NULL;
  SFc1_MPC_regulInstanceStruct *chartInstance;
  chartInstance = (SFc1_MPC_regulInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_b_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_b_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static int32_T c1_c_emlrt_marshallIn(SFc1_MPC_regulInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i6;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_b_u), &c1_i6, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i6;
  sf_mex_destroy(&c1_b_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_MPC_regulInstanceStruct *chartInstance;
  chartInstance = (SFc1_MPC_regulInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = (const char *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_d_emlrt_marshallIn(SFc1_MPC_regulInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_MPC_regul, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_MPC_regul), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_MPC_regul);
  return c1_y;
}

static uint8_T c1_e_emlrt_marshallIn(SFc1_MPC_regulInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_b_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_b_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_MPC_regulInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc1_MPC_regulInstanceStruct *chartInstance)
{
  chartInstance->c1_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c1_u = (real_T (*)[2])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c1_ddph = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_ph = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    1);
  chartInstance->c1_th = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    2);
  chartInstance->c1_dph = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c1_dth = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c1_w1 = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    5);
  chartInstance->c1_w2 = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    6);
  chartInstance->c1_ddth = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c1_dw1 = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c1_dw2 = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c1_x_0 = (real_T (*)[6])ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c1_MPC_regul_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4052683805U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1209421129U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1333809097U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1482350805U);
}

mxArray* sf_c1_MPC_regul_get_post_codegen_info(void);
mxArray *sf_c1_MPC_regul_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("eNBoblYtp80rNHzY8v08xG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,8,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c1_MPC_regul_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_MPC_regul_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_MPC_regul_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("pre");
  mxArray *fallbackReason = mxCreateString("hasBreakpoints");
  mxArray *hiddenFallbackType = mxCreateString("none");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c1_MPC_regul_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c1_MPC_regul_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c1_MPC_regul(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[5],T\"ddph\",},{M[1],M[12],T\"ddth\",},{M[1],M[13],T\"dw1\",},{M[1],M[14],T\"dw2\",},{M[8],M[0],T\"is_active_c1_MPC_regul\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_MPC_regul_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_MPC_regulInstanceStruct *chartInstance = (SFc1_MPC_regulInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _MPC_regulMachineNumber_,
           1,
           1,
           1,
           0,
           12,
           0,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_MPC_regulMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_MPC_regulMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _MPC_regulMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"u");
          _SFD_SET_DATA_PROPS(1,1,1,0,"ph");
          _SFD_SET_DATA_PROPS(2,1,1,0,"th");
          _SFD_SET_DATA_PROPS(3,1,1,0,"dph");
          _SFD_SET_DATA_PROPS(4,1,1,0,"dth");
          _SFD_SET_DATA_PROPS(5,1,1,0,"w1");
          _SFD_SET_DATA_PROPS(6,1,1,0,"w2");
          _SFD_SET_DATA_PROPS(7,1,1,0,"x_0");
          _SFD_SET_DATA_PROPS(8,2,0,1,"ddph");
          _SFD_SET_DATA_PROPS(9,2,0,1,"ddth");
          _SFD_SET_DATA_PROPS(10,2,0,1,"dw1");
          _SFD_SET_DATA_PROPS(11,2,0,1,"dw2");
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
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2006);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 6U;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _MPC_regulMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_MPC_regulInstanceStruct *chartInstance = (SFc1_MPC_regulInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)chartInstance->c1_u);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)chartInstance->c1_ddph);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c1_ph);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c1_th);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)chartInstance->c1_dph);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)chartInstance->c1_dth);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c1_w1);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c1_w2);
        _SFD_SET_DATA_VALUE_PTR(9U, (void *)chartInstance->c1_ddth);
        _SFD_SET_DATA_VALUE_PTR(10U, (void *)chartInstance->c1_dw1);
        _SFD_SET_DATA_VALUE_PTR(11U, (void *)chartInstance->c1_dw2);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)chartInstance->c1_x_0);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sk6zBgy8DJ9Xh7BCpJoqEeC";
}

static void sf_opaque_initialize_c1_MPC_regul(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_MPC_regulInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c1_MPC_regul((SFc1_MPC_regulInstanceStruct*)
    chartInstanceVar);
  initialize_c1_MPC_regul((SFc1_MPC_regulInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_MPC_regul(void *chartInstanceVar)
{
  enable_c1_MPC_regul((SFc1_MPC_regulInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_MPC_regul(void *chartInstanceVar)
{
  disable_c1_MPC_regul((SFc1_MPC_regulInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_MPC_regul(void *chartInstanceVar)
{
  sf_gateway_c1_MPC_regul((SFc1_MPC_regulInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c1_MPC_regul(SimStruct* S)
{
  return get_sim_state_c1_MPC_regul((SFc1_MPC_regulInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c1_MPC_regul(SimStruct* S, const mxArray *st)
{
  set_sim_state_c1_MPC_regul((SFc1_MPC_regulInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c1_MPC_regul(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_MPC_regulInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_MPC_regul_optimization_info();
    }

    finalize_c1_MPC_regul((SFc1_MPC_regulInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_MPC_regul((SFc1_MPC_regulInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_MPC_regul(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_MPC_regul((SFc1_MPC_regulInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c1_MPC_regul(SimStruct *S)
{
  /* Set overwritable ports for inplace optimization */
  ssSetStatesModifiedOnlyInUpdate(S, 1);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_MPC_regul_optimization_info(sim_mode_is_rtw_gen(S),
      sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,1,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 1);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,8);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 8; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2024997447U));
  ssSetChecksum1(S,(2139391104U));
  ssSetChecksum2(S,(1161207210U));
  ssSetChecksum3(S,(3767912800U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_MPC_regul(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_MPC_regul(SimStruct *S)
{
  SFc1_MPC_regulInstanceStruct *chartInstance;
  chartInstance = (SFc1_MPC_regulInstanceStruct *)utMalloc(sizeof
    (SFc1_MPC_regulInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc1_MPC_regulInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_MPC_regul;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_MPC_regul;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_MPC_regul;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_MPC_regul;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_MPC_regul;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_MPC_regul;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_MPC_regul;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_MPC_regul;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_MPC_regul;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_MPC_regul;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_MPC_regul;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c1_MPC_regul(chartInstance);
}

void c1_MPC_regul_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_MPC_regul(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_MPC_regul(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_MPC_regul(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_MPC_regul_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
