# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvquarkmodule
{
    name          = QuarkTV
    deterministic = false
    group         = EffecTV
    xpm           = effectvquarkmodule.xpm
    author        = ----
    version       = 1.0
	static        = true
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
