# Wandelt Positionen in Zahlen um

mod_pos2num
{
    name          = Position->X,Y
    deterministic = true
    group         = Position
    xpm           = posnummodule.xpm
    author        = Barbie&Ken
    version       = 0.0.1
}

inputs
{
    pos
    {
        name              = Position
        type              = typ_PositionType
        const             = true
        strong_dependency = true
        default           = [0.5 0.5]
    }
}

outputs
{
    xresult
    {
        name = X-Position
        type = typ_NumberType
    }

    yresult
    {
        name = Y-Position
        type = typ_NumberType
    }
}
