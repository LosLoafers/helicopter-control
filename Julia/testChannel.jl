c = Channel(2)
put!(c,0)

@async begin 
	while (true)
		if(isReady)
			take!(c)
		end
		put!(c,putValue)
	end
end

@async begin
	res = 0
	while(true)
		res = fetch(c)
		println("Result: " , res)
		if (count >= 20)
			break
		end
		count = count + 1
	end
end



