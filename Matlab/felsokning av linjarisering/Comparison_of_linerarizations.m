%% marcus Parameters
% Weights
ml = 0.280;  % [kg]
m1 = 0.3792; % [kg]
m2 = 0.1739; % [kg]
mw = 0.158;  % [kg]
m  = ml + m1 + m2 + mw; % [kg] (eq. 24)
% Distances
l1 = 0.1995; % [m]
l2 = 0.1743; % [m]
lw = 0.090;  % [m]
h  = 0.0298; % [m]
lc = (m1*(l1-l2)+m1*l1-m2*l2-mw*lw)/m; % [m] (eq. 27)
% Inertial parameters
g = 9.81; % [m/s^2]
Ja = 0; % [] (eq. 26)
Jl = (ml/3)*((l1^3+l2^3)/(l1+l2))+m1*l1^2+m2*l2^2+mw*lw^2; % [] (eq. 25)
% Time, motor and aerodynamics constants
k1 = 1.00e-2; % [Vs/rad]
k2 = 1.39e-2; % [Vs/rad]
C1 = 2.50e-5; % [Ns^/rad^2]
C2 = 1.58e-6; % [Ns^/rad^2]
D1 = 2.90e-7; % [Nms^/rad^2]
D2 = 1.76e-7; % [Nms^/rad^2]
T1 = 1.10;    % [s]
T2 = 0.33;    % [s]

%% sverres constants (checked no diffrence.)
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

%% calculation of state equations
syms ph th dph dth w1 w2 real
x = [ph th dph dth w1 w2]';

%control signal vector
syms u1 u2 real
u = [u1 u2];

% Parameters


% Pre-computation of angles
cth = cos(th);
sth = sin(th);

% Integration model
ddph = (cth^2*Jl - 2*h*cth*sth*m*lc + h^2*sth^2*m + Ja)\...
       (2*cth*sth*dph*dth*Jl - 2*h*(sth^2-cth^2)*dph*dth*m*lc - ...
	2*h^2*sth*cth*dph*dth*m + D1*w1*abs(w1)*cth + l2*cth*C2*w2*abs(w2));
ddth = (Jl + h^2*m)\...
       (-cth*sth*dph^2*Jl - h*(-sth^2+cth^2)*dph^2*m*lc - g*cth*m*lc ...
	+ h^2*sth*cth*dph^2*m + m*g*h*sth + l1*C1*w1*abs(w1) + D2*w2*abs(w2));
dw1 = -w1/T1 + u1/(k1*T1);
dw2 = -w2/T2 + u2/(k2*T2);

f = [dph, dth, ddph, ddth, dw1, dw2]';


Anonlin=matlabFunction(f); %the nonlinear state equations returned as a function
%marcus point
  x1=  0;
 x2=        0;
  x3=       0;
  x4=       0;
 x5= 288.2586;
 x6=-295.8040;
 u1=k1*x5;
 u2=k2*x6;
 
 %sverres point
 

         x1=0;
         x2=0;
         x3=0;
         x4=0;
         x5=279.2602;
         x6=-286.5701;
         u1=k1*x5;
         u2=k2*x6;
Anonlin(x3,x4,x2,u1,u2,x5,x6)


%% sverres calc of state equations
%nonlinearmodel
%d/dt x1=x3
%d/dt x2=x4
%d/dt x3=f1
%d/dt x4=f2
%d/dt x5=f3
%d/dt x6=f4
syms x1 x2 x3 x4 x5 x6 f1 f2 f3 f4 u1 u2 Asym

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

f=[x3;x4;f1;f2;f3;f4];
Anonlin=matlabFunction(f); %the nonlinear state equations returned as a function
%marcus point
  x1=  0;
 x2=        0;
  x3=       0;
  x4=       0;
 x5= 288.2586;
 x6=-295.8040;
 u1=k1*x5;
 u2=k2*x6;
 
 %sverres point
 

         x1=0;
         x2=0;
         x3=0;
         x4=0;
         x5=279.2602;
         x6=-286.5701;
         u1=k1*x5;
         u2=k2*x6;
         
Anonlin(u1,u2,x2,x3,x4,x5,x6)


