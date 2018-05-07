% Denna fil är mest tänkt som ett test av CVXgen 

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

%någon random punkt
u10=10;
u20=10;
x10=0;
x20=0;
x30=pi/4;
x40=0;
x50=u10/k1;
x60=u20/k2;

%samplingstid
h=0.1;
[Asystem,Bsystem,LinearizationPoint_x,LinearizationPoint_u]=linearDiscreteModelGen(0,0,Ts_control);


%setup opt problem
global Asystem;
global Bsystem;
global Ts_control;
global umaxglobal;
global uminglobal;
global Qglobal;
global Rglobal;
global reference;
global LinearizationPoint_x;
global LinearizationPoint_u;
global phi_max;
global phi_min;
global theta_min;
global theta_max;
%setup opt problem

%blockingfactor 2 in x and u 
% Bsystem=(Asystem*Bsystem+Bsystem);
% Asystem=Asystem*Asystem;

%parameters

params.x_0=[LinearizationPoint_x;0;0];
params.A=[Asystem,Bsystem;zeros(2,6),eye(2)];
params.B=[Bsystem;zeros(2,2)];
params.Q=Qglobal;
params.R=Rglobal;
params.u_max=umaxglobal-LinearizationPoint_u;
params.u_min=uminglobal-LinearizationPoint_u;

params.phi_max=phi_max-LinearizationPoint_x(1);
params.phi_min=phi_min-LinearizationPoint_x(1);
params.theta_min=theta_min-LinearizationPoint_x(2);
params.theta_max=theta_max-LinearizationPoint_x(2);


% Create a new settings structure. Just some example
% copied from the cvx homepage:
settings.verbose = 1;  % disable output of solver progress.
 settings.max_iters = 100;  % reduce the maximum iteration count, from 25.
% settings.eps = 0.1;  % reduce the required objective tolerance, from 1e-6.
% settings.resid_tol = 1e-2;  % reduce the required residual tolerances, from 1e-4.
r=zeros(1,17);
for i=1:17 
    
    params.r{i}=i*[0,0.1,0,0,0,0,0,0]'-[LinearizationPoint_x;0;0];
    
    r(i)=params.r{i}(2)+LinearizationPoint_x(2);
end
% Create a new settings structure, with some example settings.
% settings.verbose = 0;  % disable output of solver progress.
% settings.max_iters = 10;  % reduce the maximum iteration count, from 25.
% settings.eps = 0.1;  % reduce the required objective tolerance, from 1e-6.
% settings.resid_tol = 1e-2;  % reduce the required residual tolerances, from 1e-4.

% solve
[vars, status] = csolve(params, settings);
u=vars.u;
x=vars.x;
x3=x{1}(3);
theta=zeros(1,17);
uu=zeros(2,17);
for i=1:17
    theta(i)=x{i}(2)+LinearizationPoint_x(2);
    uu(:,i)=vars.u{i}+LinearizationPoint_u;
end
plot(theta)
hold on
plot(r)
legend('th','r')
figure
plot(uu')