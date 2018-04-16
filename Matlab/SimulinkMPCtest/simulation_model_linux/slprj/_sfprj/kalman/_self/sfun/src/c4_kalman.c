/* Include files */

#include "blascompat32.h"
#include "kalman_sfun.h"
#include "c4_kalman.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "kalman_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c4_debug_family_names[38] = { "ml", "m1", "m2", "mw", "m",
  "l1", "l2", "lw", "h", "lc", "g", "Ja", "Jl", "k1", "k2", "C1", "C2", "D1",
  "D2", "T1", "T2", "cth", "sth", "u1", "u2", "nargin", "nargout", "u", "ph",
  "th", "dph", "dth", "w1", "w2", "ddph", "ddth", "dw1", "dw2" };

/* Function Declarations */
static void initialize_c4_kalman(SFc4_kalmanInstanceStruct *chartInstance);
static void initialize_params_c4_kalman(SFc4_kalmanInstanceStruct *chartInstance);
static void enable_c4_kalman(SFc4_kalmanInstanceStruct *chartInstance);
static void disable_c4_kalman(SFc4_kalmanInstanceStruct *chartInstance);
static void c4_update_debugger_state_c4_kalman(SFc4_kalmanInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c4_kalman(SFc4_kalmanInstanceStruct
  *chartInstance);
static void set_sim_state_c4_kalman(SFc4_kalmanInstanceStruct *chartInstance,
  const mxArray *c4_st);
static void finalize_c4_kalman(SFc4_kalmanInstanceStruct *chartInstance);
static void sf_c4_kalman(SFc4_kalmanInstanceStruct *chartInstance);
static void c4_chartstep_c4_kalman(SFc4_kalmanInstanceStruct *chartInstance);
static void initSimStructsc4_kalman(SFc4_kalmanInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber);
static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData);
static real_T c4_emlrt_marshallIn(SFc4_kalmanInstanceStruct *chartInstance,
  const mxArray *c4_dw2, const char_T *c4_identifier);
static real_T c4_b_emlrt_marshallIn(SFc4_kalmanInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_info_helper(c4_ResolvedFunctionInfo c4_info[17]);
static void c4_eml_scalar_eg(SFc4_kalmanInstanceStruct *chartInstance);
static real_T c4_mpower(SFc4_kalmanInstanceStruct *chartInstance, real_T c4_a);
static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int32_T c4_c_emlrt_marshallIn(SFc4_kalmanInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static uint8_T c4_d_emlrt_marshallIn(SFc4_kalmanInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_kalman, const char_T *c4_identifier);
static uint8_T c4_e_emlrt_marshallIn(SFc4_kalmanInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void init_dsm_address_info(SFc4_kalmanInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c4_kalman(SFc4_kalmanInstanceStruct *chartInstance)
{
  chartInstance->c4_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c4_is_active_c4_kalman = 0U;
}

static void initialize_params_c4_kalman(SFc4_kalmanInstanceStruct *chartInstance)
{
}

static void enable_c4_kalman(SFc4_kalmanInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c4_kalman(SFc4_kalmanInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c4_update_debugger_state_c4_kalman(SFc4_kalmanInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c4_kalman(SFc4_kalmanInstanceStruct
  *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  real_T c4_hoistedGlobal;
  real_T c4_u;
  const mxArray *c4_b_y = NULL;
  real_T c4_b_hoistedGlobal;
  real_T c4_b_u;
  const mxArray *c4_c_y = NULL;
  real_T c4_c_hoistedGlobal;
  real_T c4_c_u;
  const mxArray *c4_d_y = NULL;
  real_T c4_d_hoistedGlobal;
  real_T c4_d_u;
  const mxArray *c4_e_y = NULL;
  uint8_T c4_e_hoistedGlobal;
  uint8_T c4_e_u;
  const mxArray *c4_f_y = NULL;
  real_T *c4_ddph;
  real_T *c4_ddth;
  real_T *c4_dw1;
  real_T *c4_dw2;
  c4_dw2 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c4_dw1 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c4_ddth = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c4_ddph = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c4_st = NULL;
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellarray(5), FALSE);
  c4_hoistedGlobal = *c4_ddph;
  c4_u = c4_hoistedGlobal;
  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c4_y, 0, c4_b_y);
  c4_b_hoistedGlobal = *c4_ddth;
  c4_b_u = c4_b_hoistedGlobal;
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c4_y, 1, c4_c_y);
  c4_c_hoistedGlobal = *c4_dw1;
  c4_c_u = c4_c_hoistedGlobal;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_c_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c4_y, 2, c4_d_y);
  c4_d_hoistedGlobal = *c4_dw2;
  c4_d_u = c4_d_hoistedGlobal;
  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", &c4_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c4_y, 3, c4_e_y);
  c4_e_hoistedGlobal = chartInstance->c4_is_active_c4_kalman;
  c4_e_u = c4_e_hoistedGlobal;
  c4_f_y = NULL;
  sf_mex_assign(&c4_f_y, sf_mex_create("y", &c4_e_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c4_y, 4, c4_f_y);
  sf_mex_assign(&c4_st, c4_y, FALSE);
  return c4_st;
}

static void set_sim_state_c4_kalman(SFc4_kalmanInstanceStruct *chartInstance,
  const mxArray *c4_st)
{
  const mxArray *c4_u;
  real_T *c4_ddph;
  real_T *c4_ddth;
  real_T *c4_dw1;
  real_T *c4_dw2;
  c4_dw2 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c4_dw1 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c4_ddth = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c4_ddph = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c4_doneDoubleBufferReInit = TRUE;
  c4_u = sf_mex_dup(c4_st);
  *c4_ddph = c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u,
    0)), "ddph");
  *c4_ddth = c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u,
    1)), "ddth");
  *c4_dw1 = c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 2)),
    "dw1");
  *c4_dw2 = c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 3)),
    "dw2");
  chartInstance->c4_is_active_c4_kalman = c4_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c4_u, 4)), "is_active_c4_kalman");
  sf_mex_destroy(&c4_u);
  c4_update_debugger_state_c4_kalman(chartInstance);
  sf_mex_destroy(&c4_st);
}

