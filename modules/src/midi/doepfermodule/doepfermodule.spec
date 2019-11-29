# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_doepfermodule
{
	name          = Doepferl
	group	      = Midi
	deterministic = true
	xpm	          = doepfermodule.xpm
	author        = Mel Duran
    version       = 1000.65-prealpha
	static        = false
}

inputs
{

	channel
	{
		name = MIDI_Channel
		type = typ_NumberType
		const	=	true
		strong_dependency = true
		hidden	= true
		widget_type	=  number_selector
		lower_bound	= 0
		higher_bound = 15
		step_size = 1
		default	= 0
		help	= Midi Kanal
	}

	button_group
	{
		name = Key_Group
		type = typ_NumberType
		const	=	true
		strong_dependency = true
		hidden	= true
		widget_type	=	number_selector
		lower_bound	= 0
		higher_bound = 5
		step_size = 1
		default	= 0
		help	= balh
	}

	midi
	{
		name = MidiStrom
		type = typ_MidiType
		const	=	true
		strong_dependency = true
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
