# Number to color module, converts numbers to colors

mod_number2colormodule
{
	name          = Zahl zu Farbe Konvertierer
	deterministic = true
	group	      = Farbe
	xpm	      = number2colormodule.xpm
	author        = coma
    	version       = 0.65-pregammaalphabetaficken
}

inputs
{
    r
    {
	name		  = Rot
        type              = typ_NumberType
	const             = true
	strong_dependency = true
	lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
        default           = 0.5
    }

    g
    {
	name		  = Gruen
        type              = typ_NumberType
	const             = true
	strong_dependency = true
	lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
        default           = 0.5
    }

    b
    {
	name		  = Blau
        type              = typ_NumberType
	const             = true
	strong_dependency = true
	lower_bound       = 0
        higher_bound      = 1
        step_size         = 0.01
        default           = 0.5
    }
}

outputs
{
    color
    {
	name = Farbe
	type = typ_RGBType
    }
}
