#include "picmanager.h"

#include <QtGui/qpainter.h>

#include "node.xpm"

namespace gui
{

  namespace
  {
    void draw_border(QPixmap& pixmap, const QColor& border_col)
    {
       QPainter p( &pixmap );
       //p.setBrush( border_col );
       p.setPen( Qt::SolidLine );
       p.drawRect( QRect(0, 0, 8, 8) );
       p.end();
    }

    QPixmap create_pixmap(const QColor& col)
    {
      QPixmap pixmap(8,8);

      pixmap.fill(col);

      draw_border(pixmap, Qt::black);

      return pixmap;
    }

    QColor color_from_type(const std::string& type)
    {
      if (type == "typ_NumberType")
        {
          return QColor(199, 20, 35);
        }
      else if (type == "typ_FrameBufferType")
        {
          return QColor(30, 30, 190);
        }
      else if (type == "typ_MidiType")
        {
          return QColor(255, 255, 0);
        }
      else if (type == "typ_AudioType")
        {
          return QColor(200, 53, 188);
        }
      else if (type == "typ_PositionType")
        {
          return QColor(174, 36, 202);
        }
      else
        {
          return QColor(25, 170, 37);
        }
    }

    QColor free_color(const QColor& col)
    {
      return QColor(col.red() / 2, col.green() / 2, col.blue() / 2);
    }

  }

  QPixmap PicManager::node_pic() const
  {
    return QPixmap(node_xpm);
  }

  QPixmap PicManager::plug_pic(const std::string& type, bool connected) const
  {
    QColor col = color_from_type(type);
    if (!connected)
      col = free_color(col);

    return create_pixmap(col);
  }
}
