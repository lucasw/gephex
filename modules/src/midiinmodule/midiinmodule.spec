# Das ist die Spezifikation fuer das Midi-In Modul. Blabla

mod_midiinmodule
{
    name          = Midi Source
    deterministic = false
    group         = Midi
    xpm           = midiinmodule.xpm
    author        = Duran Duran
    version       = 0.65-prealpha
    static        = true
}

inputs
{
    device
    {
        name              = Device
        type              = typ_NumberType
        hidden            = true
        default           = 0
        strong_dependency = true
        const             = true
		widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 256
        step_size         = 1
    }
}

outputs
{
    r
    {
        name = Midi-Stream
        type = typ_MidiType
    }
}
