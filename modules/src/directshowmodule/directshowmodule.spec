mod_directShowSource
{
	name = DirectShow Quelle
	deterministic = false
	group = Quellen
	xpm = video.xpm
	author = mistkerl&coma
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
		file_mask         = *.avi;*.mpg
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