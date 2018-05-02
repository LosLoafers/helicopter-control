server =  listen(2001)
while
    socket = accept(server)
    println("Connection established.")
    while isopen(socket)
        println(readuntil(socket,";") , " was received from client.")
    end
    break
end
close(server)
println("server closed.")
