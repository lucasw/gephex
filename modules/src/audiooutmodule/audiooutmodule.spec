# Das ist die Spezifikation fuer das Midi-In Modul. Blabla

mod_audiooutmodule
{
    name          = Out
    deterministic = false
    group         = Audio
    xpm           = audiooutmodule.xpm
    author        = Duran Duran
    version       = 0.65-prealpha
    static        = true
}

inputs
{
    device
    {
        name              = Device
        type              = typ_NumberType
        hidden            = true
        default           = 0
        strong_dependency = true
        const             = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 256
        step_size         = 1
    }


    audio
    {
        name              = Audio-Strom
        type              = typ_AudioType
        strong_dependency = true
        const             = true
    }

    latency
    {
        name              = Latenz(ms)
        type              = typ_NumberType
        hidden            = true
        const             = true
        strong_dependency = true
        default           = 200
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 1000
        step_size         = 1
        help              = [Latenz in Millisekunden - erhoehen wenn es oft zu Aussetzern kommt]
    }

    driver
    {
        name              = Treiber
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = default
        widget_type       = combo_box
        values            = default,waveout,alsa,oss
    }
}

outputs
{
}
