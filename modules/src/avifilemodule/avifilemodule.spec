mod_avifileSource
{
	name = Video Quelle
	deterministic = false
	group = Quellen
	xpm = avifilemodule.xpm
	author = mistkerl&coma&martin
	version = 1.2.1beta
}

inputs
{
	fileName
	{
		name = Dateiname
		type = typ_StringType
		const = true
		strong_dependency = true
		hidden            = true
		widget_type       = file_selector
		file_mask         = *.avi
		file_mask_name    = Video
	}
}

outputs
{
	result
	{
		name = Video
		type = typ_FrameBufferType
	}
}
