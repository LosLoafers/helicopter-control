client = connect("127.0.1.1", 2018);
phi = 30
theta = 44
refPhi = 33
refTheta = 40
u1=4
u2=3
iter = 0
while(true)
    if iter == 100
        phi = -phi
        theta = -theta
        refPhi = -refPhi
        refTheta = -refTheta
        u1 = 10-u1
        u2 = 10-u2
        iter = 0
    end
    println(client,"$phi/$theta/$refPhi/$refTheta/$u1/$u2")
    sleep(0.01)
    iter = iter + 1
end
