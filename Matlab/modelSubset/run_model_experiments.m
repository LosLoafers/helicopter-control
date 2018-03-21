%% run_model_experiments.m
% This script linearizes the system about an arbitrary point
% in the angular sate space and initializes the magic model for comparison.
%
% Implemented by Marcus Greiff for the project course in FRTN01/15 18-03-18
clear; close all;

% Linearize the model about an arbitrary point [phi, theta]
phi0  = 0;
theta0 = pi;
% Linearize the lodel
run('synthesize_model')

% Load the magic model
run('magic_model')

% Step time in the forward discretized nonlinenar model
dt = 0.0005;

%% Open and run the controller example
open('model_experiments.slx')
sim('model_experiments.slx')