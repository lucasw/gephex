# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_addmodule
{
    name              = Addierer
    deterministic     = true
    group             = Signale
    xpm               = addmodule.xpm
    author            = Duran Duran
    version           = 0.65-prealpha
}

inputs
{
    lhs
    {
    name              = Summand1
    type              = typ_NumberType
    const             = true
    strong_dependency = true
    default           = 0
    widget_type       = unboundednumber_selector
    }

    rhs
    {
    name              = Summand2
    type              = typ_NumberType
    const             = true
    strong_dependency = true
    widget_type       = unboundednumber_selector
	default           = 0
    }
}

outputs
{
    r
    {
    name              = Summe
    type              = typ_NumberType
    }
}
