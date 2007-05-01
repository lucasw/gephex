# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_mirrormodule
{
    name          = Mirror
    deterministic = true
    group         = Filter
    xpm	          = mirrormodule.xpm
    author        = Lars Siebold
    version       = 0.1
}

inputs
{

    lrrl
    {
        name                    = lr-rl
        type                    = typ_NumberType
        const                   = true
        strong_dependency       = true
	hidden			= true
        default                 = 1
        widget_type             = number_selector
        lower_bound             = 1
        higher_bound            = 2
        step_size               = 1
        help                    = Copy left to right (1) or right to left (2)
    }

    tbbt
    {
        name                    = tb-bt
        type                    = typ_NumberType
        const                   = true
        strong_dependency       = true
	hidden			= true
        default                 = 1
        widget_type             = number_selector
        lower_bound             = 1
        higher_bound            = 2
        step_size               = 1
        help                    = Copy top to bottom (1) or bottom to top (2)
    }

    mode
    {
        name                    = Mode
        type                    = typ_NumberType
        const                   = true
        strong_dependency       = true
	hidden			= true
        default                 = 0
        widget_type             = number_selector
        lower_bound             = 0
        higher_bound            = 3
        step_size               = 1
        help                    = None (0) / Left-Right (1) / Top-Bottom (2) / Both (3)
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
