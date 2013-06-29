# Das ist die Spezifikation fuer das Midi-In Modul. Blabla

mod_audiowavegenmodule
{
    name          = WaveGen
    deterministic = false
    group         = Audio
    xpm           = audiowavegenmodule.xpm
    author        = Duran Duran
    version       = 0.65-prealpha
    static        = false
}

inputs
{
    freq
    {
        name              = Frequency
        type              = typ_NumberType
        hidden            = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 11025
        step_size         = 1
        default           = 440
        strong_dependency = true
        const             = true
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

    amplitude
    {
       name              = Amplitude
       type              = typ_NumberType
       hidden            = true
       widget_type       = number_selector
       lower_bound       = 0
       higher_bound      = 1
       step_size         = 0.01
       default           = 0.5
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
