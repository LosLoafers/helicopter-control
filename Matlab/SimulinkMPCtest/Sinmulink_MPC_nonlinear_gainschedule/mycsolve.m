function u=mycsolve(x)
%This function "wraps" the csolve MEX solver in a matlab function.
% This is done beacouse Simulink is afraid of cell arrays and wont accept
% csolve.mex directly.

%Globaly defined parameters is set
% the solver.
global Asystem;
global Bsystem;
global Ts;
global umaxglobal;
global Qglobal;
global Rglobal;
global reference;
global LinearizationPoint_x;
global LinearizationPoint_u;

%calculate linearizatin in current point
[Asystem,Bsystem,LinearizationPoint_x,LinearizationPoint_u]=linearDiscreteModelGen(x(1),x(2),Ts); 

%setup opt problem
params.x_0=x-LinearizationPoint_x;
params.A=Asystem;
params.B=Bsystem;
params.Q=Qglobal;
params.R=Rglobal;
params.u_max=umaxglobal-LinearizationPoint_u;
params.r=reference-LinearizationPoint_x;



% Create a new settings structure. Just some example
% copied from the cvx homepage:
settings.verbose = 1;  % disable output of solver progress.
% settings.max_iters = 10;  % reduce the maximum iteration count, from 25.
% settings.eps = 0.1;  % reduce the required objective tolerance, from 1e-6.
% settings.resid_tol = 1e-2;  % reduce the required residual tolerances, from 1e-4.

% solve

[vars, ~] = csolve(params, settings);
u=vars.u{1}+LinearizationPoint_u; %return the first output
