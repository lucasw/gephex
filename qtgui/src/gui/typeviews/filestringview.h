#ifndef INCLUDED_FILE_STRING_VIEW_H
#define INCLUDED_FILE_STRING_VIEW_H

#include <string>

#include "gui/typeview.h"

namespace gui
{
  class FileStringViewConstructor : public TypeViewConstructor
  {
  public:
    FileStringViewConstructor(const std::string& media_path);
    virtual TypeView* construct(QWidget* parent,
				const ParamMap& params) const;

  private:
    std::string m_media_path;

  };

}

#endif
