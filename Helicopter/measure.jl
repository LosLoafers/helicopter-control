using LabProcesses

heli = ETHHelicopter()
u1=zeros(1,100)
u2=zeros(1,100)
for i=1:100
	y=measure(heli)	
	u1[i]=y[1]/10*175/180*pi
	u2[i]=y[2]/10*59/180*pi
	sleep(0.1)
end
u = [u1;u2]
println(cov(u'))
