# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvlifemodule
{
    name          = Life
    deterministic = false
    group         = EffecTV
    xpm           = effectvlifemodule.xpm
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
        name              = kill_cells
        type              = typ_NumberType
        const             = true
        strong_dependency = true 
        default           = 0
        widget_type       = radio_button
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
