clear all 
global Ts;
global Asystem;
global Bsystem;
global Csystem;
global Dsystem;
global Qglobal;
global Rglobal;
global umaxglobal;
global reference;
global LinearizationPoint_x;
global LinearizationPoint_u;
Ts=0.05; % sample time
Qglobal=diag([10 10 1 1 0 0])*10; %weight on states
Rglobal=eye(2);     %weight on control signal
umaxglobal=[1,1]'*100; %constraint on control

%linearization point
theta0=-pi/8;
phi0=0;

[A, B,LinearizationPoint_x,LinearizationPoint_u]=linearDiscreteModelGen(phi0,theta0,Ts);

reference=LinearizationPoint_x; %+[1,0,0,0,0,0]'; %in origninal state space

%save the linearization in global vaariabels avalible to simulink function.
Asystem=A;
Bsystem=B;
% Csystem=C;
% Dsystem=D;


%initial condition 
x_0=LinearizationPoint_x;




