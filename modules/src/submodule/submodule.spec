# Das ist die Spezifikation fuer das Subtrahier Modul!
# (aka der SUBSTRATOR!)

mod_submodule
{
    name                  = Subtrahierer
    deterministic         = true
    group                 = Signale
    xpm                   = submodule.xpm
    author                = Das kleine pelziges Tierchen
    version               = 0.23
}

inputs
{
    lhs
    {
    name              = Zahl1
    type              = typ_NumberType
    const             = true
    strong_dependency = true
    default           = 0
    widget_type       = unboundednumber_selector
    }

    rhs
    {
    name              = Zahl2
    type              = typ_NumberType
    const             = true
    strong_dependency = true
    default           = 0
    widget_type       = unboundednumber_selector
    }
}

outputs
{
    r
    {
    name              = Differenz
    type              = typ_NumberType
    }
}
