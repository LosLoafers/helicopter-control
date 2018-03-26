function X = testlin(ph,th,dth,dph,w1,w2)
%UNTITLED8 Summary of this function goes here
%   Detailed explanation goes here
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
Ja = 0;   % [] (eq. 26)
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
%% sverres constants




%% Pre-computation of angles and extraction of states
cth = cos(th);
sth = sin(th);
u1 = w1*k1;
u2 = w2*k2;


ddph = (cth^2*Jl - 2*h*cth*sth*m*lc + h^2*sth^2*m + Ja)\...
       (2*cth*sth*dph*dth*Jl - 2*h*(sth^2-cth^2)*dph*dth*m*lc - ...
	2*h^2*sth*cth*dph*dth*m + D1*w1*abs(w1)*cth + l2*cth*C2*w2*abs(w2));
ddth = (Jl + h^2*m)\...
       (-cth*sth*dph^2*Jl - h*(-sth^2+cth^2)*dph^2*m*lc - g*cth*m*lc ...
	+ h^2*sth*cth*dph^2*m + m*g*h*sth + l1*C1*w1*abs(w1) + D2*w2*abs(w2));
dw1 = -w1/T1 + u1/(k1*T1);
dw2 = -w2/T2 + u2/(k2*T2);
X=[ dph,dth,ddph,ddth,dw1,dw2];
end

