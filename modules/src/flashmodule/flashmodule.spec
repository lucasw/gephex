# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_flashmodule
{
	name          = Flashfader
	deterministic = false
	group	      = Filter
	xpm	      = flashmodule.xpm
	author        = Flash Gordon
    	version       = 0.65-pregamma
	enablePatching = true
}

inputs
{
    trigger
    {
	name		  = Trigger
        type              = typ_NumberType
	const             = true
	strong_dependency = true
    }

    src
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
