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
