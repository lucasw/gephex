# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_bwmodule
{
    name          = Grayscale
    deterministic = true
    group         = Filter
    xpm	          = bwmodule.xpm
    author        = Turnvater Jan
    version       = ich bin froh daﬂ ich ein alpha bin
}

inputs
{
    1
    {
       name  	         = Bild
       type              = typ_FrameBufferType
       const             = true
       strong_dependency = true
    }
}

outputs
{
    r
    {
       name              = Bild
       type              = typ_FrameBufferType
    }
}
