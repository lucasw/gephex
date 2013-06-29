# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_pixelizemodule
{
    name           = Pixelizer
    deterministic  = true
    group          = Filter
    xpm            = pixelizemodule.xpm
    author         = Flash Gordon
    version        = 0.65-pregamma
    enablePatching = true
}

inputs
{
    bsize
    {
        name              = BlockSize(X)
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 1
        hidden            = false
        widget_type       = number_selector
        lower_bound       = 1
        higher_bound      = 80
        step_size         = 1
        display_format    = fixed
        precision         = 0          
    }

    bsizey
    {
        name              = BlockSize(Y)
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0
        hidden            = false
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 80
        step_size         = 1
        display_format    = fixed
        precision         = 0
        special_text      = match x
        help              = if you set this value to 0, the y blocksize will match the x blocksize
    }

    src
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
