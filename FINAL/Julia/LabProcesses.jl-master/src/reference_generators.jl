export PRBSGenerator

#PRBS
"""
    r = PRBSGenerator()
Generates a pseudo-random binary sequence. Call like `random_input = r()`.
"""
mutable struct PRBSGenerator
    state::Int
end

PRBSGenerator() = PRBSGenerator(Int(1))

function (r::PRBSGenerator)(args...)
    state = r.state
    bit   = ((state >> 0) ⊻ (state >> 2) ⊻ (state >> 3) ⊻ (state >> 5) ) & 1
    r.state = (state >> 1) | (bit << 15)
    bit
end