static void finalize_c4_kalman(SFc4_kalmanInstanceStruct *chartInstance)
{
}

static void sf_c4_kalman(SFc4_kalmanInstanceStruct *chartInstance)
{
  int32_T c4_i0;
  real_T *c4_ddph;
  real_T *c4_ph;
  real_T *c4_th;
  real_T *c4_dph;
  real_T *c4_dth;
  real_T *c4_w1;
  real_T *c4_w2;
  real_T *c4_ddth;
  real_T *c4_dw1;
  real_T *c4_dw2;
  real_T (*c4_u)[2];
  c4_dw2 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c4_dw1 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c4_ddth = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c4_w2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c4_w1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c4_dth = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c4_dph = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c4_th = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c4_ph = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c4_ddph = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c4_u = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  for (c4_i0 = 0; c4_i0 < 2; c4_i0++) {
    _SFD_DATA_RANGE_CHECK((*c4_u)[c4_i0], 0U);
  }

  _SFD_DATA_RANGE_CHECK(*c4_ddph, 1U);
  _SFD_DATA_RANGE_CHECK(*c4_ph, 2U);
  _SFD_DATA_RANGE_CHECK(*c4_th, 3U);
  _SFD_DATA_RANGE_CHECK(*c4_dph, 4U);
  _SFD_DATA_RANGE_CHECK(*c4_dth, 5U);
  _SFD_DATA_RANGE_CHECK(*c4_w1, 6U);
  _SFD_DATA_RANGE_CHECK(*c4_w2, 7U);
  _SFD_DATA_RANGE_CHECK(*c4_ddth, 8U);
  _SFD_DATA_RANGE_CHECK(*c4_dw1, 9U);
  _SFD_DATA_RANGE_CHECK(*c4_dw2, 10U);
  chartInstance->c4_sfEvent = CALL_EVENT;
  c4_chartstep_c4_kalman(chartInstance);
  sf_debug_check_for_state_inconsistency(_kalmanMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c4_chartstep_c4_kalman(SFc4_kalmanInstanceStruct *chartInstance)
{
  real_T c4_hoistedGlobal;
  real_T c4_b_hoistedGlobal;
  real_T c4_c_hoistedGlobal;
  real_T c4_d_hoistedGlobal;
  real_T c4_e_hoistedGlobal;
  real_T c4_f_hoistedGlobal;
  int32_T c4_i1;
  real_T c4_u[2];
  real_T c4_ph;
  real_T c4_th;
  real_T c4_dph;
  real_T c4_dth;
  real_T c4_w1;
  real_T c4_w2;
  uint32_T c4_debug_family_var_map[38];
  real_T c4_ml;
  real_T c4_m1;
  real_T c4_m2;
  real_T c4_mw;
  real_T c4_m;
  real_T c4_l1;
  real_T c4_l2;
  real_T c4_lw;
  real_T c4_h;
  real_T c4_lc;
  real_T c4_g;
  real_T c4_Ja;
  real_T c4_Jl;
  real_T c4_k1;
  real_T c4_k2;
  real_T c4_C1;
  real_T c4_C2;
  real_T c4_D1;
  real_T c4_D2;
  real_T c4_T1;
  real_T c4_T2;
  real_T c4_cth;
  real_T c4_sth;
  real_T c4_u1;
  real_T c4_u2;
  real_T c4_nargin = 7.0;
  real_T c4_nargout = 4.0;
  real_T c4_ddph;
  real_T c4_ddth;
  real_T c4_dw1;
  real_T c4_dw2;
  real_T c4_x;
  real_T c4_b_x;
  real_T c4_c_x;
  real_T c4_d_x;
  real_T c4_a;
  real_T c4_y;
  real_T c4_b;
  real_T c4_b_y;
  real_T c4_b_a;
  real_T c4_b_b;
  real_T c4_c_y;
  real_T c4_c_a;
  real_T c4_d_y;
  real_T c4_d_a;
  real_T c4_e_y;
  real_T c4_c_b;
  real_T c4_f_y;
  real_T c4_e_a;
  real_T c4_g_y;
  real_T c4_d_b;
  real_T c4_h_y;
  real_T c4_f_a;
  real_T c4_e_b;
  real_T c4_i_y;
  real_T c4_g_a;
  real_T c4_f_b;
  real_T c4_j_y;
  real_T c4_h_a;
  real_T c4_g_b;
  real_T c4_k_y;
  real_T c4_i_a;
  real_T c4_l_y;
  real_T c4_h_b;
  real_T c4_m_y;
  real_T c4_j_a;
  real_T c4_i_b;
  real_T c4_n_y;
  real_T c4_k_a;
  real_T c4_j_b;
  real_T c4_o_y;
  real_T c4_l_a;
  real_T c4_p_y;
  real_T c4_m_a;
  real_T c4_q_y;
  real_T c4_k_b;
  real_T c4_r_y;
  real_T c4_n_a;
  real_T c4_l_b;
  real_T c4_s_y;
  real_T c4_o_a;
  real_T c4_m_b;
  real_T c4_t_y;
  real_T c4_p_a;
  real_T c4_n_b;
  real_T c4_u_y;
  real_T c4_q_a;
  real_T c4_v_y;
  real_T c4_o_b;
  real_T c4_w_y;
  real_T c4_e_x;
  real_T c4_f_x;
  real_T c4_x_y;
  real_T c4_r_a;
  real_T c4_p_b;
  real_T c4_y_y;
  real_T c4_s_a;
  real_T c4_q_b;
  real_T c4_ab_y;
  real_T c4_r_b;
  real_T c4_bb_y;
  real_T c4_t_a;
  real_T c4_cb_y;
  real_T c4_u_a;
  real_T c4_s_b;
  real_T c4_db_y;
  real_T c4_g_x;
  real_T c4_h_x;
  real_T c4_eb_y;
  real_T c4_v_a;
  real_T c4_t_b;
  real_T c4_fb_y;
  real_T c4_A;
  real_T c4_B;
  real_T c4_i_x;
  real_T c4_gb_y;
  real_T c4_j_x;
  real_T c4_hb_y;
  real_T c4_w_a;
  real_T c4_u_b;
  real_T c4_ib_y;
  real_T c4_x_a;
  real_T c4_v_b;
  real_T c4_jb_y;
  real_T c4_y_a;
  real_T c4_kb_y;
  real_T c4_w_b;
  real_T c4_lb_y;
  real_T c4_ab_a;
  real_T c4_x_b;
  real_T c4_mb_y;
  real_T c4_bb_a;
  real_T c4_nb_y;
  real_T c4_cb_a;
  real_T c4_ob_y;
  real_T c4_y_b;
  real_T c4_pb_y;
  real_T c4_db_a;
  real_T c4_qb_y;
  real_T c4_eb_a;
  real_T c4_rb_y;
  real_T c4_ab_b;
  real_T c4_sb_y;
  real_T c4_fb_a;
  real_T c4_bb_b;
  real_T c4_tb_y;
  real_T c4_gb_a;
  real_T c4_cb_b;
  real_T c4_ub_y;
  real_T c4_hb_a;
  real_T c4_vb_y;
  real_T c4_db_b;
  real_T c4_wb_y;
  real_T c4_eb_b;
  real_T c4_xb_y;
  real_T c4_k_x;
  real_T c4_l_x;
  real_T c4_yb_y;
  real_T c4_ib_a;
  real_T c4_fb_b;
  real_T c4_ac_y;
  real_T c4_gb_b;
  real_T c4_bc_y;
  real_T c4_m_x;
  real_T c4_n_x;
  real_T c4_cc_y;
  real_T c4_jb_a;
  real_T c4_hb_b;
  real_T c4_dc_y;
  real_T c4_b_B;
  real_T c4_o_x;
  real_T c4_p_x;
  real_T c4_b_A;
  real_T c4_q_x;
  real_T c4_r_x;
  real_T c4_ec_y;
  real_T c4_c_A;
  real_T c4_s_x;
  real_T c4_t_x;
  real_T c4_fc_y;
  real_T c4_d_A;
  real_T c4_u_x;
  real_T c4_v_x;
  real_T c4_gc_y;
  real_T c4_e_A;
  real_T c4_w_x;
  real_T c4_x_x;
  real_T c4_hc_y;
  real_T *c4_b_dw2;
  real_T *c4_b_dw1;
  real_T *c4_b_ddth;
  real_T *c4_b_ddph;
  real_T *c4_b_w2;
  real_T *c4_b_w1;
  real_T *c4_b_dth;
  real_T *c4_b_dph;
  real_T *c4_b_th;
  real_T *c4_b_ph;
  real_T (*c4_b_u)[2];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  c4_b_dw2 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c4_b_dw1 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c4_b_ddth = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c4_b_w2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c4_b_w1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c4_b_dth = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c4_b_dph = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c4_b_th = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c4_b_ph = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c4_b_ddph = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c4_b_u = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  c4_hoistedGlobal = *c4_b_ph;
  c4_b_hoistedGlobal = *c4_b_th;
  c4_c_hoistedGlobal = *c4_b_dph;
  c4_d_hoistedGlobal = *c4_b_dth;
  c4_e_hoistedGlobal = *c4_b_w1;
  c4_f_hoistedGlobal = *c4_b_w2;
  for (c4_i1 = 0; c4_i1 < 2; c4_i1++) {
    c4_u[c4_i1] = (*c4_b_u)[c4_i1];
  }

  c4_ph = c4_hoistedGlobal;
  c4_th = c4_b_hoistedGlobal;
  c4_dph = c4_c_hoistedGlobal;
  c4_dth = c4_d_hoistedGlobal;
  c4_w1 = c4_e_hoistedGlobal;
  c4_w2 = c4_f_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 38U, 38U, c4_debug_family_names,
    c4_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c4_ml, 0U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_m1, 1U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_m2, 2U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_mw, 3U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_m, 4U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_l1, 5U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_l2, 6U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_lw, 7U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_h, 8U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_lc, 9U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_g, 10U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c4_Ja, 11U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c4_Jl, 12U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_k1, 13U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_k2, 14U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_C1, 15U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_C2, 16U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_D1, 17U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_D2, 18U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_T1, 19U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_T2, 20U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c4_cth, 21U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_sth, 22U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_u1, 23U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_u2, 24U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_nargin, 25U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_nargout, 26U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c4_u, 27U, c4_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_ph, 28U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_th, 29U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_dph, 30U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_dth, 31U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_w1, 32U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_w2, 33U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c4_ddph, 34U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_ddth, 35U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_dw1, 36U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_dw2, 37U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 12);
  c4_ml = 0.28;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 13);
  c4_m1 = 0.3792;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 14);
  c4_m2 = 0.1739;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 15);
  c4_mw = 0.158;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 16);
  c4_m = 0.9911;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 19);
  c4_l1 = 0.1995;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 20);
  c4_l2 = 0.1743;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 21);
  c4_lw = 0.09;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 22);
  c4_h = 0.0298;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 23);
  c4_lc = 0.038518444152961372;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 26);
  c4_g = 9.81;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 27);
  c4_Ja = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 28);
  c4_Jl = 0.024959958411000002;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 31);
  c4_k1 = 0.01;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 32);
  c4_k2 = 0.0139;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 33);
  c4_C1 = 2.5E-5;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 34);
  c4_C2 = 1.58E-6;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 35);
  c4_D1 = 2.9E-7;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 36);
  c4_D2 = 1.76E-7;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 37);
  c4_T1 = 1.1;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 38);
  c4_T2 = 0.33;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 42);
  c4_x = c4_th;
  c4_cth = c4_x;
  c4_b_x = c4_cth;
  c4_cth = c4_b_x;
  c4_cth = muDoubleScalarCos(c4_cth);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 43);
  c4_c_x = c4_th;
  c4_sth = c4_c_x;
  c4_d_x = c4_sth;
  c4_sth = c4_d_x;
  c4_sth = muDoubleScalarSin(c4_sth);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 44);
  c4_u1 = c4_u[0];
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 45);
  c4_u2 = c4_u[1];
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 51);
  c4_a = c4_mpower(chartInstance, c4_cth);
  c4_y = c4_a * 0.024959958411000002;
  c4_b = c4_cth;
  c4_b_y = 0.0596 * c4_b;
  c4_b_a = c4_b_y;
  c4_b_b = c4_sth;
  c4_c_y = c4_b_a * c4_b_b;
  c4_c_a = c4_c_y;
  c4_d_y = c4_c_a * 0.9911;
  c4_d_a = c4_d_y;
  c4_e_y = c4_d_a * 0.038518444152961372;
  c4_c_b = c4_mpower(chartInstance, c4_sth);
  c4_f_y = 0.00088804 * c4_c_b;
  c4_e_a = c4_f_y;
  c4_g_y = c4_e_a * 0.9911;
  c4_d_b = c4_cth;
  c4_h_y = 2.0 * c4_d_b;
  c4_f_a = c4_h_y;
  c4_e_b = c4_sth;
  c4_i_y = c4_f_a * c4_e_b;
  c4_g_a = c4_i_y;
  c4_f_b = c4_dph;
  c4_j_y = c4_g_a * c4_f_b;
  c4_h_a = c4_j_y;
  c4_g_b = c4_dth;
  c4_k_y = c4_h_a * c4_g_b;
  c4_i_a = c4_k_y;
  c4_l_y = c4_i_a * 0.024959958411000002;
  c4_h_b = c4_mpower(chartInstance, c4_sth) - c4_mpower(chartInstance, c4_cth);
  c4_m_y = 0.0596 * c4_h_b;
  c4_j_a = c4_m_y;
  c4_i_b = c4_dph;
  c4_n_y = c4_j_a * c4_i_b;
  c4_k_a = c4_n_y;
  c4_j_b = c4_dth;
  c4_o_y = c4_k_a * c4_j_b;
  c4_l_a = c4_o_y;
  c4_p_y = c4_l_a * 0.9911;
  c4_m_a = c4_p_y;
  c4_q_y = c4_m_a * 0.038518444152961372;
  c4_k_b = c4_sth;
  c4_r_y = 0.00177608 * c4_k_b;
  c4_n_a = c4_r_y;
  c4_l_b = c4_cth;
  c4_s_y = c4_n_a * c4_l_b;
  c4_o_a = c4_s_y;
  c4_m_b = c4_dph;
  c4_t_y = c4_o_a * c4_m_b;
  c4_p_a = c4_t_y;
  c4_n_b = c4_dth;
  c4_u_y = c4_p_a * c4_n_b;
  c4_q_a = c4_u_y;
  c4_v_y = c4_q_a * 0.9911;
  c4_o_b = c4_w1;
  c4_w_y = 2.9E-7 * c4_o_b;
  c4_e_x = c4_w1;
  c4_f_x = c4_e_x;
  c4_x_y = muDoubleScalarAbs(c4_f_x);
  c4_r_a = c4_w_y;
  c4_p_b = c4_x_y;
  c4_y_y = c4_r_a * c4_p_b;
  c4_s_a = c4_y_y;
  c4_q_b = c4_cth;
  c4_ab_y = c4_s_a * c4_q_b;
  c4_r_b = c4_cth;
  c4_bb_y = 0.1743 * c4_r_b;
  c4_t_a = c4_bb_y;
  c4_cb_y = c4_t_a * 1.58E-6;
  c4_u_a = c4_cb_y;
  c4_s_b = c4_w2;
  c4_db_y = c4_u_a * c4_s_b;
  c4_g_x = c4_w2;
  c4_h_x = c4_g_x;
  c4_eb_y = muDoubleScalarAbs(c4_h_x);
  c4_v_a = c4_db_y;
  c4_t_b = c4_eb_y;
  c4_fb_y = c4_v_a * c4_t_b;
  c4_A = ((c4_y - c4_e_y) + c4_g_y) + c4_Ja;
  c4_B = (((c4_l_y - c4_q_y) - c4_v_y) + c4_ab_y) + c4_fb_y;
  c4_i_x = c4_B;
  c4_gb_y = c4_A;
  c4_j_x = c4_i_x;
  c4_hb_y = c4_gb_y;
  c4_ddph = c4_j_x / c4_hb_y;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 54);
  c4_w_a = -c4_cth;
  c4_u_b = c4_sth;
  c4_ib_y = c4_w_a * c4_u_b;
  c4_x_a = c4_ib_y;
  c4_v_b = c4_mpower(chartInstance, c4_dph);
  c4_jb_y = c4_x_a * c4_v_b;
  c4_y_a = c4_jb_y;
  c4_kb_y = c4_y_a * 0.024959958411000002;
  c4_w_b = -c4_mpower(chartInstance, c4_sth) + c4_mpower(chartInstance, c4_cth);
  c4_lb_y = 0.0298 * c4_w_b;
  c4_ab_a = c4_lb_y;
  c4_x_b = c4_mpower(chartInstance, c4_dph);
  c4_mb_y = c4_ab_a * c4_x_b;
  c4_bb_a = c4_mb_y;
  c4_nb_y = c4_bb_a * 0.9911;
  c4_cb_a = c4_nb_y;
  c4_ob_y = c4_cb_a * 0.038518444152961372;
  c4_y_b = c4_cth;
  c4_pb_y = 9.81 * c4_y_b;
  c4_db_a = c4_pb_y;
  c4_qb_y = c4_db_a * 0.9911;
  c4_eb_a = c4_qb_y;
  c4_rb_y = c4_eb_a * 0.038518444152961372;
  c4_ab_b = c4_sth;
  c4_sb_y = 0.00088804 * c4_ab_b;
  c4_fb_a = c4_sb_y;
  c4_bb_b = c4_cth;
  c4_tb_y = c4_fb_a * c4_bb_b;
  c4_gb_a = c4_tb_y;
  c4_cb_b = c4_mpower(chartInstance, c4_dph);
  c4_ub_y = c4_gb_a * c4_cb_b;
  c4_hb_a = c4_ub_y;
  c4_vb_y = c4_hb_a * 0.9911;
  c4_db_b = c4_sth;
  c4_wb_y = 0.28973619180000004 * c4_db_b;
  c4_eb_b = c4_w1;
  c4_xb_y = 4.9875E-6 * c4_eb_b;
  c4_k_x = c4_w1;
  c4_l_x = c4_k_x;
  c4_yb_y = muDoubleScalarAbs(c4_l_x);
  c4_ib_a = c4_xb_y;
  c4_fb_b = c4_yb_y;
  c4_ac_y = c4_ib_a * c4_fb_b;
  c4_gb_b = c4_w2;
  c4_bc_y = 1.76E-7 * c4_gb_b;
  c4_m_x = c4_w2;
  c4_n_x = c4_m_x;
  c4_cc_y = muDoubleScalarAbs(c4_n_x);
  c4_jb_a = c4_bc_y;
  c4_hb_b = c4_cc_y;
  c4_dc_y = c4_jb_a * c4_hb_b;
  c4_b_B = (((((c4_kb_y - c4_ob_y) - c4_rb_y) + c4_vb_y) + c4_wb_y) + c4_ac_y) +
    c4_dc_y;
  c4_o_x = c4_b_B;
  c4_p_x = c4_o_x;
  c4_ddth = c4_p_x / 0.025840094855000002;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 57);
  c4_b_A = -c4_w1;
  c4_q_x = c4_b_A;
  c4_r_x = c4_q_x;
  c4_ec_y = c4_r_x / 1.1;
  c4_c_A = c4_u1;
  c4_s_x = c4_c_A;
  c4_t_x = c4_s_x;
  c4_fc_y = c4_t_x / 0.011000000000000001;
  c4_dw1 = c4_ec_y + c4_fc_y;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 58);
  c4_d_A = -c4_w2;
  c4_u_x = c4_d_A;
  c4_v_x = c4_u_x;
  c4_gc_y = c4_v_x / 0.33;
  c4_e_A = c4_u2;
  c4_w_x = c4_e_A;
  c4_x_x = c4_w_x;
  c4_hc_y = c4_x_x / 0.004587;
  c4_dw2 = c4_gc_y + c4_hc_y;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 60);
  guard1 = FALSE;
  guard2 = FALSE;
  if (CV_EML_COND(0, 1, 0, c4_th <= -0.78539816339744828)) {
    if (CV_EML_COND(0, 1, 1, c4_dth <= 0.0)) {
      if (CV_EML_COND(0, 1, 2, c4_ddth < 0.0)) {
        CV_EML_MCDC(0, 1, 0, TRUE);
        CV_EML_IF(0, 1, 0, TRUE);
        _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 61);
        c4_ddth = 0.0;
      } else {
        guard1 = TRUE;
      }
    } else {
      guard2 = TRUE;
    }
  } else {
    guard2 = TRUE;
  }

  if (guard2 == TRUE) {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    CV_EML_MCDC(0, 1, 0, FALSE);
    CV_EML_IF(0, 1, 0, FALSE);
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -61);
  sf_debug_symbol_scope_pop();
  *c4_b_ddph = c4_ddph;
  *c4_b_ddth = c4_ddth;
  *c4_b_dw1 = c4_dw1;
  *c4_b_dw2 = c4_dw2;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
}

