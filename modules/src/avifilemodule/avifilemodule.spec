mod_avifileSource
{
	name = Avi Quelle
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
		file_mask         = *
		file_mask_name    = Video
	}

	seek
	{
	    name              = seek
	    type              = typ_NumberType
	    const             = true
	    strong_dependency = true
	    hidden            = true
	    widget_type       = radio_button
	    true_value        = 1
	    false_value       = 0
	    default           = 0
	    help              = seek to position
	}

	position
	{
		name              = Position
		type              = typ_NumberType
		const             = true
		strong_dependency = true
		hidden            = false
		widget_type       = number_selector
		lower_bound       = 0
		higher_bound      = 1
		default           = 0.0
		step_size         = 0.001
	}
}

outputs
{
	result
	{
		name = Video
		type = typ_FrameBufferType
	}

	position
	{
		name = Position
		type = typ_NumberType
	}
}
