#include "treeview.h"

#include <map>

#include <qlistview.h>
#include <qpopupmenu.h>

#include "treeviewitem.h"

#include "utils/autoptr.h"

#include "guimodel/point.h"

namespace gui
{


  class TreeViewItemImpl : public QListViewItem,
			   public TreeViewItem
  {
  public:
    
    TreeViewItemImpl(QListViewItem* parent,
		     TreeViewItem& item)
      : QListViewItem(parent), m_item(item)
    {
    }

    TreeViewItemImpl(QListView* parent,
		     TreeViewItem& item)
      : QListViewItem(parent), m_item(item)
    {
    }

  private:
    TreeViewItem& m_item;
  };

  class ColumnTextChangeListenerImpl : public ColumnTextChangeListener
  {
  public:
    ColumnTextChangeListenerImpl(QListViewItem* item)
      : m_item(item) {}

    virtual void textChanged(int column, const std::string& newText)
    {
      m_item->setText(column, newText.c_str());
    }

  private:
    QListViewItem* m_item;
  };

  class TreeViewImpl : public QListView
  {
    Q_OBJECT
  public:
    TreeViewImpl(QWidget* parent, const std::string& name,
		const std::vector<std::string>& columnNames)
      : QListView(parent, name.c_str()), activeItem(0)
    {
      for (unsigned int i = 0; i < columnNames.size(); ++i)
	this->addColumn(columnNames[i].c_str());


      connect(this,SIGNAL(doubleClicked ( QListViewItem * )),
	      this,SLOT(doubleClickedSlot ( QListViewItem * )));

      connect(this,SIGNAL(rightButtonClicked ( QListViewItem *, 
						   const QPoint &, int )),
	      this,SLOT(rightButtonClickedSlot ( QListViewItem *,
						 const QPoint &, int )));

      connect(this,SIGNAL(rightButtonPressed ( QListViewItem *,
						   const QPoint &, int )),
	      this,SLOT(rightButtonPressedSlot ( QListViewItem *,
						 const QPoint &, int )));

      connect(this,SIGNAL(mouseButtonPressed ( int, QListViewItem *,
						   const QPoint &, int )),
	      this,SLOT(mouseButtonPressedSlot ( int, QListViewItem *,
						 const QPoint &, int )));

      connect(this,SIGNAL(mouseButtonClicked ( int, QListViewItem *,
						   const QPoint &, int )),
	      this,SLOT(mouseButtonClickedSlot ( int, QListViewItem *,
						 const QPoint &, int )));

      connect(this,SIGNAL(onItem ( QListViewItem * )),
	      this,SLOT(onItemSlot ( QListViewItem * )));
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
	  newItem = ItemImplPtr( new TreeViewItemImpl(this, item) );
	  newItem->setOpen(true);
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
	      newItem = ItemImplPtr(new TreeViewItemImpl(&*parentItem,item));
	    }
	}

      TextChangeListenerPtr 
	newListener ( new ColumnTextChangeListenerImpl(&*newItem) );

      item.setColumnTextChangeListener(*newListener);
      m_impls[&item] = std::make_pair(newItem, newListener);
      m_items[dynamic_cast<QListViewItem*>(&*newItem)] = &item;
    }

    void removeItem( TreeViewItem& item )
    {
      ImplMap::iterator it = m_impls.find(&item);
      if (it == m_impls.end())
	{
	  throw std::runtime_error("impl not found at "
				   "TreeViewItemImpl::removeItem");
	}
      else
	{
	  ItemMap::iterator it2 = m_items.find(&*it->second.first); //TODO
	  if (it2 == m_items.end())
	    {
	      throw std::runtime_error("item not found at "
				       "TreeViewItemImpl::removeItem");
	    }
	  else
	    {
	      assert(it2->second == &item);

	      //TODO: remove it->second.first from parent before deleting?

	      m_impls.erase(it);
	      m_items.erase(it2);
	      
	      // std::cout << "Treeview: Removed item!" << std::endl;
	    }
	}
    }

  private:
    
    TreeViewItem* findTreeViewItem(QListViewItem* item)
    {
      ItemMap::const_iterator it = m_items.find(item);
      if (it == m_items.end())
	{
	  //TODO
	  assert(!"tschuess");
	  //std::cerr << "mist" << std::endl;
	  return 0;
	}
      else
	{
	  return &*it->second;
	}
    }

   private slots:
    
    void doubleClickedSlot (QListViewItem* item)
    {
      if (!item)
	return;

      TreeViewItem* treeItem = findTreeViewItem(item);

      treeItem->doubleClicked( );
    }

    void rightButtonClickedSlot (QListViewItem* item, const QPoint& p, int c)
    {
      if (!item)
	return;

      TreeViewItem* treeItem = findTreeViewItem(item);

      QPopupMenu* popme = treeItem->getPropertyMenu();

      if (popme != 0)
	{
	  popme->move(p);
	  popme->show();
	  activeItem = treeItem;
	  connect(popme,SIGNAL(activated(int)),
		  this,SLOT(popupActivated(int)));
	}

      treeItem->rightButtonClicked(gui::Point(p.x(),p.y()), c);
    }

    void rightButtonPressedSlot (QListViewItem* item, const QPoint& p, int c)
    {
      if (!item)
	return;

      TreeViewItem* treeItem = findTreeViewItem(item);

      treeItem->rightButtonPressed(gui::Point(p.x(),p.y()), c);
    }

    void mouseButtonPressedSlot (int button, QListViewItem* item,
				 const QPoint& p, int c)
    {
      if (!item)
	return;

      TreeViewItem* treeItem = findTreeViewItem(item);

      if (button == Qt::LeftButton)
	treeItem->leftButtonPressed(gui::Point(p.x(),p.y()), c);
    }

    void mouseButtonClickedSlot (int button,QListViewItem* item,
				 const QPoint& p, int c)
    {
      if (!item)
	return;

      TreeViewItem* treeItem = findTreeViewItem(item);

      if (button == Qt::LeftButton)
	treeItem->leftButtonClicked(gui::Point(p.x(),p.y()), c);
    }

    void onItemSlot (QListViewItem* item)
    {
      if (!item)
	return;

      TreeViewItem* treeItem = findTreeViewItem(item);

      treeItem->mouseOnItem();
    }

    void popupActivated(int id)
    {
      if (activeItem == 0)
	{
	  assert("!!!!!"); //TODO
	}
      else
	activeItem->propertySelected(id);
    }

    
  private:
    typedef utils::AutoPtr<TreeViewItemImpl> ItemImplPtr;
    typedef utils::AutoPtr<ColumnTextChangeListenerImpl> TextChangeListenerPtr;
    typedef std::map<TreeViewItem*, std::pair<ItemImplPtr,TextChangeListenerPtr> > ImplMap;
    ImplMap m_impls;

    typedef std::map<QListViewItem*, TreeViewItem*> ItemMap;
    ItemMap m_items;

    TreeViewItem* activeItem;
  };


  TreeView::TreeView(QWidget* parent, const std::string& name,
	  const std::vector<std::string>& columnNames)
    : m_impl(new TreeViewImpl(parent, name, columnNames))
  {
  }
  
  TreeView::~TreeView()
  {
    //qt paranoia (try to make sure that m_impl os not deleted twice)!
    m_impl->parentWidget()->removeChild(m_impl);
    delete m_impl;
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
