#ifndef INCLUDED_TREE_VIEW_H
#define INCLUDED_TREE_VIEW_H

#include <string> 
#include <vector>

//#include <qwidget.h>
class QWidget;

namespace gui
{

  class TreeViewItem;
  class TreeViewImpl;

  /**
   * This class aims to be a simple and clean wrapper for the QT QListView.
   * It is much less flexible than QListView an the performance is
   * probably worse.
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
     * @param parent is the parent item. If parent=0 item will be
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
