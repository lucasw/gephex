# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvrevmodule
{
    name          = Rev
    deterministic = false
    group         = EffecTV
    xpm           = effectvrevmodule.xpm
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
    vgrabtime
    {
        name              = VGrabTime
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	hidden            = true
	lower_bound       = 1
	higher_bound      = 255
	default           = 1
	precision         = 0
	display_format    = fixed
    }
    linespace
    {
        name              = LineSpace
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	hidden            = true
	lower_bound       = 1
	higher_bound      = 255
	default           = 6
	precision         = 0
	display_format    = fixed
    }
    vscale
    {
        name              = VScale
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	hidden            = true
	lower_bound       = 1
	higher_bound      = 255
	default           = 25
	precision         = 0
	display_format    = fixed
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
