# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_twolayermodule
{
    name          = Black and White
    deterministic = true
    group         = Filter
    xpm           = twolayermodule.xpm
    author        = mascht
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
}

outputs
{
    r
    {
        name = Image
        type = typ_FrameBufferType
    }
}
