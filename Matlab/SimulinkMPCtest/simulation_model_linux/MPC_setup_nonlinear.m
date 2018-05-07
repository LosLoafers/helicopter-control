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
Ts_control=0.02; % sample time
Qglobal=diag([3 3 2 2 0 0 0 0]); %weight on states
Rglobal=diag([1 1])*1;     %weight on control signal
%constraints
umaxglobal=[1,0]'*10; %constraint on control
uminglobal=[0,-1]'*10;
phi_min=-170/180*pi;
phi_max=170/180*pi;
theta_min=-0.98;
theta_max=0.45;
%theta_max=0;



%initial condition on model 
x_0=[0,-pi/4,0,0,0,0,0,0]; 


%kalman setup
global Q;
global R;
global Ts_kalman;
Ts_kalman=0.01;
h=Ts_kalman; % for the real process
Q=diag([1 1 1 1 1 1 80 80])*1e-3;
%R = rand(2,2);
R=[0.0679 0.0274;0.0274 0.4867]*1e-5; %covariance
R1=sqrtm(R); %std
P_0=eye(8)*100;




