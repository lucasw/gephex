# This is the specification of the XFade module

mod_xfademodule
{
    name           = Crossfader
    deterministic  = true
    group          = Mixer
    xpm            = xfademodule.xpm
    author         = Mel Froehlich
    version        = 0.65-pregamma
    enablePatching = true
}

inputs
{
    x
    {
        name              = Fader
        type              = typ_NumberType
        const             = true
        default           = 0
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
        strong_dependency = true
    }

    1
    {
        name              = Image1
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = false
    }

    2
    {
        name              = Image2
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = false
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
        default           = mmx
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
