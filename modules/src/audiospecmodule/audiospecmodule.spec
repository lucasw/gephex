# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_audiospecmodule
{
    name          = Frequency-Decomposition
    group         = Audio
    deterministic = true
    xpm           = audiospecmodule.xpm
    author        = Mel Duran
    version       = 1000.65-prealpha
    static        = false
}

inputs
{

    audio
    {
        name              = AudioStream
        type              = typ_AudioType
        const             = true
        strong_dependency = true
        help              = blah
    }
}


outputs
{
    f
    {
       name = Frequencies
       type = typ_AudioType
    }
}
