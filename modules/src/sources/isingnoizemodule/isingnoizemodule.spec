#  Ising noize effect.
#  Copyright (C) 2003 Georg Seidel
#  This file is part of GePhex.
#
#  GePhex is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public
#  License as published by the Free Software Foundation; either
#  version 2 of the License, or (at your option) any later version.
#
#  GePhex is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
#  General Public License for more details.
#
#  You should have received a copy of the GNU General Public
#  License along with GePhex; if not, write to the Free
#  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
#  02111-1307 USA.  
#
#  You can reach me via email: georg.seidel@web.de

mod_isingnoizemodule
{
    name              = Isingnoize
    deterministic     = false
    group             = Sources
    xpm               = isingnoizemodule.xpm
    author            = Tellerwaescher
    version           = 0.1
}

inputs
{
    temp
    {
        name              = Temperature
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        help              = Relative temperature
        widget_type       = unboundednumber_selector
        default           = 0
        lower_bound       = 0
        higher_bound      = 6
    }

    border_growth
    {
        name              = Bordergrowth
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = 4
        widget_type       = number_selector
        lower_bound       = 1
        higher_bound      = 16
        step_size         = 0.5
    }

    spont_growth
    {
        name              = Spontaneousgrowth
        type              = typ_NumberType
        const             = true
        strong_dependency = true
        hidden            = true
        default           = 8
        widget_type       = number_selector
        lower_bound       = 1
        higher_bound      = 48
        step_size         = 0.5
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
       lower_bound        = 1
       higher_bound       = 1024
       step_size          = 1
       display_format     = fixed
       precision          = 0
       help               = Size of the resulting image
    }

    outy
    {
       name               = outy
       type               = typ_NumberType
       const              = true
       strong_dependency  = true
       hidden             = true
       default            = 480
       widget_type        = number_selector
       lower_bound        = 1
       higher_bound       = 1024
       step_size          = 1
       display_format     = fixed
       precision          = 0
       help               = Size of the resulting image
    }
}

outputs
{
    r
    {
        name              = Image
        type              = typ_FrameBufferType
    }
}
