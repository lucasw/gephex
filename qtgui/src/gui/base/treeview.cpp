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

#include "treeview.h"

#include <map>

#include <QtGui/QTreeWidget>
#include <QtGui/QMenu>
#include <QtGui/QMouseEvent>

#include "treeviewitem.h"

#include "utils/autoptr.h"

#include "guimodel/point.h"

namespace gui
{
  class ColumnTextChangeListenerImpl : public ColumnTextChangeListener
  {
  public:
    ColumnTextChangeListenerImpl(QTreeWidgetItem* item)
      : m_item(item) {}

    virtual void textChanged(int column, const std::string& newText)
    {
      m_item->setText(column, newText.c_str());
    }

  private:
    QTreeWidgetItem* m_item;
  };

  class TreeViewImpl : public QTreeWidget
  {
    Q_OBJECT
  public:
    TreeViewImpl(QWidget* parent, const std::string& name,
                 const std::vector<std::string>& columnNames,
                 TreeView* treeview)
      : QTreeWidget(parent), activeItem(0),
        m_treeview(treeview)
    {
      this->setColumnCount(columnNames.size());

      QStringList headerNames;
      for (unsigned int i = 0; i < columnNames.size(); ++i)
	headerNames.append(columnNames[i].c_str());

      this->setHeaderLabels(headerNames);

      connect(this,SIGNAL(itemClicked(QTreeWidgetItem *, int)),
	      this,SLOT(itemClickedSlot(QTreeWidgetItem *, int)));

      connect(this, SIGNAL(itemActivated ( QTreeWidgetItem *, int )),
	      this, SLOT(itemActivatedSlot ( QTreeWidgetItem *, int )));
    }

    virtual ~TreeViewImpl()
    {
      delete m_treeview;
    }

    void insertItem( TreeViewItem& item, TreeViewItem* parent)
    {
      if (m_impls.find(&item) != m_impls.end()) //item already included
	{
	  assert(!"hallo");
	  //TODO: signal error or move the item?
	}

      ItemImplPtr newItem;
      if (parent == 0) //top level item?
	{
	  newItem = ItemImplPtr( new QTreeWidgetItem(this) );
	  expandItem(&*newItem);
	}
      else
	{
	  ImplMap::const_iterator it = m_impls.find(parent);
	  if (it == m_impls.end())
	    {
	      //TODO
	      assert(!"hallo");
	    }
	  else
	    {
	      ItemImplPtr parentItem = it->second.first;
	      newItem = ItemImplPtr(new QTreeWidgetItem(&*parentItem));
	    }
	}

      TextChangeListenerPtr 
	newListener ( new ColumnTextChangeListenerImpl(&*newItem) );

      item.setColumnTextChangeListener(*newListener);
      m_impls[&item] = std::make_pair(newItem, newListener);
      m_items[&*newItem] = &item;
    }

    void removeItem( TreeViewItem& item )
    {
      ImplMap::iterator it = m_impls.find(&item);
      if (it == m_impls.end())
	{
	  throw std::runtime_error("impl not found at "
				   "TreeViewImpl::removeItem");
	}
      else
	{
	  ItemMap::iterator it2 = m_items.find(&*it->second.first); //TODO
	  if (it2 == m_items.end())
	    {
	      throw std::runtime_error("item not found at "
				       "TreeViewImpl::removeItem");
	    }
	  else
	    {
	      assert(it2->second == &item);

	      //TODO: remove it->second.first from parent before deleting?

              delete it->second.first;
	      m_impls.erase(it);
		  

	      m_items.erase(it2);
	      
	      // std::cout << "Treeview: Removed item!" << std::endl;
	    }

	}
    }

  private:
    
    TreeViewItem* findTreeViewItem(QTreeWidgetItem* item)
    {
      ItemMap::const_iterator it = m_items.find(item);
      if (it == m_items.end())
	{	  
	  //std::cerr << "mist" << std::endl;
	  return 0;
	}
      else
	{
	  return &*it->second;
	}
    }

    void mouseReleaseEvent(QMouseEvent* event)
    {
      QTreeWidgetItem* item = itemAt ( event->pos() );
      if (event->button() == Qt::RightButton && item != 0)
	{

	  TreeViewItem* treeItem = findTreeViewItem(item);

	  if (treeItem)
	    {
	      QMenu* popme = treeItem->getPropertyMenu();
          
	      if (popme != 0)
		{
		  // TODO
		  popme->move( event->globalPos() );
		  popme->show();
		  activeItem = treeItem;
		}
	    }
	}

      QTreeWidget::mouseReleaseEvent(event);
    }


private slots:

    void itemClickedSlot(QTreeWidgetItem* item,
			 int column)
    {
      if (!item)
	return;

      TreeViewItem* treeItem = findTreeViewItem(item);

      treeItem->onClick(column);
    }

    void itemActivatedSlot(QTreeWidgetItem* item,
			   int column)
    {
      if (!item)
	return;

      TreeViewItem* treeItem = findTreeViewItem(item);

      treeItem->onActivate(column);
    }

    
  private:
    typedef QTreeWidgetItem* ItemImplPtr;
    typedef utils::AutoPtr<ColumnTextChangeListenerImpl> TextChangeListenerPtr;
    typedef std::map<TreeViewItem*,
      std::pair<ItemImplPtr, TextChangeListenerPtr> > ImplMap;
    ImplMap m_impls;

    typedef std::map<QTreeWidgetItem*, TreeViewItem*> ItemMap;
    ItemMap m_items;

    TreeViewItem* activeItem;

    TreeView* m_treeview;
  };


  TreeView::TreeView(QWidget* parent, const std::string& name,
                     const std::vector<std::string>& columnNames)
    : m_impl(new TreeViewImpl(parent, name, columnNames, this))
  {
  }
  
  TreeView::~TreeView()
  {
    // Note: the Treeview dtor is called by the TreeViewImpl
  }

  QWidget* TreeView::widget()
  {
    return m_impl;
  }
    
  void TreeView::insertItem(TreeViewItem& item, TreeViewItem* parent)
  {
    m_impl->insertItem(item, parent);
  }
  
  void TreeView::removeItem(TreeViewItem& item)
  {
    m_impl->removeItem(item);
  }
}

#include "treeview_moc.cpp"
