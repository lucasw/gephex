# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_isingnoizemodule
{
    name              = Isingnoize
    deterministic     = false
    group             = Quellen
    xpm               = isingnoizemodule.xpm
    author            = Tellerwaescher
    version           = 0.1
}

inputs
{
    temp
    {
        name              = Temperatur
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        help              = Relative Temperatur
	widget_type       = unboundednumber_selector
        default           = 0
        lower_bound       = 0
        higher_bound      = 6
    }

    border_growth
    {
        name              = Randwachstum
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = 4
        widget_type       = number_selector
        lower_bound       = 1
        higher_bound      = 16
	step_size         = 0.5
        help              = Gibt an, wie stark der Rand fluktuiert
    }

    spont_growth
    {
        name              = Spontanes_Wachstum
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = 8
        widget_type       = number_selector
        lower_bound       = 1
        higher_bound      = 48
	step_size         = 0.5
        help              = Gibt an, wie stark Flächen fluktuieren
    }

    outx
    {
       name               = outx
       type               = typ_NumberType
       const              = true
       strong_dependency  = true
       hidden             = true
       default            = 640
       widget_type        = number_selector
       lower_bound        = 0
       higher_bound       = 1024
       step_size          = 1
       help               = Groesse des Ergebnis-Bildes
    }

    outy
    {
       name               = outy
       type               = typ_NumberType
       const              = true
       strong_dependency  = true
       hidden             = true
       default            = 480
       widget_type        = number_selector
       lower_bound        = 0
       higher_bound       = 1024
       step_size          = 1
       help               = Groesse des Ergebnis-Bildes
    }
}

outputs
{
    r
    {
        name              = Bild
        type              = typ_FrameBufferType
    }
}
