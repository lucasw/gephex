# Das ist die Spezifikation fuer das Midi-In Modul. Blabla

mod_midiinmodule
{
	name          = MidiQuelle
	deterministic = false
	group	      = Quellen
	xpm	      = midiinmodule.xpm
	author        = Duran Duran
    	version       = 0.65-prealpha
}

inputs
{
    device
    {
	name = Device-Name
	type = typ_StringType
	hidden = true
	default = /dev/midi
	strong_dependency = true
	const = true
    }
}

outputs
{
    r
    {
	name = Midi-Strom
	type = typ_MidiType
    }
}
