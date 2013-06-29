# Das ist die Spezifikation fuer das SerialOutput Module. Blabla

mod_serialoutput
{
    name          = SerialOutput
    deterministic = true
    group         = Outputs
    static        = true
    xpm           = serialicon.xpm
    author        = Duran Duran
    version       = 0.61-prealpha
}

inputs
{

    control
    {
        name              = Steuerung
        type              = typ_StringType
        const             = true
        strong_dependency = true
        default           = []
        widget_type       = videowall_edit
    }

    key_change
    {
        name              = Tastendruck
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        default           = -1
        widget_type       = none
        toggle_keys       = 0[0,100];1[1,101];2[2,102];3[3,103];4[4,104];5[5,105];6[6,106];7[7,107];8[8,108];9[9,109];F1[10,110];F2[11,111];F3[12,112];F4[13,113];F5[14,114];F6[15,115];F7[16,116];F8[17,117];
    }
}

outputs
{
}
