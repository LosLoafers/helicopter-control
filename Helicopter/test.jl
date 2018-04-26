#push!(LOAD_PATH, "~/PredictiveProject/helicopter-control/Helicopter/LabProcesses.jl-master/src/LabConnections.jl")
using LabProcesses

prinln("Starting...")
P=LabProcesses.ETHHelicopter
println(P)
prinln("Got here")
y=measure(P)
println(y)
prinln("And here")
