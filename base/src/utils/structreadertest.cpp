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

#include "structreadertest.h"

#include "structreader.h"
#include <map>

/*---------------------------------------------------------------------------*/

StructReaderTest::StructReaderTest()
  : EasyTest("StructReaderTest","")
{
}

StructReaderTest::~StructReaderTest()
{
}

void StructReaderTest::pre() throw(std::runtime_error)
{
}

void StructReaderTest::run() throw(std::runtime_error)
{
  std::string structure = "test { var1=1; var2=Hallo; var3=true; }";
  utils::StructReader reader(structure);

  if (reader.getName() != "test")
    throw std::runtime_error("Name ist falsch erkannt");

  if (reader.getIntValue("var1") != 1)
    throw std::runtime_error("Int Variable falsch");

  if (reader.getStringValue("var2") != "Hallo")
    throw std::runtime_error("String Variable falsch");

  if (reader.getBoolValue("var3") != true)
    throw std::runtime_error("Bool Variable falsch");

  bool exception = true;
  try {
    int tmp =  reader.getIntValue("var3"); // exception shoul be thrown
    exception = false;
  }
  catch (std::runtime_error) {}

  if (!exception) 
    throw std::runtime_error("Typueberpruefung fehlgeschlagen");
}

void StructReaderTest::post() throw(std::runtime_error)
{
}
/*---------------------------------------------------------------------------*/
