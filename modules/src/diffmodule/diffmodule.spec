# Das ist die Spezifikation fuer das Differenzenquotienten Modul!

mod_diffmodule
{
    name                 = Difference Quotient
    deterministic        = true
    group                = Number
    xpm                  = diffmodule.xpm
    author               = Das kleine pelziges Tierchen
    version              = 0.24
}
inputs
{
    d
    {
        name              = data
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
        name              = out
        type              = typ_NumberType
    }
}
