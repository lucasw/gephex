# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_y4moutmodule
{
    name          = YUV4MPEG2 Output
    deterministic = false
    group         = Outputs
    xpm           = y4moutputmodule.xpm
    author        = Martin
    version       = 1.0
}

inputs
{
    in
    {
        name              = Image
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = true
    }

    filename
    {
        name              = Filename
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = false
    }

    xsize
    {
        name              = xsize
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = 320
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 2560
        step_size         = 4
        display_format    = fixed
        precision         = 0
        help              = If x_size and y_size > 0 the image is scaled
    }

    ysize
    {
        name              = ysize
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = 240
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 1600
        step_size         = 4
        display_format    = fixed
        precision         = 0
    }

    color_model
    {
        name              = ColorModel
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = false
        default           = yuv420p
        widget_type       = combo_box
        values            = yuv420p,bgra8888
    }

}

outputs
{
}
