#ifndef INCLUDED_POSITION_VIEW_H
#define INCLUDED_POSITION_VIEW_H

#include "gui/typeview.h"

namespace gui
{
  class PositionViewConstructor : public TypeViewConstructor
  {
  public:
    PositionViewConstructor();
    virtual TypeView* construct(QWidget* parent, const ParamMap& params) const;
  };
}
#endif
