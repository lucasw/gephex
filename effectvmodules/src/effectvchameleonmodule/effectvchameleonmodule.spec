# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvchameleonmodule
{
    name          = Chameleon
    deterministic = false
    group         = EffecTV
    xpm           = effectvchameleonmodule.xpm
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
	widget_type       = number_selector
	lower_bound       = 0
	higher_bound      = 1
	step_size         = 1
	display_format    = fixed
	precision         = 0
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
