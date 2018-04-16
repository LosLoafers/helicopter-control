include("Kalman.jl")
include("cvx.jl")

#---------------global variables------------------------------------------------
x_hat=[0;-pi/4;0;0;0;0;0;0] #estimated states
u=[0 0]' #control signal
y=[0 0]' #measurement signal
P=eye(8) #covariance matrix
#--------------------------------------------------------------------------------

#dessa två funktionerna är de enda som behövs i main
#exempel på användning ->
    #(x_hat,p)=updateKalman(x_hat,u,y,p)
    #(x_hat,p)=updateKalman([1 2 3 4 5 6 7 8]',[1 1]',[1 2]',100*eye(8))
    #u=cvxsolve(x_hat,ref)
ref=[1;1]
@time begin
	for i=1:10000
     		#u=cvxsolve(x_hat,ref)
		(x_hat,p)=updateKalman([1 2 3 4 5 6 7 8]',[1 1]',[1 2]',100*eye(8))
	end
end
