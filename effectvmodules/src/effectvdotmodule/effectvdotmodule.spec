# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvdotemodule
{
    name          = DotTV
    deterministic = false
    group         = EffecTV
    static        = true
    xpm           = effectvdotmodule.xpm
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
        name              = Dunno
        type              = typ_NumberType
        const             = true
        strong_dependency = true 
        widget_type       = radio_button
        default           = 0
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
