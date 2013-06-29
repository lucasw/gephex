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

#include "streamtokenizertest.h"

#include "streamtokenizer.h"

#include <sstream>
//#include <iostream>

/*---------------------------------------------------------------------------*/

StreamTokenizerTest::StreamTokenizerTest()
  : EasyTest("StreamTokenizerTest","")
{
}

StreamTokenizerTest::~StreamTokenizerTest()
{
}

void StreamTokenizerTest::pre() throw(std::runtime_error)
{
}

void StreamTokenizerTest::run() throw(std::runtime_error)
{
  std::istringstream stream("Hallo, ein\ttest\nfuer st     \nream");
  utils::StreamTokenizer st(stream);
  std::string token;

  token = st.next("\n\t\r ");
  if (token != "Hallo,")
    throw std::runtime_error("Fehler1");

  token = st.next("\n\t\r ");
  if (token != "ein")
    throw std::runtime_error((token + " (expected ein)").c_str());

  token = st.next(" \n\t\r");
  if (token != "test")
    throw std::runtime_error("Fehler3");

  token = st.next(" \n\t\r");
  if (token != "fuer")
    throw std::runtime_error("Fehler4");

  token = st.next(" \n\t\r");
  if (token != "st")
    throw std::runtime_error("Fehler5");

  token = st.next(" \n\t\r");
  if (token != "ream")
    throw std::runtime_error("Fehler6");

  token = st.next(" \n\t\r");
  if (token != "")
    throw std::runtime_error("Fehler7");
}

void StreamTokenizerTest::post() throw(std::runtime_error)
{
}
/*---------------------------------------------------------------------------*/
