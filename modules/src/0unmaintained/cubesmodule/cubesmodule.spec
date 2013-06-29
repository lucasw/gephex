# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_cubesmodule
{
	name          = Cubes
	deterministic = true
	group	      = Quellen
	xpm	      = cubesmodule.xpm
	author        = Delta9
    	version       = 0.9
}

inputs
{
    offset_r
    {
	name		  = Drehung
        type              = typ_NumberType
	const             = true
	strong_dependency = true
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
