function [ x_new,P_new ] = updateKalman(x_hat,u,y,P,stop_angle)
global R;
global Q;
global Ts_kalman;
C=[1 0 0 0 0 0 0 0;0 1 0 0 0 0 0 0];
H=C;
N=20;

F=Jacobi_fk(x_hat,Ts_kalman,stop_angle);
for i=1:N %update
  x_hat=f_k(x_hat,u,Ts_kalman/N,stop_angle);
end

%kalman predict
P_new=F*P*F'+(Ts_kalman)^2*Q;
ye=y-C*x_hat; %measurment residual
S=H*P_new*H'+R;    %residual covariance
K=P_new*H'/S;       %"optimal" kalman gain
x_new=x_hat+K*ye;
P_new=(eye(8)-K*H)*P_new;%updated covariance
P_new=(P_new+P_new')./2; %P must be symetric 
% end