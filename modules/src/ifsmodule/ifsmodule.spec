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
	higher_bound = 1024
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
	higher_bound = 1024
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

    amount
    {
	name	=	lightness
	type	=	typ_NumberType
	const	=	true
	strong_dependency = true
	hidden	= true
	widget_type	=	number_selector
	lower_bound	= 0
	higher_bound = 1
	step_size = 0.01
	default	= 0.2
	help	= lightness
    }

    ifs
    {
	name	=	ifsin
	type	=	typ_IfsType
	const	=	true
	strong_dependency = true
    }

    num_rec
    {
	name	=	recdeep
	type	=	typ_NumberType
	const	=	true
	strong_dependency = true
	hidden	= true
	widget_type	=	number_selector
	lower_bound	= 0
	higher_bound = 255
	default	= 5
	help	= puh
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
