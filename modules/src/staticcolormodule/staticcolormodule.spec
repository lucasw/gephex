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
	default           = [0.5 0.5 0.5]
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
		higher_bound    = 4096
                step_size       = 1
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
                step_size       = 1
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
