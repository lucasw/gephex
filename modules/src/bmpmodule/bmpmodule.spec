# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_bmpmodule
{
	name          = Bitmap Loader
	deterministic = true
	group	      = Quellen
	xpm	      = bmpmodule.xpm
	author        = Harry Hirsch
    version       = 0.61-prealpha
	help		= Dieses Modul lädt eine Bitmap Datei
}

inputs
{
    file
    {
	name		  = Dateiname
        type              = typ_StringType
	const             = true
	strong_dependency = true
	hidden            = true
        widget_type       = file_selector
	file_mask         = *.bmp
	file_mask_name    = Bild
	help	= Name und Pfad des Bildes
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
		help	= Wenn x_size und y_size > 0, wird das bild beim Laden auf xsize x ysize skaliert
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
		help	= Wenn x_size und y_size > 0, wird das bild beim Laden auf xsize x ysize skaliert
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
