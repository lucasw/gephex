# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_addmodule
{
	name          = Addierer
	deterministic = true
	group	      = shit
	xpm			  = addmodule_icon.xpm
	author        = Duran Duran
    version       = 0.65-prealpha
}

inputs
{
    lhs
    {
	name		  = Summand1
        type              = typ_NumberType
	const             = true
	strong_dependency = true
    }

    rhs
    {
	name 			= Summand2
        type             	= typ_NumberType
	const             	= true
	strong_dependency 	= true
    }
}

outputs
{
    r
    {
	name = Summe
	type = typ_NumberType
    }
}
