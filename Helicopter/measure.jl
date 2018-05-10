using LabProcesses

heli = ETHHelicopter()
u=0
for i=1:100
	y=measure(heli)
	u=u+y[1]
	sleep(0.1)
end
println(u/100)
