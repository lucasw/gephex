# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_watermodule
{
	name          = Wasser Effekt
	deterministic = false
	group	      = GrafikEffekte
	xpm			  = watermodule.xpm
	author        = coma	
    version       = 0.65-prealpha
}

inputs
{
    numDrops
    {
		name		  = Anzahl-Tropfen
        type              = typ_NumberType
		hidden = true
		const             = true
		strong_dependency = true
		widget_type = number_selector
		lower_bound = 0;
		higher_bound = 30;
    }

	frequency
	{
		name	= Tropffrequenz
		type = typ_NumberType
		const = true
		strong_dependency = true
		widget_type = number_selector
		lower_bound = 10
		higher_bound = 200
	}

	dropSize
	{
		name = Tropfen-Grösse
		type = typ_NumberType
		const = true
		hidden = true
		strong_dependency = true
		widget_type = number_selector
		lower_bound = 5
		higher_bound = 15
	}

	splashStrength
	{
		name	= TropfStärke
		type = typ_NumberType
		const = true
		hidden = true
		strong_dependency = true
		widget_type = number_selector
		lower_bound = 10
		higher_bound = 25
	}

    src
    {
		name 			= Qellbild
        type             	= typ_FrameBufferType
		const             	= true
		strong_dependency 	= true
    }
}

outputs
{
    result
    {
		name = Wasserbild
		type = typ_FrameBufferType
    }
}
