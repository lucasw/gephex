#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <string>
#include <qwidget.h>
//#include <qworkspace.h>
//#include <qtabwidget.h>
#include <qsplitter.h>

//class QWidget;

#include "utils/autoptr.h"

class IModelControlReceiver;
class IModuleStatisticsSender;
class IModelStatusSender;
class IErrorReceiver;

namespace gui
{

  class GraphEditor;
  class ControlEditor;
  class GraphModel;
  class ControlModel;
  class ModuleClassView;
  class ModuleClassTabView;
  class IPropertyDescription;
  class ControlValueDispatcher;
  class KeyboardManager;

  class EditorWidget : public QSplitter {
    Q_OBJECT
  public: 
    EditorWidget(QWidget *parent, const char *name, 
		 GraphModel& graphModel,IModelControlReceiver& model,
		 ControlModel& controlModel,
		 ModuleClassView&,
         const utils::AutoPtr<ControlValueDispatcher>& disp,
		 IModuleStatisticsSender&,
		 IModelStatusSender&,
		 KeyboardManager* kbManager,
		 IErrorReceiver& log,
		 const std::string& media_path);

    ~EditorWidget();

public slots:
void displayStatusText(const std::string& s);
    void displayProperties_(const IPropertyDescription& pd);	
	void undisplayProperties_();

    void newEditGraphSlot(const std::string&,const std::string&);
    void newRenderedGraphSlot(const std::string&);

    signals:
    void statusText(const std::string&);
    void displayProperties(const IPropertyDescription& pd);	
	void undisplayProperties();

    void newEditGraph( const std::string&, const std::string& );
    void newRenderedGraph( const std::string& );

  private:
  
    GraphEditor* graphEditor;
    ControlEditor* controlEditor;

    //	ControlDispatcher* controlDispatcher;
  };

}
#endif


