#ifndef INCLUDE_SLIDER_NUMBER_VIEW_H
#define INCLUDE_SLIDER_NUMBER_VIEW_H

#include "gui/typeview.h"

namespace gui
{
  class HSliderNumberViewConstructor : public TypeViewConstructor
  {
  public:
    HSliderNumberViewConstructor();
    virtual TypeView* construct(QWidget* parent, const ParamMap&) const;
  };

  class VSliderNumberViewConstructor : public TypeViewConstructor
  {
  public:
    VSliderNumberViewConstructor();
    virtual TypeView* construct(QWidget* parent, const ParamMap&) const;
  };

}

#endif
