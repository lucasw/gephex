#ifndef INCLUDED_FONT_VIEW_H
#define INCLUDED_FONT_VIEW_H

#include "gui/typeview.h"

namespace gui
{

  class FontViewConstructor : public TypeViewConstructor
  {
  public:
    FontViewConstructor();
    virtual TypeView* construct(QWidget* parent,
				const ParamMap& params) const;
  };

}

#endif
