# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_tunnelmodule
{
    name          = Tunnel
    deterministic = true
    group         = Effects
    xpm           = tunnelmodule.xpm
    author        = Coma
    version       = 0.999999
}

inputs
{
    t
    {
        name              = Motion
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 3
        step_size         = 0.01
        precision         = 2
        display_format    = fixed
        default           = 0
    }

    rot
    {
        name              = Rotation
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        lower_bound       = -180
        higher_bound      = 180
        step_size         = 0.5
        precision         = 2
        display_format    = fixed
        default           = 0
    }

    pos
    {
        name              = Position
        type              = typ_PositionType
        const             = true
        strong_dependency = true        
        default           = [0.5 0.5]
    }

    xres
    {
        name              = Size(X)
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 1024
        step_size         = 1
        display_format    = fixed
        precision         = 0
        help              = Size of the output in pixels
        default           = 640
    }

    yres
    {
        name              = Size(Y)
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 1024
        step_size         = 1
        display_format    = fixed
        precision         = 0
        help              = Size of the output in pixels
        default           = 480
    }

    radius
    {
        name              = Radius
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        lower_bound       = 1
        higher_bound      = 100
        step_size         = 1
        default           = 10
        hidden            = true
    }

    zdist
    {
        name              = Z-Dist
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        lower_bound       = 0.1
        higher_bound      = 10
        step_size         = 0.1
        default           = 1.5
    }

    shading
    {
        name              = Shading
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.1
        display_format    = fixed
        precision         = 2
        help              = Degree of shading
        default           = 0
    }

    mode
    {
        name              = Mode
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = combo_box
        values            = default,krass
        default           = default
    }

    b
    {
        name              = Image
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = true
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
