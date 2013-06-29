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

#include "combinededitor.h"

#include "ivisibleelement.h"

namespace gui {

  CombinedEditor::CombinedEditor(QWidget* parent)
    : QWidget(parent, "CombinedEditor", 0),
      m_listener(0), m_lastID(-1)
  {
  }
  
  void CombinedEditor::registerListener(IEditorCommandListener& listener)
  {
    m_listener = &listener;
  }

  int CombinedEditor::elementAdded(IVisibleElement* elem, int x, int y)
  {
    int newID = ++m_lastID;
    
    m_elems.insert(std::make_pair(newID, IVisibleElementPtr(elem)));

    return newID;
  }

  void CombinedEditor::elementRemoved(int elementID)
  {
    ElementMap::iterator it = m_elems.find(elementID);
    if (it == m_elems.end())
      {
	throw std::runtime_error("No such element at "
				 "CombinedEditor::elementRemoved()");
      }

    m_elems.erase(it);
  }

  void CombinedEditor::elementsConnected(int id1, int outIndex,
					 int id2, int inIndex)
  {
    ElementMap::const_iterator it1 = m_elems.find(id1);
    ElementMap::const_iterator it2 = m_elems.find(id2);

    if (it1 == m_elems.end() || it2 == m_elems.end())
      {
	throw std::runtime_error("No such element at "
				 "CombinedEditor::elementsConnected()");
      }

    IVisibleElement* elem1 = &*it1->second;
    IVisibleElement* elem2 = &*it2->second;

    if (outIndex < 0 || outIndex >= elem1->numberOfOutputs() ||
	inIndex < 0 || inIndex >= elem2->numberOfInputs())
      {
	throw std::runtime_error("Wrong input/output index at "
				 "CombinedEditor::elementsConnected()");
      }

    m_connections.insert(std::make_pair(std::make_pair(id2, inIndex),
					std::make_pair(id1, outIndex)));
  }

  void CombinedEditor::elementsDisconnected(int elemID, int inIndex)
  {
    ConnectionMap::iterator
      it = m_connections.find(std::make_pair(elemID, inIndex));

    if (it == m_connections.end())
      {
	throw std::runtime_error("No such connection at "
				 "CombinedEditor::elementsDisconnected()");
      }
  }

  void CombinedEditor::connectInputInProgress(int elemID, int inIndex,
					      int x, int y)
  {
  }

  void CombinedEditor::connectOutputInProgress(int elemID, int outIndex,
					       int x, int y)
  {
  }

}
