#ifndef INCLUDED_COMBINED_EDITOR_H
#define INCLUDED_COMBINED_EDITOR_H

#include <map>
#include <qwidget.h>

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
