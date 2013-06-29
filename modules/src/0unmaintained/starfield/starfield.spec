# blablablabla starfield monstereffect....


mod_starfield
{
	name          = Moving Starfield
	deterministic = true
	group	      = Quellen
	xpm	      = starfield.xpm
	author        = Coma
    version       = 0.61-betakarotin
}

inputs
{
	colorStars
	{
		name = Farbe Sterne
		type = typ_RGBType
		const = true 
		strong_dependency = true
		hidden = true
		widget_type       = color_selector
	}
	colorBG
	{	
		name = Farbe Hintergrund
		type = typ_RGBType
		const = true
		strong_dependency = true 
		hidden = true
		widget_type       = color_selector
	}
	speed
	{
		name = Geschwindigkeit
		type = typ_NumberType
		const = true 
		strong_dependency = true
	}
	currentNumStars
	{
		name = Anzahl Sterne
		type = typ_NumberType
		const = true 
		strong_dependency = true
	}

}

outputs
{
    result
    {
		name = StarField
        type = typ_FrameBufferType
    }
}
