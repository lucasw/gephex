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

#ifndef INCLUDED_CONTROL_WIDGET_H
#define INCLUDED_CONTROL_WIDGET_H

#include <string>
#include <map>

#include <QtGui/qframe.h>

#include "interfaces/icontrolvaluereceiver.h"

namespace utils {
  class Buffer;
}	

namespace gui
{
  class TypeViewConstructor;
  class TypeView;

  class ControlWidget : public QFrame, 
			public IControlValueReceiver
  {

    Q_OBJECT
  public:
    typedef std::map<std::string, std::string> ParamMap;

    ControlWidget(QWidget* parent, const std::string& name, int controlID,
		  int nodeID, int inputIndex,
		  const ParamMap& params,
		  const TypeViewConstructor* con);

    virtual ~ControlWidget();

    std::string name() const { return m_name; }
    int controlID() const { return m_controlID; }
    int nodeID() const { return m_nodeID; }
    int inputIndex() const { return m_inputIndex; }

    QWidget* getLabel();

    void setName(const std::string& newName);	

    virtual void controlValueChanged(int nodeID,int intputIndex,
				     const utils::Buffer& newValue);

    virtual void syncInputValuesStarted();
    virtual void syncInputValuesFinished();

  protected:
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent* e);

  protected slots:

    void changeValue(const utils::Buffer&);

  signals:
    void valueChanged(int,int,const utils::Buffer&);
    void moved(ControlWidget*, const QPoint&);
    void released(ControlWidget*, const QPoint&);

    void beenRightClicked(ControlWidget*, const QPoint& );

  private:
    std::string m_name;
    int m_controlID;
    int m_nodeID;
    int m_inputIndex;
    bool dragMode;
    QPoint clickedPos;
    QWidget* m_label;
    TypeView* m_view;
  };
}
#endif
