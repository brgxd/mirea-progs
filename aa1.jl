using HorizonSideRobots
r=Robot(animate=true)
inverse(side::HorizonSide)::HorizonSide = HorizonSide(mod(Int(side)+2, 4))
function markedline!(r::Robot,direct)
    while isborder(r,HorizonSide(direct))==false
        move!(r,HorizonSide(direct))
        putmarker!(r)
    end
    while ismarker(r)==true
        move!(r,inverse(HorizonSide(direct)))
    end
end 
function num1!(r)
    for n in range(0,3)
        markedline!(r,n)
    end
    putmarker!(r)
end