client = connect("127.0.1.1", 2018);
phi = 30
theta = 44
refPhi = 33
refTheta = 40
iter = 0
while(true)
    if iter == 100
        phi = -phi
        theta = -theta
        refPhi = -refPhi
        refTheta = -refTheta
        iter = 0
    end
    println(client,"$phi/$theta/$refPhi/$refTheta")
    sleep(0.01)
    iter = iter + 1
end
