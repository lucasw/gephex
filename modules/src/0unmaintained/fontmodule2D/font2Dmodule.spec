# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_font2dmodule
{
	name          = Font2D
	deterministic = false
	group	      = Schrift Effekte
	xpm	      = font2dmodule.xpm
	author        = Captain Kirk
    	version       = ultra.5
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

	color
	{
		name		= Farbe
		type		= typ_RGBType
		const		= true
		strong_dependency = true
		widget_type	= color_selector
		hidden		= true
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
