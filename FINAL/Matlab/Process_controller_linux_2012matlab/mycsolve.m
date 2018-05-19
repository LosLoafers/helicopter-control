function u=mycsolve(x,r)
%This function "wraps" the csolve MEX solver in a matlab function.
% This is done beacouse Simulink is afraid of cell arrays and wont accept
% csolve.mex directly.

%Globaly defined parameters is set
% the solver.
global Asystem;
global Bsystem;
global Ts_control;
global umaxglobal;
global uminglobal;
global Qglobal;
global Rglobal;
global reference;
global LinearizationPoint_x;
global LinearizationPoint_u;
global phi_max;
global phi_min;
global theta_min;
global theta_max;
[Asystem,Bsystem,LinearizationPoint_x,LinearizationPoint_u]=linearDiscreteModelGen(x(1),x(2),x(7),x(8),Ts_control);
%setup opt problem
reference=[r;0;0;0;0;0;0];
params.x_0=x-LinearizationPoint_x;
params.A=[Asystem,Bsystem;zeros(2,6),eye(2)];
params.B=[Bsystem;zeros(2,2)];
params.Q=Qglobal;
params.R=Rglobal;
params.u_max=umaxglobal-LinearizationPoint_u;
params.u_min=uminglobal-LinearizationPoint_u;
params.r=reference-LinearizationPoint_x;
params.phi_max=phi_max-LinearizationPoint_x(1);
params.phi_min=phi_min-LinearizationPoint_x(1);
params.theta_min=theta_min-LinearizationPoint_x(2);
params.theta_max=theta_max-LinearizationPoint_x(2);


% Create a new settings structure. Just some example
% copied from the cvx homepage:
settings.verbose = 0;  % disable output of solver progress.
% settings.max_iters = 10;  % reduce the maximum iteration count, from 25.
% settings.eps = 0.1;  % reduce the required objective tolerance, from 1e-6.
% settings.resid_tol = 1e-2;  % reduce the required residual tolerances, from 1e-4.

% solve

[vars, ~] = csolve(params, settings);
u=vars.u_0+LinearizationPoint_u; %return the first output
