# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_dxoutmodule
{
	name          = DX Output
	deterministic = true
	group	      = Outputs
	xpm	      = dxmonitor.xpm
	author        = Georg
    	version       = 1.0
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
#	attributes			= a$.xsize ~ 640; a$.ysize ~ 480;
    }
	preview
	{
		name = Preview?
		type = typ_NumberType
		const = true
		strong_dependency = true
		hidden = true
		widget_type = radio_button
	}
}

outputs
{
}
