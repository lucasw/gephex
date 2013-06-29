# This is the spec file for the ifs module

mod_ifsmodule
{
	name          = IFS
	deterministic = false
	group	      = Ifs
	xpm	      = ifsmodule.xpm
	author        = mascht
    	version       = 0.001
	static        = true
}

inputs
{
    x_size
    {
	name	=	Größe(x)
	type	=	typ_NumberType
	const	=	true
	strong_dependency = true
	hidden	= true
	widget_type	=	number_selector
	lower_bound	= 0
	higher_bound = 2048
	default	= 0
	step_size = 1
	help	= Wenn x_size und y_size > 0, wird das bild auf xsize x ysize skaliert
    }

    y_size
    {
	name	=	Größe(y)
	type	=	typ_NumberType
	const	=	true
	strong_dependency = true
	hidden	= true
	widget_type	=	number_selector
	lower_bound	= 0
	higher_bound = 2048
	default	= 0
	step_size = 1
	help	= Wenn x_size und y_size > 0, wird das bild auf xsize x ysize skaliert
    }

    num_dot
    {
	name	=	dotnum
	type	=	typ_NumberType
	const	=	true
	strong_dependency = true
	hidden	= true
	widget_type	= unboundednumber_selector
	default	= 10000
	help	= try something 5000 - 100000
    }

    ifs
    {
	name	=	ifsin
	type	=	typ_IfsType
	const	=	true
	strong_dependency = true
    }

}

outputs
{
    out
    {
	name		  = Frame
        type              = typ_FrameBufferType
    }
}
