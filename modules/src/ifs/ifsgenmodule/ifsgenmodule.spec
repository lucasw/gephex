# spec of the ifs module
mod_ifsgenmodule
{
	name          = Ifsdatagenerator
	deterministic = false
	group	      = Ifs
	xpm	      = ifsgenmodule.xpm
	author        = MurMur
    	version       = pre0.0.3
}

inputs
{
    num_fun
    {
	name	=	funnum
	type	=	typ_NumberType
	const	=	true
	strong_dependency = true
	hidden	= true
	widget_type	=	number_selector
	lower_bound	= 1
	higher_bound = 25
	step_size = 1
	default	= 6
	help	= phu
    }
}

outputs
{
    ifs
    {
	name = ifsdata
	type = typ_IfsType
    }
}
