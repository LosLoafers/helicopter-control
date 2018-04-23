#------------MPC setup--------------------------------------------------------
const Ts_control = 0.05 #sample time
const Q = reshape(Diagonal([1;1;1;1;0;0;0;0]),1,:) #weight on states
const R = reshape(Diagonal([1;1])*1,1,:)     #weight on control signal

#constraints
const umaxglobal = [1 0]'*10 #constraint on control
const uminglobal = [0 -1]'*10
const phi_min = -pi
const phi_max = pi
const theta_min = -pi/3.9
const theta_max = pi/3.9

#------------------------------------------------------------------------------

function cvxsolve(x,r)
    [Asystem,Bsystem,LinearizationPoint_x,LinearizationPoint_u]=linearDiscreteModelGen(x[1],x[2],Ts_control)

#setup opt problem
    reference=[r;0;0;0;0;0;0]
    param_x_0=x-[LinearizationPoint_x;0;0]
    param_A=reshape([Asystem,Bsystem;zeros(2,6),eye(2)],1,:)
    param_B=reshape([Bsystem;zeros(2,2)],1,:)
    #param_Q=Qglobal
    #param_R=Rglobal
    param_u_max=(umaxglobal-LinearizationPoint_u)'
    param_u_min=(uminglobal-LinearizationPoint_u)'
    param_r=(reference-[LinearizationPoint_x;0;0])'
    #param_phi_max=phi_max;
    #param_phi_min=phi_min;
    #param_theta_min=theta_min;
    #param_theta_max=theta_max;

    #call c function
    #return u
end
#---------------------------------------------------------------------------

function linearDescreteModelGen(x1,x2,Ts)
#calculates a stationary point given x1=phi, x2=theta. And returns this
#point together with the linearized A and B discretized with sample time Ts
#constants
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

#calculate stationary point given x1 and x2
    Theta_expression=m*g*(lc*cos(x2)-h*sin(x2))
    w2_expression=D1/(-(l1*l2*C1*C2)+D1*D2)*Theta_expression
    w1_expression=-l2*C2/D1*w2_expression

    if w2_expression < 0
        w2 = -sqrt(-w2_expression)
    else
        w2 = sqrt(w2_expression)
    end

    if w1_expression < 0
        w1=-sqrt(-w1_expression)
    else
        w1=sqrt(w1_expression)
    end
    x5=w1
    x6=w2
    x3=0
    x4=0

#define the linear A in afunction of the states. derived in the function
#linearization.m

    Afunction=(C1,C2,D1,D2,JA,JL,T1,T2,g,h,l1,l2,lc,m,x2,x3,x4,x5,x6) -> reshape([0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,-(JL.*x3.*x4.*cos(x2.*2.0).*-4.0+D1.*x5.*abs(x5).*sin(x2).*2.0+C2.*l2.*x6.*abs(x6).*sin(x2).*2.0+h.^2.*m.*x3.*x4.*cos(x2.*2.0).*4.0+h.*lc.*m.*x3.*x4.*sin(x2.*2.0).*8.0)./(JA.*2.0+JL+h.^2.*m+JL.*cos(x2.*2.0)-h.^2.*m.*cos(x2.*2.0)-h.*lc.*m.*sin(x2.*2.0).*2.0)+(JL.*sin(x2.*2.0)-h.^2.*m.*sin(x2.*2.0)+h.*lc.*m.*cos(x2.*2.0).*2.0).*1.0./(JA+JL.*cos(x2).^2+h.^2.*m.*sin(x2).^2-h.*lc.*m.*cos(x2).*sin(x2).*2.0).^2.*(D1.*x5.*abs(x5).*cos(x2)+JL.*x3.*x4.*sin(x2.*2.0)+C2.*l2.*x6.*abs(x6).*cos(x2)-h.^2.*m.*x3.*x4.*sin(x2.*2.0)+h.*lc.*m.*x3.*x4.*cos(x2.*2.0).*2.0),(-JL.*x3.^2.*(cos(x2).^2.*2.0-1.0)+h.^2.*m.*x3.^2.*(cos(x2).^2.*2.0-1.0)+g.*h.*m.*cos(x2)+g.*lc.*m.*sin(x2)+h.*lc.*m.*x3.^2.*cos(x2).*sin(x2).*4.0)./(JL+h.^2.*m),0.0,0.0,1.0,0.0,(x4.*(JL.*cos(x2).*sin(x2).*2.0-h.^2.*m.*cos(x2).*sin(x2).*2.0+h.*lc.*m.*(cos(x2).^2.*2.0-1.0).*2.0))./(JA+JL.*cos(x2).^2+h.^2.*m.*sin(x2).^2-h.*lc.*m.*cos(x2).*sin(x2).*2.0),-(x3.*(JL.*sin(x2.*2.0)-h.^2.*m.*sin(x2.*2.0)+h.*lc.*m.*cos(x2.*2.0).*2.0))./(JL+h.^2.*m),0.0,0.0,0.0,1.0,(x3.*(JL.*cos(x2).*sin(x2).*2.0-h.^2.*m.*cos(x2).*sin(x2).*2.0+h.*lc.*m.*(cos(x2).^2.*2.0-1.0).*2.0))./(JA+JL.*cos(x2).^2+h.^2.*m.*sin(x2).^2-h.*lc.*m.*cos(x2).*sin(x2).*2.0),0.0,0.0,0.0,0.0,0.0,(D1.*x5.*cos(x2).*(sign(x5).^2+1.0))./(sign(x5).*(JA+JL.*cos(x2).^2+h.^2.*m.*sin(x2).^2-h.*lc.*m.*cos(x2).*sin(x2).*2.0)),(C1.*l1.*x5.*(sign(x5).^2+1.0))./(sign(x5).*(JL+h.^2.*m)),-1.0./T1,0.0,0.0,0.0,(C2.*l2.*x6.*cos(x2).*(sign(x6).^2+1.0))./(sign(x6).*(JA+JL.*cos(x2).^2+h.^2.*m.*sin(x2).^2-h.*lc.*m.*cos(x2).*sin(x2).*2.0)),(D2.*x6.*(sign(x6).^2+1.0))./(sign(x6).*(JL+h.^2.*m)),0.0,-1.0./T2],(6,6))

    A=Afunction(C1,C2,D1,D2,JA,JL,T1,T2,g,h,l1,l2,lc,m,x2,x3,x4,x5,x6)

    B=[0 0;0 0;0 0;0 0;1.0./(T1.*k1) 0;0 1.0./(T2.*k2)]

#calculating descrete matrices
    Adisc=expm(A*Ts)
    Aintegral=eye(6)
    temp_term=1

    for i=1:20 #taylor expanssion of the integral term int(expm(A*Ts)).
        temp_term=temp_term*(A*Ts)/(i+1)
        Aintegral=Aintegral+temp_term
    end

    Bdisc=Aintegral*Ts*B
    linearizationPoint_x=[x1,x2,0,0,x5,x6]'
    linearizationPoint_u=[x5*k1;x6*k2]

    Adisc, Bdisc, linearizationPoint_x, linearizationPoint_u
end
