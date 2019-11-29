# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_resultmodule
{
    name          = Result
    deterministic = true
    group         = Number
    xpm           = resultmodule_icon.xpm
    author        = Duran Duran
    version       = 0.61-prealpha
}

inputs
{

    in
    {
        name              = Input
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0
        widget_type       = unboundednumber_selector
        toggle_keys       = a[1.0,0]
        keys              = b[0.5];ctrl-b[0.25]
    }

    shut_up
    {
        name              = ShutUp!
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true        
        widget_type       = check_box
        values            = a,b
        default           = 3
    }

}

outputs
{
}
