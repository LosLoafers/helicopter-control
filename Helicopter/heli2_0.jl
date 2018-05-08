include("Kalman.jl")
include("cvx.jl")
using LabProcesses

Choppah=ETHHelicopter()

client = connect("130.235.83.11",2018)

#---------------global variables------------------------------------------------
#(Asystem,Bsystem,LinearizationPoint_x,LinearizationPoint_u)=linearDescreteModelGen(0,0,0.02)
x_hat=[0;-0.93;0;0;0;0;0;0] #estimated states
u=[0.0 0.0]' #control signal
u_temp=[0.0 0.0]'
y=[0.0 0.0]' #measurement signal
P=100*eye(8) #covariance matrix
const ampref = [0.0; 0.0]
const period = 15 #seconds
#--------------------------------------------------------------------------------
#client = connect(2001)

#set up thread channels:
global u_remote = u_temp
global x_remote = x_hat
global we_should_run = true
Lu=ReentrantLock()
Lx=ReentrantLock()




kalman=@spawn begin
	global we_should_run
	global u_remote
	global x_remote

	while we_should_run
				@periodically Ts_kalman begin
						y_temp=measure(Choppah)
						y[2]=y_temp[1]/10*59/180*pi
						y[1]=y_temp[2]/10*175/180*pi

						lock(Lu)
				    u=u_remote;
				    unlock(Lu)

						(x_hat,P)=updateKalman(x_hat,u,y,P)

						lock(Lx)
				    x_remote=x_hat;
				    unlock(Lx)
				end

		end
end


MPC=@spawn begin
	i=0
	global we_should_run
	global u_remote
	global x_remote
	while we_should_run
				@periodically Ts_control begin
						i=i+1
						lock(Lx)
				    x_hat=x_remote;
						unlock(Lx)

						u_temp=cvxsolve(x_hat,ref)
						u[1]=sat(u_temp[1])
						u[2]=-sat(u_temp[2])

						if i>100
							control(Choppah,u)
							lock(Lu)
					    u_remote=u_temp;
					    unlock(Lu)
						else
							control(Choppah,[0.0 0.0]')
							lock(Lu)
					    u_remote=[0.0 0.0]'
					    unlock(Lu)
						end

						if y[1]<-160/180*pi || y[1]>160/180*pi ||y[2]>0.7
							control(Choppah,[0.0 0.0]')
							we_should_run=false

						end
				end

		end
end
