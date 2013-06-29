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

#ifndef _INCLUDED_CONTROL_EDITOR_H_
#define _INCLUDED_CONTROL_EDITOR_H_

#include <list>
#include <map>
#include <string>

#include <QtGui/QWidget>

#include "guimodel/icontrolview.h"
#include "guimodel/point.h"

#include "utils/autoptr.h"

namespace utils
{
  class Buffer;
}

class QAction;
class IModelControlReceiver;

namespace gui
{

  class ControlModel;
  class ControlWidget;
  class ControlValueDispatcher;

  class LabelWidget;

  class TypeViewFactory;

  class ControlEditor: public QWidget, 
		       public IControlView
  {
    Q_OBJECT
  public:
    typedef std::map<std::string, std::string> ParamMap;

    ControlEditor(QWidget* parent,
		  ControlModel& cModel, IModelControlReceiver& model,
		  const utils::AutoPtr<ControlValueDispatcher>& disp,
		  const std::string& media_path);

    virtual ~ControlEditor();

    virtual void controlAdded(int controlID, const std::string& name,
			      int nodeID,int inputIndex, 
			      const std::string& widgetType,
			      const ParamMap& params);

    virtual void controlMoved(int controlID, const Point& p);
    virtual void controlDeleted(int controlID);

    virtual void controlRenamed(int controlID, const std::string& name);

    virtual void labelAdded(int labelID, const std::string& text);
    virtual void labelMoved(int labelID, const Point& p);
    virtual void labelDeleted(int labelID);

public slots:
    void controlChanged(int nodeID, int inputIndex, const utils::Buffer&);

    void selectWidgetType(const std::string& name, const std::string& type,
			  int nodeID,int inputIndex,
			  const ParamMap& params, const QPoint&);

    void deleteControl(int nodeID,int inputIndex);

    void controlWidgetMoved(ControlWidget*, const QPoint&);
    void controlWidgetReleased(ControlWidget* n,const QPoint& pos);
    void openPopup(ControlWidget*, const QPoint&);

    void labelWidgetMoved(LabelWidget*, const QPoint&);
    void labelWidgetReleased(LabelWidget* n,const QPoint& pos);
    void openLabelPopup(LabelWidget*, const QPoint&);

  protected slots:
    void actionTriggeredSlot(QAction*);

    void killControlSlot();

    void killLabelSlot();

    void addLabelSlot();

    // this slot is used to check wether the mouse is over a controlwidget 
    //    void checkMouse();

    void mouseOverControl(QWidget* w);

  protected:
    virtual void mousePressEvent(QMouseEvent*);

  signals:

    // this signal is emitted if the user wants
    // to find out to which input a control is connected
    void inputSelected(int moduleID, int inputIndex);

  private:
    ControlModel* m_controller;
    IModelControlReceiver* m_model;
    TypeViewFactory* m_factory;	
	
    std::map<int, ControlWidget*> widgets;
    std::map<int, LabelWidget*> labels;

    Point clickedPos;
    int currentNodeID;
    int currentInputIndex;
    std::string currentName;
    std::string currentWidgetType;
    ParamMap currentParams;

    ControlWidget* currentControl;

    LabelWidget* currentLabel;

    utils::AutoPtr<ControlValueDispatcher> m_controlValueDispatcher;
  };

} // end of namespace gui

#endif
