# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvpuzzlemodule
{
    name          = Puzzle
    deterministic = false
    group         = EffecTV
    xpm           = effectvpuzzlemodule.xpm
    static        = true
    author        = ----
    version       = 1.0
}

inputs
{
    b
    {
        name              = Image
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = true
    }

    left
    {
        name              = Left
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
        name              = Right
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
        name              = Up
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
        name              = Down
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
        name = Image
        type = typ_FrameBufferType
    }
}
