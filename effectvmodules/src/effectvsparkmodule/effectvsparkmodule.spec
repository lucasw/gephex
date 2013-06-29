# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvsparkmodule
{
    name          = SparkTV
    deterministic = false
    group         = EffecTV
    xpm           = effectvsparkmodule.xpm
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

    bg
    {
        name              = Background
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
