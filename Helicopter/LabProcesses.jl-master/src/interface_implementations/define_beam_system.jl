using ControlSystems

"""
    beammodel, beamcontroller = define_beam_system(;doplot=false)

Return a continuous time model of the beam (`::StateSpace`) and a feedback controller that
gives ϕₘ = 56°, Aₘ = 4, Mₛ = 1.6.
Don't forget to discretize both before use. Call this method with
doplot = true to display a bunch of plots to convince yourself.

The numbers in the code have been selected based on the fra performed and reported in
`beamdetails.pdf`
"""
function define_beam_system(;doplot=false)
    K  = 5    # gain of internal velocity control
    I1 = 1    # intertia of motor mass
    I2 = 1    # inertia of beam
    C  = 5    # beam flexibility
    D  = 0.1  # beam damping
    T  = 0.01 # motor torque time constant
    E  = 1    # motor viscous damping

    # transfer function from input signal to motor position
    G1 = 2*tf([I2, D, C]*K,conv([T, 1],conv([I1, (D+E), C],[I2, D, C]) - [0; 0; conv([D, C],[D, C])]) + K*[0, 0, I2, D, C, 0])

    G2 = 2*tf([D, C]*K,conv([T, 1],conv([I1, (D+E), C],[I2, D, C]) - [0; 0; conv([D, C],[D, C])]) + K*[0, 0, I2, D, C, 0])
    # pzmap(G1)
    # bodeplot([G1,G2], logspace(-2,3,500))

    # Above model is super inaccurate and I have no idea where it comes from, let's define
    # a simple but more accurate model // Bagge

    G1 = zpk([-145],[0, -60, -100], 4.5*60*100/145)
    ωz = 145
    ζz = 0.01
    ωp = 150
    ζp = 0.005
    G1 *= tf([1,2ζz*ωz, ωz^2]*ωp^2, [1,2ζp*ωp, ωp^2]*ωz^2)


    sysFBc = ss(zpk([], [-40, -40], 2*40*40)) # Controller suggesten in assistant manual, works fine =)
    # gives ϕₘ = 56°, Aₘ = 4, Mₛ = 1.6. Don't forget to discretize it before use. Call this method with
    # doplot = true to display a bunch of plots to convince yourself
    if doplot
        ControlSystems.setPlotScale("log10")
        bodeplot(tf(G1), logspace(0,log10(200),300))
        bodeplot([tf(G1), sysFBc*G1], logspace(0,log10(200),300))
        marginplot(sysFBc*tf(G1))
        gangoffourplot(tf(G1), tf(sysFBc))
    end
    ss(G1), sysFBc
end
