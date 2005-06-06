# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvshagadelicmodule
{
    name          = Shagadelic
    deterministic = false
    group         = EffecTV
    xpm           = effectvshagadelicmodule.xpm
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
    colors
    {
        name              = Colors
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	hidden            = true
	widget_type       = check_box
	values            = Red,Green,Blue
	default           = 7
	toggle_keys       = p[0,1]
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