static void initSimStructsc4_kalman(SFc4_kalmanInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber)
{
}

static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc4_kalmanInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static real_T c4_emlrt_marshallIn(SFc4_kalmanInstanceStruct *chartInstance,
  const mxArray *c4_dw2, const char_T *c4_identifier)
{
  real_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_dw2), &c4_thisId);
  sf_mex_destroy(&c4_dw2);
  return c4_y;
}

static real_T c4_b_emlrt_marshallIn(SFc4_kalmanInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d0;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d0, 1, 0, 0U, 0, 0U, 0);
  c4_y = c4_d0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_dw2;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc4_kalmanInstanceStruct *)chartInstanceVoid;
  c4_dw2 = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_dw2), &c4_thisId);
  sf_mex_destroy(&c4_dw2);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i2;
  real_T c4_b_inData[2];
  int32_T c4_i3;
  real_T c4_u[2];
  const mxArray *c4_y = NULL;
  SFc4_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc4_kalmanInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i2 = 0; c4_i2 < 2; c4_i2++) {
    c4_b_inData[c4_i2] = (*(real_T (*)[2])c4_inData)[c4_i2];
  }

  for (c4_i3 = 0; c4_i3 < 2; c4_i3++) {
    c4_u[c4_i3] = c4_b_inData[c4_i3];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

const mxArray *sf_c4_kalman_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo;
  c4_ResolvedFunctionInfo c4_info[17];
  const mxArray *c4_m0 = NULL;
  int32_T c4_i4;
  c4_ResolvedFunctionInfo *c4_r0;
  c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  c4_info_helper(c4_info);
  sf_mex_assign(&c4_m0, sf_mex_createstruct("nameCaptureInfo", 1, 17), FALSE);
  for (c4_i4 = 0; c4_i4 < 17; c4_i4++) {
    c4_r0 = &c4_info[c4_i4];
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->context)), "context", "nameCaptureInfo",
                    c4_i4);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c4_r0->name)), "name", "nameCaptureInfo", c4_i4);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c4_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c4_i4);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->resolved)), "resolved", "nameCaptureInfo",
                    c4_i4);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c4_i4);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c4_i4);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c4_i4);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c4_i4);
  }

  sf_mex_assign(&c4_nameCaptureInfo, c4_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c4_nameCaptureInfo);
  return c4_nameCaptureInfo;
}

