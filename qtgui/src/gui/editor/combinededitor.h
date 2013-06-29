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

#ifndef INCLUDED_COMBINED_EDITOR_H
#define INCLUDED_COMBINED_EDITOR_H

#include <map>
#include <QtGui/qwidget.h>

#include "ieditor.h"

#include "utils/autoptr.h"

namespace gui {

  class CombinedEditor : public QWidget,
			 public IEditor
  {
  public:
    CombinedEditor(QWidget* parent);
  
    virtual void registerListener(IEditorCommandListener& listener);

    virtual int elementAdded(IVisibleElement* elem, int x, int y);

    virtual void elementRemoved(int elementID);

    virtual void elementsConnected(int id1, int outIndex,
				   int id2, int inIndex);

    virtual void elementsDisconnected(int elemID, int inIndex);

    virtual void connectInputInProgress(int elemID, int inIndex,
					int x, int y);
    virtual void connectOutputInProgress(int elemID, int outIndex,
					 int x, int y);

  private:
    IEditorCommandListener* m_listener;
    int m_lastID;

    typedef utils::AutoPtr<IVisibleElement> IVisibleElementPtr;
    typedef std::map<int, IVisibleElementPtr> ElementMap;
    ElementMap m_elems;

    typedef std::map<std::pair<int, int>, std::pair<int, int> >
    ConnectionMap;

    ConnectionMap m_connections;
  };

}

#endif
