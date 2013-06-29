# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_colorcyclermodule
{
	name          = Color Cycler
	group	      = Farben
	deterministic = false
	xpm	      = colorcyclermodule.xpm
	author        = Marlene Dietrich
    	version       = 100
}

inputs
{
    mode
    {
	name			= Modus
        type             	= typ_StringType
	const             	= true
	strong_dependency 	= true
	hidden                  = true
	widget_type             = combo_box
	values			= random
	default                 = random
    }
}

outputs
{
    Farbe
    {
	name = Signal
	type = typ_RGBType
    }
}
