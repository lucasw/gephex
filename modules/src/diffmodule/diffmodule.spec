# Das ist die Spezifikation fuer das Differenzenquotienten Modul!

mod_diffmodule
{
    name                 = Differenzenquotient
    deterministic        = true
    group                = Signale
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
