# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectv1dmodule
{
    name          = 1d
    deterministic = false
    group         = EffecTV
    xpm           = effectv1dmodule.xpm
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
    doublebuff
    {
        name              = DoubleBuff
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
