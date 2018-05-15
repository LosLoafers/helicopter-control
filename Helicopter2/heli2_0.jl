#stäng av regulatorn genom att skriva: @everywhere we_should_run=false

@everywhere include("Kalman.jl")
@everywhere include("cvx.jl")
@everywhere using LabProcesses

@everywhere Choppah=ETHHelicopter()

#@everywhere client = connect("130.235.83.11",2018)

#---------------global variables------------------------------------------------
@everywhere x_hat=[0.0 -0.95 0.0 0.0 0.0 0.0 0.0 0.0]'
@everywhere u=[0.0 0.0]' #control signal
@everywhere u_temp=[0.0 0.0]'
@everywhere y=[0.0 0.0]' #measurement signal
@everywhere P=100*eye(8) #covariance matrix
@everywhere we_should_run=true
#--------------------------------------------------------------------------------


#set up channels and mutex:
xchannel=RemoteChannel(()->Channel{Tuple}(2));
uchannel=RemoteChannel(()->Channel{Tuple}(2));

Lock_u=ReentrantLock()
Lock_x=ReentrantLock()

#----------------------kalman Loop-----------------------------------------------
kalman=@spawnat 1 begin

put!(xchannel,(x_hat[1],x_hat[2],x_hat[3],x_hat[4],x_hat[5],x_hat[6],x_hat[7],x_hat[8]))
put!(uchannel,(u[1],u[2]))


	while we_should_run
				@periodically Ts_kalman begin
						y_temp=measure(Choppah)
						y[2]=y_temp[1]/10*59/180*pi
						y[1]=y_temp[2]/10*175/180*pi

						lock(Lock_u)
							if isready(uchannel)
								u[1],u[2]=take!(uchannel)
							end
						unlock(Lock_u)

						(x_hat,P)=updateKalman(x_hat,u,y,P)

						lock(Lock_x)
				      while isready(xchannel) #empty channel. only last result should be stored
				        take!(xchannel)
				      end
				      put!(xchannel,(x_hat[1],x_hat[2],x_hat[3],x_hat[4],x_hat[5],x_hat[6],x_hat[7],x_hat[8]))
				    unlock(Lock_x)
				end

		end
end

#----------------------MPC Loop-----------------------------------------------
MPC=@spawnat 2 begin
	i=0
	put!(xchannel,(x_hat[1],x_hat[2],x_hat[3],x_hat[4],x_hat[5],x_hat[6],x_hat[7],x_hat[8]))
	put!(uchannel,(u[1],u[2]))
	while we_should_run
				@periodically Ts_control begin
						i=i+1
						lock(Lock_x)
				      if isready(xchannel)
				        x_hat[1],x_hat[2],x_hat[3],x_hat[4],x_hat[5],x_hat[6],x_hat[7],x_hat[8]=take!(xchannel)
				      end
				    unlock(Lock_x)

						u_temp=cvxsolve(x_hat,[0;0])
						u[1]=sat(u_temp[1])
						u[2]=-sat(u_temp[2])

						if i>100
							control(Choppah,u)

							lock(Lock_u)
					      while isready(uchannel) #empty channel. only last result should be stored
					        take!(uchannel)
					      end
					      put!(uchannel,(u_temp[1],u_temp[2]))
					    unlock(Lock_u)

						else

							control(Choppah,[0.0 0.0]')

							lock(Lock_u)
					      while isready(uchannel) #empty channel. only last result should be stored
					        take!(uchannel)
					      end
					      put!(uchannel,(0.0,0.0))
					    unlock(Lock_u)

						end

						if y[1]<-160/180*pi || y[1]>160/180*pi ||y[2]>0.7
							control(Choppah,[0.0 0.0]')
							@everywhere we_should_run=false

						end
				end

		end
		control(Choppah,[0.0 0.0]') # if we_should_run is set to false in terminal
end
