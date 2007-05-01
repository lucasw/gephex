# This module decodes note on/off events from a midi stream

mod_midiprgchdecmodule
{
	name          = prgch decoder
	group	      = Midi
	deterministic = false
	xpm	      = midiprgchdecmodule.xpm
	author        = Martin Bayer
        version       = 0.1
	static        = false
}

inputs
{

	channel
	{
		name              = MIDI_Channel
		type              = typ_NumberType
		const	          = true
		strong_dependency = true
		hidden	          = true
		widget_type	  = number_selector
		lower_bound	  = 0
		higher_bound      = 15
		step_size         = 1
		default	          = 0
		help	          = Midi Channel
	}

	midi
	{
		name              = MidiStream
		type              = typ_MidiType
		const             = true
		strong_dependency = true
		help              = The Midi stream
	}
}


outputs
{
    prg
    {
    name = Program
    type = typ_NumberType
    }
}
