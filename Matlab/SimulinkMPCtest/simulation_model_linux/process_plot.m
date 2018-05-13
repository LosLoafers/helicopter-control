%% theta ref
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
%ylim([0,0.6])
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
load('real_phi_ref_2.mat')
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
ylim([-0.7,0.6])
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
load('real_theta_constraint_2.mat')
t=tid.data;
theta=xOut.data(:,2);
phi=xOut.data(:,1);
thetar=refOut.data(:,2);
phir=refOut.data(:,1);
constr=0.2*ones(size(t));
subplot(2,1,2);
subplot(2,1,1);
plot(t,phi,'b')
hold on
plot(t,phir,'r')
title('Phi')
plot(1,0.5,'g')
legend('Position angle','Reference angle','Constraint')
ylabel('rad')
subplot(2,1,2);

plot(t,theta,'b')
hold on 
plot(t,thetar,'r')
plot(t,constr,'g')
title('Theta')
xlabel('Time (s)')
ylabel('rad')
ylim([-1 0.6])
u1_err=xOut.data(:,7);
u2_err=xOut.data(:,8);

figure
plot(t,u1_err,'b')
hold on
plot(t,u2_err,'r')
title('Loaddisturbance Estimates')
xlabel('Time (s)')
ylabel('Voltage')