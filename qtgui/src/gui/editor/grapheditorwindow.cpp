#include "grapheditorwindow.h"

#include <qscrollview.h>

#include "grapheditor.h"

namespace gui
{

GraphEditorWindow::GraphEditorWindow(QWidget* parent, const char* name, 
				     WFlags fl, GraphModel& graphModel,
				     const IModuleInfoBaseStation& base,
				     ControlValueDispatcher& dispatcher,
				     IModelControlReceiver& mod,
				     KeyboardManager& kbManager,
					 IErrorReceiver& log)
  : QMainWindow(parent,name,fl)
{
  QScrollView* graphScroller = new QScrollView(this);

  m_graphEditor = new GraphEditor(graphScroller->viewport(),"graph",
				  0,graphModel,base,dispatcher,mod,
				  kbManager, log);
  
  this->setCaption("Graph");
  
  graphScroller->addChild(m_graphEditor);
  m_graphEditor->resize(2000,2000);
  graphScroller->resize(200, 400);
  this->resize(400,200);
  graphScroller->center(1000,1000);

  this->setCentralWidget(graphScroller);
}

GraphEditor* GraphEditorWindow::graphEditor()
{
  return m_graphEditor;
}

} // end of namespace gui

