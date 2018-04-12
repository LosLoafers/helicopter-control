clear all 
global Ts_control;
global Asystem;
global Bsystem;

global Qglobal;
global Rglobal;
global umaxglobal;
global reference;
global LinearizationPoint_x;
global LinearizationPoint_u;
Ts_control=0.05; % sample time
Qglobal=diag([10 30 10 10 0 0]); %weight on states
Rglobal=diag([1 1])*100;     %weight on control signal
umaxglobal=[1,1]'*10; %constraint on control

%initial linearization point
theta0=0;
phi0=0;
[Asystem,Bsystem,LinearizationPoint_x]=linearDiscreteModelGen(phi0,theta0,Ts_control);
k1=1e-2;
k2=1.39e-2;
LinearizationPoint_u=[LinearizationPoint_x(1)*k1,LinearizationPoint_x(2)*k2]'; %store lin. u
reference=[0,-pi/8,0,0,0,0]'; %in origninal state space

%save the linearization in global vaariabels avalible to simulink function.



%initial condition 
x_0=[0,0,0,0,0,0]; %LinearizationPoint_x;

%initial u signal for startup
[~,~,step_x]=linearDiscreteModelGen(0,pi/4.3,Ts_control);
u_step=[step_x(5)*k1;step_x(6)*k2];
%kalman setup
global Q;
global R;
global Ts_kalman;
Ts_kalman=0.005;
Q=diag([100 100 1 1 0.1 0.1]);
R=eye(2)*10;
P_0=eye(6)*100;




