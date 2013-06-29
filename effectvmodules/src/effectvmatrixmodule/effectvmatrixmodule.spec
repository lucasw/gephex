# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvmatrixmodule
{
    name          = Matrix
    deterministic = false
    group         = EffecTV
    xpm           = effectvmatrixmodule.xpm
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
	hidden            = true
	widget_type       = radio_button
    }

    space
    {
        name              = Space
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
