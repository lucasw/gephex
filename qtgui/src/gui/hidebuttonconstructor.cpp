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

#include "hidebuttonconstructor.h"

#include "hidebutton.h"

namespace gui
{

  HideButtonConstructor::HideButtonConstructor(InputPlugWidget& in)
    : m_in(&in)
  {
  }
  
  QWidget* HideButtonConstructor::constructWidget(QWidget* parent) const
  {
    return new HideButton(parent,*m_in);
  }
  
  void HideButtonConstructor::destroyWidget(QWidget* w) const
  {
    HideButton* hb = dynamic_cast<HideButton*>(w);

    //delete hb;
  }

} // end of namespace gui
