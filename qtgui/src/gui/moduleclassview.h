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

#ifndef INCLUDED_MODULE_CLASS_VIEW_H
#define INCLUDED_MODULE_CLASS_VIEW_H

#include <map>
#include <string>
#include <vector>

#include <QtGui/qmenubar.h>
#include <QtGui/qtoolbar.h>

#include "imoduleinfobasestation.h"
#include "guimodel/imoduleclassview.h"
#include "utils/autoptr.h"

class QAction;

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
    ModuleClassView(QMenu* parent);

    virtual ~ModuleClassView();
    //virtual void hasChanged(const std::list<ChangeInfo>& changedClasses);
    virtual void moduleClassLoaded(const std::string& moduleClassName,const ModuleInfo&);
    virtual void moduleClassUnloaded(const std::string& moduleClassName);

    virtual const ModuleInfo& getModuleInfo(const std::string& moduleClassName) const;

	void syncStarted();
	void syncFinished();

	void clear();
private slots:
void moduleClassSelected(QAction*);

    signals:
 void selectModuleClass(const std::string& moduleClassName);

  private:
    QMenu* m_menu;

    std::map<std::string,QMenu*> groups;
    std::map<std::string,QMenu*> menues;

    typedef std::map<std::string,utils::AutoPtr<ModuleInfo> > ModuleInfoMap;
    ModuleInfoMap infos; 

    typedef std::map<std::string, QAction*> ActionMap;
    ActionMap m_actions;
  };

} // end of namespace gui

#endif
