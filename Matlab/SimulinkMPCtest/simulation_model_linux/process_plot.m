clear all
load('real_theta_ref.mat')
t=tid.data;
theta=xOut.data(:,2);
phi=xOut.data(:,1);
thetar=refOut.data(:,2);
phir=refOut.data(:,1);
subplot(2,1,2);
subplot(2,1,1);
plot(t,phi,'b')
hold on
plot(t,phir,'r')
title('Phi')

legend('Position angle','Reference angle')
ylabel('rad')
subplot(2,1,2);

plot(t,theta,'b')
hold on 
plot(t,thetar,'r')
title('Theta')
xlabel('Time (s)')
ylabel('rad')

u1_err=xOut.data(:,7);
u2_err=xOut.data(:,8);

figure
plot(t,u1_err,'b')
hold on
plot(t,u2_err,'r')
title('Loaddisturbance Estimates')
xlabel('Time (s)')
ylabel('Voltage')

%% real phi_ref
clear all
load('real_phi_ref.mat')
t=tid.data;
theta=xOut.data(:,2);
phi=xOut.data(:,1);
thetar=refOut.data(:,2);
phir=refOut.data(:,1);
subplot(2,1,2);
subplot(2,1,1);
plot(t,phi,'b')
hold on
plot(t,phir,'r')
title('Phi')

legend('Position angle','Reference angle')
ylabel('rad')
subplot(2,1,2);

plot(t,theta,'b')
hold on 
plot(t,thetar,'r')
title('Theta')
xlabel('Time (s)')
ylabel('rad')

u1_err=xOut.data(:,7);
u2_err=xOut.data(:,8);

figure
plot(t,u1_err,'b')
hold on
plot(t,u2_err,'r')
title('Loaddisturbance Estimates')
xlabel('Time (s)')
ylabel('Voltage')

%% real theta constraint
clear all
load('real_theta_constraint.mat')
t=tid.data;
theta=xOut.data(:,2);
phi=xOut.data(:,1);
thetar=refOut.data(:,2);
phir=refOut.data(:,1);
subplot(2,1,2);
subplot(2,1,1);
plot(t,phi,'b')
hold on
plot(t,phir,'r')
title('Phi')

legend('Position angle','Reference angle')
ylabel('rad')
subplot(2,1,2);

plot(t,theta,'b')
hold on 
plot(t,thetar,'r')
title('Theta')
xlabel('Time (s)')
ylabel('rad')

u1_err=xOut.data(:,7);
u2_err=xOut.data(:,8);

figure
plot(t,u1_err,'b')
hold on
plot(t,u2_err,'r')
title('Loaddisturbance Estimates')
xlabel('Time (s)')
ylabel('Voltage')