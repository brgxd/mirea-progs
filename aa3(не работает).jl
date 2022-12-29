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
function return_snake_by_markers!(r,direct)
    return_by_markers!(r,inverse(direct+1))
    trymove!(r,direct)
    return_by_markers!(r,direct+1)
end
function fill_if_border!(r,side)
    mark_till_border!(r,side+1)
    while isborder(r,HorizonSide(side))==false
        fill_snake!(r,side)
    end
    while ismarker(r)==true
        return_snake_by_markers!(r,inverse(side))
    end
    putmarker!(r)
end
function fill!(r,side)
    while isborder(r,HorizonSide(side))==false
        fill_snake!(r,side)
    end
    mark_till_border!(r,1)
    mark_till_border!(r,3)
    while ismarker(r)==true
        return_snake_by_markers!(r,inverse(side))
    end
end
if isborder(r,HorizonSide(0))==true
    mark_till_border!(r,3)
    fill_if_border!(r,2)
elseif isborder(r,HorizonSide(2))==true
    mark_till_border!(r,1)
    fill_if_border!(r,0)
else
    mark_till_border!(r,1)
    return_by_markers!(r,3)
    mark_till_border!(r,3)
    return_by_markers!(r,1)
    fill!(r,0)
    fill!(r,2)
end