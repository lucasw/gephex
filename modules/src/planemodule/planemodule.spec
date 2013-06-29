# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_planemodule
{
    name          = Plane
    deterministic = true
    group         = Effects
    xpm           = planemodule.xpm
    author        = captain Coma
    version       = 0.9999991
}

inputs
{
    t
    {
        name              = Motion
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0
        widget_type       = unboundednumber_selector
        precision         = 2
        display_format    = fixed
    }

    rot
    {
        name              = Z-Rotation
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 90
        default           = 0
        precision         = 2
        display_format    = fixed
        step_size         = 0.5
    }

    pos
    {
        name              = Position
        type              = typ_PositionType
        const             = true
        strong_dependency = true
        default           = [0.5 0.5]
        hidden            = true
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
        default           = 640
        step_size         = 1
        display_format    = fixed
        precision         = 0
        help              = Size of output in pixels
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
        default           = 480
        step_size         = 1
        display_format    = fixed
        precision         = 0
        help              = Size of output in pixels
    }

    d
    {
        name              = Plane-Distance
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        lower_bound       = 0.1
        higher_bound      = 1
        step_size         = 0.01
        default           = 0.5
        hidden            = true
    }

    shading
    {
        name              = Shading
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = number_selector
        higher_bound      = 1
        lower_bound       = 0
        step_size         = 0.05
        default           = 0
        display_format    = fixed
        precision         = 2
        help              = Degree of Shading
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
        name              = Image
        type              = typ_FrameBufferType
    }
}

