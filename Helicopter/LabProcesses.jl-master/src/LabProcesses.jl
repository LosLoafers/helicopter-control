__precompile__()
installed_packages = Pkg.installed()
if "LabConnections" ∉ keys(installed_packages)
	#Pkg.clone("https://gitlab.control.lth.se/cont-frb/LabConnections.jl")
	#Pkg.checkout("LabConnection","v0.0.1")
end


module LabProcesses

using ControlSystems, LabConnections.Computer, Parameters

include("utilities.jl")

include("interface.jl")
include("interface_documentation.jl")
include("interface_implementations/ballandbeam.jl")
include("interface_implementations/eth_helicopter.jl")

include("reference_generators.jl")
include("controllers.jl")

end # module

