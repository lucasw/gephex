#include "treeviewitem.h"

namespace gui
{

  ColumnTextChangeListener::~ColumnTextChangeListener()
  {
  }


  TreeViewItem::~TreeViewItem()
  {
  }

  void TreeViewItem::setColumnTextChangeListener(ColumnTextChangeListener& l)
  {
    m_textListener = &l;
  }


  // Empty Default Implementations
  void TreeViewItem::leftButtonClicked( const Point& /*pos*/, int /*column*/ )
  {
  }

  void TreeViewItem::rightButtonClicked( const Point& /*pos*/, int /*column*/ )
  {
  }

  void TreeViewItem::leftButtonPressed( const Point& /*pos*/, int /*column*/ )
  {
  }

  void TreeViewItem::rightButtonPressed( const Point& /*pos*/, int /*column*/ )
  {
  }

  void TreeViewItem::doubleClicked()
  {
  }

  void TreeViewItem::mouseOnItem()
  {
  }

  void TreeViewItem::propertySelected(int /*id*/)
  {
  }

  QPopupMenu* TreeViewItem::getPropertyMenu()
  {
    return 0;
  }

}
