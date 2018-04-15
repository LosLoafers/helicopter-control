#Source: https://gitlab.control.lth.se/processes/LabProcesses.jl/blob/master/src/utilities.jl

macro periodically(h, body)
	quote
		local start_time = time()
		$(esc(body))
		local execution_time = time()-start_time
		#Libc.systemsleep(max(0,$(esc(h))-execution_time))
        sleep(max(0,$(esc(h))-execution_time))
	end
end

#Above code taken from the LabProcesses.jl repository on gitLab written by
#Fredrik Bagge Carlsson.

channel = Channel(10)
# channel2 = Channel(11)
put!(channel,"Initial value")
@async begin
    #first process
    server =  listen(2001)
    println("Server started.")
    while true
        println("Listening for new connection.")
        socket = accept(server)
        println("Connection established.")
        while isopen(socket)
            #println(readuntil(socket,";") , " was received from client.")
            #res = readuntil(socket,";")
            #print(res , "skrivet av server \n")
            #set_res(readuntil(socket,";"))
            res = readuntil(socket,";")
            if res == ""
                println("Connection terminated by client")
                break
            end
            put!(channel,res[1:length(res) - 1])
            #take!(channel)
        end
    end
    close(server)
    println("server closed.")
end

# Second process to demonstrate that we can do 2 things "at the same time."
# x = 1
# @async begin
#     while true
#         #print("Round: " , x , "\n")
#         #x = x + 1
#         put!(channel2,take!(channel))
#         #sleep(1)   #sleep 1 second
#     end
# end

#control loop simulation
# @async begin
#     ref = "Initial value"
#     itr = 1
#     while true
#         if isready(channel)
#             ref = take!(channel)
#             println("New ref set to: " , ref)
#         end
#         println("control loop iteration: " , itr , " , current ref: " , ref)
#         itr = itr + 1
#         sleep(1)
#     end
# end



#periodical control loop simulation
@async begin
    h = 1
    ref = ""
    itr = 1
    while true
		@time @periodically h begin
            if isready(channel)
                ref = take!(channel)
                println("New ref set to: " , ref)
            end
            println("control loop iteration: " , itr , " , current ref: " , ref)
            itr = itr + 1
        end
    end
end
