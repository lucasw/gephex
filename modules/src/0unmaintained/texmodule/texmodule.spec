# Spezifikation für texture module

mod_texmodule
{
	name          = Bild
	deterministic = true
	group	      = Quellen
	xpm	      = texmodule.xpm
	author        = coma
	version       = 0.61-präalpha-furz
	help		= Dieses Modul lädt Bild Dateien(fast) jeder Art :)
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
	file_mask         = *.bmp *.jpg *.jpeg *.png
	file_mask_name    = Bilddateien
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
		higher_bound = 4096
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
		higher_bound = 4096
		default	= 0
		step_size = 1
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
