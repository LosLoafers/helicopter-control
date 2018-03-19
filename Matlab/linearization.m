function [A,B,Afunction]=linearization(x10,x20,x30,x40,x50,x60,u10,u20)
%constants
g=9.81;
l1=0.1995;
l2=0.1743;
ml=0.289;
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

syms x1 x2 x3 x4 x5 x6 f1 f2 f3 f4 u1 u2  
%x1=phi x2=d/dt phi x3=theta x4=d/dt theta x5=w1 x6=w2

%d/dt x1=x2
%d/dt x2=f1
%d/dt x3=x4
%d/dt x4=f2
%d/dt x5=f3
%d/dt x6=f4

f1=(2*cos(x3)*sin(x3)*x2*x4*JL-2*h*(sin(x3)^2-cos(x3)^2)*x2*x4*m*lc...
    -2*h^2*sin(x3)*cos(x3)*x2*x4*m+D1*x5*abs(x5)*cos(x3)...
    +l2*cos(x3)*C2*x6*abs(x6))/(cos(x3)^2*JL-2*h*cos(x3)*sin(x3)*m*lc+...
    h^2*sin(x3)^2*m+JA);


f1prime_x1=diff(f1,x1);
f1prime_x2=diff(f1,x2);
f1prime_x3=diff(f1,x3);
f1prime_x4=diff(f1,x4);
f1prime_x5=diff(f1,x5);
f1prime_x6=diff(f1,x6);

f2=(-cos(x3)*sin(x3)*x2^2*JL-h*(-sin(x3)^2+cos(x3)^2)*x2^2*m*lc...
    -g*cos(x3)*m*lc+h^2*sin(x3)*cos(x3)*x2^2*m+m*g*h*sin(x3)+l1*C1*x5*abs(x5)...
    +D2*x6*abs(x6))/(JL+h^2*m);

f2prime_x1=diff(f2,x1);
f2prime_x2=diff(f2,x2);
f2prime_x3=diff(f2,x3);
f2prime_x4=diff(f2,x4);
f2prime_x5=diff(f2,x5);
f2prime_x6=diff(f2,x6);

f3=-1/T1*x5+1/(T1*k1)*u1;

f3prime_x5=diff(f3,x5);
f3prime_u1=diff(f3,u1);


f4=-1/T2*x6+1/(T2*k2)*u2;


f4prime_x6=diff(f4,x6);
f4prime_u2=diff(f4,u2);

%lin point
% x10=0;
% x20=0;
% x30=pi/4;
% x40=0;
% x50=u10/k1;
% x60=u20/k2;
% u10=10;
% u20=10;

%A matrix
A=[0 1 0 0 0 0;
    f1prime_x1 f1prime_x2 f1prime_x3 f1prime_x4 f1prime_x5 f1prime_x6;
    0 0 0 1 0 0 ;
    f2prime_x1 f2prime_x2 f2prime_x3 f2prime_x4 f2prime_x5 f2prime_x6;
    0 0 0 0 f3prime_x5 0;
    0 0 0 0 0 f4prime_x6];

Afunction=matlabFunction(A);

A=Afunction(x20,x30,x40,x50,x60)


%B matrix
Bfunction=matlabFunction([0;0;0;0;f3prime_u1;f4prime_u2]);
B=Bfunction();
C=[1 0 1 0 0 0];
linSystem=ss(A,B,C,0)