# Number to color module, converts numbers to colors

mod_number2colormodule
{
    name          = Colour from RGB
    deterministic = true
    group         = Colour
    xpm           = number2colormodule.xpm
    author        = coma
    version       = 0.65-pregammaalphabetaficken
}

inputs
{
    r
    {
        name              = Red
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
        default           = 0.5
    }

    g
    {
        name              = Green
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
        default           = 0.5
    }

    b
    {
        name              = Blue
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
        default           = 0.5
    }
}

outputs
{
    color
    {
        name = Colour
        type = typ_RGBType
    }
}
