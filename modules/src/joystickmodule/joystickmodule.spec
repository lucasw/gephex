# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_joystickmodule
{
    name          = Joystick
    group         = Quellen
    deterministic = false
    xpm           = joystickmodule.xpm
    author        = A PATHETIC HUMAN
    version       = -0.9
    static = false
}

inputs
{
    joy_id
    {
    name = Joystick_ID
    type = typ_NumberType
	strong_dependency = true
	const = true

    hidden = true	
    widget_type =   number_selector
    lower_bound = 0
    higher_bound = 4
    absolute = true
    default = 0
    }
}


outputs
{
    signal_x
    {
    name = X_Richtung
    type = typ_NumberType
    }

    signal_y
    {
    name = Y_Richtung
    type = typ_NumberType
    }

    button_1
    {
    name = Button_1
    type = typ_NumberType
    }    

    button_2
    {
    name = Button_2
    type = typ_NumberType
    }
}
