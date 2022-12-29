include("lib.jl")
function x2_move_till_border!(r,side)
    if !isborder(r,HorizonSide(side))
        move!(r,HorizonSide(side))
        x2_move_till_border!(r,side)
    else
        move_n_times!(r,inverse(side),2)
    end
end