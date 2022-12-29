function toborder!(r,side)
    while !isborder(r,HorizonSide(side))
        move!(r,HorizonSide(side))
        toborder!(r,side)
    end
end