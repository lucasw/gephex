# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_gradnormmodule
{
    name          = Gradientnorm
    deterministic = true
    group         = Filter
    xpm           = gradnormmodule.xpm
    author        = mascht
    version       = 1.0
}

inputs
{
    b
    {
        name              = Image
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = true
    }

    scale
    {
        name              = Lightness
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
        default           = 0.5
        help              = lightness
    }

    algo
    {
        name                = Algorithm
        type                = typ_StringType
        const               = true
        strong_dependency   = true
        hidden              = true
        widget_type         = combo_box
        values              = sobel,roberts-cross
        default             = roberts-cross
        help                = sobel is slower and smoother, roberts-cross is quick and dirty
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
