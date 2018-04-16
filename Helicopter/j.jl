a=0.8;


x=zeros(1,6)

x[1] = 0.20319161029830202;
x[2] = 0.8325912904724193;
x[3] = -0.8363810443482227;
x[4] = 0.04331042079065206;
x[5] = 1.5717878173906188;
x[6] = 1.5851723557337523;
b=ccall((:mpc,"./libcvx"),Ptr{Float64},(Float64,Ptr{Float64}),a,x)

u = [unsafe_load(b,1) unsafe_load(b,2)]
println(u)
#Ptr{Cdouble}
