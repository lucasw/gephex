# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvtransformmodule
{
    name          = Transform
    deterministic = false
    group         = EffecTV
    xpm           = effectvtransformmodule.xpm
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

    transform
    {
        name              = Transform
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	hidden            = true
	widget_type       = number_selector
	lower_bound       = 0
	higher_bound      = 5
	step_size         = 1
	default           = 0
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
