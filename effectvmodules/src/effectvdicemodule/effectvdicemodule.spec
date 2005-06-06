# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvdicemodule
{
    name          = Dice
    deterministic = false
    group         = EffecTV
    xpm           = effectvdicemodule.xpm
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

    cubebits
    {
        name              = cubebits
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	hidden            = true
	widget_type       = number_selector
	lower_bound       = 0
	higher_bound      = 5
	precision         = 0
	display_format    = fixed
        default           = 4
    }
    update
    {
        name              = update
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
