# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvscrollmodule
{
    name          = Scroll
    deterministic = false
    group         = EffecTV
    xpm           = effectvscrollmodule.xpm
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
}

outputs
{
    r
    {
        name = Image
        type = typ_FrameBufferType
    }
}
