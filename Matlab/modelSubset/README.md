Update 2018-03-18.

This is a revised model of the ETH helicopter in Gafverts report. The
strange 10-dimensional model used in previous project is referred to as the
"magic model", and was found using Matlabs black box modelling tootlbox.
This model, used in priorprojects, can be compared to the system response
of gafverts model in linear/nonlinear continuous/discrete time by running
"run_model_experiments". The "magic model" seems unphysical, and 
I cannot explain why it would possible work. The linearized models tend to
be unstable and blow up in finite time if left to their own devicing, and
the non-linear models exhibit the expected limit cycles when after the
initial impuse, being marginally stable due to the conservation of energy.

When linearizing the gafvert model about an arbitrary point in the statespace
and syntheizing the an LQR feedback law for the linearized model,
the nonlinear models can be controlled nicely to the a reference. To see
this run "run_control_experiments.m". Note that the "theta" angle need to
be controlled in the positive direction for this method to be feasible.

In this repository, you will find all five referencesmodels + the script I
wrote for linearizing the dynamics. However, the files for synthesizing and
exemplifying LQR control have been removed.

Best,
Marcus