# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_xfademodule
{
	name          = Crossfader
	deterministic = true
	group	      = Mixer
	xpm	      = xfademodule.xpm
	author        = Mel Froehlich
    	version       = 0.65-pregamma
	enablePatching = true
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
	name 			= Bild1
        type             	= typ_FrameBufferType
	const             	= true
	strong_dependency 	= false
    }

    2
    {
	name 			= Bild2
        type             	= typ_FrameBufferType
	const             	= true
	strong_dependency 	= false
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
