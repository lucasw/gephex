# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_audiobdmodule
{
        name          = Beat
        group         = Audio
        deterministic = true
        xpm           = audiobdmodule.xpm
        author        = Mel Duran
        version       = 1000.65-prealpha
        static        = false
}

inputs
{

   audio
   {
       name              = AudioStrom
       type              = typ_AudioType
       const             = true
       strong_dependency = true
       help              = blah
   }

   thr
   {
       name              = Threshold
       type              = typ_NumberType
       hidden            = true
       widget_type       = number_selector
       lower_bound       = 0
       higher_bound      = 1
       step_size         = 0.01
       default           = 0.3
       strong_dependency = true
       const             = true
       help              = 0=sensitiv 1=wenig sensitiv
    }

   algo
   {
       name              = Algorithmus
       type              = typ_StringType
       const             = true
       strong_dependency = true
       hidden            = true
       widget_type       = combo_box
       values            = exp,avg
       default           = exp
   }
}


outputs
{
    b
    {
       name = Beat
       type = typ_NumberType
    }
}
