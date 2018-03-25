function xdot=GafvertsModelFunction(x)
% x=[u1,u2,phi, theta, dphi,dtheta,w1,w2]';
% xdot=[phi, theta, dphi,dtheta,w1,w2]'

%this function is 
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

u1=x(1);
u2=x(2);
x1=x(3);
x2=x(4);
x3=x(5);
x4=x(6);
x5=x(7);
x6=x(8);


%the folowing notation is used:
%x1=phi x2=theta x3=d/dt(phi) x4=d/dt(theta) x5=w1 x6=w2

%nonlinearmodel
%d/dt x1=x3
%d/dt x2=x4
%d/dt x3=f1
%d/dt x4=f2
%d/dt x5=f3
%d/dt x6=f4

%define f1
f1=(2*cos(x2)*sin(x2)*x3*x4*JL-2*h*(sin(x2)^2-cos(x2)^2)*x3*x4*m*lc...
    -2*h^2*sin(x2)*cos(x2)*x3*x4*m+D1*x5*abs(x5)*cos(x2)...
    +l2*cos(x2)*C2*x6*abs(x6))/(cos(x2)^2*JL-2*h*cos(x2)*sin(x2)*m*lc+...
    h^2*sin(x2)^2*m+JA);
%define f2
f2=(-cos(x2)*sin(x2)*x3^2*JL-h*(-sin(x2)^2+cos(x2)^2)*x3^2*m*lc...
    -g*cos(x2)*m*lc+h^2*sin(x2)*cos(x2)*x3^2*m+m*g*h*sin(x2)+l1*C1*x5*abs(x5)...
    +D2*x6*abs(x6))/(JL+h^2*m);

%define f3
f3=-1/T1*x5+1/(T1*k1)*u1;

%define f4
f4=-1/T2*x6+1/(T2*k2)*u2;

xdot=[x3;x4;f1;f2;f3;f4];