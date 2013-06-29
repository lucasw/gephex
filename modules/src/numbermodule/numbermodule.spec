# Das ist die Spezifikation fuer das Number Modul. Blabla

mod_numbermodule
{
    name          = Random
    deterministic = false
    group         = Number
    xpm           = numbermodule_icon.xpm
    author        = Duran Duran
    version       = 0.65-prealpha
}

inputs
{
    tpf
    {
        name              = Feedback
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
        default           = 0
        hidden            = true    
    }

    min
    {
        name              = min
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0
        hidden            = true
        widget_type       = unboundednumber_selector
    }

    max
    {
        name              = max
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 1
        hidden            = true
        widget_type       = unboundednumber_selector
    }
}

outputs
{
    r
    {
        name = RandomNumber
        type = typ_NumberType
    }
}
