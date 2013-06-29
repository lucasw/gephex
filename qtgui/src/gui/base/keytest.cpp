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

#include "keytest.h"

#include <iostream>

#include "key.h"

using gui::Key;
/*---------------------------------------------------------------------------*/

KeyTest::KeyTest()
  : EasyTest("KeyTest","")
{
}

KeyTest::~KeyTest()
{
}

void KeyTest::pre() throw(std::runtime_error)
{
}

void KeyTest::run() throw(std::runtime_error)
{
  gui::Key k1(Key::Key_A, Key::AltModifier);
  
  if (k1.code() != Key::Key_A || k1.modifierMask() != Key::AltModifier)
    {
      throw std::runtime_error("Schlecht!");
    }

  gui::Key k2("Alt-A");
  
  if (k2.code() != Key::Key_A || k2.modifierMask() != Key::AltModifier)
    {
      throw std::runtime_error("2xSchlecht!");
    }

  if (!(k1 == k2))
    {
      throw std::runtime_error("3xSchlecht!");
    }

  if (k1 != k2)
    {
      throw std::runtime_error("4xSchlecht!");
    }
}

void KeyTest::post() throw(std::runtime_error)
{
}
/*---------------------------------------------------------------------------*/
