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
      if (metric == PM_ScrollBarExtent)
        return 15;
      else
        return STYLE::pixelMetric(metric, widget);
    }
#endif

  protected:
      
  };
}

#endif
