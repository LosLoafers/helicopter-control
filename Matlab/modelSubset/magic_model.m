% This is a discrete-time LTI approximation of the ETH helicopter
% at a stable point x^0, u^0, discretized at h=0.05, where
%
%     x(k+1) = Phi * x(k) + Gamma * u(k)
%     y(k)   =   C * x(k)
%
% The model parameters in  in the report by g?fvert are used, and the
% stationary point is taken as for a given elevation angle, and the
% and unforced equilibrium point theta0 \in [-pi/2,pi/2].

Phi = [3.111 0.429 1 0 0 0 0 0 0 0;
    0.08268 2.794 0 1 0 0 0 0 0 0;
    -3.182 -0.9092 0 0 1 0 0 0 0 0;
    -0.2245 -2.631 0 0 0 1 0 0 0 0;
    0.8211 0.3671 0 0 0 0 1 0 0 0;
    0.1541 0.8153 0 0 0 0 0 1 0 0;
    0.455 0.2896 0 0 0 0 0 0 1 0;
    0.02951 0.06612 0 0 0 0 0 0 0 1;
    -0.2051 -0.1762 0 0 0 0 0 0 0 0;
    -0.04261 -0.04461 0 0 0 0 0 0 0 0;
    ];

Gamma = [0.0008364 -0.0004057;
    0.0008679 -0.0001901;
    0.0009015 -0.0009729;
    0.0006347 -0.00009547;
    0.001133 0.002063;
    -0.002024 0.0000549;
    -0.001292 -0.0003008;
    0.0003297 -0.0003316;
    0 0;
    0 0;
   ];

C = [1 0 0 0 0 0 0 0 0 0;
    0 1 0 0 0 0 0 0 0 0];

D = [0 0;
    0 0];

% sample time [s]:
h = 0.05;