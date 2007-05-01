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

#include "askforstringdialog.h"

#include <QtGui/qlabel.h>
#include <QtGui/qlineedit.h>
#include <QtGui/qpushbutton.h>
#include <QtCore/qvariant.h>
#include <QtGui/qtooltip.h>
#include <QtGui/qwhatsthis.h>

namespace gui
{

AskForStringDialog::AskForStringDialog(QWidget* parent,
				       const std::string& caption,
				       const std::string& text )
    : QDialog( parent)
{
    resize( 227, 60 ); 
    setProperty( "caption", tr( caption.c_str() ) );

    LineEdit1 = new QLineEdit( this );
    LineEdit1->setGeometry( QRect( 10, 30, 120, 22 ) ); 

    TextLabel = new QLabel( this);
    TextLabel->setGeometry( QRect( 10, 7, 180, 13 ) ); 
    TextLabel->setProperty( "text", tr( text.c_str() ) );

    DoneButton = new QPushButton( this);
    DoneButton->setGeometry( QRect( 160, 30, 60, 26 ) ); 
    DoneButton->setProperty( "text", tr( "Done" ) );

    // signals and slots connections    
    connect( DoneButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( LineEdit1, SIGNAL( returnPressed() ), this, SLOT( accept() ) );
}


AskForStringDialog::~AskForStringDialog()
{
}

std::string AskForStringDialog::open(QWidget* parent,
				     const std::string& caption,
				     const std::string& text)
{
	AskForStringDialog dialog(parent, caption, text);

	//dialog.show();

	dialog.exec();

	return dialog.LineEdit1->text().toUtf8().constData();
}

}
