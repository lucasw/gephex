# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_gradnormmodule
{
    name          = Gradientnorm
    deterministic = true
    group         = Filter
    xpm           = gradnormmodule.xpm
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
