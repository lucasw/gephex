# Color to number module, converts colors to numbers

mod_color2numbermodule
{
	name          = Farbe zu Zahl Konvertierer
	deterministic = true
	group	      = Filter
	xpm	      = color2numbermodule.xpm
	author        = coma
    	version       = 0.65-pregammaalphabetaficken
}

inputs
{
    color
    {
	name		  = Farbe
        type              = typ_RGBType
	const             = true
	strong_dependency = true
    }
}

outputs
{
    number
    {
	name = Zahl
	type = typ_NumberType
    }
}
