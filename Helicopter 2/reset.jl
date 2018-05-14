using LabProcesses

P = ETHHelicopter()

control(P,[0.0 0.0])

#@spawnat 2 control(P,[0.0 0.0])

