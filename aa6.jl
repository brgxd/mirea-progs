include("lib.jl")
include("aa2.jl")
function count_xy!(r)
    x = 0
    y = 0
    while !isborder(r,HorizonSide(0)) || !isborder(r,HorizonSide(1))
        x += count_till_border!(r,1)
        y += count_till_border!(r,0)
    end
    return x,y
end

function returnx!(r,req_x)
    move_n_times!(r,3,req_x)
end

function count_y_around_border!(r,direct)::Int64
    x = 0
    y = 0
    while isborder(r,HorizonSide(direct))
        x = count_along_border!(r,rotate_r(direct),direct)
    end
    move!(r,HorizonSide(direct))
    while isborder(r,HorizonSide(rotate_l(direct)))
        y = count_along_border!(r,direct,rotate_l(direct))
    end
    move_n_times!(r,rotate_l(direct),x)
    y += 1
    return y
end

function returny!(r,req_y)
    y = 0
    while y != req_y
        if !trymove!(r,2)
            y += count_y_around_border!(r,2)
        else
            y += 1
        end
    end
end

function num6_a!(r)
    req_x,req_y = count_xy!(r)
    for n in (2,3,0,1)
        frame(r,n)
    end
    returnx!(r,req_x)
    returny!(r,req_y)
end

function num6_b!(r)
    req_x,req_y = count_xy!(r)
    for n in (2,3,0,1)
        move_till_border!(r,n)
        putmarker!(r)
    end
    returnx!(r,req_x)
    returny!(r,req_y)
end