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

#include "buffertest.h"

#include <iostream>

#include "buffer.h"
#include "block.h"


std::string BufferTest::getName() const
{
	return "BufferTest";
}

std::string BufferTest::getDescription() const
{
	return "";
}

void BufferTest::pre() throw(std::runtime_error)
{
}

void BufferTest::run() throw(std::runtime_error)
{
  // teste ob sich der buffer die daten kopiert
  std::string msg = "Hallo Kinder";
  utils::Buffer b((unsigned char*) msg.c_str(),msg.length()+1);

  msg = "00000";
  if (strcmp((const char*) b.getPtr(),"Hallo Kinder") != 0)
    throw std::runtime_error("Fehler");

  // teste + und += und =
  for (int size = 1; size <= 1024; size *= 2)
    {
      unsigned char* data = createRandomBlock(size*2);
      utils::Buffer b1(data,size);
      utils::Buffer b2(data+size,size);

      utils::Buffer b3 = b1 + b2;
      if (!compareBlocks(data,size*2,b3.getPtr(),b3.getLen()))
	{
	  throw std::runtime_error("Fehler!");
	}
  
      b1 += b2;
      if (!compareBlocks(data,size*2,b1.getPtr(),b1.getLen()))
	{
	  throw std::runtime_error("Fehler!");
	}

      b2 = b3;
      if (!compareBlocks(data,size*2,b2.getPtr(),b2.getLen()))
	{
	  throw std::runtime_error("Fehler!");
	}
      delete[] data;
    }

}

void BufferTest::post() throw(std::runtime_error)
{
}

