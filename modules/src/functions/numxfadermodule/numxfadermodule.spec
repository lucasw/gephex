# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_numxfademodule
{
	name          = Zahlen Crossfader
	deterministic = true
	group	      = Mixer
    xpm           = numxfadermodule.xpm
	author        = Don Bosco
    version       = 0.65-pregamma
}

inputs
{
    x
    {
	name		  = Fader
    type              = typ_NumberType
	const             = true
	strong_dependency = true
    }

    1
    {
	name 			= Signal_1
    type             	= typ_NumberType
	const             	= true
	strong_dependency 	= false
    }

    2
    {
	name 			= Signal_2
    type             	= typ_NumberType
	const             	= true
	strong_dependency 	= false
    }
}

outputs
{
    r
    {
	name = Gemischtes_Signal
	type = typ_NumberType
    }
}
