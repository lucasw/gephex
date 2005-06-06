# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvrdsmodule
{
    name          = Rds
    deterministic = false
    group         = EffecTV
    xpm           = effectvrdsmodule.xpm
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
    method
    {
        name              = Method
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	widget_type       = number_selector
	lower_bound       = 0
	higher_bound      = 1
	default           = 0
	step_size         = 1
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
