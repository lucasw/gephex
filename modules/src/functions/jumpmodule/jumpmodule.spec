# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_jumpmodule
{
	name          = Jump Signal
	deterministic = true
	group	      = Signale
	xpm	      = jumpmodule.xpm
	author        = Barbarella
    	version       = 0.65-prealpha
}

inputs
{
    in
    {
	name		  = Eingangssignal
        type              = typ_NumberType
	const             = true
	strong_dependency = true
    }

    thr
    {
	name 			= Schwellwert
        type             	= typ_NumberType
	const             	= true
	strong_dependency 	= true
    }

    upper
    {
	name 			= Oberer_Wert
        type             	= typ_NumberType
	const             	= true
	strong_dependency 	= true
    }

    lower
    {
	name 			= Unterer_Wert
        type             	= typ_NumberType
	const             	= true
	strong_dependency 	= true
    }
}

outputs
{
    r
    {
	name = Ausgangssignal
	type = typ_NumberType
    }
}
