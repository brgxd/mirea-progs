include("lib.jl")

function count_border_horiz!(r,side)::Int64
    while isborder(r,HorizonSide(2))
        move!(r,HorizonSide(side))
    end
    return 1
end

function count_borders_horiz!(r,side)::Int64
    x = 0
    while !isborder(r,HorizonSide(side))
        if isborder(r,HorizonSide(2))
            x = x + count_border_horiz!(r,side)
        end
        trymove!(r,side)
    end
    return x
end

function num11!(r)
    side = 3
    total_borders = 0
    global num_steps_x = 0
    global num_steps_y = 0
    countx!(r)
    county!(r)
    while !isborder(r,HorizonSide(2))
        total_borders += count_borders_horiz!(r,side)
        move!(r,HorizonSide(2))
        side = inverse(side)
    end
    move_till_border!(r,1)
    move_till_border!(r,0)
    move_n_times!(r,2,num_steps_y)
    move_n_times!(r,3,num_steps_x)
    return total_borders
end
