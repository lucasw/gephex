
mod_ffmpegoutmodule
{
    name          = FFMPEG Output
    deterministic = false
    group         = Outputs
    xpm           = ffmpegoutmodule.xpm
    author        = Michael
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

    encoding
    {
	name              = Encoding
	type              = typ_StringType
	const             = true
	strong_dependency = true
	hidden            = true
	widget_type       = combo_box
	values            = DIVX High,DIVX Low,MPEG2 High,MPEG2 Low,RM High,RM Low,MOV High,MOV Low
	default           = DIVX High
	help              = Codec and quality 
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

}

outputs
{
}
