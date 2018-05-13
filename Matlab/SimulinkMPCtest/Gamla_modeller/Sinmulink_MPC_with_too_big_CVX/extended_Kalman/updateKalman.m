function [ x_new,P_new ] = updateKalman(x_hat,u,y,P,stop_angle)
global R;
global Q;
global Ts_kalman;

%stop_angle=-pi/4; %MUST be lager than the real stop value! Kalman will 
%fail otherwise.



% if(y(2)<stop_angle_)
%     x_temp=f_k(x_hat,u,Ts_kalman,stop_angle_);
%     x_new=[y;x_temp(3:8)]
%     P_new=P;
% else
%x_k+1=f(x_k)+vk
%y_k=h(x_k)=C*x_k
F=Jacobi_fk(x_hat,Ts_kalman,stop_angle); %jacobian of f evaluated at x_hat
 %Jacobian of h(x)

C=[1 0 0 0 0 0 0 0;0 1 0 0 0 0 0 0];
H=C;

%kalman update
P_new=F*P*F'+Q; %predicted covariance
ye=y-C*x_hat; %measurment residual
S=H*P_new*H'+R;    %residual covariance
K=P_new*H'/S;       %"optimal" kalman gain
x_new=f_k(x_hat,u,Ts_kalman,stop_angle)+K*ye;
P_new=(eye(8)-K*H)*P_new;%updated covariance
P_new=(P_new+P_new')./2; %P must be symetric 
% end