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
    }

    rot
    {
        name              = Rotation
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 360
        step_size         = 0.5
    }

    pos
    {
        name              = Position
        type              = typ_PositionType
        const             = true
        strong_dependency = true
        default           = [0.5 0.5]
    }

    b
    {
        name              = Image
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = true
        attributes        = a$.xsize ~ 256; a$.ysize ~ 256;
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
        name              = Distance
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
        default           = 0.5
    }

    shading
    {
        name              = Shading
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = number_selector
        higher_bound      = 10
        lower_bound       = 0
        step_size         = 1
        default           = 0
        display_format    = fixed
        precision         = 0
        help              = Degree of Shading
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

