# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_audiovismodule
{
        name          = AudioVis
        group         = Audio
        deterministic = true
        xpm           = audiovismodule.xpm
        author        = Mel Duran
        version       = 1000.65-prealpha
        static        = false
}

inputs
{

        audio
        {
                name = AudioStrom
                type = typ_AudioType
                const   =  true
                strong_dependency = true
                help    = blah
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
