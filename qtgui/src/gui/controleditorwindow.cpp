#include "controleditorwindow.h"

#include <qscrollview.h>

#include "controleditor.h"


namespace gui
{

  ControlEditorWindow::ControlEditorWindow(QWidget* parent,const char* name,
					   WFlags fl, 
					   ControlModel& controlModel,
					   IModelControlReceiver& model,
					   ControlValueDispatcher& disp)
    : QMainWindow(parent,name,fl)
  {
    QScrollView* controlScroller = new QScrollView(this);
    m_controlEditor = new ControlEditor(controlScroller->viewport(),"control",0,
					controlModel,model,disp);

    controlScroller->addChild(m_controlEditor);
    this->setCaption("Controls");

    m_controlEditor->resize(1000,1000);
    controlScroller->resize(200, 400);
    this->resize(400, 200);
    controlScroller->center(500,500);

    this->setCentralWidget(controlScroller);
  }

  ControlEditor* ControlEditorWindow::controlEditor()
  {
    return m_controlEditor;
  }

} // end of namespace gui
