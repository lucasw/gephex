#ifndef INCLUDED_RADIO_NUMBER_VIEW_H
#define INCLUDED_RADIO_NUMBER_VIEW_H

#include "gui/typeview.h"

namespace gui
{

  class RadioNumberViewConstructor : public TypeViewConstructor
  {
  public:
    RadioNumberViewConstructor();
    virtual TypeView* construct(QWidget* parent, const ParamMap& params) const;
  };

}

#endif
