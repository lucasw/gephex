# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvedgemodule
{
    name          = Edge
    deterministic = true
    group         = EffecTV
    xpm           = effectvedgemodule.xpm
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
}

outputs
{
    r
    {
    name = Bild
    type = typ_FrameBufferType
    }
}
