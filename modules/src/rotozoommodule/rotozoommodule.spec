# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_rotozoommodule
{
    name           = Rotozoom
    deterministic  = true
    group          = Effects
    xpm            = rotozoommodule.xpm
    author         = Miss Piggy
    version        = 0.0
    enablePatching = true
}

inputs
{
    zoom
    {
        name              = Zoom
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 8
        step_size         = 0.04
        default           = 1
    }

    rot
    {
        name              = Rotation
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        lower_bound       = -180
        higher_bound      = 180
        step_size         = 1
        default           = 0
    }

    disp
    {
        name              = Translation
        type              = typ_PositionType
        const             = true
        default           = [0.5 0.5]
        strong_dependency = true
    }

    texture
    {
        name              = Texture
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = true
    }

    background
    {
        name              = Background
        type              = typ_FrameBufferType
        const             = false
        strong_dependency = false
        help              = The background image
    }

    copy_background
    {
        name              = Copy_Background
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = radio_button
        true_value        = 1
        false_value       = 0
        default           = 1
        help              = Should background be copied or modified?
    }

    routine
    {
        name              = Mode
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = combo_box
        values            = regular,poly,mirror
        default           = regular
        help              = regular is stable, poly is faster
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


