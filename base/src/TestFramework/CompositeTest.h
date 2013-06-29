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

#ifndef INCLUDED_COMPOSITE_TEST_H
#define INCLUDED_COMPOSITE_TEST_H

#include "Test.h"
#include <list>

class CompositeTest : public Test
{
public:
	CompositeTest(std::string name,std::string description);
	virtual ~CompositeTest();

	virtual std::string getName() const;
	virtual std::string getDescription() const;

	virtual void addTest(Test&);

	virtual void action(Tester&);

private:
	std::list<Test*> m_tests;
	std::string m_name;
	std::string m_description;
};

#endif
