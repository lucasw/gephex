# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvfiremodule
{
    name          = Fire
    deterministic = false
    group         = EffecTV
    static        = true
    xpm           = effectvfiremodule.xpm
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

    bg
    {
        name              = Background
        type              = typ_NumberType
        const             = true
        strong_dependency = true 
        widget_type       = radio_button
        default           = 0
    }

    mode
    {
        name              = Mode
        type              = typ_StringType
        const             = true
        strong_dependency = true 
        hidden            = true
        widget_type       = combo_box
        default           = foreground
        values            = foreground,light,dark
        help              = burn foreground, light part or dark part
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
