/* Produced by CVXGEN, 2018-04-11 10:20:22 -0400.  */
/* CVXGEN is Copyright (C) 2006-2017 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2017 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: testsolver.c. */
/* Description: Basic test harness for solver.c. */
#include "solver.h"
Vars vars;
Params params;
Workspace work;
Settings settings;
#define NUMTESTS 0
double* mpc(double *x_0, double *r, double *Q, double *R, double *A, double *B, double *u_min, double *u_max, double phi_min, double phi_max, double theta_min, double theta_max) {
	int i;	
	set_defaults();
	setup_indexing();
	for (i = 0; i < 8; i++){
		params.x_0[i] = x_0[i];	
	}
	for (i = 0; i < 8; i++){
		params.r[i] = r[i];	
	}
	for (i = 0; i < 64; i++){
		params.Q[i] = Q[i];	
	}
	for (i = 0; i < 4; i++){
		params.R[i] = R[i];	
	}
	for (i = 0; i < 64; i++){
		params.A[i] = A[i];	
	}
	for (i = 0; i < 16; i++){
		params.B[i] = B[i];	
	}
	params.u_min[0] = u_min[0];
	params.u_min[1] = u_min[1];
	params.u_max[0] = u_max[0];
	params.u_max[1] = u_max[1];
	params.phi_min[0] = phi_min;
	params.phi_max[0] = phi_max;
	params.theta_min[0] = theta_min;
	params.theta_max[0] = theta_max;
	
	settings.verbose = 0;
	solve();
	return vars.u_0;
}

