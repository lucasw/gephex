#sepc file for the ifs xfader module

mod_stringtokenizermodule
{
    name          = Stringtokenizer
    deterministic = true
    group         = Textprocessing
    xpm           = stringtokenizermodule.xpm
    author        = da office masta
    version       = 0.0.4    
}

inputs
{
    string
    {
        name              = Inputstring
        type              = typ_StringType
        widget_type       = file_selector
        const             = true
        strong_dependency = true
    }

    entry
    {
        name              = Entry
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        widget_type       = number_selector
        lower_bound       = 1
        higher_bound      = 1000
        step_size         = 1
        display_format    = fixed
        precision         = 0
        default           = 1        
    }

}

outputs
{
    len
    {
       name = Number_of_Tokens
       type = typ_NumberType
    }

    token
    {
        name = extracted_Token
        type = typ_StringType
    }
}
