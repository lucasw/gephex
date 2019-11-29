mod_num2lfo
{
    name          = num->lfo-Params
    deterministic = true
    group         = Audio
    xpm           = numlfomodule.xpm
    author        = Kecke Koksnase
    version       = 0.0.1
}

inputs
{
    amount
    {
        name              = Amount
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0.5
        lower_bound       = 0
        higher_bound      = 100
        step_size         = 0.01
    }

    frequ
    {
        name              = Frequency
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0.5
        lower_bound       = 0
        higher_bound      = 50
        step_size         = 0.01
    }
}

outputs
{
    result
    {
        name = Lfo-Parameter
        type = typ_LfoType
    }
}
