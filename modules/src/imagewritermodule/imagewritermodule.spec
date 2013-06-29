# This is the spec file for the image writer module

mod_imagewritermodule
{
	name          = ImageWriter
	deterministic = true
	group	      = Outputs
	xpm	      = imagewritermodule.xpm
	author        = mascht
    	version       = 0.001
	static        = true
}

inputs
{

    prefix
    {
	name		  = Filename
        type              = typ_StringType
	const             = true
	strong_dependency = true
	hidden            = true
	help	= Prefix of the Filename
    }

    in
    {
	name		  = Image
        type              = typ_FrameBufferType
	const             = true
	strong_dependency = true
    }

}

outputs
{
}
