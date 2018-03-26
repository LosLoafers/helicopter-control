function [ x_new,P_new ] = updateKalman( x_hat,u,y,P )

global Qe;
global Qv;
global Ts;
global x_lin;
global u_lin;
global Asystem;
global Bsystem;

%get linearization in each point

%[A, B,x_lin]=linearDiscreteModelGen(y(1),y(2),Ts);

 %or only one lin. point from setup code
A=Asystem;
B=Bsystem;
C=[1 0 0 0 0 0;0 1 0 0 0 0 ];

delta_x_hat=x_hat-x_lin;
delta_u = u-u_lin;
delta_y=y-x_lin(1:2);

%predict
delta_x_predict=A*delta_x_hat+B*delta_u;
P=A*P*A'+Qv;

%kalman update
delta_y_hat=C*delta_x_hat; %predicted output
R=Qe+C*P*C';
K=(P*C')/R; 
P_new=(eye(6)-K*C)*P; %covariance of new prediction
P_new=(P_new+P_new')./2; %protect from numerical error. P must be symetric.
x_new=delta_x_predict+K*(delta_y-delta_y_hat)+x_lin; %new prediction 

