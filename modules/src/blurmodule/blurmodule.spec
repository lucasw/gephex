# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_blurmodule
{
	name          = Verwischer
	deterministic = true
	group	      = GrafikEffekte
	xpm	      = blurmodule.xpm
	author        = Enzo
    	version       = 0.65-pregamma
}

inputs
{
    x
    {
	name		  = Wischkraft
        type              = typ_NumberType
	const             = true
	strong_dependency = true
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
