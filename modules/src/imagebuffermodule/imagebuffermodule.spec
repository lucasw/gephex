# Das ist die Spezifikation fuer das imagebuffermodule

mod_imagebuffermodule
{
    name          = Buffer
    deterministic = true
    group         = Filter
    xpm           = imagebuffermodule.xpm
    author        = g3org
    version       = 0.1
}

inputs
{
    bsize
    {
        name                    = Puffergroesse
        type                    = typ_NumberType
        const                   = true
        strong_dependency       = true
		default                 = 1
		widget_type             = number_selector
		lower_bound             = 1
		higher_bound            = 250
		step_size               = 1
		help                    = Groesse des Puffers in Frames
    }

    bpos
    {
        name                    = Pufferposition
        type                    = typ_NumberType
        const                   = true
        strong_dependency       = true
		widget_type             = number_selector
		lower_bound             = 0
		higher_bound            = 1
		default                 = 0
		help                    = Position im Puffer: 0 = aeltestes Bild, 1 = neustes Bild
    }

	record
	{
	    name                    = Aufnehmen
		type                    = typ_NumberType
		const                   = true
		strong_dependency       = true
		widget_type             = radio_button
		true_value              = 1
		false_value             = 0
		default                 = 1
		help                    = Neue Bilder aufnehmen oder alte beibehalten
    }

	b
    {
        name                    = Bild
        type                    = typ_FrameBufferType
        const                   = true
        strong_dependency       = true
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
