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

#include "Tester.h"

#include "LeafTest.h"
#include "CompositeTest.h"

#include <iostream>


TesterStream::TesterStream(std::ostream& s)
 : m_s(&s), m_level(0)
{
}

TesterStream::~TesterStream()
{
}

void TesterStream::performTest(LeafTest& lt)
{
	std::string spaces = "";
	for (int i = 0; i < m_level; ++i)
		spaces += ' ';

	(*m_s) << spaces << "Test: " << lt.getName() << std::endl;
	(*m_s) << spaces << lt.getDescription() << std::endl;

	try 
	{
		lt.pre();
	}
	catch (std::exception& e)
	{
		(*m_s) << spaces <<"FAIL at pre(): " << e.what() << std::endl;
		lt.post(); //TODO
		return;
	}
	try 
	{
		lt.run();
	}
	catch (std::exception& e)
	{
		(*m_s) << spaces <<"FAIL at run(): " << e.what() << std::endl;
		lt.post(); //TODO
		return;
	}
	try 
	{
		lt.post();
	}
	catch (std::exception& e)
	{
		(*m_s) << spaces <<"FAIL at post(): " << e.what() << std::endl;
		return;
	}

	(*m_s) << spaces <<"OK" << std::endl;
}

void TesterStream::preTests(CompositeTest& ct)
{
	std::string spaces = "";
	for (int i = 0; i < m_level; ++i)
		spaces += ' ';

	(*m_s) << spaces << "Starting Test Group: " << ct.getName() << std::endl << ct.getDescription() << std::endl;
	++m_level;
}

void TesterStream::postTests(CompositeTest& ct)
{
	--m_level;
	std::string spaces;
	for (int i = 0; i < m_level; ++i)
		spaces += ' ';

	(*m_s) << spaces << "Finished Test Group: " << ct.getName() << std::endl;
}
