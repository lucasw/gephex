#ifndef INCLUDED_FRAME_VIEW_H
#define INCLUDED_FRAME_VIEW_H

#include "gui/typeview.h"

namespace gui
{

  class FrameViewConstructor : public TypeViewConstructor
  {
  public:
    FrameViewConstructor();
    virtual TypeView* construct(QWidget* parent,
				const ParamMap& params) const;
  };

}

#endif
