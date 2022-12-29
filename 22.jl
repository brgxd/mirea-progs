include("lib.jl")

function to_sym!(robot, side)
    if isborder(robot, side)
        tolim!(robot, inverse(side))
    else
        move!(robot,side)
        to_sym!(robot, side)
        move!(robot,side)
    end
end

function toborder!(robot, side)
    if !isborder(robot, side)
        move!(robot,side)
        toborder!(robot, side)
    end
end