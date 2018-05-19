@everywhere	include("cvx.jl")
@everywhere	include("Kalman.jl")


@everywhere using LabProcesses
@everywhere Choppah=ETHHelicopter()

#---------------global variables------------------------------------------------
@everywhere x_hat=[0.0 -0.95 0.0 0.0 0.0 0.0 0.0 0.0]'
@everywhere u=[0.0 0.0]' #control signal
@everywhere u_temp=[0.0 0.0]'
@everywhere const ampref = [0.0; -0.7]
@everywhere const period = 15 #seconds
@everywhere wsr = true
@everywhere y=[0.0 0.0]' #measurement signal
@everywhere P=100*eye(8) #covariance matrix
#--------------------------------------------------------------------------------

#set up thread channels:

u_channel=RemoteChannel(()->Channel{Any}(1))
x_channel=RemoteChannel(()->Channel{Any}(1))
put!(u_channel,u)
put!(x_channel,x_hat)



@spawnat 2 begin
	client = connect("130.235.83.11",2018)
	i=0
	k=0
	ref = [0.0 -0.7]'
	while wsr
		@periodically Ts_control begin
			x_hat=fetch(x_channel)
			u_temp=cvxsolve(x_hat,ref)  #fix ref change later.
			u[1]=sat(u_temp[1])
			u[2]=-sat(u_temp[2])
			if i>100
				control(Choppah,u)
				take!(u_channel)
				put!(u_channel,u_temp)
			else
				i=i+1
				control(Choppah,[0.0 0.0]')
				take!(u_channel)
				put!(u_channel,[0.0 0.0]')
			end
			println(client,x_hat[1],"/",x_hat[2],"/",ref[1],"/",ref[2],"/",u_temp[1],"/",u_temp[2])	
		#	if y[1]<-160/180*pi || y[1]>160/180*pi ||y[2]>0.7
		#		control(Choppah,[0.0 0.0]')
		#		@everywhere wsr = false
		#	end
			k = k+1
			if k == period/Ts_control
				if ref[1] == 0.0 && ref[2]==0.0
					ref=ampref
				else
					ref=[0.0;0.0]
				end
				k=0
			end
		end
	end
		#Add we should run in last if statement.
		control(Choppah,[0.0 0.0]') # if we_should_run is set to false in terminal
end

@spawnat 3 begin
global x_hat,P
while wsr
	@periodically Ts_kalman begin
		#@time begin
		y_temp=measure(Choppah)
		y[2]=y_temp[1]/10*59/180*pi
		y[1]=y_temp[2]/10*175/180*pi
		u=fetch(u_channel)
		(x_hat,P)=updateKalman(x_hat,u,y,P)
		take!(x_channel)	#empty channel before putting
		put!(x_channel,x_hat)
		#end
	end
end
end

#stop = readline()

#put something in channel and use isready on it in workers to put wsr to false so they quit.
