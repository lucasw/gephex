# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_funparsemodule
{
    name              = FunctionParser
    deterministic     = true
    group             = Number
    xpm               = funparsemodule.xpm
    author            = Georg Seidel
    version           = 0.8
}

inputs
{
    exp
    {
      name              = Expression
      type              = typ_StringType
      const             = true
      strong_dependency = true
      hidden            = true
      default           = 0
      help              = Enter an arithmetic expression here (the inputs can be accessed through the variables x1 to x4, e.g. 'x1 + x2').
    }

    x1
    {
      name              = x1
      type              = typ_NumberType
      const             = true
      strong_dependency = false
      default           = 0
      widget_type       = unboundednumber_selector
    }

    x2
    {
      name              = x2
      type              = typ_NumberType
      const             = true
      strong_dependency = false
      widget_type       = unboundednumber_selector
      default           = 0
    }

    x3
    {
      name              = x3
      type              = typ_NumberType
      const             = true
      strong_dependency = false
      widget_type       = unboundednumber_selector
      default           = 0
    }

    x4
    {
      name              = x4
      type              = typ_NumberType
      const             = true
      strong_dependency = false
      widget_type       = unboundednumber_selector
      default           = 0
    }
}

outputs
{
    r
    {
      name              = Result
      type              = typ_NumberType
    }
}
