%clear all 
global Ts_control;
global Asystem;
global Bsystem;
global Qglobal;
global Rglobal;
global umaxglobal;
global uminglobal;
global reference;
global LinearizationPoint_x;
global LinearizationPoint_u;
global phi_max;
global phi_min;
global theta_min;
global theta_max;
Ts_control=0.05; % sample time
Qglobal=diag([1 1 5 5 0 0 0 0]); %weight on states
Rglobal=diag([1 1])*1;     %weight on control signal
umaxglobal=[1,0]'*10; %constraint on control
uminglobal=[0,-1]'*10;
phi_min=-pi;
phi_max=pi;
theta_min=-pi/3.9;
theta_max=pi/3.9;

%initial linearization point
theta0=0;
phi0=0;
[Asystem,Bsystem,LinearizationPoint_x]=linearDiscreteModelGen(phi0,theta0,Ts_control);
k1=1e-2;
k2=1.39e-2;
LinearizationPoint_u=[LinearizationPoint_x(1)*k1,LinearizationPoint_x(2)*k2]'; %store lin. u
%reference=[0,-pi/6,0,0,0,0,0,0]'; %in origninal state space

%save the linearization in global vaariabels avalible to simulink function.



%initial condition 
x_0=[0,-pi/4,0,0,0,0,0,0]; 

%initial u signal for startup
[~,~,step_x]=linearDiscreteModelGen(0,pi/4.3,Ts_control);
u_step=[step_x(5)*k1;step_x(6)*k2];
%kalman setup
global Q;
global R;
global Ts_kalman;
Ts_kalman=0.01;
h=Ts_kalman;
Q=diag([0.1 0.1 0.1 0.1 0.1 0.1 10 10])*1e-6;
R = rand(2,2);
R=R*R'*1e-4; %variance
R1=sqrtm(R); %std
%R=eye(2)*1e-5;
P_0=eye(8)*100;




