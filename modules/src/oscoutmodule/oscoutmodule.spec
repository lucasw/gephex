# sec file for th osc input module

mod_oscoutmodule
{
    name          = Osc Output
    deterministic = true
    group         = Osc
    xpm           = oscoutmodule.xpm
    author        = Martin Bayer
    version       = 0.1
    static        = true
}

inputs
{
    r
    {
        name = OSC-Stream
        type = typ_OscType
	strong_dependency = true
        const             = true
        strong_dependency = true
    }


    dest
    {
        name              = dest
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = 127.0.0.1
    }


    port
    {
        name              = port
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = 9342
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 65535
        step_size         = 1
        display_format    = fixed
        precision         = 0
    }
}

outputs
{
}
