using LabProcesses

println("Starting...")
Choppah=ETHHelicopter()
y_temp=[0.0 0.0]
y=[0.0 0.0]
println("Got here")
for i=0:100
	y_temp=measure(Choppah)
	y[2]=y_temp[1]/10*59/180*pi
	y[1]=y_temp[2]/10*175/180*pi
	println(y)
	sleep(1)
end
println("And here")
