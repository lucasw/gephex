# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_centermodule
{
    name          = Center
    deterministic = true
    group         = Position
    xpm	          = centermodule.xpm
    author        = Martin Bayer
    version       = 0.1
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
       name              = Center
       type              = typ_PositionType
    }
}