static void c4_info_helper(c4_ResolvedFunctionInfo c4_info[17])
{
  c4_info[0].context = "";
  c4_info[0].name = "mtimes";
  c4_info[0].dominantType = "double";
  c4_info[0].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[0].fileTimeLo = 1289519692U;
  c4_info[0].fileTimeHi = 0U;
  c4_info[0].mFileTimeLo = 0U;
  c4_info[0].mFileTimeHi = 0U;
  c4_info[1].context = "";
  c4_info[1].name = "mrdivide";
  c4_info[1].dominantType = "double";
  c4_info[1].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c4_info[1].fileTimeLo = 1325124138U;
  c4_info[1].fileTimeHi = 0U;
  c4_info[1].mFileTimeLo = 1319729966U;
  c4_info[1].mFileTimeHi = 0U;
  c4_info[2].context =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c4_info[2].name = "rdivide";
  c4_info[2].dominantType = "double";
  c4_info[2].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/ops/rdivide.m";
  c4_info[2].fileTimeLo = 1286818844U;
  c4_info[2].fileTimeHi = 0U;
  c4_info[2].mFileTimeLo = 0U;
  c4_info[2].mFileTimeHi = 0U;
  c4_info[3].context =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/ops/rdivide.m";
  c4_info[3].name = "eml_div";
  c4_info[3].dominantType = "double";
  c4_info[3].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/eml/eml_div.m";
  c4_info[3].fileTimeLo = 1313347810U;
  c4_info[3].fileTimeHi = 0U;
  c4_info[3].mFileTimeLo = 0U;
  c4_info[3].mFileTimeHi = 0U;
  c4_info[4].context = "";
  c4_info[4].name = "mpower";
  c4_info[4].dominantType = "double";
  c4_info[4].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/ops/mpower.m";
  c4_info[4].fileTimeLo = 1286818842U;
  c4_info[4].fileTimeHi = 0U;
  c4_info[4].mFileTimeLo = 0U;
  c4_info[4].mFileTimeHi = 0U;
  c4_info[5].context =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/ops/mpower.m";
  c4_info[5].name = "power";
  c4_info[5].dominantType = "double";
  c4_info[5].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/ops/power.m";
  c4_info[5].fileTimeLo = 1307651240U;
  c4_info[5].fileTimeHi = 0U;
  c4_info[5].mFileTimeLo = 0U;
  c4_info[5].mFileTimeHi = 0U;
  c4_info[6].context =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/ops/power.m";
  c4_info[6].name = "eml_scalar_eg";
  c4_info[6].dominantType = "double";
  c4_info[6].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c4_info[6].fileTimeLo = 1286818796U;
  c4_info[6].fileTimeHi = 0U;
  c4_info[6].mFileTimeLo = 0U;
  c4_info[6].mFileTimeHi = 0U;
  c4_info[7].context =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/ops/power.m";
  c4_info[7].name = "eml_scalexp_alloc";
  c4_info[7].dominantType = "double";
  c4_info[7].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c4_info[7].fileTimeLo = 1286818796U;
  c4_info[7].fileTimeHi = 0U;
  c4_info[7].mFileTimeLo = 0U;
  c4_info[7].mFileTimeHi = 0U;
  c4_info[8].context =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/ops/power.m";
  c4_info[8].name = "eml_scalar_floor";
  c4_info[8].dominantType = "double";
  c4_info[8].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c4_info[8].fileTimeLo = 1286818726U;
  c4_info[8].fileTimeHi = 0U;
  c4_info[8].mFileTimeLo = 0U;
  c4_info[8].mFileTimeHi = 0U;
  c4_info[9].context = "";
  c4_info[9].name = "cos";
  c4_info[9].dominantType = "double";
  c4_info[9].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/elfun/cos.m";
  c4_info[9].fileTimeLo = 1286818706U;
  c4_info[9].fileTimeHi = 0U;
  c4_info[9].mFileTimeLo = 0U;
  c4_info[9].mFileTimeHi = 0U;
  c4_info[10].context =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/elfun/cos.m";
  c4_info[10].name = "eml_scalar_cos";
  c4_info[10].dominantType = "double";
  c4_info[10].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c4_info[10].fileTimeLo = 1286818722U;
  c4_info[10].fileTimeHi = 0U;
  c4_info[10].mFileTimeLo = 0U;
  c4_info[10].mFileTimeHi = 0U;
  c4_info[11].context = "";
  c4_info[11].name = "sin";
  c4_info[11].dominantType = "double";
  c4_info[11].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/elfun/sin.m";
  c4_info[11].fileTimeLo = 1286818750U;
  c4_info[11].fileTimeHi = 0U;
  c4_info[11].mFileTimeLo = 0U;
  c4_info[11].mFileTimeHi = 0U;
  c4_info[12].context =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/elfun/sin.m";
  c4_info[12].name = "eml_scalar_sin";
  c4_info[12].dominantType = "double";
  c4_info[12].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c4_info[12].fileTimeLo = 1286818736U;
  c4_info[12].fileTimeHi = 0U;
  c4_info[12].mFileTimeLo = 0U;
  c4_info[12].mFileTimeHi = 0U;
  c4_info[13].context = "";
  c4_info[13].name = "abs";
  c4_info[13].dominantType = "double";
  c4_info[13].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/elfun/abs.m";
  c4_info[13].fileTimeLo = 1286818694U;
  c4_info[13].fileTimeHi = 0U;
  c4_info[13].mFileTimeLo = 0U;
  c4_info[13].mFileTimeHi = 0U;
  c4_info[14].context =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/elfun/abs.m";
  c4_info[14].name = "eml_scalar_abs";
  c4_info[14].dominantType = "double";
  c4_info[14].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c4_info[14].fileTimeLo = 1286818712U;
  c4_info[14].fileTimeHi = 0U;
  c4_info[14].mFileTimeLo = 0U;
  c4_info[14].mFileTimeHi = 0U;
  c4_info[15].context = "";
  c4_info[15].name = "mldivide";
  c4_info[15].dominantType = "double";
  c4_info[15].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/ops/mldivide.p";
  c4_info[15].fileTimeLo = 1325124138U;
  c4_info[15].fileTimeHi = 0U;
  c4_info[15].mFileTimeLo = 1319729966U;
  c4_info[15].mFileTimeHi = 0U;
  c4_info[16].context =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/ops/mldivide.p";
  c4_info[16].name = "rdivide";
  c4_info[16].dominantType = "double";
  c4_info[16].resolved =
    "[ILXE]/opt/matlab/matlab-R2012a/toolbox/eml/lib/matlab/ops/rdivide.m";
  c4_info[16].fileTimeLo = 1286818844U;
  c4_info[16].fileTimeHi = 0U;
  c4_info[16].mFileTimeLo = 0U;
  c4_info[16].mFileTimeHi = 0U;
}

