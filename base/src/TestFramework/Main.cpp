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

#include "LeafTest.h"
#include "CompositeTest.h"
#include "Tester.h"

#include <iostream>

class MyTest : public LeafTest
{
public:
	virtual std::string getName() const
	{
		return "Test1";
	}

	virtual std::string getDescription() const
	{
		return "An important test";
	}

	virtual void pre() throw(std::runtime_error)
	{
	}

	virtual void run() throw(std::runtime_error)
	{
		throw std::runtime_error("Hello");
	}

	virtual void post() throw(std::runtime_error)
	{
	}
};

int main(int argc,char* argv[])
{

	MyTest t1, t2;
	TesterStream ts(std::cout);
	
	CompositeTest ct("Compo", "Yes");

	ct.addTest(t1);
	ct.addTest(t2);

	ct.action(ts);

	return 0;
}
