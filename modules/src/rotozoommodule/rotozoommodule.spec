# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_rotozoommodule
{
	name          = Rotary Zoomer
	deterministic = true
	group	      = GrafikEffekte
	xpm	      = rotozoommodule.xpm
	author        = Miss Piggy
    	version       = -1.0
}

inputs
{
    zoom
    {
	name		  = Zoom
        type              = typ_NumberType
	const             = true
	strong_dependency = true
    }

    rot
    {
	name 			= Drehung
        type             	= typ_NumberType
	const             	= true
	strong_dependency 	= true
    }

    disp
    {
	name 			= Verschiebung
        type             	= typ_PositionType
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