static void c4_eml_scalar_eg(SFc4_kalmanInstanceStruct *chartInstance)
{
}

static real_T c4_mpower(SFc4_kalmanInstanceStruct *chartInstance, real_T c4_a)
{
  real_T c4_b_a;
  real_T c4_ak;
  c4_b_a = c4_a;
  c4_eml_scalar_eg(chartInstance);
  c4_ak = c4_b_a;
  return muDoubleScalarPower(c4_ak, 2.0);
}

static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc4_kalmanInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(int32_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static int32_T c4_c_emlrt_marshallIn(SFc4_kalmanInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_y;
  int32_T c4_i5;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_i5, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i5;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_sfEvent;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y;
  SFc4_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc4_kalmanInstanceStruct *)chartInstanceVoid;
  c4_b_sfEvent = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_sfEvent),
    &c4_thisId);
  sf_mex_destroy(&c4_b_sfEvent);
  *(int32_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static uint8_T c4_d_emlrt_marshallIn(SFc4_kalmanInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_kalman, const char_T *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_b_is_active_c4_kalman), &c4_thisId);
  sf_mex_destroy(&c4_b_is_active_c4_kalman);
  return c4_y;
}

static uint8_T c4_e_emlrt_marshallIn(SFc4_kalmanInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u0;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u0, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void init_dsm_address_info(SFc4_kalmanInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c4_kalman_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2119387448U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1540464727U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1624560469U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(430762584U);
}

mxArray *sf_c4_kalman_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("aag7fLuop0yqEyz0IQ78CE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,7,3,dataFields);

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
      pr[0] = (double)(1);
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
      pr[0] = (double)(1);
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
      pr[0] = (double)(1);
      pr[1] = (double)(1);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));
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
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
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
      pr[0] = (double)(1);
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
      pr[0] = (double)(1);
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
      pr[0] = (double)(1);
      pr[1] = (double)(1);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c4_kalman(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[5],T\"ddph\",},{M[1],M[12],T\"ddth\",},{M[1],M[13],T\"dw1\",},{M[1],M[14],T\"dw2\",},{M[8],M[0],T\"is_active_c4_kalman\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_kalman_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_kalmanInstanceStruct *chartInstance;
    chartInstance = (SFc4_kalmanInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_kalmanMachineNumber_,
          4,
          1,
          1,
          11,
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
          _SFD_SET_DATA_PROPS(1,2,0,1,"ddph");
          _SFD_SET_DATA_PROPS(2,1,1,0,"ph");
          _SFD_SET_DATA_PROPS(3,1,1,0,"th");
          _SFD_SET_DATA_PROPS(4,1,1,0,"dph");
          _SFD_SET_DATA_PROPS(5,1,1,0,"dth");
          _SFD_SET_DATA_PROPS(6,1,1,0,"w1");
          _SFD_SET_DATA_PROPS(7,1,1,0,"w2");
          _SFD_SET_DATA_PROPS(8,2,0,1,"ddth");
          _SFD_SET_DATA_PROPS(9,2,0,1,"dw1");
          _SFD_SET_DATA_PROPS(10,2,0,1,"dw2");
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
        _SFD_CV_INIT_EML(0,1,1,1,0,0,0,0,3,1);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1617);
        _SFD_CV_INIT_EML_IF(0,1,0,1572,1601,-1,1617);

        {
          static int condStart[] = { 1575, 1586, 1594 };

          static int condEnd[] = { 1584, 1592, 1600 };

          static int pfixExpr[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,1575,1600,3,0,&(condStart[0]),&(condEnd[0]),
                                5,&(pfixExpr[0]));
        }

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
            1.0,0,0,(MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)c4_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)c4_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)c4_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)c4_sf_marshallIn);

        {
          real_T *c4_ddph;
          real_T *c4_ph;
          real_T *c4_th;
          real_T *c4_dph;
          real_T *c4_dth;
          real_T *c4_w1;
          real_T *c4_w2;
          real_T *c4_ddth;
          real_T *c4_dw1;
          real_T *c4_dw2;
          real_T (*c4_u)[2];
          c4_dw2 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c4_dw1 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c4_ddth = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c4_w2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
          c4_w1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
          c4_dth = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
          c4_dph = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c4_th = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c4_ph = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c4_ddph = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c4_u = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c4_u);
          _SFD_SET_DATA_VALUE_PTR(1U, c4_ddph);
          _SFD_SET_DATA_VALUE_PTR(2U, c4_ph);
          _SFD_SET_DATA_VALUE_PTR(3U, c4_th);
          _SFD_SET_DATA_VALUE_PTR(4U, c4_dph);
          _SFD_SET_DATA_VALUE_PTR(5U, c4_dth);
          _SFD_SET_DATA_VALUE_PTR(6U, c4_w1);
          _SFD_SET_DATA_VALUE_PTR(7U, c4_w2);
          _SFD_SET_DATA_VALUE_PTR(8U, c4_ddth);
          _SFD_SET_DATA_VALUE_PTR(9U, c4_dw1);
          _SFD_SET_DATA_VALUE_PTR(10U, c4_dw2);
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
  return "GnM3qM9CViHuGy2VbhI8Q";
}

