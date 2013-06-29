# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvnoisemodule
{
    name          = Noise
    deterministic = false
    group         = EffecTV
    xpm           = effectvnoisemodule.xpm
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
        name              = Bg
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	hidden            = true
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
