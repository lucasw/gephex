# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_sdloutmodule
{
	name          = SDL Output
	deterministic = true
	group	      = Outputs
	xpm	      = sdloutputmodule.xpm
	author        = Gargamel
    	version       = 10.5
	static        = true
}

inputs
{
    in
    {
	name		  = Bild
        type              = typ_FrameBufferType
	const             = true
	strong_dependency = true
    }

    xsize
    {
	name	= xsize
	type	= typ_NumberType
	const	= true
	strong_dependency	= true
	hidden	= true
	default = 640
	widget_type	=	number_selector
	lower_bound	= 0
	higher_bound = 1024
	absolute	= true
	help	= Wenn x_size und y_size > 0, wird das bild beim Laden auf xsize x ysize skaliert
     }

     ysize
     {
	name	= ysize
	type	= typ_NumberType
	const	= true
	strong_dependency	= true
	hidden	= true
	default = 480
	widget_type	=	number_selector
	lower_bound	= 0
	higher_bound = 1024
	absolute	= true
	help	= Wenn x_size und y_size > 0, wird das bild beim Laden auf xsize x ysize skaliert
     }
}

outputs
{
}

