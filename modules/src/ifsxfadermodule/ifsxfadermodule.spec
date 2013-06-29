#sepc file for the ifs xfader module

mod_ifsxfadermodule
{
	name          = Ifs_x_fader
	deterministic = true
	group	      = Ifs
	xpm	      = ifsxfadermodule.xpm
	author        = MC Flashfader
    	version       = 0.65-pregamma
	enablePatching = false
}

inputs
{
    x
    {
	name		  = Fader
        type              = typ_NumberType
	const             = true
	default           = 0
	strong_dependency = true
    }

    1
    {
	name 			= ifs1
        type             	= typ_IfsType
	const             	= true
	strong_dependency 	= false
    }

    2
    {
	name 			= Ifs2
        type             	= typ_IfsType
	const             	= true
	strong_dependency 	= false
    }
}

outputs
{
    r
    {
	name = mixedifs
	type = typ_IfsType
    }
}
