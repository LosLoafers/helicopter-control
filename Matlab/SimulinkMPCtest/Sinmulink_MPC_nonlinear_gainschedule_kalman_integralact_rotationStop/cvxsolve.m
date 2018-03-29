% Produced by CVXGEN, 2018-03-29 07:59:22 -0400.
% CVXGEN is Copyright (C) 2006-2017 Jacob Mattingley, jem@cvxgen.com.
% The code in this file is Copyright (C) 2006-2017 Jacob Mattingley.
% CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial
% applications without prior written permission from Jacob Mattingley.

% Filename: cvxsolve.m.
% Description: Solution file, via cvx, for use with sample.m.
function [vars, status] = cvxsolve(params, settings)
A = params.A;
B = params.B;
Q = params.Q;
R = params.R;
phi_max = params.phi_max;
phi_min = params.phi_min;
r = params.r;
theta_max = params.theta_max;
theta_min = params.theta_min;
u_max = params.u_max;
u_min = params.u_min;
x_0 = params.x_0;
cvx_begin
  % Caution: automatically generated by cvxgen. May be incorrect.
  variable x_1(8, 1);
  variable x_3(8, 1);
  variable x_5(8, 1);
  variable x_7(8, 1);
  variable x_9(8, 1);
  variable x_11(8, 1);
  variable x_13(8, 1);
  variable u_1(2, 1);
  variable u_0(2, 1);
  variable u_2(2, 1);
  variable u_3(2, 1);
  variable u_4(2, 1);
  variable u_5(2, 1);
  variable x_2(8, 1);
  variable x_4(8, 1);
  variable x_6(8, 1);
  variable u_6(2, 1);
  variable x_8(8, 1);
  variable u_7(2, 1);
  variable u_8(2, 1);
  variable x_10(8, 1);
  variable u_9(2, 1);
  variable u_10(2, 1);
  variable x_12(8, 1);
  variable u_11(2, 1);
  variable u_12(2, 1);
  variable u_13(2, 1);

  minimize(quad_form(x_1 - r, Q) + quad_form(x_3 - r, Q) + quad_form(x_5 - r, Q) + quad_form(x_7 - r, Q) + quad_form(x_9 - r, Q) + quad_form(x_11 - r, Q) + quad_form(x_13 - r, Q) + quad_form(u_1 - u_0, R) + quad_form(u_2 - u_1, R) + quad_form(u_3 - u_2, R) + quad_form(u_4 - u_3, R) + quad_form(u_5 - u_4, R));
  subject to
    x_1 == A*x_0 + B*u_0;
    x_2 == A*x_1 + B*u_1;
    x_3 == A*x_2 + B*u_2;
    x_4 == A*x_3 + B*u_3;
    x_5 == A*x_4 + B*u_4;
    x_6 == A*x_5 + B*u_5;
    x_7 == A*x_6 + B*u_6;
    x_8 == A*x_7 + B*u_7;
    x_9 == A*x_8 + B*u_8;
    x_10 == A*x_9 + B*u_9;
    x_11 == A*x_10 + B*u_10;
    x_12 == A*x_11 + B*u_11;
    x_13 == A*x_12 + B*u_12;
    u_min <= u_0;
    u_min <= u_1;
    u_min <= u_2;
    u_min <= u_3;
    u_min <= u_4;
    u_min <= u_5;
    u_0 <= u_max;
    u_1 <= u_max;
    u_2 <= u_max;
    u_3 <= u_max;
    u_4 <= u_max;
    u_5 <= u_max;
    u_6 == u_5;
    u_7 == u_6;
    u_8 == u_7;
    u_9 == u_8;
    u_10 == u_9;
    u_11 == u_10;
    u_12 == u_11;
    u_13 == u_12;
    phi_min <= x_1(1);
    phi_min <= x_2(1);
    phi_min <= x_3(1);
    phi_min <= x_4(1);
    phi_min <= x_5(1);
    phi_min <= x_6(1);
    phi_min <= x_7(1);
    phi_min <= x_8(1);
    phi_min <= x_9(1);
    phi_min <= x_10(1);
    phi_min <= x_11(1);
    phi_min <= x_12(1);
    phi_min <= x_13(1);
    x_1(1) <= phi_max;
    x_2(1) <= phi_max;
    x_3(1) <= phi_max;
    x_4(1) <= phi_max;
    x_5(1) <= phi_max;
    x_6(1) <= phi_max;
    x_7(1) <= phi_max;
    x_8(1) <= phi_max;
    x_9(1) <= phi_max;
    x_10(1) <= phi_max;
    x_11(1) <= phi_max;
    x_12(1) <= phi_max;
    x_13(1) <= phi_max;
    theta_min <= x_13(2);
    theta_min <= x_13(2);
    theta_min <= x_13(2);
    theta_min <= x_13(2);
    theta_min <= x_13(2);
    theta_min <= x_13(2);
    theta_min <= x_13(2);
    theta_min <= x_13(2);
    theta_min <= x_13(2);
    theta_min <= x_13(2);
    theta_min <= x_13(2);
    theta_min <= x_13(2);
    theta_min <= x_13(2);
    x_13(2) <= theta_max;
    x_13(2) <= theta_max;
    x_13(2) <= theta_max;
    x_13(2) <= theta_max;
    x_13(2) <= theta_max;
    x_13(2) <= theta_max;
    x_13(2) <= theta_max;
    x_13(2) <= theta_max;
    x_13(2) <= theta_max;
    x_13(2) <= theta_max;
    x_13(2) <= theta_max;
    x_13(2) <= theta_max;
    x_13(2) <= theta_max;
cvx_end
vars.u_0 = u_0;
vars.u_1 = u_1;
vars.u{1} = u_1;
vars.u_2 = u_2;
vars.u{2} = u_2;
vars.u_3 = u_3;
vars.u{3} = u_3;
vars.u_4 = u_4;
vars.u{4} = u_4;
vars.u_5 = u_5;
vars.u{5} = u_5;
vars.u_6 = u_6;
vars.u{6} = u_6;
vars.u_7 = u_7;
vars.u{7} = u_7;
vars.u_8 = u_8;
vars.u{8} = u_8;
vars.u_9 = u_9;
vars.u{9} = u_9;
vars.u_10 = u_10;
vars.u{10} = u_10;
vars.u_11 = u_11;
vars.u{11} = u_11;
vars.u_12 = u_12;
vars.u{12} = u_12;
vars.u_13 = u_13;
vars.u{13} = u_13;
vars.x_1 = x_1;
vars.x{1} = x_1;
vars.x_2 = x_2;
vars.x{2} = x_2;
vars.x_3 = x_3;
vars.x{3} = x_3;
vars.x_4 = x_4;
vars.x{4} = x_4;
vars.x_5 = x_5;
vars.x{5} = x_5;
vars.x_6 = x_6;
vars.x{6} = x_6;
vars.x_7 = x_7;
vars.x{7} = x_7;
vars.x_8 = x_8;
vars.x{8} = x_8;
vars.x_9 = x_9;
vars.x{9} = x_9;
vars.x_10 = x_10;
vars.x{10} = x_10;
vars.x_11 = x_11;
vars.x{11} = x_11;
vars.x_12 = x_12;
vars.x{12} = x_12;
vars.x_13 = x_13;
vars.x{13} = x_13;
status.cvx_status = cvx_status;
% Provide a drop-in replacement for csolve.
status.optval = cvx_optval;
status.converged = strcmp(cvx_status, 'Solved');
