#ifndef INCLUDED_CONTROL_EDITOR_WINDOW_H
#define INCLUDED_CONTROL_EDITOR_WINDOW_H

#include <qmainwindow.h>

class IModelControlReceiver;

namespace gui
{
  class ControlEditor;
  class ControlModel;
  class ControlValueDispatcher;

class ControlEditorWindow : public QMainWindow
{
public:
  ControlEditorWindow(QWidget* parent, const char* name, WFlags fl,
		      ControlModel& cModel, IModelControlReceiver& model,
			  ControlValueDispatcher& disp);

  ControlEditor* controlEditor();

private:
  ControlEditor* m_controlEditor;
};

} // end of namespace gui

#endif
