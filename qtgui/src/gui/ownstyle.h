/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#ifndef INCLUDED_OWN_STYLE_H
#define INCLUDED_OWN_STYLE_H

#include <qstyle.h>

namespace gui
{

  template <class STYLE>
  class OwnStyle : public STYLE
  {
  public:
    OwnStyle() : STYLE()
    {
#if (QT_VERSION < 300)
      setScrollBarExtent(11, 11);
#endif
    }

#if (QT_VERSION > 300)
    virtual int pixelMetric( QStyle::PixelMetric metric,
                             const QWidget * widget = 0 ) const
    {
      if (metric == QStyle::PM_ScrollBarExtent)
        return 15;
      else
        return STYLE::pixelMetric(metric, widget);
    }
#endif

  protected:
      
  };
}

#endif
