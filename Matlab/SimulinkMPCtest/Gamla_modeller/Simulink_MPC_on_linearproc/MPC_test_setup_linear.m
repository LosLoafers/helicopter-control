%Setup code for MPC_regul_linear in simulink. This model test an MPC with CVXgen on a linerar process
%derived from Gräfverts nonliner model through linearization. 
clear all;
%global parameters used by mysolve function.
global Ts;
global Asystem;
global Bsystem;
global Csystem;
global Dsystem;
global Qglobal;
global Rglobal;
global umaxglobal;
global reference;

Ts=0.1; % sample time
Qglobal=diag([10 10 1 1 0 0])*10; %weight on states. Zero weight on w1 and w1 to be able to follow a reference
Rglobal=eye(2);     %weight on \Delta{u} (slew-rate)
umaxglobal=[1,1]'*10; %constraint on controlsignal

%linearization point
theta0=0;
phi0=0;

run('synthesize_model.m'); %run marcus linearization
x_0=x0; %store lin. point
u_0=u0;

reference=[0 2 0 0 0 0]'; %reference set to zero to follow the lin. point.

%save the linearization in global vaariabels avalible to simulink function.
Asystem=A;
Bsystem=B;
Csystem=C;
Dsystem=D;





