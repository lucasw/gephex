# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvdiffmodule
{
    name          = Diff
    deterministic = false
    group         = EffecTV
    xpm           = effectvdiffmodule.xpm
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

    red
    {
        name              = Red
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	widget_type       = number_selector
	lower_bound       = 0
	higher_bound      = 63
	precision         = 0
	step_size         = 1
	default           = 10
	display_format    = fixed
    }
    green
    {
        name              = Green
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	widget_type       = number_selector
	lower_bound       = 0
	higher_bound      = 63
	precision         = 0
	step_size         = 1
	default           = 10
	display_format    = fixed
    }
    blue
    {
        name              = Blue
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	widget_type       = number_selector
	lower_bound       = 0
	higher_bound      = 63
	precision         = 0
	step_size         = 1
	default           = 10
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
