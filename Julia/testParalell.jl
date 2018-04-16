#Start Julia with at least 2 processes when running this file.

KalmanIter = 0
ControlIter = 0

# Kalman loop

while(true)
	r = remoteCall(waitTime,1,0.005,KalmanIter)

end


#Controller loop





function waitTime(time2wait, iter)
	wait(time2wait);
	iter + 1   #return value
end

