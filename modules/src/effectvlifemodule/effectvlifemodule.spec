# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvlifemodule
{
    name          = Life
    deterministic = false
    group         = EffecTV
    xpm           = effectvlifemodule.xpm
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

    bg
    {
        name              = Zellen_loeschen
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
    name = Bild
    type = typ_FrameBufferType
    }
}
