# Das ist die Spezifikation fuer das imagebuffermodule

mod_imagebuffermodule
{
    name          = Buffer
    deterministic = true
    group         = Filter
    xpm           = imagebuffermodule.xpm
    author        = g3org
    version       = 0.1
}

inputs
{
    bsize
    {
        name                    = Buffersize
        type                    = typ_NumberType
        const                   = true
        strong_dependency       = true
        default                 = 1
        widget_type             = number_selector
        lower_bound             = 1
        higher_bound            = 250
        step_size               = 1
        help                    = Size of the buffer (in frames)
    }

    bpos
    {
        name                    = Position
        type                    = typ_NumberType
        const                   = true
        strong_dependency       = true
        widget_type             = number_selector
        lower_bound             = 0
        higher_bound            = 1
        default                 = 0
        help                    = Position in the buffer: 0 = oldest image, 1 = newest image
    }

    record
    {
        name                    = Record
        type                    = typ_NumberType
        const                   = true
        strong_dependency       = true
        widget_type             = radio_button
        true_value              = 1
        false_value             = 0
        default                 = 1
        help                    = Record new images or keep the old ones
    }

    b
    {
        name                    = Image
        type                    = typ_FrameBufferType
        const                   = true
        strong_dependency       = true
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
