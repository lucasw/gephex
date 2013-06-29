# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvripplemodule
{
    name          = Ripple
    deterministic = false
    group         = EffecTV
    xpm           = effectvripplemodule.xpm
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
	lower_bound       = 0
	higher_bound      = 1
	step_size         = 1
	default           = 0
	precision         = 0
	widget_type       = number_selector
	display_format    = fixed
    }
    bg
    {
        name              = Mode
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
