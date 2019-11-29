# This module decodes controll change events from a midi stream

mod_midiccdecmodule
{
	name          = Midi cc decoder
	group	      = Midi
	deterministic = false
	xpm	      = midiccdecmodule.xpm
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

	cc_nr
	{
		name              = Controller_Number
		type              = typ_NumberType
		const	          = true
		strong_dependency = true
		hidden	          = true
		widget_type       = number_selector
		lower_bound	  = 0
		higher_bound      = 127
		step_size         = 1
		default	          = 0
		help              = The Number of the Controll
	}

	defval
	{
		name              = Default_Value
		type              = typ_NumberType
		const	          = true
		strong_dependency = true
		hidden	          = true
		widget_type       = number_selector
		lower_bound	  = 0
		higher_bound      = 1
		default	          = 0
		help              = The default value
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
    value
    {
    name = Value
    type = typ_NumberType
    }

    event
    {
    name = Event
    type = typ_NumberType
    }
}
