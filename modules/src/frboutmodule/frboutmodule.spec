# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_frboutmodule
{
    name          = Image Output
    deterministic = true
    group         = Outputs
    xpm           = frboutmodule.xpm
    author        = Georg
    version       = 1.0
    static        = true
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
        values            = On Top,Rahmen,Mirror X,Mirror Y,Invert
        default           = 0
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
        higher_bound      = 1024
        step_size         = 1
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
        higher_bound      = 1024
        step_size         = 1
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
        help              = Bestimmt auf welchem Monitor der Output angezeigt wird
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
        values            = default,GDI,XImage,XShm,SDL,GL,aalib
    }

    server
    {
        name               = Xserver
        type               = typ_StringType
        const              = true
        strong_dependency  = true
        hidden             = true
        default            = :0.0
        toggle_keys        = p[:0.1,:0.0]
        help               = Format is SERVER_HOSTNAME:XSERVER:SCREEN
    }

}

outputs
{
}
