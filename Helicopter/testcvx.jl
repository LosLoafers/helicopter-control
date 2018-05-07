include("Kalman.jl")
include("cvx.jl")

x_hat=[1.0;2.0;3.0;4.0;5.0;6.0;7.0;8.0]
#x_hat=zeros(8,1)
ref=[0.0;0.0]
u=cvxsolve(x_hat,ref)
println(u)
