/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#include "moduleclassview.h"

#include <sstream>

#include <string>
#include <vector>
#include <stdexcept>

#include <QtGui/qcombobox.h>

#include "guimodel/moduleinfo.h"
#include "guimodel/xpm.h"

namespace gui
{
  ModuleClassView::ModuleClassView(QMenu* menu)
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
    QMenu* currentGroup = 0;
    std::map<std::string,QMenu*>::const_iterator
      it = groups.find(group);
    if (it == groups.end())
      {
        currentGroup = m_menu->addMenu(group.c_str());
        groups[group] = currentGroup;
      }
    else
      {
        currentGroup = it->second;
      }

    menues[moduleClassName] = currentGroup;

    QAction* ac = new QAction(mi->getName().c_str(), currentGroup);
    ac->setIcon(QPixmap(mi->getIcon().getPtr()));
    ac->setData(QVariant(moduleClassName.c_str()));
    currentGroup->addAction(ac);

    connect(currentGroup, SIGNAL(triggered(QAction*)),
	    this, SLOT(moduleClassSelected(QAction*)));

    m_actions.insert(std::make_pair(moduleClassName, ac));
  }

  void ModuleClassView::moduleClassUnloaded(const std::string& moduleClassName)
  {
    ActionMap::iterator it = m_actions.find(moduleClassName);

    if (it == m_actions.end())
      throw std::runtime_error("Fehler bei moduleClassUnloaded()");

    QAction* ac = it->second;
    m_actions.erase(it);

    std::map<std::string,QMenu*>::iterator 
      jt = menues.find(moduleClassName);
    if (jt == menues.end())
      throw std::runtime_error("Fehler bei moduleClassUnloaded()");

    QMenu* menu = jt->second;
    menues.erase(jt);

    ModuleInfoMap::iterator kt = infos.find(moduleClassName);
    if (kt == infos.end())
      throw std::runtime_error("Fehler bei moduleClassUnloaded()");
	
    infos.erase(kt);

    menu->removeAction(ac);
  }

  void ModuleClassView::moduleClassSelected(QAction* ac)
  {
    std::string moduleClassName = ac->data().toString().toUtf8().constData();
    emit selectModuleClass(moduleClassName);
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
    m_actions.clear();	

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
