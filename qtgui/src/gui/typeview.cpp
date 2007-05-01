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

#include "typeview.h"

#include <iostream>

#include <QtGui/qwidget.h>
#include <QtGui/QHBoxLayout>

namespace gui 
{

TypeView::TypeView(QWidget* parent, const ParamMap& params)
  : QWidget(parent,  0), m_params(params)
{
  setFocusPolicy(Qt::ClickFocus);
  setSizePolicy(QSizePolicy::MinimumExpanding,
                QSizePolicy::MinimumExpanding);

  m_layout = new QHBoxLayout(this);
  m_layout->setMargin(0);
  m_layout->setSpacing(0);

  ParamMap::const_iterator it = m_params.find("help");
  if (it != m_params.end())
    {
      std::string toolTip = it->second;
      
      setToolTip(toolTip.c_str());
    }
}

TypeView::~TypeView()
{
  //std::cout << "ljsdhlksdgh" << std::endl;
}


TypeViewConstructor::TypeViewConstructor(const std::string& name,
					 const std::string& viewID)
  : m_name(name),m_viewID(viewID)
{
}

TypeViewConstructor::~TypeViewConstructor()
{
}

const std::string& TypeViewConstructor::getName()
{
  return m_name;
}

const std::string& TypeViewConstructor::getViewID()
{
  return m_viewID;
}

}
