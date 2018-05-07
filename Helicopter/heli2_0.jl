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
xchannel=RemoteChannel(()->Channel{Int}(32))
uchannel=RemoteChannel(()->Channel{Int}(32))
x=0
put!(xchannel,x)

u=0
put!(uchannel,u)
Su=ReentrantLock()
Sx=ReentrantLock()


i=0
we_should_run=true

kalman=@spawn begin
	while we_should_run
				@periodically Ts_kalman begin
						y_temp=measure(Choppah)
						y[2]=y_temp[1]/10*59/180*pi
						y[1]=y_temp[2]/10*175/180*pi

						lock(Su)
				    if isready(uchannel)
				      u=take!(uchannel)
				    end
				    unlock(Su)

						(x_hat,P)=updateKalman(x_hat,u,y,P)

						lock(Sx)
				    while isready(xchannel)
				      take!(xchannel)  				#empty xchannel
				    end
				    put!(xchannel,x)
				    unlock(Sx)
				end

		end
end


MPC=@spawn begin
	while we_should_run
				@periodically Ts_control begin
						i=i+1
						lock(Sx)
				    if isready(xchannel)
				      xhat=take!(xchannel)
				    end
						unlock(Sx)

						u_temp=cvxsolve(x_hat,ref)
						u[1]=sat(u_temp[1])
						u[2]=-sat(u_temp[2])
						if i>100
							control(Choppah,u)
						else
							control(Choppah,[0.0 0.0]')
						end

						lock(Su)
				    while isready(uchannel)
				      take!(uchannel)         #empty uchannel
				    end
				    put!(uchannel,u)
				    unlock(Su)
						
						if y[1]<-160/180*pi || y[1]>160/180*pi
							control(Choppah,[0.0 0.0]')
							we_should_run=false

						end
				end

		end
end
