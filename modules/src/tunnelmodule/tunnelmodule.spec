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
        lower_bound       = -1.6
        higher_bound      = 1.6
        default           = 0
    }

    rot
    {
        name              = Rotation
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        default           = 0         
        lower_bound       = -180
        higher_bound      = 180
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
        attributes        = a$.xsize ~ 512; a$.ysize ~ 512;
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
        help              = Size of the output in pixels
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
        help              = Size of the output in pixels
    }

    radius
    {
        name              = Radius
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
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
        help              = Degree of shading
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
