# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_invertmodule
{
	name          = Inverter
	deterministic = true
	group	      = Filter
	xpm	      = invertmodule.xpm
	author        = TheMadman
    	version       = 1.0
}

inputs
{
    b
    {
	name 			= Bild
        type             	= typ_FrameBufferType
	const             	= true
	strong_dependency 	= true
    }

}

outputs
{
    r
    {
	name = Bild
	type = typ_FrameBufferType
    }
}
