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

#ifndef INCLUDED_INPUT_PLUG_WIDGET_H
#define INCLUDED_INPUT_PLUG_WIDGET_H

#include <map>
#include <string>

#include "plugwidget.h"

namespace gui
{

  class OutputPlugWidget;

class InputPlugWidget : public gui::PlugWidget
  {
    Q_OBJECT

  public:
    typedef std::map<std::string, std::string> ParamMap;
    InputPlugWidget(QWidget* parent,
		    const QPixmap& free_, const QPixmap& busy_,  
		    const std::string& name,
		    const std::string& type,
		    const ParamMap& params,
		    int _index, int _ID, bool _inPropertyDialog);

    void setVisible();
    void setInvisible();
    bool isVisible() const;

    const ParamMap& getParams() const;

  signals:
    void connectionRequestFromInput(const InputPlugWidget*, const QPoint& to);
    void beenRightClicked( InputPlugWidget*);

    void underMouse(const InputPlugWidget*);
    // TODO:
    // somehow qt seems not to know about signals inherited from the superclass
    //	void beginLineDraw();
    //    void redrawLine(const QPoint& from, const QPoint& to);

    //    void wannaBeAProperty(int);
	
  protected:
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);

  private:
    const OutputPlugWidget* connectedTo;
    bool inPropertyDialog;
    ParamMap m_params;
  };

} // end of namespace gui

#endif

