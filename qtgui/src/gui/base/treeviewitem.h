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

#ifndef INCLUDED_TREEVIEW_ITEM_H
#define INCLUDED_TREEVIEW_ITEM_H

#include <string>

class QMenu;

namespace gui
{

  class Point;

  /**
   * Instances of this class listen to text changes in TreeView items.
   */
  class ColumnTextChangeListener
  {
  public:
    virtual ~ColumnTextChangeListener();

    /**
     * Tells the listener that the text of a column has changed.
     * @param column the number of the column (0..)
     * @param newText the new text of the column
     */
    virtual void textChanged(int column, const std::string& newText) = 0;
  };

  /**
   * This is a base class for all items that can be inserted into a TreeView.
   * All its virtual functions have a default implementation that does
   * nothing, only setColumnTextChangeListener() sets the attribute
   * m_textListener.
   */
  class TreeViewItem
  {
  public:
    virtual ~TreeViewItem();

    /**
     * The TreeView passes a listener to the item.
     * With this listener the item can change the text that is displayed.
     * @param l the listener
     */
    virtual void setColumnTextChangeListener(ColumnTextChangeListener& l);
    
    /**
     * Tells the item that it has received a left button click.
     * @param column column that was clicked
     */
    virtual void onClick(int column);

    /**
     * Tells the item that it has been activated (double clicked, enter pressed,
     * ...).
     * @param column column that was activated
     */
    virtual void onActivate(int column);

    /**
     * With this the item can give its property menu to the TreeView.
     * If 0 is returned, no property menu is shown on right click.
     * This method is called every time before the property menu
     * is displayed, so that the item can adapt the menu according
     * to its state (for example it can grey some entries).
     * The default Implementation returns 0.
     * @return The Property Menu of the item.
     */
    virtual QMenu* getPropertyMenu();

  protected:
    ColumnTextChangeListener* m_textListener;
  };

}

#endif

