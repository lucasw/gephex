#ifndef INCLUDED_IEDITOR_H
#define INCLUDED_IEDITOR_H

#include "ieditorcommandlistener.h"

namespace gui {
  class IVisibleElement; 

  class IEditor
  {
  public:

    virtual void registerListener(IEditorCommandListener& listener) = 0;

    /**
     * The editor aquires ownership!
     * returns the id
     */
    virtual int elementAdded(IVisibleElement* elem, int x, int y) = 0;

    /**
     * ...
     */
    virtual void elementRemoved(int elementID) = 0;

    /**
     *
     */
    virtual void elementsConnected(int id1, int outIndex,
				   int id2, int inIndex) = 0;

    /**
     *
     */
    virtual void elementsDisconnected(int id, int inIndex) = 0;

    /**
     *
     */
    virtual void connectInputInProgress(int elemId, int inIndex,
					int x, int y) = 0;

    /**
     *
     */
    virtual void connectOutputInProgress(int elemId, int outIndex,
					 int x, int y) = 0;

  };

}

#endif
