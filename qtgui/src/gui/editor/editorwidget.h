#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <string>
#include <qwidget.h>
//#include <qworkspace.h>
//#include <qtabwidget.h>
#include <qsplitter.h>

//class QWidget;

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
		 ModuleClassView&, /*ModuleClassTabView&, */ControlValueDispatcher& disp,
		 IModuleStatisticsSender&,
		 IModelStatusSender&,
		 KeyboardManager& kbManager,
		 IErrorReceiver& log);
    //TODO, uncomment if u want the ugly tabview back

    ~EditorWidget();

public slots:
void displayStatusText(const std::string& s);
    void displayProperties(const IPropertyDescription& pd);	

    void newEditGraphSlot(const std::string&,const std::string&);
    void newRenderedGraphSlot(const std::string&);

    signals:
    void statusText(const std::string&);
    void properties(const IPropertyDescription& pd);	

    void newEditGraph( const std::string&, const std::string& );
    void newRenderedGraph( const std::string& );

  private:
  
    GraphEditor* graphEditor;
    ControlEditor* controlEditor;

    //	ControlDispatcher* controlDispatcher;
  };

}
#endif


