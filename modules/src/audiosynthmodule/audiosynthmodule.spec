# Das ist die Spezifikation fuer das Midi-In Modul. Blabla

mod_audiosynthmodule
{
    name          = Audiosynth
    deterministic = false
    group         = Audio
    xpm           = audiosynthmodule.xpm
    author        = mascht
    version       = 0.0.0.0.512-prefinal
    static        = false
}

inputs
{
    key_press
    {
       name              = KeyOnOff
       type              = typ_NumberType
       hidden            = false
       widget_type       = radio_button
       true_value        = 1
       false_value       = 0
       default           = 0
       strong_dependency = true
       const             = true
    }

    key
    {
        name              = Key
        type              = typ_NumberType
        hidden            = false
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 127
        step_size         = 1
        default           = 24
        strong_dependency = true
        const             = true
		keys              = a[10];s[11];d[12];f[13];g[14];h[15];j[16]
    }

    amplitude
    {
       name              = Amplitude
       type              = typ_NumberType
       hidden            = false
       widget_type       = number_selector
       lower_bound       = 0
       higher_bound      = 1
       step_size         = 0.01
       default           = 1.0
       strong_dependency = true
       const             = true
    }

    signal
    {
	name                = Signal
	type                = typ_StringType
	const               = true
	strong_dependency   = true
	hidden              = true
	widget_type         = combo_box
	values              = sinus,saegezahn,rechteck,noize,brownnoize
	default             = sinus
    }

    a_env
    {
	name                = Amplitude_ENV
	type                = typ_EnvType
	const               = true
	strong_dependency   = true
	hidden              = false
    }

    a_lfo
    {
	name                = Amplitude_LFO
	type                = typ_LfoType
	const               = true
	strong_dependency   = true
	hidden              = false
    }

    f_env
    {
	name                = Frequenz_ENV
	type                = typ_EnvType
	const               = true
	strong_dependency   = true
	hidden              = false
    }

    f_lfo
    {
	name                = Frequenz_LFO
	type                = typ_LfoType
	const               = true
	strong_dependency   = true
	hidden              = false
    }

    sample_rate
    {
        name              = SampleRate
        type              = typ_NumberType
        hidden            = true
        widget_type       = number_selector
        lower_bound       = 8000
        higher_bound      = 44100
        step_size         = 1
        default           = 44100
        strong_dependency = true
        const             = true
    }

}

outputs
{
    r
    {
        name = Audio-Strom
        type = typ_AudioType
    }
}
