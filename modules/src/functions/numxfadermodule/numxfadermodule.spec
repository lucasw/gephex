# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_numxfademodule
{
    name          = Number Crossfader
    deterministic = true
    group         = Number
    xpm           = numxfadermodule.xpm
    author        = Don Bosco
    version       = 0.65-pregamma
}

inputs
{
    x
    {
        name              = Fader
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
		lower_value       = 0
		higher_value      = 1
		step_size         = 0.01
        default           = 0
    }

    1
    {
        name              = Signal_1
        type              = typ_NumberType
        const             = true
        strong_dependency = false
        widget_type       = unboundednumber_selector
        default           = 0
    }

    2
    {
        name              = Signal_2
        type              = typ_NumberType
        const             = true
        strong_dependency = false
        widget_type       = unboundednumber_selector
        default           = 0
    }
}

outputs
{
    r
    {
        name = Mix_Signal
        type = typ_NumberType
    }
}
