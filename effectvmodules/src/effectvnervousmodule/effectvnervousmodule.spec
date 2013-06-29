# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvnervousmodule
{
    name          = Nervous
    deterministic = false
    group         = EffecTV
    xpm           = effectvnervousmodule.xpm
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
    mode
    {
        name              = Mode
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
