# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_midicontrolmodule
{
	name          = MidiController
	group	      = Quellen
	deterministic = false
	xpm	      = midicontrolmodule.xpm
	author        = Mel Duran
    version       = 1000.65-prealpha
	static = false
}

inputs
{

	chan
	{
		name = MIDI_Channel
		type = typ_NumberType
		const	=	true
		strong_dependency = true
		hidden	= true
		widget_type	=	number_selector
		lower_bound	= 1
		higher_bound = 16
		default	= 1
		absolute	= true
		help	= Midi Kanal
	}

	midi_mode
	{
		name = MIDI_Mode
		type = typ_NumberType
		const	=	true
		strong_dependency = true
		hidden	= true
		widget_type	=	number_selector
		lower_bound	= 0
		higher_bound = 5
		default	= 0
		absolute	= true
		help	= balh
	}

	midi1_param
	{
		name = output1_param
		type = typ_NumberType
		const	=	true
		strong_dependency = true
		hidden	= true
		widget_type	=	number_selector
		lower_bound	= 0
		higher_bound = 127
		default	= 0
		absolute	= true
		help	= balh
	}


	midi2_param
	{
		name = output2_param
		type = typ_NumberType
		const	=	true
		strong_dependency = true
		hidden	= true
		widget_type	=	number_selector
		lower_bound	= 0
		higher_bound = 127
		default	= 0
		absolute	= true
		help	= balh
	}

	midi3_param
	{
		name = output3_param
		type = typ_NumberType
		const	=	true
		strong_dependency = true
		hidden	= true
		widget_type	=	number_selector
		lower_bound	= 0
		higher_bound = 127
		default	= 0
		absolute	= true
		help	= balh
	}

	midi4_param
	{
		name = output4_param
		type = typ_NumberType
		const	=	true
		strong_dependency = true
		hidden	= true
		widget_type	=	number_selector
		lower_bound	= 0
		higher_bound = 127
		default	= 0
		absolute	= true
		help	= balh
	}
}


outputs
{
    signal_1
    {
    name = Button_1
    type = typ_NumberType
    }

    signal_2
    {
    name = Button_2
    type = typ_NumberType
    }

    signal_3
    {
    name = Button_3
    type = typ_NumberType
    }

    signal_4
    {
    name = Button_4
    type = typ_NumberType
    }
}
