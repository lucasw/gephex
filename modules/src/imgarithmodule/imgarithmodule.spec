# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_imgarithmodule
{
    name          = Image Calculon
    deterministic = true
    group         = Mixer
    xpm           = imgarithmodule.xpm
    author        = coma
    version       = 1.0.1stable
}

inputs
{
    amount
    {
        name              = c
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = hslider
        lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
        default           = 0
    }

    input1
    {
        name              = x
        type              = typ_FrameBufferType
        const             = true 
        strong_dependency = true    
    }

    input2
    {
        name              = y
        type              = typ_FrameBufferType
        const             = true 
        strong_dependency = false
    }

    mmx
    {
        name              = Use-MMX
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = combo_box
        values            = yes,no
        default           = yes
    }


    op
    {
        name              = Operation
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = combo_box
        values            = x + c*y,x - c*y,(1-c)*x + c*(x*y),x + c,x - c,x * 4*c,1 - x
        default           = [x + c*y]
        help              = x and y are the input images, c is the number input
    }


}

outputs
{
    result
    {
        name = Result
        type = typ_FrameBufferType
    }
}
