#ifndef INCLUDED_IEDITOR_COMMAND_LISTENER_H
#define INCLUDED_IEDITOR_COMMAND_LISTENER_H

namespace gui {

class IEditorCommandListener
{
 public:
  virtual void moveElement(int elemID, int newX, int newY) = 0;
  virtual void deleteElement(int elemID) = 0;

  virtual void disconnectInput(int elemID, int inputIndex) = 0;
};

}
#endif
