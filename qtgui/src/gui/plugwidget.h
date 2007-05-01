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

#include <QtGui/qwidget.h>
#include <QtGui/qpixmap.h>

namespace gui
{
  
  class PlugWidget : public QWidget
  {
    Q_OBJECT
  public:
    enum PlugStatus {PLUG_FREE, PLUG_CONNECTED};

    PlugWidget(QWidget* parent,
	       const std::string& name,
	       const std::string& type,
	       int index, int ID, 
	       const QPixmap& free_,
	       const QPixmap& busy_);

    std::string getType() const { return m_type; }
    int getIndex() const { return m_index; }
    int getID() const { return m_ID; }
    std::string getName() const { return m_name; }
    void setStatus(PlugStatus status);

    void highlight();
    void removeHighlight();

  protected:
    virtual void mousePressEvent(QMouseEvent*);
    virtual void paintEvent(QPaintEvent*);       

    signals:
    void redrawLine(const QPoint& from, const QPoint& to);

  private:
    const std::string m_name;
    const std::string m_type;
    const int m_index;
    const int m_ID;
    PlugStatus m_status;

  protected:
    bool m_lineDrawMode;
    const QPixmap m_freePic;	
    const QPixmap m_busyPic;
    QPixmap m_pixmap;

  };


} // end of namespace gui

#endif

