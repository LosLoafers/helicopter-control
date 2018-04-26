include("Kalman.jl")
include("cvx.jl")

#Periodical macro
macro periodically(h,body)
	quote
		local start_time = time()
		$(esc(body))
		local execution_time = time()-start_time
		sleep(max(0,$esc(h))-execution_time())
	end
end

#---------------global variables------------------------------------------------
x_hat=[0;-pi/4;0;0;0;0;0;0] #estimated states
u=[0 0]' #control signal
y=[0 0]' #measurement signal
P=eye(8) #covariance matrix
const ampref = [0.3;0.3] #radians
const period = 10 #seconds
#--------------------------------------------------------------------------------
#client = connect(2001)
i=0
ref=ampref

#@periodically Ts_kalman begin
#	while true
#		i=i+1
#		if i == period/Ts_kalman
#			if ref[0] == 0
#				ref=ampref
#			end
#			else
#				ref=[0;0]
#			end
#			i=0
#		end
		u=cvxsolve(x_hat,ref)
		println(u)
		#analog.out(u)
		#theta = analog.inT()
		#(x_hat,p)=updateKalman(x_hat,u,y,p)
		#javastring="$x_hat[1]/$x_hat[2]/$ref[1]/ref[2];"   #sending protocol
		#println(client,javastring)	#send to java
#	end
#end


