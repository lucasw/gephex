#include "moduleclassview.h"

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

#include <qcombobox.h>

#include "guimodel/moduleinfo.h"
#include "guimodel/xpm.h"

namespace gui
{
  ModuleClassView::ModuleClassView(QPopupMenu* menu)
    : QObject(menu), m_menu(menu)
  {	
  }

  ModuleClassView::~ModuleClassView()
  {
  }

  void ModuleClassView::moduleClassLoaded(const std::string& moduleClassName,
                                          const ModuleInfo& minfo)
  {				
    utils::AutoPtr<ModuleInfo> mi ( new ModuleInfo(minfo) );
    infos.insert(std::make_pair(moduleClassName,mi));
    std::string group = mi->getGroup();
    QPopupMenu* currentGroup = 0;
    std::map<std::string,QPopupMenu*>::const_iterator
      it = groups.find(group);
    if (it == groups.end())
      {
        currentGroup = new QPopupMenu(m_menu);
        m_menu->insertItem(group.c_str(),currentGroup);
        groups[group] = currentGroup;
		
        connect(currentGroup,SIGNAL(activated(int)),
                this,SLOT(moduleClassSelected(int)));
        //currentGroup->show();
      }
    else
      {
        currentGroup = it->second;
      }

    menues[moduleClassName] = currentGroup;
	
    const char* bla = mi->getName().c_str();
	
    /*ModuleButton* mb1 = new ModuleButton(classID, currentGroup,bla);
      mb1->setTextLabel(bla);
      mb1->setPixmap(QPixmap(mi->getIcon()->getPtr()));
      mb1->setController(m_controller);*/
	
    //currentGroup->insertItem(mb1);

    mClassID2Name.push_back(moduleClassName);
	

    int id = currentGroup->insertItem(QPixmap(mi->getIcon().getPtr()),
                                      mi->getName().c_str(),
                                      mClassID2Name.size()-1); 

    m_itemIDs[moduleClassName] = id;
	
    //m_buttons[classID] = mb1;
				
  }

  void ModuleClassView::moduleClassUnloaded(const std::string& moduleClassName)
  {
    std::map<std::string,int>::iterator 
      it = m_itemIDs.find(moduleClassName);

    if (it == m_itemIDs.end())
      throw std::runtime_error("Fehler bei moduleClassUnloaded()");

    int id = it->second;
    m_itemIDs.erase(it);

    std::map<std::string,QPopupMenu*>::iterator 
      jt = menues.find(moduleClassName);
    if (jt == menues.end())
      throw std::runtime_error("Fehler bei moduleClassUnloaded()");

    QPopupMenu* menu = jt->second;
    menues.erase(jt);

    ModuleInfoMap::iterator kt = infos.find(moduleClassName);
    if (kt == infos.end())
      throw std::runtime_error("Fehler bei moduleClassUnloaded()");
	
    infos.erase(kt);

    menu->removeItem(id);
  }

  void ModuleClassView::moduleClassSelected(int mClassID)
  {
    emit selectModuleClass(mClassID2Name[mClassID]);
  }

  const ModuleInfo& 
  ModuleClassView::getModuleInfo(const std::string& moduleClassName) const
  {
    ModuleInfoMap::const_iterator it = infos.find(moduleClassName);

    if (it == infos.end())
      {
        throw std::runtime_error("moduleClassName unknown!");
      }

    return *it->second;
  }

  void ModuleClassView::clear()
  {
    infos.clear();
    mClassID2Name.clear();
    m_itemIDs.clear();	

    /*for (std::map<std::string,QPopupMenu*>::iterator it = groups.begin();
      it != groups.end(); ++it)
      {
      delete it->second;
      }*/

    groups.clear();
    menues.clear();

    m_menu->clear();
  }

  void ModuleClassView::syncStarted()
  {
    clear();
  }

  void ModuleClassView::syncFinished()
  {
  }

} // end of namespace gui
