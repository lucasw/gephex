# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_staticcolormodule
{
	name          = Static Color
	deterministic = true
	group	      = Quellen
	xpm	      = staticcolormodule.xpm
	author        = Mad Enzensberger
    	version       = 0.61-prealpha
}

inputs
{
    col
    {
	name		  = Farbe
        type              = typ_RGBType
	const             = true
	strong_dependency = true
	hidden            = true
        widget_type       = color_selector
    }

	xsize
	{
		name	= xsize
		type	= typ_NumberType
		const	= true
		strong_dependency	= true
		hidden	= true
		default = 320
		widget_type	=	number_selector
		lower_bound	= 0
		higher_bound = 4096
		absolute	= true
	}

	ysize
	{
		name	= ysize
		type	= typ_NumberType
		const	= true
		strong_dependency	= true
		hidden	= true
		default = 240
		widget_type	=	number_selector
		lower_bound	= 0
		higher_bound = 4096
		absolute	= true
	}

}

outputs
{
    r
    {
	name		  = Bild
        type              = typ_FrameBufferType
    }
}
