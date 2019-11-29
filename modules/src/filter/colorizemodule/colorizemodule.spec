# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_colorizemodule
{
    name          = Colorize
    deterministic = true
    group         = Filter
    xpm	          = colorizemodule.xpm
    author        = Lars Siebold
    version       = 0.1
}

inputs
{

    color
    {
        name              = Color
        type              = typ_RGBType
        const             = true
        hidden            = true
        default           = [0 0 0]
        strong_dependency = true
    }
    
    mode
    {
        name              = Mode
        type              = typ_NumberType
        const             = true
        hidden            = true
        widget_type       = number_selector
        lower_bound       = 1
        higher_bound      = 7
        step_size         = 1
        default           = 1
        strong_dependency = true
    }

    
    tolerance
    {
        name              = Tolerance
        type              = typ_NumberType
        const             = true
        hidden            = true
        default           = 0.5
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
        strong_dependency = true
    }
    
    1
    {
       name  	         = Bild
       type              = typ_FrameBufferType
       const             = true
       strong_dependency = true
    }
}

outputs
{
    r
    {
       name              = Bild
       type              = typ_FrameBufferType
    }
}
