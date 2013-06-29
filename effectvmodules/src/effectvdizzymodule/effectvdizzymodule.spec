# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvdizzymodule
{
    name          = Dizzy
    deterministic = false
    group         = EffecTV
    xpm           = effectvdizzymodule.xpm
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
 
    phase
    {
        name              = Phase
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	widget_type       = number_selector
	lower_bound       = 0
	higher_bound      = 1
	precision         = 3
	step_size         = 0.01
	default           = 0.02
	display_format    = fixed
    }
    zoom
    {
        name              = Zoom
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	widget_type       = number_selector
	lower_bound       = 1.01
	higher_bound      = 1.1
	precision         = 3
	step_size         = 0.01
	default           = 1.01
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
