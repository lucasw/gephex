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
        type              = typ_StringType
        hidden            = true
        default           = /dev/midi00
        strong_dependency = true
        const             = true
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
