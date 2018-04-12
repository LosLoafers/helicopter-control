% csolve  Solves a custom quadratic program very rapidly.
%
% [vars, status] = csolve(params, settings)
%
% solves the convex optimization problem
%
%   minimize(quad_form(x_1 - r, Q) + quad_form(x_3 - r, Q) + quad_form(x_5 - r, Q) + quad_form(x_7 - r, Q) + quad_form(x_9 - r, Q) + quad_form(x_11 - r, Q) + quad_form(x_13 - r, Q) + quad_form(u_1 - u_0, R) + quad_form(u_2 - u_1, R) + quad_form(u_3 - u_2, R) + quad_form(u_4 - u_3, R) + quad_form(u_5 - u_4, R))
%   subject to
%     x_1 == A*x_0 + B*u_0
%     x_2 == A*x_1 + B*u_1
%     x_3 == A*x_2 + B*u_2
%     x_4 == A*x_3 + B*u_3
%     x_5 == A*x_4 + B*u_4
%     x_6 == A*x_5 + B*u_5
%     x_7 == A*x_6 + B*u_6
%     x_8 == A*x_7 + B*u_7
%     x_9 == A*x_8 + B*u_8
%     x_10 == A*x_9 + B*u_9
%     x_11 == A*x_10 + B*u_10
%     x_12 == A*x_11 + B*u_11
%     x_13 == A*x_12 + B*u_12
%     u_min <= u_0
%     u_min <= u_1
%     u_min <= u_2
%     u_min <= u_3
%     u_min <= u_4
%     u_min <= u_5
%     u_0 <= u_max
%     u_1 <= u_max
%     u_2 <= u_max
%     u_3 <= u_max
%     u_4 <= u_max
%     u_5 <= u_max
%     u_6 == u_5
%     u_7 == u_6
%     u_8 == u_7
%     u_9 == u_8
%     u_10 == u_9
%     u_11 == u_10
%     u_12 == u_11
%     u_13 == u_12
%     phi_min <= x_1(1)
%     phi_min <= x_2(1)
%     phi_min <= x_3(1)
%     phi_min <= x_4(1)
%     phi_min <= x_5(1)
%     phi_min <= x_6(1)
%     phi_min <= x_7(1)
%     phi_min <= x_8(1)
%     phi_min <= x_9(1)
%     phi_min <= x_10(1)
%     phi_min <= x_11(1)
%     phi_min <= x_12(1)
%     phi_min <= x_13(1)
%     x_1(1) <= phi_max
%     x_2(1) <= phi_max
%     x_3(1) <= phi_max
%     x_4(1) <= phi_max
%     x_5(1) <= phi_max
%     x_6(1) <= phi_max
%     x_7(1) <= phi_max
%     x_8(1) <= phi_max
%     x_9(1) <= phi_max
%     x_10(1) <= phi_max
%     x_11(1) <= phi_max
%     x_12(1) <= phi_max
%     x_13(1) <= phi_max
%     theta_min <= x_13(2)
%     theta_min <= x_13(2)
%     theta_min <= x_13(2)
%     theta_min <= x_13(2)
%     theta_min <= x_13(2)
%     theta_min <= x_13(2)
%     theta_min <= x_13(2)
%     theta_min <= x_13(2)
%     theta_min <= x_13(2)
%     theta_min <= x_13(2)
%     theta_min <= x_13(2)
%     theta_min <= x_13(2)
%     theta_min <= x_13(2)
%     x_13(2) <= theta_max
%     x_13(2) <= theta_max
%     x_13(2) <= theta_max
%     x_13(2) <= theta_max
%     x_13(2) <= theta_max
%     x_13(2) <= theta_max
%     x_13(2) <= theta_max
%     x_13(2) <= theta_max
%     x_13(2) <= theta_max
%     x_13(2) <= theta_max
%     x_13(2) <= theta_max
%     x_13(2) <= theta_max
%     x_13(2) <= theta_max
%
% with variables
%      u_0   2 x 1
%      u_1   2 x 1
%      u_2   2 x 1
%      u_3   2 x 1
%      u_4   2 x 1
%      u_5   2 x 1
%      u_6   2 x 1
%      u_7   2 x 1
%      u_8   2 x 1
%      u_9   2 x 1
%     u_10   2 x 1
%     u_11   2 x 1
%     u_12   2 x 1
%     u_13   2 x 1
%      x_1   8 x 1
%      x_2   8 x 1
%      x_3   8 x 1
%      x_4   8 x 1
%      x_5   8 x 1
%      x_6   8 x 1
%      x_7   8 x 1
%      x_8   8 x 1
%      x_9   8 x 1
%     x_10   8 x 1
%     x_11   8 x 1
%     x_12   8 x 1
%     x_13   8 x 1
%
% and parameters
%        A   8 x 8
%        B   8 x 2
%        Q   8 x 8    PSD
%        R   2 x 2    PSD
%  phi_max   1 x 1
%  phi_min   1 x 1
%        r   8 x 1
% theta_max   1 x 1
% theta_min   1 x 1
%    u_max   2 x 1    positive
%    u_min   2 x 1
%      x_0   8 x 1
%
% Note:
%   - Check status.converged, which will be 1 if optimization succeeded.
%   - You don't have to specify settings if you don't want to.
%   - To hide output, use settings.verbose = 0.
%   - To change iterations, use settings.max_iters = 20.
%   - You may wish to compare with cvxsolve to check the solver is correct.
%
% Specify params.A, ..., params.x_0, then run
%   [vars, status] = csolve(params, settings)
% Produced by CVXGEN, 2018-03-29 07:59:22 -0400.
% CVXGEN is Copyright (C) 2006-2017 Jacob Mattingley, jem@cvxgen.com.
% The code in this file is Copyright (C) 2006-2017 Jacob Mattingley.
% CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial
% applications without prior written permission from Jacob Mattingley.

% Filename: csolve.m.
% Description: Help file for the Matlab solver interface.
