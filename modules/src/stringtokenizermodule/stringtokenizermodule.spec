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
        name                = Entry
        type                = typ_NumberType
        const               = true
        strong_dependency   = true
        widget_type         = number_selector
        lower_bound         = 1
        higher_bound        = 1000
		step_size           = 1
        default             = 1        
    }

}

outputs
{
    token
    {
        name = extracted Token
        type = typ_StringType
    }
}
