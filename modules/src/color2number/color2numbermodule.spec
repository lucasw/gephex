# Color to number module, converts colors to numbers

mod_color2numbermodule
{
    name          = Farbe zu Zahl Konvertierer
    deterministic = true
    group         = Farbe
    xpm           = color2numbermodule.xpm
    author        = coma
    version       = 0.65-pregammaalphabetaficken
}

inputs
{
    color
    {
      name              = Farbe
      type              = typ_RGBType
      const             = true
      strong_dependency = true
      default           = [0.5 0.5 0.5]
    }
}

outputs
{
    r
    {
      name = Rot
      type = typ_NumberType
    }
    g
    {
      name = Gruen
      type = typ_NumberType
    }
    b
    {
      name = Blau
      type = typ_NumberType
    }
}
