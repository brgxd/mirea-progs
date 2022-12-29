using HorizonSideRobots
include("lib.jl")
function cross_goback!(r,direct_x,direct_y)
    if ismarker(r)==true
        move!(r,HorizonSide(inverse(direct_x)))
        move!(r,HorizonSide(inverse(direct_y)))
    end
end
function cross_line!(r,direct_x,direct_y)
    while isborder(r,HorizonSide(direct_x))==false && isborder(r,HorizonSide(direct_y))==false
        move!(r,HorizonSide(direct_x))
        move!(r,HorizonSide(direct_y))
        putmarker!(r)
    end
    while ismarker(r)==true
        cross_goback!(r,direct_x,direct_y)
    end
end
function cross!(r)
    cross_line!(r,1,0)
    cross_line!(r,1,2)
    cross_line!(r,3,0)
    cross_line!(r,3,2)
end
function num4!(r)
    cross!(r)
    putmarker!(r)
end