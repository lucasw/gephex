# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_netcontrol
{
    name          = Netcontrol
    group         = Quellen
    deterministic = false
    xpm           = netcontrol.xpm
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
    absolute = true
    default = 8888
    help = the port on the remote machine
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
