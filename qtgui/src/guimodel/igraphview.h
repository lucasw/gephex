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

#ifndef _INCLUDED_IGRAPHVIEW_H__
#define _INCLUDED_IGRAPHVIEW_H__

namespace gui
{

class Point;

class IGraphView
{

public:
	virtual ~IGraphView() {}

	virtual void moduleAdded(const std::string& moduleClassName,int modID) = 0;
	
	virtual void modulesConnected(int moduleID1,int outputIndex,
								int moduleID2,int inputIndex) = 0;
	virtual void modulesDisconnected( int moduleID,int inputIndex) = 0;
	
	virtual void moduleDeleted(int moduleID) = 0;

	virtual void moduleMoved(int moduleID, const Point&) = 0;
};

}


#endif
