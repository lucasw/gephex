# specification of the OpenGL videooutput module

mod_gloutmodule
{
    name          = OpenGL
    deterministic = false
    group	  = Outputs
    xpm	          = glmonitor.xpm
    author        = Duran Duran
    version       = 0.61-prealpha
    static        = true
}

inputs
{
    in
    {
	name		  = Bild
        type              = typ_FrameBufferType
	const             = true
	strong_dependency = true
    }

    xsize
    {
	name	          = xsize
	type	          = typ_NumberType
	const	          = true
	strong_dependency = true
	hidden	          = true
	default           = 320
	widget_type       = number_selector
	lower_bound       = 0
	higher_bound      = 1280
	step_size         = 1
	help	          = [ Set the x-size of the output window. If set to 0 the window size is set to the size of the input ]
    }

    ysize
    {
	name	          = ysize
	type	          = typ_NumberType
	const	          = true
	strong_dependency = true
	hidden	          = true
	default           = 240
	widget_type       = number_selector
	lower_bound       = 0
	higher_bound      = 1024
	step_size         = 1
	help	          = [ Set the y-size of the output window. If set to 0 the window size is set to the size of the input ]
    }
}

outputs
{
}
