a=2.5
b=2.5

x=ccall((:cvxsolve,"$(pwd())/libcvx"),Float64,(Float64,Float64),a,b)
println(x)

