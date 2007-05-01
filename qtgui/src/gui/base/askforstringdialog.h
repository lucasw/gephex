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

#ifndef ASKFORSTRINGDIALOG_H
#define ASKFORSTRINGDIALOG_H

#include <string>
//#include <QtGui/qvariant.h>
#include <QtGui/qdialog.h>

class QLabel;
class QLineEdit;
class QPushButton;

namespace gui
{

class AskForStringDialog : public QDialog
{ 
    Q_OBJECT

public:
    AskForStringDialog( QWidget* parent, const std::string& caption, const std::string& text );
    ~AskForStringDialog();

	static std::string open(QWidget* parent, const std::string& caption,
		const std::string& text);

private:
    QLineEdit* LineEdit1;
    QLabel* TextLabel;
    QPushButton* DoneButton;

};

}

#endif

