# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_planemodule
{
    name          = Plane
    deterministic = true
    group         = GrafikEffekte
    xpm           = planemodule.xpm
    author        = captain Coma
    version       = 0.9999991
}

inputs
{
    t
    {
        name              = Bewegung
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0
        widget_type       = unboundednumber_selector
    }

    rot
    {
        name              = Drehung
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
        name              = Bild
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = true
        attributes        = a$.xsize ~ 256; a$.ysize ~ 256;
    }

    xres
    {
        name              = Groesse(X)
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       =  number_selector
        lower_bound       = 0
        higher_bound      = 1024
        default           = 640
        step_size         = 1
        help              = Größe des Outputs in Pixeln
    }

    yres
    {
        name              = Groesse(Y)
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 1024
        default           = 480
        step_size         = 1
        help              = Größe des Outputs in Pixeln
    }

    d
    {
        name              = Abstand
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
        help              = Stärke des Shadings
    }
}

outputs
{
    r
    {
        name              = Bild
        type              = typ_FrameBufferType
    }
}

