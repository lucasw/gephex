# This is the spec for the timesource module

mod_timesource
{
    name                = TimeSource
    group               = Number
    deterministic       = false
    xpm                 = timesourcemodule.xpm
    author              = Martin Bayer
    version             = 0.1
}

inputs
{
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
    Time
    {
        name                = Time
        type                = typ_NumberType
    }
}
