# spec file for the audioenergie module

mod_audioenergymodule
{
    name          = Energy
    group         = Audio
    deterministic = true
    xpm           = audioenergymodule.xpm
    author        = Mel Duran
    version       = 1000.65-prealpha
    static        = false
}

inputs
{

    audio
    {
        name              = AudioStream
        type              = typ_AudioType
        const             = true
        strong_dependency = true
        help              = blah
    }

   amp
    {
        name                = Responsivity
        type                = typ_NumberType
        const               = true
        strong_dependency   = true
        widget_type         = unboundednumber_selector
        default             = 0
        hidden              = true
    }
}


outputs
{
    e1
    {
       name = Low
       type = typ_NumberType
    }
    e2
    {
       name = Middle1
       type = typ_NumberType
    }
    e3
    {
       name = Middle2
       type = typ_NumberType
    }
    e4
    {
       name = High
       type = typ_NumberType
    }
}
