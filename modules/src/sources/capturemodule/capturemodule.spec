mod_capturemodule
{
    name          = Capture Source
    deterministic = false
    group         = Sources
    xpm           = capturemodule.xpm
    author        = mistkerl&coma&martin
    version       = 1.2.1beta
}

inputs
{
    device
    {
        name              = Device
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 15
        step_size         = 1
        default           = 0
        help              = device number of the capture device
    }

    x_size
    {
        name              = Size(x)
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 1024
        step_size         = 1
        default           = 0
        help              = If x_size and y_size > 0 the image is scaled
    }

    y_size
    {
        name              = Size(y)
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 1024
        step_size         = 1
        default           = 0
        help              = If x_size and y_size > 0 the image is scaled
    }

}

outputs
{
    result
    {
        name = Video
        type = typ_FrameBufferType
    }
}
