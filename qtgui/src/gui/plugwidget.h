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

#ifndef INCLUDED_PLUG_WIDGET_H
#define INCLUDED_PLUG_WIDGET_H

#include <string>

#include <qwidget.h>
#include <qpixmap.h>

namespace gui
{
  
  class PlugWidget : public QWidget
  {
    Q_OBJECT
  public:
    enum PlugStatus {PLUG_FREE, PLUG_CONNECTED};

    PlugWidget(QWidget* parent, const char* name, 
	       std::string _name, std::string _type, int _index, int _ID, 
	       const QPixmap& free_, const QPixmap& busy_);

    std::string getType() const { return type; }
    int getIndex() const { return index; }
    int getID() const { return ID; }
    std::string getName() const { return name; }
    void setStatus(PlugStatus status);

    void highlight();
    void removeHighlight();

  protected:
    virtual void mousePressEvent(QMouseEvent*);
       
    signals:
    void beginLineDraw();
    void redrawLine(const QPoint& from, const QPoint& to);

  private:
    const std::string name;
    const std::string type;
    const int index;
    const int ID;
    PlugStatus m_status;

  protected:
    bool lineDrawMode;
    const QPixmap freePic;	
    const QPixmap busyPic;

  };


} // end of namespace gui

#endif

