% Denna fil är mest tänkt som ett test av CVXgen 

%någon random punkt
x10=0;
x20=0;
x30=pi/4;
x40=0;
x50=u10/k1;
x60=u20/k2;
u10=10;
u20=10;
%samplingstid
h=0.1;
[A,B]=linearDescreteModelGen(x10,x20,x30,x40,x50,x60,u10,u20,h);

%setup opt problem
params.A=A;
params.B=B;
params.Q=eye(6);
params.R=eye(2);
params.u_max=10;
params.u_min=-10;
params.x_0=[x10,x20,x30,x40,x50,x60]';

% Create a new settings structure, with some example settings.
% settings.verbose = 0;  % disable output of solver progress.
% settings.max_iters = 10;  % reduce the maximum iteration count, from 25.
% settings.eps = 0.1;  % reduce the required objective tolerance, from 1e-6.
% settings.resid_tol = 1e-2;  % reduce the required residual tolerances, from 1e-4.

% solve
[vars, status] = csolve(params, settings);
u=vars.u{1};
x=vars.x;
x3=x{1}(3);
