# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_netcontrol
{
    name          = Netcontrol
    group         = Input
    deterministic = false
    xpm           = netcontrolmodule.xpm
    author        = A PATHETIC HUMAN
    version       = -0.9
    static = false
}

inputs
{
    port
    {
    name = Port
    type = typ_NumberType
    strong_dependency = true
    const = true
    hidden = true
    widget_type	= number_selector
    lower_bound	= 0
    higher_bound = 64000
    step_size = 1
    default = 1337
    help = the local port
    }
}


outputs
{
    signal
    {
    name = MidiSignal
    type = typ_MidiType
    }
}

