function [ x_new,P_new ] = updateKalman(x_hat,u,y,P )
global R;
global Q;
global Ts_kalman;


%x_k+1=f(x_k)+vk
%y_k=h(x_k)=C*x_k
F=Jacobi_fk(x_hat,Ts_kalman); %jacobian of f evaluated at x_hat
 %Jacobian of h(x)

C=[1 0 0 0 0 0 0 0;0 1 0 0 0 0 0 0];
H=C;

%kalman update
P_new=F*P*F'+Q; %predicted covariance
y_hat=y-C*x_hat; %measurment residual
S=H*P_new*H'+R;     %residual covariance
K=P_new*H'/S;       %"optimal" kalman gain
x_new=f_k(x_hat,u,Ts_kalman)+K*y_hat;
P_new=(eye(8)-K*H)*P_new;%updated covariance
P_new=(P_new+P_new')./2;