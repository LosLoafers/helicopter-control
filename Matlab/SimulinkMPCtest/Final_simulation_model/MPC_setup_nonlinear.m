clear all 
global Ts_control;

global Qglobal;
global Rglobal;
global umaxglobal;
global uminglobal;

global phi_max;
global phi_min;
global theta_min;
global theta_max;

%MPC setup
Ts_control=0.05; % sample time
Qglobal=diag([1 1 1 1 0 0 0 0]); %weight on states
Rglobal=diag([1 1])*1;     %weight on control signal
%constraints
umaxglobal=[1,0]'*10; %constraint on control
uminglobal=[0,-1]'*10;
phi_min=-pi;
phi_max=pi;
theta_min=-pi/3.9;
theta_max=pi/3.9;



%initial condition on model 
x_0=[0,0,0,0,0,0,0,0]; 


%kalman setup
global Q;
global R;
global Ts_kalman;
Ts_kalman=0.01;
h=Ts_kalman; % for the real process
Q=diag([0.1 0.1 0.1 0.1 0.1 0.1 60 60])*1e-4;
%R = rand(2,2);
R=[0.0679 0.0274;0.0274 0.4867]*1e-5; %covariance
R1=sqrtm(R); %std
P_0=eye(8)*100;




