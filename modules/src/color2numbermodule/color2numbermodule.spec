# Color to number module, converts colors to numbers

mod_color2numbermodule
{
    name          = Colour to RGB
    deterministic = true
    group         = Colour
    xpm           = color2numbermodule.xpm
    author        = coma
    version       = 0.65-pregammaalphabetaficken
}

inputs
{
    color
    {
      name              = Colour
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
      name = Red
      type = typ_NumberType
    }
    g
    {
      name = Green
      type = typ_NumberType
    }
    b
    {
      name = Blue
      type = typ_NumberType
    }
}
