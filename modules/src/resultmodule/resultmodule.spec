# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_resultmodule
{
    name          = Result
    deterministic = true
    group         = Outputs
    xpm           = resultmodule_icon.xpm
    author        = Duran Duran
    version       = 0.61-prealpha
}

inputs
{

    in
    {
        name              = Eingang
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
        widget_type       = radio_button
        true_value        = 1
        false_value       = 0
        default           = 1
    }

}

outputs
{
}
