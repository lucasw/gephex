#  white noise generator
#  Copyright (C) 2004 Martin Bayer
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
#  You can reach me via email: martin@gephex.org

mod_noisemodule
{
    name              = Noise Generator
    deterministic     = false
    group             = Sources
    xpm               = noisemodule.xpm
    author            = mascht
    version           = 0.1
}

inputs
{

    monochrom
    {
        name              = Monochrom
        type              = typ_NumberType
        const             = true
        strong_dependency = true
		widget_type       = radio_button
        default           = 0
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
       higher_bound       = 2048
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
       higher_bound       = 2048
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
