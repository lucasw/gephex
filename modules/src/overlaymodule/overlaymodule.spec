# This is the specification of the XFade module

mod_overlaymodule
{
    name           = Overlay
    deterministic  = true
    group          = Mixer
    xpm            = overlaymodule.xpm
    author         = Mel Froehlich
    version        = 0.65-pregamma
    enablePatching = false
}

inputs
{
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


    alpha_mode
    {
        name              = Alpha_mode
        type              = typ_NumberType
        const             = true
	widget_type       = radio_button
	true_value        = 1
	false_value       = 0
        default           = 0
        strong_dependency = true
    }


    control
    {
        name              = ControlImage
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = false
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

}

outputs
{
    r
    {
        name = Image
        type = typ_FrameBufferType
    }
}
