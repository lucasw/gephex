#ifndef INCLUDED_MODULE_CLASS_VIEW_H
#define INCLUDED_MODULE_CLASS_VIEW_H

#include <map>
#include <string>
#include <vector>

#include <qmenubar.h>
#include <qtoolbar.h>

#include "imoduleinfobasestation.h"
#include "guimodel/imoduleclassview.h"
#include "utils/autoptr.h"

class QMainWindow;

namespace utils {
  class Buffer;
}

namespace gui
{

  class ModuleClassView : public QObject, 
			  public IModuleClassView, 
			  public IModuleInfoBaseStation
  {
    Q_OBJECT
  public:
    ModuleClassView(QPopupMenu* parent);

    virtual ~ModuleClassView();
    //virtual void hasChanged(const std::list<ChangeInfo>& changedClasses);
    virtual void moduleClassLoaded(const std::string& moduleClassName,const ModuleInfo&);
    virtual void moduleClassUnloaded(const std::string& moduleClassName);

    virtual const ModuleInfo& getModuleInfo(const std::string& moduleClassName) const;
private slots:
void moduleClassSelected(int);

    signals:
void selectModuleClass(const std::string& moduleClassName);

  private:
    QPopupMenu* m_menu;

    std::map<std::string,QPopupMenu*> groups;
    std::map<std::string,QPopupMenu*> menues;

    typedef std::map<std::string,utils::AutoPtr<ModuleInfo> > ModuleInfoMap;
    ModuleInfoMap infos;
    std::vector<std::string> mClassID2Name;

    std::map<std::string,int> m_itemIDs;

 
  };

} // end of namespace gui

#endif
