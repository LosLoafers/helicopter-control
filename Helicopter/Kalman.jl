#kalman setup
const Ts_kalman=0.01;
const Q=Diagonal([0.1;0.1;0.1;0.1;0.1;0.1;60;80])*1e-3
const R=[0.0679 0.0274;0.0274 0.4867]*1e-5 #covariance
const stop_angle = -0.95
const N=20
#---------------------------------------------------------------------------

function updateKalman(x_hat,u,y,P)


    F=Jacobi_fk(x_hat,Ts_kalman,stop_angle) #jacobian of f evaluated at x_hat
#Jacobian of h(x)
    C=[1 0 0 0 0 0 0 0;0 1 0 0 0 0 0 0]
    H=C
	for i=1:N
		x_hat=f_k(x_hat,u,Ts_kalman/N,stop_angle)
	end
#kalman update
    P_new=F*P*F'+Ts_kalman^2*Q #predicted covariance
    ye=y-C*x_hat #measurment residual
    S=H*P_new*H'+R  #residual covariance
    K=P_new*H'/S  #"optimal" kalman gain
    x_new=x_hat+K*ye
    P_new=(eye(8)-K*H)*P_new #updated covariance
    P_new=(P_new+P_new')./2 #P must be symetric
	#println("P=",P_new)
    x_new,P_new
end

#---------------------------------------------------------------------------

function f_k(X,U,Ts,stop_angle)
#x=[u1,u2,phi, theta, dphi,dtheta,w1,w2]';
#y=[phi, theta, dphi,dtheta,w1,w2]'
    const g=9.81
    const l1=0.1995
    const l2=0.1743
    const ml=0.280
    const h=0.0298
    const mw=0.158
    const lw=0.090
    const m1=0.3792
    const m2=0.1739
    const T1=1.1
    const T2=0.33
    const k1=1e-2
    const k2=1.39e-2
    const C1=2.50e-5
    const C2=1.58e-6
    const D1=2.90e-7
    const D2=1.76e-7

    const m=ml+m1+m2+mw
    const JL=ml/3*(l1^3+l2^3)/(l1+l2)+m1*l1^2+m2*l2^2+mw*lw^2
    const JA=0
    const lc=(ml*(l1-l2)+m1*l1-m2*l2-mw*lw)/m

    u1=U[1]
    u2=U[2]
    x1=X[1]
    x2=X[2]
    x3=X[3]
    x4=X[4]
    x5=X[5]
    x6=X[6]

#the folowing notation is used:
#x1=phi x2=theta x3=d/dt(phi) x4=d/dt(theta) x5=w1 x6=w2
#nonlinearmodel

#d/dt x1=x3
#d/dt x2=x4
#d/dt x3=f1
#d/dt x4=f2
#d/dt x5=f3
#d/dt x6=f4

#define f1
    f1=(2*cos(x2)*sin(x2)*x3*x4*JL-2*h*(sin(x2)^2-cos(x2)^2)*x3*x4*m*lc-2*h^2*sin(x2)*cos(x2)*x3*x4*m+D1*x5*abs(x5)*cos(x2)+l2*cos(x2)*C2*x6*abs(x6))/(cos(x2)^2*JL-2*h*cos(x2)*sin(x2)*m*lc+h^2*sin(x2)^2*m+JA)

#define f2
    f2=(-cos(x2)*sin(x2)*x3^2*JL-h*(-sin(x2)^2+cos(x2)^2)*x3^2*m*lc-g*cos(x2)*m*lc+h^2*sin(x2)*cos(x2)*x3^2*m+m*g*h*sin(x2)+l1*C1*x5*abs(x5)+D2*x6*abs(x6))/(JL+h^2*m)

#define f3
    f3=-1/T1*x5+1/(T1*k1)*(u1+X[7])

#define f4
    f4=-1/T2*x6+1/(T2*k2)*(u2+X[8])

    f=[x3;x4;f1;f2;f3;f4;0;0]

    X_new=X+Ts*f #forward euler

    if X_new[2]<=stop_angle+0.01 && X_new[4]<=0 # makes the pich angel stop at the starting pos.
        X_new[2]=stop_angle;
        X_new[4]=0;
    end
    X_new
end

#---------------------------------------------------------------------------

function Jacobi_fk(X,Ts,stop_angle)
    x2=X[2]
    x3=X[3]
    x4=X[4]
    x5=X[5]
    x6=X[6]

#jacobian of the discretized state equation

    Jf= (x2,x3,x4,x5,x6) -> reshape([0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,-(x3.*x4.*cos(x2).^2.*(-4.8159643934e-2)+x3.*x4.*sin(x2).^2.*4.8159643934e-2+x5.*abs(x5).*sin(x2).*2.9e-7+x6.*abs(x6).*sin(x2).*2.75394e-7+x3.*x4.*cos(x2).*sin(x2).*9.101070192000004e-3)./(cos(x2).*sin(x2).*(-2.275267548000001e-3)+cos(x2).^2.*2.4959958411e-2+sin(x2).^2.*8.80136444e-4)+(cos(x2).*sin(x2).*4.8159643934e-2+cos(x2).^2.*2.275267548000001e-3-sin(x2).^2.*2.275267548000001e-3).*1.0./(cos(x2).*sin(x2).*(-2.275267548000001e-3)+cos(x2).^2.*2.4959958411e-2+sin(x2).^2.*8.80136444e-4).^2.*(x5.*abs(x5).*cos(x2).*2.9e-7+x6.*abs(x6).*cos(x2).*2.75394e-7+x3.*x4.*(cos(x2).^2.*5.96e-2-sin(x2).^2.*5.96e-2).*3.817563000000002e-2+x3.*x4.*cos(x2).*sin(x2).*4.8159643934e-2),cos(x2).*1.121265976095814e1+sin(x2).*1.449309425532293e1-x3.^2.*cos(x2).^2.*9.318782342759322e-1+x3.^2.*sin(x2).^2.*9.318782342759322e-1+x3.^2.*cos(x2).*sin(x2).*1.761036529291023e-1,0.0,0.0,0.0,0.0,1.0,0.0,(x4.*(cos(x2).^2.*5.96e-2-sin(x2).^2.*5.96e-2).*3.817563000000002e-2+x4.*cos(x2).*sin(x2).*4.8159643934e-2)./(cos(x2).*sin(x2).*(-2.275267548000001e-3)+cos(x2).^2.*2.4959958411e-2+sin(x2).^2.*8.80136444e-4),x3.*(cos(x2).^2.*2.98e-2-sin(x2).^2.*2.98e-2).*(-2.954759277333931)-x3.*cos(x2).*sin(x2).*1.863756468551864,0.0,0.0,0.0,0.0,0.0,1.0,(x3.*(cos(x2).^2.*5.96e-2-sin(x2).^2.*5.96e-2).*3.817563000000002e-2+x3.*cos(x2).*sin(x2).*4.8159643934e-2)./(cos(x2).*sin(x2).*(-2.275267548000001e-3)+cos(x2).^2.*2.4959958411e-2+sin(x2).^2.*8.80136444e-4),0.0,0.0,0.0,0.0,0.0,0.0,0.0,(abs(x5).*cos(x2).*2.9e-7+x5.*cos(x2).*sign(x5).*2.9e-7)./(cos(x2).*sin(x2).*(-2.275267548000001e-3)+cos(x2).^2.*2.4959958411e-2+sin(x2).^2.*8.80136444e-4),abs(x5).*1.930139973551579e-4+x5.*sign(x5).*1.930139973551579e-4,-1.0e1./1.1e1,0.0,0.0,0.0,0.0,0.0,(abs(x6).*cos(x2).*2.75394e-7+x6.*cos(x2).*sign(x6).*2.75394e-7)./(cos(x2).*sin(x2).*(-2.275267548000001e-3)+cos(x2).^2.*2.4959958411e-2+sin(x2).^2.*8.80136444e-4),abs(x6).*6.811120508171988e-6+x6.*sign(x6).*6.811120508171988e-6,0.0,-1.0e2./3.3e1,0.0,0.0,0.0,0.0,0.0,0.0,1.0e3./1.1e1,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,2.180074122520166e2,0.0,0.0],(8,8))

#jacobian of the continous f(x)
    F=eye(8)+Ts*Jf(x2,x3,x4,x5,x6) #Jacobian of the function f_k (the discrete f(x))

    if X[2] < stop_angle && X[4] < 0
        F[8,8]=0 #the integrator state of theta needs to be kept down
        F[7,7]=0
        F[4,4]=0.1 #put the dthata state derivative to zero.
                #not sure if this is necessary....
    end
	F
end

#------------------------------------------------------------------------------

#test
#(xx,pp)=updateKalman([1 2 3 4 5 6 7 8]',[1 1]',[1 2]',100*eye(8),0.25)
