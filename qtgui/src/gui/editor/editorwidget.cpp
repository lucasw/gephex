#include "editorwidget.h"

#include <cassert>

#include <qscrollview.h>

#include "grapheditor.h"
#include "grapheditorwindow.h"
#include "controleditor.h"
#include "controleditorwindow.h"

#include "moduleclassview.h"
#include "moduleclasstabview.h"

//TODO: remove
#include "guimodel/graphmodel.h"
#include "guimodel/controlmodel.h"

#include "interfaces/imodulestatisticssender.h"
#include "interfaces/imodelstatussender.h"

namespace gui
{

  typedef std::map<std::string, std::string> ParamMap;

EditorWidget::EditorWidget(QWidget* parent, const char* name,
			   GraphModel& graphModel,
			   IModelControlReceiver& model,
			   ControlModel& controlModel,
			   ModuleClassView& base,
			   //ModuleClassTabView& extendedBase,
			   ControlValueDispatcher& dispatcher,
			   IModuleStatisticsSender& mss,
			   IModelStatusSender& msts,
			   KeyboardManager& kbManager,
			   IErrorReceiver& log)
  : QSplitter(Vertical,parent,name)
{
  //  this->resize(400,400);
  
  GraphEditorWindow* geWindow = new GraphEditorWindow(this,"graph",0,
						      graphModel,base,
						      dispatcher,model,
						      kbManager, log);

  graphEditor = geWindow->graphEditor();

  graphModel.registerGraphView(*graphEditor);
  controlModel.registerControlConnectView(*graphEditor);
  mss.registerModuleStatisticsReceiver(*graphEditor);	
  msts.registerModelStatusReceiver(*graphEditor);

  connect(&base,SIGNAL(selectModuleClass(const std::string&)),
	  graphEditor,SLOT(moduleClassSelected(const std::string&)));

/*  connect(&extendedBase, SIGNAL(selectModuleClass(const std::string&)),
	  graphEditor, SLOT(moduleClassSelected(const std::string&)));*/
  
  connect(graphEditor,SIGNAL(statusText(const std::string&)),
	  this,SLOT(displayStatusText(const std::string&)));

  connect(graphEditor,SIGNAL(properties(const IPropertyDescription&)),
	  this,SLOT(displayProperties(const IPropertyDescription&)));

  connect(graphEditor,SIGNAL(newEditGraph(const std::string&,
					  const std::string&)),
	  this,SLOT(newEditGraphSlot(const std::string&,const std::string&)));

  ControlEditorWindow* ceWindow = new ControlEditorWindow(this,"control",0,
							  controlModel,model,
							  dispatcher);

  ceWindow->parentWidget()->move(0,210);
  ceWindow->move(0,210);

  controlEditor = ceWindow->controlEditor();

  controlModel.registerControlView(*controlEditor);
  
  connect(graphEditor,SIGNAL(createControl(const std::string&,
					   const std::string&,int,int,
					   const ParamMap&,
					   const QPoint&)),
	  controlEditor,SLOT(selectWidgetType(const std::string&,
					      const std::string&,int,int,
					      const ParamMap&,
					      const QPoint&)));
	
  connect(graphEditor,SIGNAL(deleteControl(int,int)),
	  controlEditor,SLOT(deleteControl(int,int)));

    //model.newGraph("DefaultGraph");
  //model.changeEditGraph("DefaultGraph","default");
  //model.changeRenderedGraph("DefaultGraph","default");

  //this->tile();
}

EditorWidget::~EditorWidget(){
	//TODO: perhaps unregister
}


void EditorWidget::displayStatusText(const std::string& s)
{
	emit statusText(s);
}

void EditorWidget::displayProperties(const IPropertyDescription& pd)
{
  emit properties(pd);
}

void EditorWidget::newEditGraphSlot(const std::string&g, const std::string&s)
{
  emit newEditGraph(g,s);
}

void EditorWidget::newRenderedGraphSlot(const std::string&g)
{
  emit newRenderedGraph(g);
}

} // end of namespace gui
