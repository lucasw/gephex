# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_tunnelmodule
{
	name          = Tunnel
	deterministic = true
	group	      = GrafikEffekte
	xpm	      = tunnelmodule.xpm
	author        = Coma
    	version       = 0.999999
}

inputs
{
    t
    {
	name		  = Bewegung
        type              = typ_NumberType
	const             = true
	strong_dependency = true
    }

    rot
    {
	name		  = Drehung
        type              = typ_NumberType
	const             = true
	strong_dependency = true
    }

    pos
    {
	name		  = Position
        type              = typ_PositionType
	const             = true
	strong_dependency = true
    }

    b
    {
	name 			= Bild
        type             	= typ_FrameBufferType
	const             	= true
	strong_dependency 	= true
	attributes			= a$.xsize ~ 512; a$.ysize ~ 512;
    }

	xres
	{
		name = Groesse(X)
		type = typ_NumberType
		const = true
		strong_dependency = true
		hidden = true
		widget_type	 =	number_selector
		lower_bound	 = 0
		higher_bound = 1024
		default	     = 640
		absolute	 = true
		help	= Größe des Outputs in Pixeln
	}

	yres
	{
		name = Groesse(Y)
		type = typ_NumberType
		const = true
		strong_dependency = true
		hidden = true
		widget_type	 =	number_selector
		lower_bound	 = 0
		higher_bound = 1024
		default	     = 480
		absolute	 = true
		help	= Größe des Outputs in Pixeln
	}

	radius
	{
		name = Radius
		type = typ_NumberType
		const = true
		strong_dependency = true
	}

	shading
	{
		name = Shading
		type = typ_NumberType
		const = true
		strong_dependency = true
		hidden = true
		widget_type = number_selector
		higher_bound = 10
		lower_bound = 0
		absolute = true
		default = 0
		help = Stärke des Shadings
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
