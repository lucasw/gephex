# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvburnmodule
{
    name          = Burn
    deterministic = false
    group         = EffecTV
    xpm           = effectvburnmodule.xpm
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
        name              = Hintergrund_uebernehmen
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
    name = Bild
    type = typ_FrameBufferType
    }
}
