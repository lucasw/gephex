# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_font3dmodule
{
    name          = Font3D
    deterministic = false
    group         = Font
    xpm           = font3dmodule.xpm
    author        = Lt. Uhura
    version       = 2
}

inputs
{
    text
    {
        name              = Text
        type              = typ_StringType
        const             = true
        strong_dependency = true
		default           = NIX
    }

    pos
    {
        name                = Position
        type                = typ_PositionType
        const               = true
        strong_dependency   = true
		default             = [0.5 0.5]
    }

    font
    {
        name                = Font
        type                = typ_FontType
        const               = true
        strong_dependency   = true
        widget_type         = font_selector
        hidden              = true
		default             = [{Arial} 0 12 400 false false]
    }

    block
    {
        name                = Thickness
        type                = typ_NumberType
        const               = true
        strong_dependency   = true
        widget_type         = number_selector
        higher_bound        = 10
        lower_bound         = 0
        default             = 0.5
        step_size           = 0.0625
        hidden              = true
    }

    color
    {
        name                = Colour
        type                = typ_RGBType
        const               = true
        strong_dependency   = true
        widget_type         = color_selector
        hidden              = true
		default             = [0.7 0.3 0.1]
    }

    xrot
    {           
        name                = XRotation
        type                = typ_NumberType
        const               = true
        strong_dependency   = true
        widget_type         = number_selector
        hidden              = true
        higher_bound        = 20
        lower_bound         = 0
        step_size           = 0.5
		default             = 0
    }

    yrot
    {           
        name                = YRotation
        type                = typ_NumberType
        const               = true
        strong_dependency   = true
        widget_type         = number_selector
        hidden              = true
        higher_bound        = 20        
        lower_bound         = 0
        step_size           = 0.5
		default             = 0
    }

    zrot
    {           
        name                = ZRotation
        type                = typ_NumberType
        const               = true
        strong_dependency   = true
        widget_type         = number_selector
        hidden              = true
        higher_bound        = 20
        lower_bound         = 0
        step_size           = 0.5
    }

    b
    {
        name                = Image
        type                = typ_FrameBufferType
        const               = true
        strong_dependency   = true
    }

}

outputs
{
    r
    {
    name = Image
    type = typ_FrameBufferType
    }
}
