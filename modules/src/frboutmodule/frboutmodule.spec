# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_frboutmodule
{
    name          = Image Output
    deterministic = false
    group         = Outputs
    xpm           = frboutmodule.xpm
    author        = Georg
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

    options
    {
        name              = Options
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = check_box
        values            = On Top,Frame,Mirror X,Mirror Y,Invert
        default           = 2
        toggle_keys       = p[0,1]        
    }

    xsize
    {
        name              = xsize
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = 0
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 2560
        step_size         = 1
        display_format    = fixed
        precision         = 0
        special_text      = auto
        help              = If x_size and y_size > 0 the image is scaled
    }

    ysize
    {
        name              = ysize
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = 480
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 1600
        step_size         = 1
        display_format    = fixed
        precision         = 0
        special_text      = auto
        help              = If x_size and y_size > 0 the image is scaled
    }

    brightness
    {
        name              = Brightness
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = 0.5
        help              = Brightness (0.5:no change)
    }

    contrast
    {
        name              = Contrast
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        lower_bound       = 0
        higher_bound      = 4
        default           = 1
        help              = Contrast (1:no change)
    }

    gamma
    {
        name              = Gamma
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        lower_bound       = 0.01
        higher_bound      = 4
        default           = 1
        help              = Gamma correction (1:no change)
    }    

    monitor
    {
        name              = Monitor
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = 0
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 3
        step_size         = 1
        help              = On which monitor should the window be placed?
    }   

    driver
    {
        name              = OutputDriver
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = default
        widget_type       = combo_box
        values            = default,x11,SDL,GL,aalib,vloopback,quartz
    }

    server
    {
        name               = Display
        type               = typ_StringType
        const              = true
        strong_dependency  = true
        hidden             = true
        default            = default
        toggle_keys        = p[:0.1,:0.0]
        help               = Format is default or SERVER_HOSTNAME:XSERVER:SCREEN (for vloopback this is the video device, e.g. '/dev/video0')
    }

}

outputs
{
}
