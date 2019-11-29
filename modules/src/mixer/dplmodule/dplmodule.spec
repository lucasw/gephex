# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_dplmodule
{
    name          = Displacement
    deterministic = true
    group         = Mixer
    xpm           = dplmodule.xpm
    author        = georg
    version       = 0.4
}

inputs
{
    amount
    {
        name              = Amount
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = hslider
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
        default           = 0
    }

    angle
    {
        name              = Angle
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 360
        step_size         = 0.5
        default           = 0
    }

    displ_mask
    {
        name              = Displacement_Mask
        type              = typ_FrameBufferType
        const             = true 
        strong_dependency = true    
    }

    in
    {
        name              = Input
        type              = typ_FrameBufferType
        const             = true 
        strong_dependency = true
    }

    mode
    {
        name              = Mode
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = combo_box
        values            = default,exact
        default           = default
        help              = displacement mode
    }


}

outputs
{
    out
    {
        name = Result
        type = typ_FrameBufferType
    }
}
