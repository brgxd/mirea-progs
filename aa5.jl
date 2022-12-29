using HorizonSideRobots
include("lib.jl")

function frame!(r)
    for n in (2,3,0,1)
        mark_till_border!(r,n)
    end
end

function find_border!(r)
    side = 3
    while !isborder(r,HorizonSide(2))
        while !isborder(r,HorizonSide(side)) && !isborder(r,HorizonSide(2))
            move!(r,HorizonSide(side))
        end
        trymove!(r,2)
        side = Int64(inverse(side))
    end
    if side == 1
        move_along_border!(r,3,2)
        move!(r,HorizonSide(1))
    end
end

function frame_border!(r)
    for side in (2,3,0,1)
        while isborder(r,HorizonSide(side))
            mark_along_border!(r,rotate_r(side),side)
        end
        move!(r,HorizonSide(side))
    end
end

function num5!(r)
    global num_steps_x = 0
    global num_steps_y = 0
    global num_steps_x2 = 0
    count!(r)
    frame!(r)
    find_border!(r)
    frame_border!(r)
    move_till_border!(r,0)
    move_till_border!(r,1)
    goback_barier!(r)
end