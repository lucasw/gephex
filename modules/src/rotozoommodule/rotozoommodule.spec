# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_rotozoommodule
{
    name           = Rotary Zoomer
    deterministic  = true
    group          = GrafikEffekte
    xpm            = rotozoommodule.xpm
    author         = Miss Piggy
    version        = -1.0
    enablePatching = true
}

inputs
{
    zoom
    {
        name              = Zoom
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 4
        step_size         = 0.04
        default           = 1
    }

    rot
    {
        name              = Drehung
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        lower_bound       = 0
        higher_bound      = 360
        step_size         = 1
        default           = 0
    }

    disp
    {
        name              = Verschiebung
        type              = typ_PositionType
        const             = true
        default           = [0.5 0.5]
        strong_dependency = true
    }

    texture
    {
        name              = Textur
        type              = typ_FrameBufferType
        const             = true
        strong_dependency = true
    }

    background
    {
        name              = Hintergrund
        type              = typ_FrameBufferType
        const             = false
        strong_dependency = false
        help              = Das Hintergrundbild
    }

    copy_background
    {
        name              = Hintergrund_Kopieren
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = radio_button
        true_value        = 1
        false_value       = 0
        default           = 0
        help              = Soll Hintergrund kopiert werden oder direkt reingeschrieben werden?
    }

    routine
    {
        name              = Rotozoom-Routine
        type              = typ_StringType
        const             = true
        strong_dependency = true
        hidden            = true
        widget_type       = combo_box
        values            = regular,poly
        default           = regular
        help              = regular ist besser getestet, poly ist schneller
    }

    outx
    {
       name               = outx
       type               = typ_NumberType
       const              = true
       strong_dependency  = true
       hidden             = true
       default            = 640
       widget_type        = number_selector
       lower_bound        = 0
       higher_bound       = 1024
       step_size          = 1
       help = Groesse des Ergebnis-Bildes
    }

    outy
    {
       name                     = outy
       type                     = typ_NumberType
       const                    = true
       strong_dependency        = true
       hidden                   = true
       default                  = 480
       widget_type              = number_selector
       lower_bound              = 0
       higher_bound             = 1024
       step_size                = 1
       help                     = Groesse des Ergebnis-Bildes
    }

}

outputs
{
    r
    {
        name = Bild
        type = typ_FrameBufferType
    }
}


