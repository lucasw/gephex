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

#ifndef INCLUDED_PROPERTY_WIDGET_H
#define INCLUDED_PROPERTY_WIDGET_H

#include <string>
#include <map>

//#include <QtGui/qframe.h>
#include <QtGui/qwidget.h>

#include "interfaces/icontrolvaluereceiver.h"
#include "utils/buffer.h"

class IModelControlReceiver;

namespace gui
{
  class TypeView;
  class TypeViewConstructor;

  class PropertyWidget : public QWidget,
			 public IControlValueReceiver
  {
    Q_OBJECT
  public:
    typedef std::map<std::string,std::string> ParamMap;
    PropertyWidget(QWidget* parent, Qt::WFlags fl,
		   int nodeID,int inIndex, int controlID,
		   IModelControlReceiver&,
		   const ParamMap& params,
		   const TypeViewConstructor& con);

    virtual ~PropertyWidget();
  
    //    virtual utils::Buffer getValue() const = 0;

    virtual void controlValueChanged(int nodeID,int intputIndex,
				     const utils::Buffer& newValue);

    virtual void syncInputValuesStarted();
    virtual void syncInputValuesFinished();
  
    int getControlID() const;
    int getNodeID() const;
    int getInputIndex() const;

  protected:

    void setValue(const utils::Buffer& b);
  
    private slots:
      void changeValue(const utils::Buffer& b);

  private:
    int m_controlID;
    int m_nodeID;
    int m_inputIndex;
    IModelControlReceiver& mcr;
    TypeView* m_view;
  };
 
}

#endif
