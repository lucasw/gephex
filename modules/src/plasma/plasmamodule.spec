# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_plasmamodule
{
    name          = Plasma
    deterministic = true
    group         = GrafikEffekte
    xpm           = plasmamodule.xpm
    author        = Spencer
    version       = ultra.5
}

inputs
{
    time
    {
      name              = Zeit
      type              = typ_NumberType
      const             = true
      strong_dependency = true
      widget_type       = unboundednumber_selector
      default           = 0
    }

    amp
    {
      name              = Amplitude
      type              = typ_NumberType
      const             = true
      strong_dependency = true
      widget_type       = number_selector
      lower_bound       = 0
      higher_bound      = 1
      step_size         = 0.01
      default           = 1
    }

    frq
    {
    name              = Frequenz
    type              = typ_NumberType
    const             = true
    strong_dependency = true
    widget_type       = unboundednumber_selector
    default           = 1
    }

    b
    {
    name              = Bild
    type              = typ_FrameBufferType
    const             = true
    strong_dependency = true
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
