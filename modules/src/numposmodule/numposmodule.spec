mod_num2pos
{
	name = X+Y->Position
	deterministic = true
	group = Signale
	xpm = numposmodule.xpm
	author = Kecke Koksnase
	version = 0.0.1
}

inputs
{
	xpos
	{
		name = X-Position
		type = typ_NumberType
		const = true
		strong_dependency = true
	}
	ypos
	{
		name = Y-Position
		type = typ_NumberType
		const = true
		strong_dependency = true
	}
}

outputs
{
	result
	{
		name = Ergebniss-Position
		type = typ_PositionType
	}
}
