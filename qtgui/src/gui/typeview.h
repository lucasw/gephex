/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#ifndef INCLUDED_TYPE_VIEW_H
#define INCLUDED_TYPE_VIEW_H

#include <string>
#include <map>

//#include <QtGui/qframe.h>
#include <QtGui/qwidget.h>

#include "utils/buffer.h"


class QBoxLayout;

namespace gui
{

  class TypeView : public QWidget
  {
    Q_OBJECT
  public:
    typedef std::map<std::string, std::string> ParamMap;
    TypeView(QWidget* parent, const ParamMap& params);

    virtual ~TypeView();
  
    virtual void valueChange(const utils::Buffer& newValue) = 0;

    signals:

    void valueChanged(const utils::Buffer& newValue);

  protected:
    QBoxLayout* m_layout;

  private:
    ParamMap m_params;
  };

  class TypeViewConstructor
  {
  public:
    typedef TypeView::ParamMap ParamMap;

    TypeViewConstructor(const std::string& name,
			const std::string& viewID);

    virtual ~TypeViewConstructor();

    const std::string& getName();
    const std::string& getViewID();

    virtual TypeView* construct(QWidget* parent,
				const ParamMap&) const= 0;

  private:
    const std::string m_name;
    const std::string m_viewID;

  };
 
}

#endif
