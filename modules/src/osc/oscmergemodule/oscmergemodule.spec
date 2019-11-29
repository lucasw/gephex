# sec file for the osc merge module

mod_oscmergemodule
{
    name          = Osc Merger
    deterministic = true
    group         = Osc
    xpm           = oscmergemodule.xpm
    author        = Martin Bayer
    version       = 0.1
    static        = true
}

inputs
{
    1
    {
        name = OSC-Stream 1
        type = typ_OscType
	strong_dependency = true
        const             = true
        strong_dependency = true
    }

    2
    {
        name = OSC-Stream 2
        type = typ_OscType
	strong_dependency = true
        const             = true
        strong_dependency = true
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
