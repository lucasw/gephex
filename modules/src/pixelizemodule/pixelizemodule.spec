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
        name              = BlockSize
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 1
        hidden            = false
        widget_type       = number_selector
        lower_bound       = 1
        higher_bound      = 30
        step_size         = 1
        display_format    = fixed
        precision         = 0          
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
