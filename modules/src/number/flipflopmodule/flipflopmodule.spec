# Das ist die Spezifikation fuer das Flipflop Modul!
# (aka der FLOP!)

mod_flipflopmodule
{
    name                 = Flipflop
    deterministic        = true
    group                = Number
    xpm                  = flipflopmodule.xpm
    author               = Das kleine pelziges Tierchen
    version              = 0.23
}

inputs
{
    d
    {
        name              = data
        type              = typ_NumberType
        const             = true
        strong_dependency = false
        widget_type       = unboundednumber_selector
        default           = 0
    }

    clk
    {
        name              = clk
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = unboundednumber_selector
        default           = 0
    }

    tol
    {
        name              = tolerance
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 1
        hidden            = true
        widget_type       = unboundednumber_selector
        help              = Minimum size of the edge
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
