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

#include "autoptrtest.h"

#include <list>

#include "autoptr.h"

class DoofesDing
{
public:
  DoofesDing(bool& b)
    : m_b(b)
  {
    m_b = false;
  }

  ~DoofesDing()
  {
    m_b = true;
  }

private:
  bool& m_b;
};

std::string AutoPtrTest::getName() const
{
	return "AutoPtrTest";
}

std::string AutoPtrTest::getDescription() const
{
	return "";
}

void AutoPtrTest::pre() throw(std::runtime_error)
{
}

void AutoPtrTest::run() throw(std::runtime_error)
{
  bool destroyed = false;

  {
    utils::AutoPtr<DoofesDing> p1(new DoofesDing(destroyed));
    {
      utils::AutoPtr<DoofesDing> p2 = p1;
    }

    if (destroyed)
      {
		throw std::runtime_error("Fehler!!");
      }
  }

  if (!destroyed)
    {
      throw std::runtime_error("Fehler!!");
    }

  utils::AutoPtr<int> p(new int(100));

  if (*p != 100)
    throw std::runtime_error("Fehler!!");

  utils::AutoPtr<std::list<int> > p2(new std::list<int>());
  
  if (p2->size() != 0)
    throw std::runtime_error("Fehler!!");
}

void AutoPtrTest::post() throw(std::runtime_error)
{
}

