# sec file for th osc input module

mod_numoscmodule
{
    name          = Num->Osc
    deterministic = false
    group         = Osc
    xpm           = numoscmodule.xpm
    author        = Martin Bayer
    version       = 0.1
    static        = true
}

inputs
{
    value
    {
        name              = Value
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = false
        widget_type       = unboundednumber_selector
        default           = 0
    }

    address
    {
        name              = Address
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = /gephex/
    }

  
}

outputs
{
    r
    {
        name = OSC-Stream
        type = typ_OscType
    }
}
