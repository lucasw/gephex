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

#ifndef INCLUDED_ICONTROL_VIEW_H
#define INCLUDED_ICONTROL_VIEW_H

#include <map>
#include <string>

namespace gui
{

  class Point;

  class IControlView
  {
  public:
    typedef std::map<std::string, std::string> ParamMap;

    virtual ~IControlView() {}

    virtual void controlAdded(int controlID, const std::string& name,
			      int nodeID,int inputIndex, 
			      const std::string& widgetType,
			      const ParamMap& params) = 0;

    virtual void controlMoved(int controlID, const Point& p) = 0;
    virtual void controlDeleted(int controlID) = 0;

    virtual void controlRenamed(int controlID, const std::string& name) = 0;

    virtual void labelAdded(int labelID, const std::string& text) = 0;
    virtual void labelMoved(int labelID, const Point& p) = 0;
    virtual void labelDeleted(int labelID) = 0;
  };

}

#endif
