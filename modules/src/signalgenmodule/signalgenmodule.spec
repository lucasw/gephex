# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_signalmodule
{
    name                = SignalGenerator
    group               = Number
    deterministic       = false
    xpm                 = signalgenmodule.xpm
    author              = Mel Duran
    version             = 1000.65-prealpha
}

inputs
{
    Amplitude
    {
        name                = Amplitude
        type                = typ_NumberType
        const               = true
        strong_dependency   = true
        widget_type         = unboundednumber_selector
        default             = 1
        hidden              = true
    }

    Frequenz
    {
        name                = Frequency
        type                = typ_NumberType
        const               = true
        strong_dependency   = true
        widget_type         = unboundednumber_selector
        default             = 1
        hidden              = true
    }

    Phase
    {
        name                = Phase
        type                = typ_NumberType
        const               = true
        strong_dependency   = true
        default             = 0
        widget_type         = number_selector
        lower_bound         = 0
        higher_bound        = 1
        step_size           = 0.01
        hidden              = true
    }

    Position
    {
        name                = Position
        type                = typ_NumberType
        const               = true
        strong_dependency   = true
        default             = 0
        widget_type         = unboundednumber_selector
        hidden              = true
    }

    signal
    {
        name                = Signal
        type                = typ_StringType
        const               = true
        strong_dependency   = true
        hidden              = true
        widget_type         = combo_box
        values              = sinus,triangle,ramp,rectangle,noize
        default             = sinus
    }

    mode
    {
        name                = Mode
        type                = typ_StringType
        const               = true
        strong_dependency   = true
        hidden              = true
        widget_type         = combo_box
        values              = real,relativ
        default             = real
        help                = real is system time, relativ is relative to the frame rate
    }
}

outputs
{
    Signal
    {
        name                = Signal
        type                = typ_NumberType
    }
}
