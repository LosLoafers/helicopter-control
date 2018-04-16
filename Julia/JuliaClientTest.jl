client = connect(2000);
phi = 30
theta = 44
refPhi = 33
refTheta = 40
iter = 0
while(true)
    if iter == 10
        phi = -phi
        theta = -theta
        refPhi = -refPhi
        refTheta = -refTheta
        iter = 0
    end
    println(client,"$phi/$theta/$refPhi/$refTheta")
    sleep(0.5)
    iter = iter + 1
end
