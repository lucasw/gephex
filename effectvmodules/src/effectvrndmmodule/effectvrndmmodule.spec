# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvrndmmodule
{
    name          = Rndm
    deterministic = false
    group         = EffecTV
    xpm           = effectvrndmmodule.xpm
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
	higher_bound      = 2
	step_size         = 1
	widget_type       = number_selector
	default           = 1
	precision         = 0
	display_format    = fixed
    }
    grabtime
    {
        name              = GrabTime
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	hidden            = true
	lower_bound       = 0
	higher_bound      = 255
	step_size         = 1
	widget_type       = number_selector
	default           = 1
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
