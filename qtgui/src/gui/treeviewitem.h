#ifndef INCLUDED_TREEVIEW_ITEM_H
#define INCLUDED_TREEVIEW_ITEM_H

#include <string>

class QPopupMenu;

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
     * @param pos position of the mouse cursor
     * @param column column that was clicked
     */
    virtual void leftButtonClicked( const Point& pos, int column );

    /**
     * Tells the item that it has received a right button click.
     * @param pos position of the mouse cursor
     * @param column column that was clicked
     */
    virtual void rightButtonClicked( const Point& pos, int column );

    /**
     * Tells the item that it has received a left button press.
     * @param pos position of the mouse cursor
     * @param column column that was pressed
     */
    virtual void leftButtonPressed( const Point& pos, int column );

    /**
     * Tells the item that it has received a right button press.
     * @param pos position of the mouse cursor
     * @param column column that was pressed
     */
    virtual void rightButtonPressed( const Point& pos, int column );

    /**
     * Tells the item that it has received a left button click.
     * @param pos position of the mouse cursor
     * @param column column that was clicked
     */
    virtual void doubleClicked( );

    /**
     * Tells the item that it has received a double click.
     * @param pos position of the mouse cursor
     * @param column column that was double clicked
     */
    virtual void mouseOnItem();

    /**
     * Tells the item, that an entry of its property menu was selected.
     * @param id the id that identifies the selected menu entry.
     */
    virtual void propertySelected(int id);

    /**
     * With this the item can give its property menu to the TreeView.
     * If 0 is returned, no property menu is shown on right click.
     * This method is called every time before the property menu
     * is displayed, so that the item can adapt the menu according
     * to its state (for example it can grey some entries).
     * The default Implementation returns 0.
     * @return The Property Menu of the item.
     */
    virtual QPopupMenu* getPropertyMenu();

  protected:
    ColumnTextChangeListener* m_textListener;
  };

}

#endif

