# sec file for th osc input module

mod_oscinmodule
{
    name          = Osc Input
    deterministic = false
    group         = Osc
    xpm           = oscinmodule.xpm
    author        = Martin Bayer
    version       = 0.1
    static        = true
}

inputs
{
    port
    {
        name              = port
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = 9343
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
    r
    {
        name = OSC-Stream
        type = typ_OscType
    }
}
