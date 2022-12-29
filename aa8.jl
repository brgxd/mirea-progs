using HorizonSideRobots
function move_if_nomarker!(r,direct)
    if !ismarker(r)
        move!(r,HorizonSide(direct))
    end
end
function move_n_times!(r,direct,n)
    for _ in 1:n
        move_if_nomarker!(r,direct)
    end
end
function num8!(r)
    n = 0
    while !ismarker(r)
        n += 1
        move_n_times!(r,0,n)
        move_n_times!(r,1,n)
        n += 1
        move_n_times!(r,2,n)
        move_n_times!(r,3,n)
    end
end