# This module decodes note on/off events from a midi stream

mod_midinotedecmodule
{
	name          = note decoder
	group	      = Midi
	deterministic = false
	xpm	      = midinotedecmodule.xpm
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

	note_nr
	{
		name              = Note
		type              = typ_NumberType
		const	          = true
		strong_dependency = true
		hidden	          = true
		widget_type       = number_selector
		lower_bound	  = 0
		higher_bound      = 127
		step_size         = 1
		default	          = 0
		help              = The Number of the Note
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
    pressed
    {
    name = Pressed
    type = typ_NumberType
    }

    toggle
    {
    name = Switch
    type = typ_NumberType
    }

    velo
    {
    name = Velocity
    type = typ_NumberType
    }
}
