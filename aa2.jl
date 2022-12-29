using HorizonSideRobots
stepsx = 0
stepsy = 0
function goback!(r)
    for _ in 1:stepsx
        move!(r,HorizonSide(1))
    end
    for _ in 1:stepsy
        move!(r,HorizonSide(0))
    end
end
function countx!(r::Robot,direct)
    while isborder(r,HorizonSide(direct))==false
        move!(r,HorizonSide(direct))
        global stepsx += 1
    end
end
function county!(r::Robot,direct)
    while isborder(r,HorizonSide(direct))==false
        move!(r,HorizonSide(direct))
        global stepsy += 1
    end
end
function frame(r,direct)
    while isborder(r,HorizonSide(direct))==false
        putmarker!(r)
        move!(r,HorizonSide(direct))
    end
end
function num2!(r)
    countx!(r,3)
    county!(r,2)
    for n in range(0,3)
        frame(r,n)
    end
    goback!(r)
end