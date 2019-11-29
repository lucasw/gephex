# sec file for th osc input module

mod_oscnummodule
{
    name          = Osc->Num
    deterministic = false
    group         = Osc
    xpm           = oscnummodule.xpm
    author        = Martin Bayer
    version       = 0.1
    static        = true
}

inputs
{

    osc
    {
        name = OSC-Stream
	strong_dependency = true
        type = typ_OscType
        strong_dependency = true
        const             = true
    }

    address
    {
        name              = OSC-address
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = /gephex/
    }

}

outputs
{
    num
    {
      name = Value
      type = typ_NumberType
    }
}
