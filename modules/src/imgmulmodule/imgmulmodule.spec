# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_imgmulmodule
{
	name          = Bild-Multiplizierer
	deterministic = true
	group	      = Mixer
	xpm	      = imgmulmodule.xpm
	author        = coma
    version       = 1.0.1stable
}

inputs
{
	amount
	{
		name = Amount
		type = typ_NumberType
		const = true
		strong_dependency =true
	}
	input1
	{
		name = Bild1
		type = typ_FrameBufferType
		const = true 
		strong_dependency = true	
	}
	input2
	{
		name = Bild1
		type = typ_FrameBufferType
		const = true 
		strong_dependency = true
	}
}

outputs
{
    result
    {
		name = Bild1 * Bild2
		type = typ_FrameBufferType
    }
}
