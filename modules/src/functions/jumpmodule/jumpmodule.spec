# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_jumpmodule
{
    name          = Jump Signal
    deterministic = true
    group         = Signale
    xpm           = jumpmodule.xpm
    author        = Barbarella
    version       = 0.65-prealpha
}

inputs
{
    in
    {
        name              = Eingangssignal
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0
        widget_type       = unboundednumber_selector
    }

    thr
    {
        name              = Schwellwert
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0.5
        widget_type       = unboundednumber_selector
        hidden            = true
    }

    lower
    {
        name              = Unterer_Wert
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0
        widget_type       = unboundednumber_selector
        hidden            = true
    }

    upper
    {
        name              = Oberer_Wert
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 1
        widget_type       = unboundednumber_selector
        hidden            = true
    }
}

outputs
{
    r
    {
        name = Ausgangssignal
        type = typ_NumberType
    }
}
