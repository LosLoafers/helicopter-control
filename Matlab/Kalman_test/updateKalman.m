function [ x_new,P_new ] = updateKalman( x_hat,u,y,P )
global Qe;
global Qv;
global Ts;

%get linearization in this point
[A, B,linearizationPoint_x]=linearDescreteModelGen(x_hat(1),x_hat(2),Ts);
delta_x_hat=x_hat-linearizationPoint_x;
delta_y=y-linearizationPoint_x(1:2);
C=[1 0 0 0 0 0;0 1 0 0 0 0 ];

%kalman update
delta_y_hat=C*delta_x_hat %predicted output
R=Qe+C*P*C';
K=(A*P*C')/R; 
P_new=A*P*A'+Qv-K*R*K'; %covariance of new prediction
x_new=A*delta_x_hat+B*u+K*(delta_y-delta_y_hat)+linearizationPoint_x; %new prediction 

