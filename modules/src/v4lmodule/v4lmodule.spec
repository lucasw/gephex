# Das ist die Spezifikation V4l Module

mod_v4lmodule
{
	name          = Video4Linux
	deterministic = false
	group	      = Quellen
	xpm	      = v4lmodule.xpm
	author        = Mad VideoJockey
    	version       = 0.61-doubleprealpha
}

inputs
{

    devicefile
    {
	name		  = Devicename
        type              = typ_StringType
	const             = true
	strong_dependency = true
	hidden            = true
        widget_type       = file_selector
	file_mask         = *
	file_mask_name    = Gerätedatei
	default           = /dev/video0
	help	= Gerätedatei der Video 4 Linux Gerätes (z.B. /dev/video0)
    }

    x_size
    {
	name	=	Größe(x)
	type	=	typ_NumberType
	const	=	true
	strong_dependency = true
	hidden	= true
	widget_type	=	number_selector
	lower_bound	= 0
	higher_bound = 1024
	step_size = 1
	default	= 0
	help	= Wenn x_size und y_size > 0, wird das bild auf xsize x ysize skaliert
    }

    y_size
    {
	name	=	Größe(y)
	type	=	typ_NumberType
	const	=	true
	strong_dependency = true
	hidden	= true
	widget_type	=	number_selector
	lower_bound	= 0
	higher_bound = 1024
	step_size = 1
	default	= 0
	help	= Wenn x_size und y_size > 0, wird das bild auf xsize x ysize skaliert
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