# This module decodes note on/off events from a midi stream

mod_midikeyrangedecmodule
{
	name          = key range dec
	group	      = Midi
	deterministic = false
	xpm	      = midikeyrangedecmodule.xpm
	author        = Martin Bayer
        version       = 0.1
	static        = false
}

inputs
{
	midi
	{
		name              = MidiStream
		type              = typ_MidiType
		const             = true
		strong_dependency = true
		hidden	          = false
		help              = The Midi stream
	}

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

	note_nr_min
	{
		name              = min
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

	note_nr_max
	{
		name              = max
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

	default
	{
		name              = default key
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



}


outputs
{
    pos
    {
    name = pos
    type = typ_NumberType
    }

    event
    {
    name = event
    type = typ_NumberType
    }

    pressed
    {
    name = event
    type = typ_NumberType
    }
}
