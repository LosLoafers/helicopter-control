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
subplot(2,1,2);

plot(t,theta,'b')
hold on 
plot(t,thetar,'r')
title('Theta')
%%
t=tid.data;
u1_err=xOut.data(:,7);
u2_err=xOut.data(:,8);


plot(t,u1_err,'b')
hold on
plot(t,uy2_err,'r')