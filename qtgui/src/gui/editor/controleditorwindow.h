#ifndef INCLUDED_CONTROL_EDITOR_WINDOW_H
#define INCLUDED_CONTROL_EDITOR_WINDOW_H

#include <string>

#include <qmainwindow.h>

#include "utils/autoptr.h"

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
			  const utils::AutoPtr<ControlValueDispatcher>& disp,
		      const std::string& media_path);

  ControlEditor* controlEditor();

private:
  ControlEditor* m_controlEditor;
};

} // end of namespace gui

#endif
