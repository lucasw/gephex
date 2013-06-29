# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvblurzoommodule
{
    name          = Blurzoom
    deterministic = false
    group         = EffecTV
    xpm           = effectvblurzoommodule.xpm
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
	higher_bound      = 3
	precision         = 0
	step_size         = 1
	default           = 0
	display_format    = fixed
    }
    palette
    {
        name              = Palette
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	widget_type       = number_selector
	lower_bound       = 0
	hidden            = true
	higher_bound      = 3
	precision         = 0
	step_size         = 1
	default           = 0
	display_format    = fixed
    }

    snapinterval
    {
        name              = SnapInterval
        type              = typ_NumberType
        const             = true
	hidden            = true
        strong_dependency = true
	widget_type       = number_selector
	lower_bound       = 1
	higher_bound      = 255
	precision         = 0
	step_size         = 1
	default           = 1
	display_format    = fixed
    }

    snaptime
    {
        name              = SnapTime
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	widget_type       = radio_button
	hidden            = true
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
