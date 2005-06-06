# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvpredatormodule
{
    name          = Holo
    deterministic = false
    group         = EffecTV
    xpm           = effectvpredatormodule.xpm
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
