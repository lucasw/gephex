mod_pos2num
{
	name = Position Zu Zahl Konverter
	deterministic = true
	group = Signale
	xpm = posnummodule.xpm
	author = Barbie&Ken
	version = 0.0.1
}

inputs
{
	pos
	{
		name = Position
		type = typ_PositionType
		const = true
		strong_dependency = true
	}
}

outputs
{
	xresult
	{
		name = X-Position
		type = typ_NumberType
	}

	yresult
	{
		name = Y-Position
		type = typ_NumberType
	}
}
