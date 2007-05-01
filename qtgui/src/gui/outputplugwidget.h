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

#ifndef INCLUDED_OUTPUT_PLUG_WIDGET_H
#define INCLUDED_OUTPUT_PLUG_WIDGET_H

#include <vector>

#include "plugwidget.h"

namespace gui
{
  class InputPlugWidget;

  class OutputPlugWidget : public gui::PlugWidget
  {
    Q_OBJECT
  private:
    std::vector<const InputPlugWidget*> connectedTo;
    
  protected:
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);

  public:
    OutputPlugWidget(QWidget* parent,
		     const QPixmap& free_, const QPixmap& busy_,
		     const std::string& name, const std::string& type,
		     int _index, int _ID);

    signals:
    void connectionRequestFromOutput(const OutputPlugWidget*,const QPoint& to);

    void underMouse(const OutputPlugWidget*);
	// TODO:
	// somehow qt seems not to no about signals inherited from the superclass
    //	void beginLineDraw();
    //    void redrawLine(const QPoint& from, const QPoint& to);
  };

} // end of namespace gui

#endif


