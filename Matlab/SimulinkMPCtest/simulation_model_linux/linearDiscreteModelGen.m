function [Adisc, Bdisc,linearizationPoint_x,linearizationPoint_u]=linearDiscreteModelGen(x1,x2,x7,x8,Ts)
%calculates a stationary point given x1=phi, x2=theta. And terurns this
%point together with the linearized A and B discretized with sample time Ts
%constants
g=9.81;
l1=0.1995;
l2=0.1743;
ml=0.280;
h=0.0298;
mw=0.158;
lw=0.090;
m1=0.3792;
m2=0.1739;
T1=1.1;
T2=0.33;
k1=1.0000e-2;
k2=1.39e-2;
C1=2.500000e-5;
C2=1.580000e-6;
D1=2.900000e-7;
D2=1.760000e-7;

m=ml+m1+m2+mw;
JL=ml/3*(l1^3+l2^3)/(l1+l2)+m1*l1^2+m2*l2^2+mw*lw^2;
JA=0;
lc=(ml*(l1-l2)+m1*l1-m2*l2-mw*lw)/m;

%calculate stationary point given x1 and x2
Theta_expression=m*g*(lc*cos(x2)-h*sin(x2));
w2_expression=D1/(-(l1*l2*C1*C2)+D1*D2)*Theta_expression;
w1_expression=-l2*C2/D1*w2_expression;
%(w_expression=w*|w|)
if(w2_expression<0)
    w2=-sqrt(-w2_expression);
else
    w2=sqrt(w2_expression);
end
if(w1_expression<0)
    w1=-sqrt(-w1_expression);
else
    w1=sqrt(w1_expression);
end

x5=w1;
x6=w2;
x3=0;
x4=0;

%define the linear A in afunction of the states. derived in the function
%linearization.m
Afunction=    @(C1,C2,D1,D2,JA,JL,T1,T2,g,h,l1,l2,lc,m,x2,x3,x4,x5,x6)reshape([0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,-(JL.*x3.*x4.*cos(x2.*2.0).*-4.0+D1.*x5.*abs(x5).*sin(x2).*2.0+C2.*l2.*x6.*abs(x6).*sin(x2).*2.0+h.^2.*m.*x3.*x4.*cos(x2.*2.0).*4.0+h.*lc.*m.*x3.*x4.*sin(x2.*2.0).*8.0)./(JA.*2.0+JL+h.^2.*m+JL.*cos(x2.*2.0)-h.^2.*m.*cos(x2.*2.0)-h.*lc.*m.*sin(x2.*2.0).*2.0)+(JL.*sin(x2.*2.0)-h.^2.*m.*sin(x2.*2.0)+h.*lc.*m.*cos(x2.*2.0).*2.0).*1.0./(JA+JL.*cos(x2).^2+h.^2.*m.*sin(x2).^2-h.*lc.*m.*cos(x2).*sin(x2).*2.0).^2.*(D1.*x5.*abs(x5).*cos(x2)+JL.*x3.*x4.*sin(x2.*2.0)+C2.*l2.*x6.*abs(x6).*cos(x2)-h.^2.*m.*x3.*x4.*sin(x2.*2.0)+h.*lc.*m.*x3.*x4.*cos(x2.*2.0).*2.0),(-JL.*x3.^2.*(cos(x2).^2.*2.0-1.0)+h.^2.*m.*x3.^2.*(cos(x2).^2.*2.0-1.0)+g.*h.*m.*cos(x2)+g.*lc.*m.*sin(x2)+h.*lc.*m.*x3.^2.*cos(x2).*sin(x2).*4.0)./(JL+h.^2.*m),0.0,0.0,1.0,0.0,(x4.*(JL.*cos(x2).*sin(x2).*2.0-h.^2.*m.*cos(x2).*sin(x2).*2.0+h.*lc.*m.*(cos(x2).^2.*2.0-1.0).*2.0))./(JA+JL.*cos(x2).^2+h.^2.*m.*sin(x2).^2-h.*lc.*m.*cos(x2).*sin(x2).*2.0),-(x3.*(JL.*sin(x2.*2.0)-h.^2.*m.*sin(x2.*2.0)+h.*lc.*m.*cos(x2.*2.0).*2.0))./(JL+h.^2.*m),0.0,0.0,0.0,1.0,(x3.*(JL.*cos(x2).*sin(x2).*2.0-h.^2.*m.*cos(x2).*sin(x2).*2.0+h.*lc.*m.*(cos(x2).^2.*2.0-1.0).*2.0))./(JA+JL.*cos(x2).^2+h.^2.*m.*sin(x2).^2-h.*lc.*m.*cos(x2).*sin(x2).*2.0),0.0,0.0,0.0,0.0,0.0,(D1.*x5.*cos(x2).*(sign(x5).^2+1.0))./(sign(x5).*(JA+JL.*cos(x2).^2+h.^2.*m.*sin(x2).^2-h.*lc.*m.*cos(x2).*sin(x2).*2.0)),(C1.*l1.*x5.*(sign(x5).^2+1.0))./(sign(x5).*(JL+h.^2.*m)),-1.0./T1,0.0,0.0,0.0,(C2.*l2.*x6.*cos(x2).*(sign(x6).^2+1.0))./(sign(x6).*(JA+JL.*cos(x2).^2+h.^2.*m.*sin(x2).^2-h.*lc.*m.*cos(x2).*sin(x2).*2.0)),(D2.*x6.*(sign(x6).^2+1.0))./(sign(x6).*(JL+h.^2.*m)),0.0,-1.0./T2],[6,6]);

A=Afunction(C1,C2,D1,D2,JA,JL,T1,T2,g,h,l1,l2,lc,m,x2,x3,x4,x5,x6);
B=[      0         0;
         0         0;
         0         0;
         0         0;
   90.9091         0;
         0  218.0074];
     

%calculating descrete matrices
Adisc=expm(A*Ts);
Aintegral=eye(6);
temp_term=1;
for i=1:20 %taylor expanssion of the integral term int(expm(A*Ts)).
    temp_term=temp_term*(A*Ts)/(i+1);
    Aintegral=Aintegral+temp_term;
end
Bdisc=Aintegral*Ts*B;

linearizationPoint_x=[x1,x2,0,0,x5,x6,x7,x8]';
linearizationPoint_u=[x5*k1-x7;x6*k2-x8];
