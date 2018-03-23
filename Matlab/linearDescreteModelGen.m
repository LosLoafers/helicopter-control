function [Adisc, Bdisc,linearizationPoint_x]=linearDescreteModelGen(x1,x2,h)
%calculates a stationary point given x1=phi, x2=theta. And terurns this
%point together with 
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
k1=1e-2;
k2=1.39e-2;
C1=2.50e-5;
C2=1.58e-6;
D1=2.90e-7;
D2=1.76e-7;

m=ml+m1+m2+mw;
JL=ml/3*(l1^3+l2^3)/(l1+l2)+m1*l1^2+m2*l2^2+mw*lw^2;
JA=0;
lc=(ml*(l1-l2)+m1*l1-m2*l2-mw*lw)/m;

%calculate stationary point given x1 and x2
Theta_hat=m*g*(lc*cos(x2)-h*sin(x2));
w2_hat=1/(-l1*l2*C1*C2/D1+D2)*Theta_hat;
w1_hat=-l2*C2/D1*w2_hat;

if(w2_hat<0)
    w2=-sqrt(-w2_hat);
else
    w2=sqrt(w2_hat);
end
if(w1_hat<0)
    w1=-sqrt(-w1_hat);
else
    w1=sqrt(w1_hat);
end

x5=w1;
x6=w2;

%define the linear A in afunction of the states.
Afunction=@(x2,x3,x4,x5,x6) reshape([0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,-(x3.*x4.*cos(x2).^2.*(-4.8159643934e-2)+x3.*x4.*sin(x2).^2.*4.8159643934e-2+x5.*abs(x5).*sin(x2).*2.9e-7+x6.*abs(x6).*sin(x2).*2.75394e-7+x3.*x4.*cos(x2).*sin(x2).*9.101070192000004e-3)./(cos(x2).*sin(x2).*(-2.275267548000001e-3)+cos(x2).^2.*2.4959958411e-2+sin(x2).^2.*8.80136444e-4)+(cos(x2).*sin(x2).*4.8159643934e-2+cos(x2).^2.*2.275267548000001e-3-sin(x2).^2.*2.275267548000001e-3).*1.0./(cos(x2).*sin(x2).*(-2.275267548000001e-3)+cos(x2).^2.*2.4959958411e-2+sin(x2).^2.*8.80136444e-4).^2.*(x5.*abs(x5).*cos(x2).*2.9e-7+x6.*abs(x6).*cos(x2).*2.75394e-7+x3.*x4.*(cos(x2).^2.*5.96e-2-sin(x2).^2.*5.96e-2).*3.817563000000002e-2+x3.*x4.*cos(x2).*sin(x2).*4.8159643934e-2),cos(x2).*1.121265976095814e1+sin(x2).*1.449309425532293e1-x3.^2.*cos(x2).^2.*9.318782342759322e-1+x3.^2.*sin(x2).^2.*9.318782342759322e-1+x3.^2.*cos(x2).*sin(x2).*1.761036529291023e-1,0.0,0.0,1.0,0.0,(x4.*(cos(x2).^2.*5.96e-2-sin(x2).^2.*5.96e-2).*3.817563000000002e-2+x4.*cos(x2).*sin(x2).*4.8159643934e-2)./(cos(x2).*sin(x2).*(-2.275267548000001e-3)+cos(x2).^2.*2.4959958411e-2+sin(x2).^2.*8.80136444e-4),x3.*(cos(x2).^2.*2.98e-2-sin(x2).^2.*2.98e-2).*(-2.954759277333931)-x3.*cos(x2).*sin(x2).*1.863756468551864,0.0,0.0,0.0,1.0,(x3.*(cos(x2).^2.*5.96e-2-sin(x2).^2.*5.96e-2).*3.817563000000002e-2+x3.*cos(x2).*sin(x2).*4.8159643934e-2)./(cos(x2).*sin(x2).*(-2.275267548000001e-3)+cos(x2).^2.*2.4959958411e-2+sin(x2).^2.*8.80136444e-4),0.0,0.0,0.0,0.0,0.0,(abs(x5).*cos(x2).*2.9e-7+x5.*cos(x2).*sign(x5).*2.9e-7)./(cos(x2).*sin(x2).*(-2.275267548000001e-3)+cos(x2).^2.*2.4959958411e-2+sin(x2).^2.*8.80136444e-4),abs(x5).*1.930139973551579e-4+x5.*sign(x5).*1.930139973551579e-4,-1.0e1./1.1e1,0.0,0.0,0.0,(abs(x6).*cos(x2).*2.75394e-7+x6.*cos(x2).*sign(x6).*2.75394e-7)./(cos(x2).*sin(x2).*(-2.275267548000001e-3)+cos(x2).^2.*2.4959958411e-2+sin(x2).^2.*8.80136444e-4),abs(x6).*6.811120508171988e-6+x6.*sign(x6).*6.811120508171988e-6,0.0,-1.0e2./3.3e1],[6,6]);
A=Afunction(x2,0,0,x5,x6);
B=[      0         0;
         0         0;
         0         0;
         0         0;
   90.9091         0;
         0  218.0074];
     

%calculating descrete matrices using c2d and 'zoh'
Adisc=expm(A*h);
Aintegral=eye(6);
temp_term=1;
for i=1:20
    temp_term=temp_term*(A*h)/(i+1);
    Aintegral=Aintegral+temp_term;
end
Bdisc=Aintegral*h*B;

linearizationPoint_x=[x1,x2,0,0,x5,x6]';