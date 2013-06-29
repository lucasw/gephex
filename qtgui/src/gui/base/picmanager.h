#ifndef INCLUDED_PICMANAGER_H
#define INCLUDED_PICMANAGER_H

#include <string>

#include <QtGui/qpixmap.h>

namespace gui
{
  class PicManager
  {
  public:
    QPixmap node_pic() const;
    QPixmap plug_pic(const std::string& type, bool connected) const;
  };
}

#endif
