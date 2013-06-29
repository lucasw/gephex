# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvpupmodule
{
    name          = Pup
    deterministic = false
    group         = EffecTV
    xpm           = effectvpupmodule.xpm
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
        type              = typ_StringType
        const             = true
        strong_dependency = true
	hidden            = true
	widget_type       = combo_box
	values            = vertical,horizontal,diagonal,dissolution,random,raster
	default           = vertical
    }
    paraminc
    {
        name              = ParamInc
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	hidden            = true
	widget_type       = number_selector
	lower_bound       = -1
	higher_bound      = 1
	precision         = 0
	display_format    = fixed
	default           = 0
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
