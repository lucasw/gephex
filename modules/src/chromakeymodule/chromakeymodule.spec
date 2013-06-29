# This is the specification of the Chroma Key module

mod_chromakeymodule
{
    name           = ChromaKey
    deterministic  = true
    group          = Mixer
    xpm            = chromakeymodule.xpm
    author         = Pepto
    version        = 0.2
    enablePatching = true
}

inputs
{
    color
    {
        name              = Color
        type              = typ_RGBType
        const             = true
        default           = [0 0 1]
        strong_dependency = false
    }

    tolerance
    {
        name              = Tolerance
        type              = typ_NumberType
        const             = true
        default           = 0
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
        strong_dependency = true
    }

    mode
    {
        name              = Mode
        type              = typ_StringType
        const             = true
        default           = default
        widget_type       = combo_box
        values            = default,smooth
        strong_dependency = false
        hidden            = true
    }

    fg
    {
        name              = Foreground
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = false
    }

    bg
    {
        name              = Background
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = false
    }
}

outputs
{
    r
    {
        name = Result
        type = typ_FrameBufferType
    }
}
