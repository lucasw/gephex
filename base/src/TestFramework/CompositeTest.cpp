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

#include "CompositeTest.h"
#include "Tester.h"

CompositeTest::CompositeTest(std::string name,std::string description)
	: m_name(name), m_description(description)
{
}

CompositeTest::~CompositeTest()
{
}

void CompositeTest::action(Tester& t)
{
  t.preTests(*this);

  for (std::list<Test*>::iterator i = m_tests.begin(); i != m_tests.end(); ++i)
    {
      (*i)->action(t);
    }

  t.postTests(*this);
}

std::string CompositeTest::getName() const
{
	return m_name;
}

std::string CompositeTest::getDescription() const
{
	return m_description;
}

void CompositeTest::addTest(Test& t)
{
	m_tests.push_back(&t);
}
