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

#ifndef INCLUDED_TREE_VIEW_H
#define INCLUDED_TREE_VIEW_H

#include <string> 
#include <vector>

class QWidget;

namespace gui
{

  class TreeViewItem;
  class TreeViewImpl;

  /**
   * This class aims to be a simple and clean wrapper for the QT QListView.
   * It is much less flexible than QListView an the performance is
   * probably worse.
   *
   * Note: with Qt >= 4.0, there is probably a much better way to do this.
   */

  class TreeView
  {
  public:

    TreeView(QWidget* parent, const std::string& name,
             const std::vector<std::string>& columnNames);

    virtual ~TreeView();

    QWidget* widget();
    
    /**
     * Inserts a new Item into the TreeView.
     * @param item is the Item that is inserted
     * @param parent is the parent item. If parent==0, item will be
     *               inserted as a top level item
     */
    void insertItem(TreeViewItem& item, TreeViewItem* parent);

    /**
     * Removes an item.
     * @param item the item that will be removed
     */
    void removeItem(TreeViewItem& item);

  private:
    TreeViewImpl* m_impl;
    
  };

}

#endif
