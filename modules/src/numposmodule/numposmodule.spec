mod_num2pos
{
    name          = X+Y->Position
    deterministic = true
    group         = Position
    xpm           = numposmodule.xpm
    author        = Kecke Koksnase
    version       = 0.0.1
}

inputs
{
    xpos
    {
        name              = X-Position
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0.5
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
    }

    ypos
    {
        name              = Y-Position
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0.5
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
    }
}

outputs
{
    result
    {
        name = Result-Position
        type = typ_PositionType
    }
}