static void sf_opaque_initialize_c4_kalman(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc4_kalmanInstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c4_kalman((SFc4_kalmanInstanceStruct*) chartInstanceVar);
  initialize_c4_kalman((SFc4_kalmanInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c4_kalman(void *chartInstanceVar)
{
  enable_c4_kalman((SFc4_kalmanInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c4_kalman(void *chartInstanceVar)
{
  disable_c4_kalman((SFc4_kalmanInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c4_kalman(void *chartInstanceVar)
{
  sf_c4_kalman((SFc4_kalmanInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c4_kalman(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c4_kalman((SFc4_kalmanInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_kalman();/* state var info */
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

extern void sf_internal_set_sim_state_c4_kalman(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_kalman();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c4_kalman((SFc4_kalmanInstanceStruct*)chartInfo->chartInstance,
    mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c4_kalman(SimStruct* S)
{
  return sf_internal_get_sim_state_c4_kalman(S);
}

static void sf_opaque_set_sim_state_c4_kalman(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c4_kalman(S, st);
}

static void sf_opaque_terminate_c4_kalman(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_kalmanInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c4_kalman((SFc4_kalmanInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_kalman_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_kalman((SFc4_kalmanInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_kalman(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c4_kalman((SFc4_kalmanInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c4_kalman(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_kalman_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,4,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,4,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,4,7);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,4,4);
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3726040320U));
  ssSetChecksum1(S,(150178392U));
  ssSetChecksum2(S,(2887434037U));
  ssSetChecksum3(S,(416175710U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c4_kalman(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_kalman(SimStruct *S)
{
  SFc4_kalmanInstanceStruct *chartInstance;
  chartInstance = (SFc4_kalmanInstanceStruct *)malloc(sizeof
    (SFc4_kalmanInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc4_kalmanInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c4_kalman;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c4_kalman;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c4_kalman;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c4_kalman;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c4_kalman;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c4_kalman;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c4_kalman;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c4_kalman;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_kalman;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_kalman;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c4_kalman;
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

void c4_kalman_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_kalman(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_kalman(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_kalman(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_kalman_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
