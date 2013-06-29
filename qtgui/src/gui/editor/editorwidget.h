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

#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <string>
#include <QtGui/qwidget.h>
//#include <QtGui/qworkspace.h>
//#include <QtGui/qtabwidget.h>
#include <QtGui/qsplitter.h>

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
    EditorWidget(QWidget *parent, 
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


