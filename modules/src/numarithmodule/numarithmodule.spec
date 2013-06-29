# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_numarithmodule
{
    name              = Calculon
    deterministic     = true
    group             = Number
    xpm               = numarithmodule.xpm
    author            = Duran Duran
    version           = 0.65-prealpha
}

inputs
{
    lhs
    {
    name              = x
    type              = typ_NumberType
    const             = true
    strong_dependency = true
    default           = 0
    widget_type       = unboundednumber_selector
    }

    rhs
    {
    name              = y
    type              = typ_NumberType
    const             = true
    strong_dependency = true
    widget_type       = unboundednumber_selector
    default           = 0
    }

    op
    {
    name              = Operation
    type              = typ_StringType
    const             = true
    strong_dependency = true
    hidden            = true
    widget_type       = combo_box
    values            = x+y,x-y,x*y,x/y,x%y,x^y,max(x;y),min(x;y),exp(x),ln(x),sin(x),|x|,x,y,floor(x),ceil(x),round(x)
    default           = x+y
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
