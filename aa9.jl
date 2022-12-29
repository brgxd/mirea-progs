using HorizonSideRobots
include("lib.jl")

function chess_line!(r,direct)
    while !isborder(r,HorizonSide(direct))
        move!(r,HorizonSide(direct))
        if trymove!(r,direct)
            putmarker!(r)
        end
    end
end

function num9!(r)
    global num_steps_x = 0
    global num_steps_y = 0
    countx!(r)
    county!(r)
    if mod(num_steps_y,2) != mod(num_steps_x,2)
        move!(r,HorizonSide(3))
    end
    putmarker!(r)
    direct = 3
    while !isborder(r,HorizonSide(2))
        chess_line!(r,direct)
        if !ismarker(r)
            move!(r,HorizonSide(2))
        else
            move!(r,HorizonSide(2))
            move!(r,HorizonSide(inverse(direct)))
        end
        putmarker!(r)
        direct = inverse(direct)
    end
    chess_line!(r,1)
    move_till_border!(r,1)
    move_till_border!(r,0)
    goback!(r)
end