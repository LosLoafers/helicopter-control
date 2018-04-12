global Q;
global R;
global Ts;
Ts=0.005;
Q=diag([10 10 10 10 10 10]);
R=eye(2)*1000;
P_0=eye(6)*100;
x_0=zeros(6,1);
