# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_audioaddmodule
{
    name          = Adder
    group         = Audio
    deterministic = true
    xpm           = audioaddmodule.xpm
    author        = Mel Duran
    version       = 1000.65-prealpha
    static        = false
}

inputs
{

    lhs
    {
        name              = Signal1
        type              = typ_AudioType
        const             = true
        strong_dependency = true
    }

    w_lhs
    {
        name              = AmpLeft
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 1
    }

    rhs
    {
        name              = Signal2
        type              = typ_AudioType
        const             = true
        strong_dependency = true
    }

    w_rhs
    {
        name              = AmpRight
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 1
    }

    thr
    {
        name              = Threshold
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = 512
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 4096
        step_size         = 1
     }

     flush
     {
	name              = FlushBuffers
	type              = typ_NumberType
	const             = true
	strong_dependency = true
	hidden            = true
	widget_type       = radio_button
     }

}


outputs
{
   
    r
    {
       name = AddedSignal
       type = typ_AudioType
    }
}
