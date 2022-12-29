include("lib.jl")
function mark_border!(r,side)
    if isborder(r,HorizonSide(side))
        putmarker!(r)
    else
        move!(r,HorizonSide(side))
        mark_border!(r,side)
        move!(r,HorizonSide(inverse(side)))
    end
end