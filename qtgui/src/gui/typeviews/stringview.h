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

#ifndef INCLUDED_STRING_VIEW_H
#define INCLUDED_STRING_VIEW_H

#include "gui/typeview.h"

#include <cstring>
#include <iostream>
#include <sstream>

#include <QtGui/QHBoxLayout>
#include <QtGui/qlineedit.h>
#include <QtGui/qvalidator.h>

#include <utils/buffer.h>
#include <utils/structreader.h>

namespace gui {
class StringView : public gui::TypeView {
  Q_OBJECT
public:
  StringView(QWidget *parent, const ParamMap &params)
      : TypeView(parent, params) {
    m_lineEdit = new QLineEdit(this);
    m_layout->addWidget(m_lineEdit);

    connect(m_lineEdit, SIGNAL(returnPressed()), this, SLOT(lineeditChanged()));
  }

  virtual ~StringView() {}

  virtual void valueChange(const utils::Buffer &newValue) {
    int len = newValue.getLen();
    const char *raw;
    if (len <= 0) {
      raw = "";
      len = 1;
    } else {
      raw = reinterpret_cast<const char *>(newValue.getPtr());
    }

    if (raw[len - 1] != 0) {
      std::cout << "ignoring string with missing termination\n";
      return;
    }
    std::string doof(raw, len);

    m_lineEdit->setText(doof.c_str());
  }

public slots:
  void lineeditChanged() {
    QByteArray raw = m_lineEdit->text().toUtf8();
    const char *text = raw.constData();

    //      std::cout << "Lineedit text = '" << text << "'" << std::endl;
    utils::Buffer b = utils::Buffer(
        reinterpret_cast<const unsigned char *>(text), std::strlen(text) + 1);

    emit valueChanged(b);
  }

private:
  QLineEdit *m_lineEdit;
};

class StringViewConstructor : public TypeViewConstructor {
public:
  StringViewConstructor();
  virtual TypeView *construct(QWidget *parent, const ParamMap &params) const;
};
} // namespace gui

#endif
