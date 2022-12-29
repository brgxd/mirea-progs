using HorizonSideRobots
include("lib.jl")
function fill_snake!(r,direct)
    mark_till_border!(r,direct+1)
    trymove!(r,direct)
    putmarker!(r)
    mark_till_border!(r,inverse(direct+1))
    trymove!(r,direct)
    putmarker!(r)
end
function num3!(r)
    global num_steps_x = 0
    global num_steps_y = 0
    countx!(r)
    county!(r)
    while !isborder(r,HorizonSide(2))
        fill_snake!(r,2)
    end
    mark_till_border!(r,3)
    move_till_border!(r,1)
    move_till_border!(r,0)
    putmarker!(r)
    goback!(r)
end