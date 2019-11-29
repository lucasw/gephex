mod_num2env
{
    name          = Number->Env
    deterministic = true
    group         = Audio
    xpm           = numenvmodule.xpm
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
        default           = 1.0
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
    }

    attack
    {
        name              = Attack
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0.01
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
    }

    decay
    {
        name              = Decay
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0.01
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
    }

    sustain_level
    {
        name              = Sustain_Level
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 1.0
        lower_bound       = 0
        higher_bound      = 1.0
        step_size         = 0.01
    }

    release
    {
        name              = Release
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0.0
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
    }

}

outputs
{
    result
    {
        name = Env Control
        type = typ_EnvType
    }
}
