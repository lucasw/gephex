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

#include "circularbuffertest.h"

#include <iostream>

#include "circularbuffer.h"
#include "block.h"

#include "buffer.h"


std::string CircularBufferTest::getName() const
{
	return "CircularBufferTest";
}

std::string CircularBufferTest::getDescription() const
{
	return "";
}

void CircularBufferTest::pre() throw(std::runtime_error)
{
}

void CircularBufferTest::run() throw(std::runtime_error)
{
  int l0 = 31;
  int l1 = 100;
  int l2 = 43001;
  int l3 = 5;

  unsigned char* b0 = createRandomBlock(l0);
  unsigned char* b1 = createRandomBlock(l1);
  unsigned char* b2 = createRandomBlock(l2);
  unsigned char* b3 = createRandomBlock(l3);

  utils::CircularBuffer cb;

  cb.push_back(utils::Buffer(b0,l0));
  if (cb.len() != l0)
	  throw std::runtime_error("Wrong length after 0 push");

  cb.push_back(utils::Buffer(b1,l1));
  if (cb.len() != l0+l1)
	  throw std::runtime_error("Wrong length after 1 push");

  utils::Buffer buf0 = cb.pop_front(l0);
  if (cb.len() != l1)
	  throw std::runtime_error("Wrong length after 1 pop");

  cb.push_back(utils::Buffer(b2,l2));
  if (cb.len() != l1+l2)
	  throw std::runtime_error("Wrong length after 2 pushs");

  cb.push_back(utils::Buffer(b3,l3));
  if (cb.len() != l1+l2+l3)
	  throw std::runtime_error("Wrong length after 3 pushs");

  utils::Buffer buf1 = cb.pop_front(l1);
  if (cb.len() != l2+l3)
	  throw std::runtime_error("Wrong length after 1 pop");

  utils::Buffer buf2 = cb.pop_front(l2);
  if (cb.len() != l3)
	  throw std::runtime_error("Wrong length after 2 pops");

  utils::Buffer buf3 = cb.pop_front(l3);
  if (cb.len() != 0)
	  throw std::runtime_error("Wrong length after 3 pops");


  if (!compareBlocks(b0, l0, buf0.getPtr(), buf0.getLen()))
	  throw std::runtime_error("Block 1 does not compare equal");

  if (!compareBlocks(b1, l1, buf1.getPtr(), buf1.getLen()))
	  throw std::runtime_error("Block 1 does not compare equal");

  if (!compareBlocks(b2, l2, buf2.getPtr(), buf2.getLen()))
	  throw std::runtime_error("Block 2 does not compare equal");

  if (!compareBlocks(b3, l3, buf3.getPtr(), buf3.getLen()))
	  throw std::runtime_error("Block 3 does not compare equal");

  delete[] b3;
  delete[] b2;
  delete[] b1;  
}

void CircularBufferTest::post() throw(std::runtime_error)
{
}

