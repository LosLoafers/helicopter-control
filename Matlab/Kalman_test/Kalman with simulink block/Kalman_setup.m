clear all
global Qe;
global Qv;
Ts=0.05;
Qe=eye(2)*100;
Qv=diag([10 10 10 10 10 10]);
P_0=eye(6)*100;
x_0=zeros(6,1);

[Asystem,Bsystem,x_lin]=linearDiscreteModelGen(0,0,Ts);
k1 = 1.00e-2; % [Vs/rad]
k2 = 1.39e-2;
u_lin=[x_lin(5)*k1,x_lin(6)*k2]';