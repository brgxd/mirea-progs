using HorizonSideRobots
include("lib.jl")
function num7!(r)
    n = 1
    while isborder(r,HorizonSide(0))==true
        move_n_times!(r,1,n)
        n += 1
        move_n_times!(r,3,n)
    end
end