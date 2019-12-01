#include "picmanager.h"

#include <QtGui/qpainter.h>

#include "node.xpm"

namespace gui {

namespace {
void draw_border(QPixmap &pixmap, const QColor &border_col) {
  QPainter p(&pixmap);
  // p.setBrush( border_col );
  p.setPen(Qt::SolidLine);
  p.drawRect(QRect(0, 0, pixmap.width(), pixmap.height()));
  p.end();
}

QPixmap create_pixmap(const QColor &col, const size_t width, const size_t height) {
  QPixmap pixmap(width, height);

  pixmap.fill(col);

  draw_border(pixmap, Qt::black);

  return pixmap;
}

QColor color_from_type(const std::string &type) {
  if (type == "typ_NumberType") {
    return QColor(255, 20, 35);
  } else if (type == "typ_FrameBufferType") {
    return QColor(30, 20, 255);
  } else if (type == "typ_MidiType") {
    return QColor(255, 0, 255);
  } else if (type == "typ_AudioType") {
    return QColor(200, 153, 188);
  } else if (type == "typ_PositionType") {
    return QColor(255, 255, 0);
  } else {
    return QColor(85, 80, 87);
  }
}

QColor free_color(const QColor &col) {
  return QColor(col.red() * 0.65, col.green() * 0.65, col.blue() * 0.65);
}

} // namespace

QPixmap PicManager::node_pic() const { return QPixmap(node_xpm); }

QPixmap PicManager::plug_pic(const std::string &type, const bool connected,
    const size_t width, const size_t height) const {
  QColor col = color_from_type(type);
  if (!connected)
    col = free_color(col);

  return create_pixmap(col, width, height);
}
} // namespace gui
