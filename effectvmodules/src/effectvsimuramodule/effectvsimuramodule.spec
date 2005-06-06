# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvsimuramodule
{
    name          = Simura
    deterministic = false
    group         = EffecTV
    xpm           = effectvsimuramodule.xpm
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

    color
    {
	name              = Color
	type		  = typ_NumberType
	const             = true
        strong_dependency = true
	hidden            = true
	widget_type       = number_selector
	default           = 0
	lower_bound       = 0
	higher_bound      = 26
	step_size         = 1
	precision         = 0
	display_format    = fixed
    }

    mirror
    {
	name              = Mirror
	type		  = typ_NumberType
	const             = true
        strong_dependency = true
	hidden            = true
	widget_type       = number_selector
	default           = 0
	lower_bound       = 0
	higher_bound      = 9
	precision         = 0
	step_size         = 1
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
