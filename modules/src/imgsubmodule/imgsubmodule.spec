# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_imgsubmodule
{
    name          = Bild-Subtrahierer
    deterministic = true
    group         = Mixer
    xpm           = imgsubmodule.xpm
    author        = coma
    version       = 1.0.1stable
}

inputs
{
    amount
    {
        name = Amount
        type = typ_NumberType
        const = true
        strong_dependency =true
	widget_type = hslider
	lower_bound = 0
	higher_bound = 1
	step_size = 0.01
        default = 0
    }

    input1
    {
        name = Bild1
        type = typ_FrameBufferType
        const = true 
        strong_dependency = true    
    }

    input2
    {
        name = Bild2
        type = typ_FrameBufferType
        const = true 
        strong_dependency = true
    }

    routine
    {
        name              = Fade-Routine
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = combo_box
        values            = regular,mmx
        default           = regular
    }
}

outputs
{
    result
    {
        name = Bild1-Bild2
        type = typ_FrameBufferType
    }
}
