#ifndef INCLUDED_GRAPH_EDITOR_WINDOW_H
#define INCLUDED_GRAPH_EDITOR_WINDOW_H

#include <qmainwindow.h>

class IModelControlReceiver;

namespace gui
{

  class GraphModel;
  class IModuleInfoBaseStation;
  class ControlValueDispatcher;
  class GraphEditor;

  class GraphEditorWindow : public QMainWindow
  {
  public:
    GraphEditorWindow(QWidget* parent, const char* name, WFlags fl,
		      GraphModel& contr,
		      const IModuleInfoBaseStation&,
		      ControlValueDispatcher& dispatcher_,
		      IModelControlReceiver&);

    GraphEditor* graphEditor();

  private:
    GraphEditor* m_graphEditor;

  };


} // end of namespace gui

#endif

