#ifndef INCLUDED_COLOR_VIEW_H
#define INCLUDED_COLOR_VIEW_H

#include "gui/typeview.h"

namespace gui
{

  class ColorViewConstructor : public TypeViewConstructor
  {
  public:
    ColorViewConstructor();
    virtual TypeView* construct(QWidget* parent,
				const ParamMap& params) const;
  };

}

#endif
