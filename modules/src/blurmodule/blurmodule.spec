# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_blurmodule
{
    name          = Blur
    deterministic = true
    group         = Effects
    xpm           = blurmodule.xpm
    author        = Enzo
    version       = 0.65-pregamma
}

inputs
{
    x
    {
        name              = Wischkraft
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        lower_bound       = 0
        higher_bound      = 400
        step_size         = 1
        default           = 0
    }

    b
    {
        name              = Bild
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = true
    }

}

outputs
{
    r
    {
        name = Bild
        type = typ_FrameBufferType
    }
}
