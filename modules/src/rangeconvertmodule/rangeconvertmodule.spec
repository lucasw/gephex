# Das ist die Spezifikation fuer das Number Modul. Blabla

mod_rangeconvertmodule
{
    name          = RangeKonvert0r
    deterministic = false
    group         = Signale
    xpm           = rangeconvertmodule.xpm
    author        = Blade
    version       = 0.61-postalphaprebeta(rightbetweenalphaandbeta)
}

inputs
{
    n
    {
    name              = Eingang
    type              = typ_NumberType
    const             = true
    strong_dependency = true
    widget_type       = unboundednumber_selector
    default           = 0
    }

    min_in
    {
    name              = Minimum_Eingang
    type              = typ_NumberType
    const             = true
    strong_dependency = true
    widget_type       = unboundednumber_selector
    hidden            = true
    default           = 0
    }

    max_in
    {
    name              = Maximum_Eingang
    type              = typ_NumberType
    const             = true
    strong_dependency = true
    default           = 1
    hidden            = true
    widget_type       = unboundednumber_selector
    }

    min_out
    {
    name              = Minimum_Ausgang
    type              = typ_NumberType
    const             = true
    strong_dependency = true
    default           = 0
    hidden            = true
    widget_type       = unboundednumber_selector
    }

    max_out
    {
    name              = Maximum_Ausgang
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
    name = Ausgang
    type = typ_NumberType
    }
}
