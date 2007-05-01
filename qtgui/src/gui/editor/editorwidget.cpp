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

#include "editorwidget.h"

#include <cassert>

#include <QtCore/QSettings>

#include "grapheditor.h"
#include "grapheditorwindow.h"
#include "controleditor.h"
#include "controleditorwindow.h"

#include "moduleclassview.h"

//TODO: remove
#include "guimodel/graphmodel.h"
#include "guimodel/controlmodel.h"

#include "interfaces/imodulestatisticssender.h"
#include "interfaces/imodelstatussender.h"

namespace gui
{

  typedef std::map<std::string, std::string> ParamMap;

  EditorWidget::EditorWidget(QWidget* parent,
			     GraphModel& graphModel,
			     IModelControlReceiver& model,
			     ControlModel& controlModel,
			     ModuleClassView& base,
                             const utils::AutoPtr<ControlValueDispatcher>& dispatcher,
			     IModuleStatisticsSender& mss,
			     IModelStatusSender& msts,
			     KeyboardManager* kbManager,
			     IErrorReceiver& log,
			     const std::string& media_path)

    : QSplitter(Qt::Vertical,parent)
  {
    GraphEditorWindow* geWindow = new GraphEditorWindow(this,
                                                        graphModel,base,
                                                        dispatcher,model,
                                                        kbManager, log,
                                                        media_path);

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

    connect(graphEditor,SIGNAL(displayProperties(const IPropertyDescription&)),
            this,SLOT(displayProperties_(const IPropertyDescription&)));

    connect(graphEditor,SIGNAL(undisplayProperties()),
            this,SLOT(undisplayProperties_()));

    connect(graphEditor,
            SIGNAL(newEditGraph(const std::string&,
                                const std::string&)),
            this,
            SLOT(newEditGraphSlot(const std::string&,
                                  const std::string&)));

    ControlEditorWindow* ceWindow = new ControlEditorWindow(0,
                                                            controlModel,
                                                            model,
                                                            dispatcher,
                                                            media_path);

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

    connect(controlEditor, SIGNAL(inputSelected(int, int)),
            graphEditor, SLOT(highlightInput(int, int)));

    connect(graphEditor,SIGNAL(deleteControl(int,int)),
            controlEditor,SLOT(deleteControl(int,int)));


    QSizePolicy policy = geWindow->sizePolicy();
    policy.setHorizontalStretch(1);
    policy.setVerticalStretch(2);
    geWindow->setSizePolicy(policy);
    
    policy = ceWindow->sizePolicy();
    policy.setHorizontalStretch(1);
    policy.setVerticalStretch(1);
    ceWindow->setSizePolicy(policy);

    addWidget(geWindow);
    addWidget(ceWindow);

    QSettings settings;
    if (settings.contains("editorSplitterState"))
      {
	restoreState(settings.value("editorSplitterState").toByteArray());
      }
  }

  EditorWidget::~EditorWidget()
  {
    QSettings settings;
    QByteArray state = saveState();
    settings.setValue("editorSplitterState", state);

    //TODO: perhaps unregister
  }


  void EditorWidget::displayStatusText(const std::string& s)
  {
    emit statusText(s);
  }

  void EditorWidget::displayProperties_(const IPropertyDescription& pd)
  {
    emit displayProperties(pd);
  }

  void EditorWidget::undisplayProperties_()
  {
    emit undisplayProperties();
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
