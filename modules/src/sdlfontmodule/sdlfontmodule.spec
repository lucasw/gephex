# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_sdlfontmodule
{
    name           = Font Module
    deterministic  = false
    group          = Font
    xpm            = sdlfontmodule.xpm
    author         = Lt. Uhura
    version        = 2
    enablePatching = true
}

inputs
{
    scroll
    {
        name              = ScrollEffect
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = horizontal_scroll
        widget_type       = combo_box
        values            = vertical_scroll,horizontal_scroll,sine_scroll,static
    }    

    effect_time
    {
        name              = Time
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = false
    }

    options
    {
        name              = Options
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = check_box
        values            = Bold,Italic,Underlined
        default           = 0
    }


    point_size
    {
        name              = FontSize
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = 24
        widget_type       = number_selector
        lower_bound       = 1
        higher_bound      = 256
        step_size         = 1
        help              = This is the selected font's size (index into fonts size table)
    }

    pos
    {
        name                = Position
        type                = typ_PositionType
        hidden              = true
        const               = true
        strong_dependency   = true
        default             = [0.0 1.0]
        help                = Use this to position the font on screen
    }

    font
    {
        name              = Font
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
#       default           = default
        widget_type       = file_selector
        file_mask1        = *.*
        file_mask1_name   = All files
        file_mask2        = *.ttf
        file_mask2_name   = True Type Fonts
        help              = Specify a true type font file here.
    }

    color
    {
        name                = Color
        type                = typ_RGBType
        const               = true
        strong_dependency   = true
        widget_type         = color_selector
        hidden              = true
        default             = [0.7 0.3 0.1]
        help                = The color of the font.
    }

    b
    {
        name                = Image
        type                = typ_FrameBufferType
        const               = true
        strong_dependency   = true
    }


    text_
    {
        name              = ScrollText
        type              = typ_StringType
        const             = true
        strong_dependency = true
        default           = NIX
   }

   patch
   {
        name              = PatchInput
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = 0
        widget_type       = check_box
        values            = Patch
		hidden            = true
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
