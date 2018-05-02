
using LabProcesses

#macro periodically(h,body)
#	quote
#		local start_time = time()
#		$(esc(body))
#		local execution_time = time()-start_time
#		sleepTime=max(0,$esc(h))-execution_time()
#		println("SleepTime: " , sleepTime)
#		sleep(sleepTime)
#	end
##end

y=[0 0]
P=ETHHelicopter()

while true
	@periodically 1 begin
		y=measure(P)	
		y[2]=y[1]/9*59/180*pi
		y[1]=y[2]/10*175/180*pi
		println(y)
	end
end
