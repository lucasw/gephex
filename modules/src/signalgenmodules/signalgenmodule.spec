# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_signalmodule
{
	name          = SignalGenerator
	group	      = Signale
	deterministic = false
	xpm	      = signalgenmodule.xpm
	author        = Mel Duran
    	version       = 1000.65-prealpha
}

inputs
{
    Amplitude
    {
	name			= Amplitude
        type              	= typ_NumberType
	const             	= true
	strong_dependency 	= true
	default				= 0
    }

    Frequenz
    {
	name			= Frequenz
        type             	= typ_NumberType
	const             	= true
	strong_dependency 	= true
	default				= 0
    }

    Phase
    {
	name			= Phase
        type             	= typ_NumberType
	const             	= true
	strong_dependency 	= true
	default				= 0
    }

    Position
    {
	name			= Position
        type             	= typ_NumberType
	const             	= true
	strong_dependency 	= true
	default				= 0
    }

    Signal
    {
	name			= Signal
        type             	= typ_StringType
	const             	= true
	strong_dependency 	= true
	hidden                  = true
	widget_type             = combo_box
	values			= sinus,saegezahn,rechteck
	default                 = sinus
    }
}

outputs
{
    Signal
    {
	name = Signal
	type = typ_NumberType
    }
}
