using HorizonSideRobots
inverse(side) = (mod(Int(side)+2, 4))
rotate_l(side) = (mod(Int(side)+1,4))
rotate_r(side) = (mod(Int(side)+3,4))

function trymove!(r,direct)::Bool
    if isborder(r,HorizonSide(direct))==false
        move!(r,HorizonSide(direct))
        return true
    else
        return false
    end
end

function move_till_border!(r,direct)
    while isborder(r,HorizonSide(direct))==false
        move!(r,HorizonSide(direct))
    end
end

function mark_till_border!(r,direct)
    while isborder(r,HorizonSide(direct))==false
        trymove!(r,direct)
        putmarker!(r)
    end
end

function count_till_border!(r,direct)::Int64
    num = 0
    while !isborder(r,HorizonSide(direct))
        move!(r,HorizonSide(direct))
        num += 1
    end
    return num
end

function move_along_border!(r,direct,border_direct)
    while isborder(r,HorizonSide(border_direct))
        trymove!(r,direct)
    end
end

function count_along_border!(r,direct,border_direct)::Int64
    n = 0
    while isborder(r,HorizonSide(border_direct))
        move!(r,HorizonSide(direct))
        n += 1
    end
    return n
end

function mark_along_border!(r,direct,border_direct)
    while isborder(r,HorizonSide(border_direct))
        putmarker!(r)
        trymove!(r,direct)
    end
end

function move_n_times!(r,direct,n)
    for _ in 1:n
        trymove!(r,direct)
    end
end

function mark_n_times!(r,direct,n)
    for _ in 1:n
        if isborder(r,HorizonSide(direct))
            putmarker!(r)
            break
        else
            move!(r,HorizonSide(direct))
            putmarker!(r)
        end
    end
end

function return_by_markers!(r,direct)
    while isborder(r,HorizonSide(direct))==false
        if ismarker(r)==true
            move!(r,HorizonSide(direct))
        end
    end
end

function move_by_markers!(r,direct)    
    if ismarker(r)
        trymove!(r,direct)
    end
end

function countx!(r)
    while isborder(r,HorizonSide(1))==false
        move!(r,HorizonSide(1))
        global num_steps_x += 1
    end
end

function county!(r)
    while isborder(r,HorizonSide(0))==false
        move!(r,HorizonSide(0))
        global num_steps_y += 1
    end
end

function goback!(r)
    move_n_times!(r,3,num_steps_x)
    move_n_times!(r,2,num_steps_y)
end

function count!(r)
    while !isborder(r,HorizonSide(1))
        move!(r,HorizonSide(1))
        global num_steps_x += 1
    end
    while !isborder(r,HorizonSide(0))
        move!(r,HorizonSide(0))
        global num_steps_y += 1
    end
    while !isborder(r,HorizonSide(1))
        move!(r,HorizonSide(1))
        global num_steps_x2 += 1
    end
end

function goback_barier!(r)
    move_n_times!(r,3,num_steps_x2)
    move_n_times!(r,2,num_steps_y)
    move_n_times!(r,3,num_steps_x)
end

function go_around_border!(r,direct)
    x = 0
    while isborder(r,HorizonSide(direct))
        x = count_along_border!(r,rotate_r(direct),direct)
    end
    move!(r,HorizonSide(direct))
    while isborder(r,HorizonSide(rotate_l(direct)))
        move_along_border!(r,direct,rotate_l(direct))
    end
    move_n_times!(r,rotate_l(direct),x)
end