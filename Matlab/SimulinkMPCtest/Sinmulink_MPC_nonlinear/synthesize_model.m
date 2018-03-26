%% syntheize_model.m
% This script linearizes the ETH helicopter model in G?fverts report
% about an arbitrary point [phi,theta] with zero velocities and
% accelerations. The model is then parametrized using values in the same
% report, and then discretized.
%
% Implemented by Marcus Greiff for the project course in FRTN01/15 18-03-18

%% State vector
syms ph th dph dth w1 w2 real
x = [ph th dph dth w1 w2]';

%% control signal vector
syms u1 u2 real
u = [u1 u2];

%% Parameters
syms l1 l2 Jl Ja h lc m k1 k2 C1 C2 D1 D2 T1 T2 g real

%% Pre-computation of angles
cth = cos(th);
sth = sin(th);

%% Integration model
ddph = (cth^2*Jl - 2*h*cth*sth*m*lc + h^2*sth^2*m + Ja)\...
       (2*cth*sth*dph*dth*Jl - 2*h*(sth^2-cth^2)*dph*dth*m*lc - ...
	2*h^2*sth*cth*dph*dth*m + D1*w1*abs(w1)*cth + l2*cth*C2*w2*abs(w2));
ddth = (Jl + h^2*m)\...
       (-cth*sth*dph^2*Jl - h*(-sth^2+cth^2)*dph^2*m*lc - g*cth*m*lc ...
	+ h^2*sth*cth*dph^2*m + m*g*h*sth + l1*C1*w1*abs(w1) + D2*w2*abs(w2));
dw1 = -w1/T1 + u1/(k1*T1);
dw2 = -w2/T2 + u2/(k2*T2);

f = [dph, dth, ddph, ddth, dw1, dw2]';

%% COmputation of jacobians
pfpx = jacobian(f, x);
pfpu = jacobian(f, u);

%% Parameters
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

%% test
ddph = (cth^2*Jl - 2*h*cth*sth*m*lc + h^2*sth^2*m + Ja)\...
       (2*cth*sth*dph*dth*Jl - 2*h*(sth^2-cth^2)*dph*dth*m*lc - ...
	2*h^2*sth*cth*dph*dth*m + D1*w1*abs(w1)*cth + l2*cth*C2*w2*abs(w2));
ddth = (Jl + h^2*m)\...
       (-cth*sth*dph^2*Jl - h*(-sth^2+cth^2)*dph^2*m*lc - g*cth*m*lc ...
	+ h^2*sth*cth*dph^2*m + m*g*h*sth + l1*C1*w1*abs(w1) + D2*w2*abs(w2));
dw1 = -w1/T1 + u1/(k1*T1);
dw2 = -w2/T2 + u2/(k2*T2);





%% Compute point of linearization
if isempty(phi0) && isempty(theta0)
    % Nominal value
    ph = -2;
    th = 1;
else
    % Value set in LQR synthisis
    ph = phi0;
    th = theta0;
end

% Set all derivative terms to zero
dph = 0;
dth = 0;
ddph = 0;
ddth = 0;
dw1 = 0;
dw2 = 0;

% Evaluarte and solve F the equation symbolically
evaluatedF = eval(eval(f));
solution = solve(evaluatedF, [w1, w2, u1, u2]);

% Extract the point of linearization
x0 = eval([ph,th,0,0,solution.w1,solution.w2]');
u0 = eval([solution.u1,solution.u2]');
w1 = solution.w1;
w2 = solution.w2;
u1 = solution.u1;
u2 = solution.u2;

%% Evalue the system dynamics at the point of linearization 
A = eval(eval(pfpx));
B = eval(pfpu);
C = [eye(2), zeros(2,4)];
D = zeros(2,2);
% sverres point 

%% Discretize the continuous time system
%Ts = 0.05;
sysCont = ss(A,B,C,D);
sysDisc = c2d(sysCont, Ts);
[A,B,C,D]=ssdata(sysDisc);
