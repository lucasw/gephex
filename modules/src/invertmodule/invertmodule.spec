# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_invertmodule
{
    name          = Inverter
    deterministic = true
    group         = Filter
    xpm           = invertmodule.xpm
    author        = TheMadman
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

    routine
    {
        name              = Fade-Routine
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = combo_box
        values            = regular,mmx
        default           = regular
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
