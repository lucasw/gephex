# Number to color module, converts numbers to colors

mod_number2colormodule
{
	name          = Zahl zu Farbe Konvertierer
	deterministic = true
	group	      = Filter
	xpm	      = number2colormodule.xpm
	author        = coma
    	version       = 0.65-pregammaalphabetaficken
}

inputs
{
    number
    {
	name		  = Zahl
        type              = typ_NumberType
	const             = true
	strong_dependency = true
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
