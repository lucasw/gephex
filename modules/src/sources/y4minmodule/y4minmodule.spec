mod_y4minmodule
{
    name          = YUV 4 MPEG Input
    deterministic = false
    group         = Sources
    xpm           = y4minmodule.xpm
    author        = georg
    version       = 0.1
}

inputs
{
    fname
    {
        name              = Filename
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = stream.yuv
        widget_type       = file_selector
        file_mask1        = *
        file_mask1_name   = All files
        file_mask2        = *.y4m;*.yuv
        file_mask2_name   = YUV4MPEG2 files
        help              = Name of the input file or pipe
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
