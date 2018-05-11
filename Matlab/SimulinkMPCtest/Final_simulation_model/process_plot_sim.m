%% plot sim theta_ref
clear all
load('sim_theta_ref.mat')
load('tid.mat','tid')
t=tid.data(1:end-4);
tr=linspace(1,100,5001);
theta=xOut.data(:,2);
phi=xOut.data(:,1);
thetar=refOut.data(:,2);
phir=refOut.data(:,1);

subplot(2,1,2);
subplot(2,1,1);
plot(t,phi,'b')
hold on
plot(tr,phir,'r')
title('Phi')
legend('Position angle','Reference angle')
ylabel('rad')
subplot(2,1,2);

plot(t,theta,'b')
hold on 
plot(tr,thetar,'r')
title('Theta')
xlabel('Time (s)')
ylabel('rad')

%loaddist
u1_err=xOut.data(:,7);
u2_err=xOut.data(:,8);

figure
plot(t,u1_err,'b')
hold on
plot(t,u2_err,'r')
title('Loaddisturbance Estimates')
xlabel('Time (s)')
ylabel('Voltage')

%% plot sim phi_ref
clear all
load('sim_phi_ref.mat')
load('tid.mat','tid')
t=tid.data(1:end-4);
tr=linspace(1,100,5001);
theta=xOut.data(:,2);
phi=xOut.data(:,1);
thetar=refOut.data(:,2);
phir=refOut.data(:,1);

subplot(2,1,2);
subplot(2,1,1);
plot(t,phi,'b')
hold on
plot(tr,phir,'r')
title('Phi')
legend('Position angle','Reference angle')
ylabel('rad')
subplot(2,1,2);

plot(t,theta,'b')
hold on 
plot(tr,thetar,'r')
title('Theta')
xlabel('Time (s)')
ylabel('rad')

%loaddist
u1_err=xOut.data(:,7);
u2_err=xOut.data(:,8);

figure
plot(t,u1_err,'b')
hold on
plot(t,u2_err,'r')
title('Loaddisturbance Estimates')
xlabel('Time (s)')
ylabel('Voltage')

%% plot sim theta_constraint
clear all
load('sim_theta_constraint.mat')
load('tid.mat','tid')
t=tid.data(1:end-4);
tr=linspace(1,100,5001);
theta=xOut.data(:,2);
phi=xOut.data(:,1);
thetar=refOut.data(:,2);
phir=refOut.data(:,1);

subplot(2,1,2);
subplot(2,1,1);
plot(t,phi,'b')
hold on
plot(tr,phir,'r')
title('Phi')
legend('Position angle','Reference angle')
ylabel('rad')
subplot(2,1,2);

plot(t,theta,'b')
hold on 
plot(tr,thetar,'r')
title('Theta')
xlabel('Time (s)')
ylabel('rad')

%loaddist
u1_err=xOut.data(:,7);
u2_err=xOut.data(:,8);

figure
plot(t,u1_err,'b')
hold on
plot(t,u2_err,'r')
title('Loaddisturbance Estimates')
xlabel('Time (s)')
ylabel('Voltage')