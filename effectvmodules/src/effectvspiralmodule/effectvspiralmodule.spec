# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_effectvspiralmodule
{
    name          = Spiral
    deterministic = false
    group         = EffecTV
    xpm           = effectvspiralmodule.xpm
    static        = true
    author        = ----
    version       = 1.0
}

inputs
{
    b
    {
        name              = Image
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = true
    }

    animate_focus
    {
        name              = AnimateFocus
        type              = typ_NumberType
        const             = true
        strong_dependency = true
	hidden            = true
	widget_type       = radio_button
    }

    toggle_xor
    {
	name              = ToggleXor
	type              = typ_NumberType
	const             = true
        strong_dependency = true
	hidden            = true
	widget_type       = radio_button
    }

    focus_interval
    {
	name              = FocusInterval
	type              = typ_NumberType
	const             = true
	strong_dependency = true
	hidden            = true
	widget_type       = number_selector
	lower_bound       = 1
	higher_bound      = 60
	step_size         = 1
	display_format    = fixed
	precision         = 0
	default           = 6
    }

    focus_increment
    {
	name              = FocusIncrement
	type              = typ_NumberType
	const             = true
	strong_dependency = true
	hidden            = true
	widget_type       = number_selector
	lower_bound       = 0.75
	higher_bound      = 1.25
	precision         = 3
	step_size         = 0.25
	default           = 1

    }

    depth_shift
    {
	name              = DepthShift
	type              = typ_NumberType
	const             = true
	strong_dependency = true
	hidden            = true
	widget_type       = number_selector
	lower_bound       = 0
	higher_bound      = 5
	precision         = 0
	step_size         = 1
	default           = 1
    }

    wave_names
    {
	name              = WaveName
	type              = typ_StringType
	const             = true
	strong_dependency = true
	hidden            = true
	widget_type       = combo_box
        values            = Concentric A,Sawtooth Up,Sawtooth Down,Triangle,Sinusoidal,Concentric B,Lens,Flat
	default           = Sinusoidal
    }

    focus
    {
	name              = Focus
	type              = typ_PositionType
	const             = true
	strong_dependency = true
	default           = [0.5 0.5]
	hidden            = true
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
