# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvpuzzlemodule
{
    name          = Puzzle
    deterministic = false
    group         = EffecTV
    xpm           = effectvpuzzlemodule.xpm
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

    left
    {
        name              = Links
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	default           = 0
        widget_type       = radio_button
        true_value        = 1
	false_value       = 0 
    }

    right
    {
        name              = Rechts
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	default           = 0
        widget_type       = radio_button
        true_value        = 1
	false_value       = 0
    }

    up
    {
        name              = Hoch
        type              = typ_NumberType
        const             = true
        strong_dependency = true 
	default           = 0
        widget_type       = radio_button
        true_value        = 1
	false_value       = 0
    }

    down
    {
        name              = Runter
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
