#ifndef INCLUDED_MODULE_CLASS_TAB_VIEW_H
#define INCLUDED_MODULE_CLASS_TAB_VIEW_H

#include <map>
#include <string>
#include <vector>

#include <qmenubar.h>
#include <qtoolbar.h>
#include <qtabbar.h>
#include <qtabwidget.h>
#include <qtoolbutton.h>

#include "imoduleinfobasestation.h"
#include "guimodel/imoduleclassview.h"
#include "utils/autoptr.h"

//class QMainWindow;
class ModuleButton;
class Uebertab;

namespace utils {
  class Buffer;
}

namespace gui
{

  class ModuleClassTabView : public QTabWidget, 
			  public IModuleClassView, 
			  public IModuleInfoBaseStation
  {
Q_OBJECT
  public:
	  ModuleClassTabView(QWidget*);
	  
	  virtual ~ModuleClassTabView();
	  //virtual void hasChanged(const std::list<ChangeInfo>& changedClasses);
	  virtual void moduleClassLoaded(const std::string& moduleClassName,const ModuleInfo&);
	  virtual void moduleClassUnloaded(const std::string& moduleClassName);
	  
	  virtual const ModuleInfo& getModuleInfo(const std::string& moduleClassName) const;
  private slots:
	  void moduleClassSelected(int);
	  void getIdOfChanged(QWidget*);
	  
  signals:
	  void selectModuleClass(const std::string& moduleClassName);
	  
  private:
	  int m_id;
	  std::map<std::string,Uebertab*> m_groups;
	  std::map<std::string,ModuleButton*> m_buttons;
	  
	  typedef std::map<std::string,utils::AutoPtr<ModuleInfo> > ModuleInfoMap;
	  ModuleInfoMap infos;
	  std::vector<std::string> mClassID2Name;
	  
	  std::map<std::string,int> m_itemIDs;
	    
	  
  };

} // end of namespace gui

#endif
