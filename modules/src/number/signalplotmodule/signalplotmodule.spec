# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_signalplotmodule
{
    name          = SignalPlotter
    group         = Number
    deterministic = false
    xpm           = signalplotmodule.xpm
    author        = Mel Duran
    version       = 0.5
}

inputs
{
    val
    {
        name              = Number
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        help              = blah
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
