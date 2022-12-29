include("lib.jl")
n = 3
function try_move_n_times!(r,direct)::Bool
    x = 0
    for _ in range(1,n)
        if trymove!(r,direct)
            x += 1
        end
    end
    if x != n
        move_n_times!(r,inverse(direct),x)
        return false
    else
        return true
    end
end

function fill_square!(r,direct)
    x = 0
    while x < n
        putmarker!(r)
        mark_n_times!(r,direct,n-1)
        x = x + 1
        if x < n
            trymove!(r,0)
            putmarker!(r)
            mark_n_times!(r,inverse(direct),n-1)
            x = x + 1
        end
        trymove!(r,0)
    end
    if !ismarker(r)
        move!(r,HorizonSide(2))
    end
    move_by_markers!(r,direct)
    move_n_times!(r,2,2)
end

function square_chess_line!(r,direct)
    fill_square!(r,direct)
    while try_move_n_times!(r,direct)
        fill_square!(r,direct)
    end
end

function dim(r)::Int64
    x = 0
    while try_move_n_times!(r,0)
        x += 1
    end
    move_till_border!(r,2)
    return x
end

function mm(r)
    direct = 1
    try_move_n_times!(r,inverse(direct))
    square_chess_line!(r,direct)
    x -= 1
end



function m(r)
    direct = 1
    move_n_times!(r,direct,n)
    square_chess_line!(r,direct)
end

function mmm(r)
    direct = 1
    move_n_times!(r,0,n)
    move_n_times!(r,direct,n)
    square_chess_line!(r,direct)
end

