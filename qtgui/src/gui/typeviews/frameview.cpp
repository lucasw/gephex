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

#include "frameview.h"

#include <sstream>
#include <iostream>

#include <qlayout.h>
#include <qpushbutton.h>
#include <qtooltip.h>
#include <qpixmap.h>
#include <qimage.h>
#include <qlabel.h>
#include <qpainter.h>

namespace gui
{

  class FrameView : public gui::TypeView
  {
    Q_OBJECT
			
  public:
    FrameView(QWidget* parent, const ParamMap& params)
      : TypeView(parent, params)
    {
      QHBoxLayout* l = new QHBoxLayout(this);
      m_view = new QLabel(this);
      m_view->setMinimumSize(16, 16);
      m_view->setScaledContents ( true );
      //select->setMaximumSize(60, 20);
      resize(32, 32);
      m_view->show();
      l->addWidget(m_view);
    }
		
    virtual ~FrameView() {}

    virtual void valueChange(const utils::Buffer& newValue)
    {
      const char* dataPtr= reinterpret_cast<const char*>(newValue.getPtr());

	  if (!dataPtr)
		return;

      // todo
      QImage img(16,16,32);
      for (int y=0;y!=16;++y)
	for (int x=0;x!=16;++x)
	  {
	    char r=*dataPtr; ++dataPtr;
	    char g=*dataPtr; ++dataPtr;
	    char b=*dataPtr; ++dataPtr;
	    //std::cerr << (int)r << "," << (int)g << "," << (int)b << std::endl;
	    img.setPixel ( x, 15-y, qRgb(r,g,b));
	  }
      
      QPixmap pix(16, 16);
      pix.convertFromImage(img);
      m_view->setPixmap(pix);
      //repaint();
    }

  private:
    QLabel* m_view;
  };


  // constructor

  FrameViewConstructor::FrameViewConstructor()
    : TypeViewConstructor("frame preview", "frame_preview")
  {
  }
	

  TypeView*
  FrameViewConstructor::construct(QWidget* parent,
				  const ParamMap& params) const
  {
    return new FrameView(parent, params);
  }

}

#include "frameview_moc_cpp.cpp"
