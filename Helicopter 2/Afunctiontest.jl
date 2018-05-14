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

Res=Jacobi_fk([1 1 0 0 0 0 0 0], 0.01,-1.83)

