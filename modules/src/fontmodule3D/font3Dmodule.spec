# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_font3dmodule
{
	name          = Font3D
	deterministic = false
	group	      = Schrift Effekte
	xpm	      = font3dmodule.xpm
	author        = Lt. Uhura
    	version       = 2
}

inputs
{
    text
    {
	name		  = Text
    type              = typ_StringType
	const             = true
	strong_dependency = true
    }

    pos
    {
	name 			= Position
        type             	= typ_PositionType
	const             	= true
	strong_dependency 	= true
    }

    font
    {
	name 			= Schriftart
        type             	= typ_FontType
	const             	= true
	strong_dependency 	= true
	widget_type			= font_selector
	hidden				= true
    }

	block
	{
		name = Dicke
		type = typ_NumberType
		const = true
		strong_dependency = true
		widget_type = number_selector
		higher_bound = 100
		lower_bound = 0
		hidden = true
	}

	color
	{
		name		= Farbe
		type		= typ_RGBType
		const		= true
		strong_dependency = true
		widget_type	= color_selector
		hidden		= true
	}

    xrot
	{    		
		name 		= XDrehung
		type		= typ_NumberType
		const		= true
		strong_dependency = true
             	widget_type	= number_selector
		hidden		= true
		higher_bound	= 20
		lower_bound	= 0
	}

    yrot
	{    		
		name 		= YDrehung
		type		= typ_NumberType
		const		= true
		strong_dependency = true
             	widget_type	= number_selector
		hidden		= true
		higher_bound	= 20
		lower_bound	= 0
	}

    zrot
	{    		
		name 		= ZDrehung
		type		= typ_NumberType
		const		= true
		strong_dependency = true
             	widget_type	= number_selector
		hidden		= true
		higher_bound	= 20
		lower_bound	= 0
	}

    b
    {
	name 				= Bild
    type           		= typ_FrameBufferType
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
