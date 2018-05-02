include("Kalman.jl")
include("cvx.jl")
using LabProcesses

Choppah=ETHHelicopter()

client = connect("130.235.83.11",2018)

#---------------global variables------------------------------------------------
#(Asystem,Bsystem,LinearizationPoint_x,LinearizationPoint_u)=linearDescreteModelGen(0,0,0.02)
x_hat=[0;-0.985;0;0;0;0;0;0] #estimated states
u=[0.0 0.0]' #control signal
u_temp=[0.0 0.0]'
y=[0.0 0.0]' #measurement signal
P=100*eye(8) #covariance matrix
const ampref = [0;0] #radians
const period = 10 #seconds
#--------------------------------------------------------------------------------
#client = connect(2001)

ref=ampref

i=0
j=0
while true

	@periodically Ts_kalman begin
		@time begin
			i=i+1
			
			if i == period/Ts_kalman
				if ref[1] == 0.0 && ref[2]==0.0
					ref=ampref
				else
					ref=[0.0;0.0]
				end
				i=0
			end
			
			y_temp=measure(Choppah)
			y[2]=y_temp[1]/10*59/180*pi
			y[1]=y_temp[2]/10*175/180*pi
			#println("y1: " , y[1])
			#println("y2: " , y[2])
			(x_hat,P)=updateKalman(x_hat,u_temp,y,P)

			j=j+1		
			if j==2
				j=0	
				u_temp=cvxsolve(x_hat,ref)
				u[1]=sat(u_temp[1])
				u[2]=-sat(u_temp[2])
				
				#println("u1: " , u[1])
				#println("u2: " , u[2])
				control(Choppah,u)
				#println("xhat: " , x_hat)
				#println("y: " , y)
							   					println(client,x_hat[1],"/",x_hat[2],"/",x_hat[7],"/",x_hat[8],"/",u_temp[1],"/",u_temp[2])
	#println("load2: " , x_hat[8])
			end
			if y[1]<-160/180*pi || y[1]>160/180*pi
				 control(Choppah,[0.0 0.0]')
				break;
			end
		end
	end
end


