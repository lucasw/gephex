# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_flashmodule
{
    name           = Flashfader
    deterministic  = false
    group          = Filter
    xpm            = flashmodule.xpm
    author         = Flash Gordon
    version        = 0.65-pregamma
    enablePatching = true
}

inputs
{
    trigger
    {
        name              = Trigger
        type              = typ_NumberType
        const             = true
        strong_dependency = true
		widget_type       = radio_button
        default           = 0
    }

    src
    {
        name              = Image
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = true
    }

	attack
	{
		name              = Attack
        type              = typ_NumberType
        const             = true
        strong_dependency = true
		default           = 3
		hidden            = true
		widget_type       = number_selector
		lower_bound       = 0
		higher_bound      = 10
		step_size         = 1		
	}

	sustain
	{
		name              = Sustain
        type              = typ_NumberType
        const             = true
        strong_dependency = true
		default           = 2
		hidden            = true
		widget_type       = number_selector
		lower_bound       = 0
		higher_bound      = 10
		step_size         = 1		
	}

	decay
	{
		name              = Decay
        type              = typ_NumberType
        const             = true
        strong_dependency = true
		default           = 10
		hidden            = true
		widget_type       = number_selector
		lower_bound       = 0
		higher_bound      = 25
		step_size         = 1		
	}
}

outputs
{
    r
    {
        name = Image
        type = typ_FrameBufferType
    }
}
