# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvlensmodule
{
    name          = Lens
    deterministic = false
    group         = EffecTV
    xpm           = effectvlensmodule.xpm
    author        = ----
    version       = 1.0
}

inputs
{
    b
    {
        name              = Bild
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = true
    }

    pos
    {
        name              = Linsenposition
        type              = typ_PositionType
        const             = true
        strong_dependency = true
        default           = [0.5 0.5]
    }

    size
    {
        name              = Linsengroesse
        type              = typ_NumberType
        const             = true
        strong_dependency = true 
	default           = 150
        lower_bound       = 10
        higher_bound      = 500
        widget_type       = unboundednumber_selector
    }

    mag
    {
        name              = Vergroesserung
        type              = typ_NumberType
        const             = true
        strong_dependency = true 
	default           = 30
        lower_bound       = 5
        higher_bound      = 200
        widget_type       = unboundednumber_selector
    }

    interactive
    {
        name              = Interaktiv
        type              = typ_NumberType
        const             = true
        strong_dependency = true 
	default           = 0
        widget_type       = radio_button
        true_value        = 1
	false_value       = 0
    }
}

outputs
{
    r
    {
    name = Bild
    type = typ_FrameBufferType
    }
}
