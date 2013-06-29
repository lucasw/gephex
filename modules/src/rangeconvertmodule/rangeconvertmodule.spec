# Das ist die Spezifikation fuer das Number Modul. Blabla

mod_rangeconvertmodule
{
    name          = RangeKonvert0r
    deterministic = false
    group         = Number
    xpm           = rangeconvertmodule.xpm
    author        = Blade
    version       = 0.61-postalphaprebeta(rightbetweenalphaandbeta)
}

inputs
{
    n
    {
        name              = Input
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = unboundednumber_selector
        default           = 0
    }

    min_in
    {
        name              = Min_In
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = unboundednumber_selector
        hidden            = true
        default           = 0
    }

    max_in
    {
        name              = Max_In
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 1
        hidden            = true
        widget_type       = unboundednumber_selector
    }

    min_out
    {
        name              = Min_Out
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0
        hidden            = true
        widget_type       = unboundednumber_selector
    }

    max_out
    {
        name              = Max_Out
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 1
        hidden            = true
        widget_type       = unboundednumber_selector
    }
}

outputs
{
    r
    {
        name = Output
        type = typ_NumberType
    }
}