int main(int argc, char **argv) {
  return 0;
}
void load_default_data(void) {
  params.x_0[0] = 0.20319161029830202;
  params.x_0[1] = 0.8325912904724193;
  params.x_0[2] = -0.8363810443482227;
  params.x_0[3] = 0.04331042079065206;
  params.x_0[4] = 1.5717878173906188;
  params.x_0[5] = 1.5851723557337523;
  params.x_0[6] = -1.497658758144655;
  params.x_0[7] = -1.171028487447253;
  params.r[0] = -1.7941311867966805;
  params.r[1] = -0.23676062539745413;
  params.r[2] = -1.8804951564857322;
  params.r[3] = -0.17266710242115568;
  params.r[4] = 0.596576190459043;
  params.r[5] = -0.8860508694080989;
  params.r[6] = 0.7050196079205251;
  params.r[7] = 0.3634512696654033;
  /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.Q[0] = 1.0239818823771654;
  params.Q[8] = 0;
  params.Q[16] = 0;
  params.Q[24] = 0;
  params.Q[32] = 0;
  params.Q[40] = 0;
  params.Q[48] = 0;
  params.Q[56] = 0;
  params.Q[1] = 0;
  params.Q[9] = 1.5588540879908819;
  params.Q[17] = 0;
  params.Q[25] = 0;
  params.Q[33] = 0;
  params.Q[41] = 0;
  params.Q[49] = 0;
  params.Q[57] = 0;
  params.Q[2] = 0;
  params.Q[10] = 0;
  params.Q[18] = 1.2592524469074653;
  params.Q[26] = 0;
  params.Q[34] = 0;
  params.Q[42] = 0;
  params.Q[50] = 0;
  params.Q[58] = 0;
  params.Q[3] = 0;
  params.Q[11] = 0;
  params.Q[19] = 0;
  params.Q[27] = 1.4151011970100695;
  params.Q[35] = 0;
  params.Q[43] = 0;
  params.Q[51] = 0;
  params.Q[59] = 0;
  params.Q[4] = 0;
  params.Q[12] = 0;
  params.Q[20] = 0;
  params.Q[28] = 0;
  params.Q[36] = 1.2835250817713186;
  params.Q[44] = 0;
  params.Q[52] = 0;
  params.Q[60] = 0;
  params.Q[5] = 0;
  params.Q[13] = 0;
  params.Q[21] = 0;
  params.Q[29] = 0;
  params.Q[37] = 0;
  params.Q[45] = 1.6931379183129964;
  params.Q[53] = 0;
  params.Q[61] = 0;
  params.Q[6] = 0;
  params.Q[14] = 0;
  params.Q[22] = 0;
  params.Q[30] = 0;
  params.Q[38] = 0;
  params.Q[46] = 0;
  params.Q[54] = 1.4404537176707395;
  params.Q[62] = 0;
  params.Q[7] = 0;
  params.Q[15] = 0;
  params.Q[23] = 0;
  params.Q[31] = 0;
  params.Q[39] = 0;
  params.Q[47] = 0;
  params.Q[55] = 0;
  params.Q[63] = 1.1568677384749633;
  /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.R[0] = 1.5446490180318446;
  params.R[2] = 0;
  params.R[1] = 0;
  params.R[3] = 1.780314764511367;
  params.A[0] = -0.774545870495281;
  params.A[1] = -1.1121684642712744;
  params.A[2] = -0.44811496977740495;
  params.A[3] = 1.7455345994417217;
  params.A[4] = 1.9039816898917352;
  params.A[5] = 0.6895347036512547;
  params.A[6] = 1.6113364341535923;
  params.A[7] = 1.383003485172717;
  params.A[8] = -0.48802383468444344;
  params.A[9] = -1.631131964513103;
  params.A[10] = 0.6136436100941447;
  params.A[11] = 0.2313630495538037;
  params.A[12] = -0.5537409477496875;
  params.A[13] = -1.0997819806406723;
  params.A[14] = -0.3739203344950055;
  params.A[15] = -0.12423900520332376;
  params.A[16] = -0.923057686995755;
  params.A[17] = -0.8328289030982696;
  params.A[18] = -0.16925440270808823;
  params.A[19] = 1.442135651787706;
  params.A[20] = 0.34501161787128565;
  params.A[21] = -0.8660485502711608;
  params.A[22] = -0.8880899735055947;
  params.A[23] = -0.1815116979122129;
  params.A[24] = -1.17835862158005;
  params.A[25] = -1.1944851558277074;
  params.A[26] = 0.05614023926976763;
  params.A[27] = -1.6510825248767813;
  params.A[28] = -0.06565787059365391;
  params.A[29] = -0.5512951504486665;
  params.A[30] = 0.8307464872626844;
  params.A[31] = 0.9869848924080182;
  params.A[32] = 0.7643716874230573;
  params.A[33] = 0.7567216550196565;
  params.A[34] = -0.5055995034042868;
  params.A[35] = 0.6725392189410702;
  params.A[36] = -0.6406053441727284;
  params.A[37] = 0.29117547947550015;
  params.A[38] = -0.6967713677405021;
  params.A[39] = -0.21941980294587182;
  params.A[40] = -1.753884276680243;
  params.A[41] = -1.0292983112626475;
  params.A[42] = 1.8864104246942706;
  params.A[43] = -1.077663182579704;
  params.A[44] = 0.7659100437893209;
  params.A[45] = 0.6019074328549583;
  params.A[46] = 0.8957565577499285;
  params.A[47] = -0.09964555746227477;
  params.A[48] = 0.38665509840745127;
  params.A[49] = -1.7321223042686946;
  params.A[50] = -1.7097514487110663;
  params.A[51] = -1.2040958948116867;
  params.A[52] = -1.3925560119658358;
  params.A[53] = -1.5995826216742213;
  params.A[54] = -1.4828245415645833;
  params.A[55] = 0.21311092723061398;
  params.A[56] = -1.248740700304487;
  params.A[57] = 1.808404972124833;
  params.A[58] = 0.7264471152297065;
  params.A[59] = 0.16407869343908477;
  params.A[60] = 0.8287224032315907;
  params.A[61] = -0.9444533161899464;
  params.A[62] = 1.7069027370149112;
  params.A[63] = 1.3567722311998827;
  params.B[0] = 0.9052779937121489;
  params.B[1] = -0.07904017565835986;
  params.B[2] = 1.3684127435065871;
  params.B[3] = 0.979009293697437;
  params.B[4] = 0.6413036255984501;
  params.B[5] = 1.6559010680237511;
  params.B[6] = 0.5346622551502991;
  params.B[7] = -0.5362376605895625;
  params.B[8] = 0.2113782926017822;
  params.B[9] = -1.2144776931994525;
  params.B[10] = -1.2317108144255875;
  params.B[11] = 0.9026784957312834;
  params.B[12] = 1.1397468137245244;
  params.B[13] = 1.8883934547350631;
  params.B[14] = 1.4038856681660068;
  params.B[15] = 0.17437730638329096;
  params.u_min[0] = -1.6408365219077408;
  params.u_min[1] = -0.04450702153554875;
  params.u_max[0] = 1.8558726951242512;
  params.u_max[1] = 1.5752363990069527;
  params.phi_min[0] = -0.05962309578364744;
  params.phi_max[0] = -0.1788825540764547;
  params.theta_min[0] = -1.1280569263625857;
  params.theta_max[0] = -1.2911464767927057;
}
