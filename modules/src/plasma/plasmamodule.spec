# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_plasmamodule
{
	name          = Plasma
	deterministic = true
	group	      = GrafikEffekte
	xpm	      = plasmamodule.xpm
	author        = Spencer
    	version       = ultra.5
}

inputs
{
    time
    {
	name		  = Zeit
        type              = typ_NumberType
	const             = true
	strong_dependency = true
    }

    amp
    {
	name 			= Amplitude
        type             	= typ_NumberType
	const             	= true
	strong_dependency 	= true
    }

    frq
    {
	name 			= Frequenz
        type             	= typ_NumberType
	const             	= true
	strong_dependency 	= true
    }

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
