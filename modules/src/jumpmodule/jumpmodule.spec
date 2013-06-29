# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_jumpmodule
{
    name          = Jump Signal
    deterministic = true
    group         = Number
    xpm           = jumpmodule.xpm
    author        = Barbarella
    version       = 0.65-prealpha
}

inputs
{
    in
    {
        name              = signal
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0
        widget_type       = unboundednumber_selector
    }

    thr
    {
        name              = Threshold
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0.5
        widget_type       = unboundednumber_selector
        hidden            = true
    }

    lower
    {
        name              = Lower_Value
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0
        widget_type       = unboundednumber_selector
        hidden            = true
    }

    upper
    {
        name              = Upper_Value
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
        name = Outputsignal
        type = typ_NumberType
    }
}
