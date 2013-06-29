# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_flagmodule
{
	name          = Flagge zeigen!
	deterministic = false
	group	      = GrafikEffekte
	xpm	      = flagmodule.xpm
	author        = Gonzo
    	version       = epsilons stinken
}

inputs
{
    x
    {
	name		  = X-Rotation
        type              = typ_NumberType
	const             = true
	strong_dependency = true
    }

    y
    {
	name		  = Y-Rotation
    type              = typ_NumberType
	const             = true
	strong_dependency = true
    }

    z
    {
	name		  = Z-Rotation
        type              = typ_NumberType
	const             = true
	strong_dependency = true
    }

    b
    {
	name 			= Textur
    type             	= typ_FrameBufferType
	const             	= true
	strong_dependency 	= true
	attributes			= a$.xsize ~ 256; a$.ysize ~ 256;
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
