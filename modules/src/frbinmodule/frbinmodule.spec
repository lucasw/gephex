mod_frbinmodule
{
    name          = Image Source
    deterministic = false
    group         = Sources
    xpm           = frbinmodule.xpm
    author        = mistkerl&coma&martin
    version       = 1.2.1beta
}

inputs
{
    fileName
    {
        name              = Filename
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = false
        widget_type       = file_selector
        file_mask1        = *.*
        file_mask1_name   = All files
        file_mask2        = *.bmp;*.jpg;*.png;*.tiff;*.ppm;*.pcx;*.gif;*.jpeg;*.xpm
        file_mask2_name   = Images
        file_mask3        = *.avi;*.mpg;*.mpeg;*.divx;*.rm;*.mov;*.wmv
        file_mask3_name   = Videos
    }

    seek
    {
        name              = seek
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = radio_button
        true_value        = 1
        false_value       = 0
        default           = 0
        help              = seek to position
    }

    position
    {
        name              = Position
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = false
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 1
        default           = 0.0
        step_size         = 0.001
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
        display_format    = fixed
        precision         = 0
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
        display_format    = fixed
        precision         = 0
        step_size         = 1
        default           = 0
        help              = If x_size and y_size > 0 the image is scaled
    }

    cache
    {
        name              = Use-Cache
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = combo_box
        values            = yes,no
        default           = no
    }

    flush
    {
       name              = FlushCache
       type              = typ_NumberType
       hidden            = true
       widget_type       = radio_button
       true_value        = 1
       false_value       = 0
       default           = 0
       strong_dependency = true
       const             = true
    }
}

outputs
{
    result
    {
        name = Video
        type = typ_FrameBufferType
    }

    position
    {
        name = Position
        type = typ_NumberType
    }
}
