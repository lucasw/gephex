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

#include "key.h"

#include <stdexcept>
#include <map>
#include <cctype>
#include <algorithm>

//TODO: ugly hack, because tolower is not in namespace std in vc6!
using namespace std;

namespace {

  struct TransTab
  {
    std::string name;
    int value;
  };
  
  using gui::Key;

class KeyTranslator
{
public:
  KeyTranslator()
  {
    
      m_modifiers["ctrl"] = Key::CtrlModifier;
      m_modifiers["ctrlalt"] = Key::CtrlModifier | Key::AltModifier;
      m_modifiers["ctrlaltshift"] = Key::CtrlModifier | Key::AltModifier 
									| Key::ShiftModifier;
      m_modifiers["alt"] = Key::AltModifier;
      m_modifiers["altshift"] = Key::AltModifier | Key::ShiftModifier ;
      m_modifiers["shift"] = Key::ShiftModifier;
      m_modifiers["ctrlshift"] = Key::CtrlModifier | Key::ShiftModifier;

	  m_codes["0"] = Key::Key_0; m_codes["1"] = Key::Key_1; m_codes["2"] = Key::Key_2;
	  m_codes["3"] = Key::Key_3; m_codes["4"] = Key::Key_4; m_codes["5"] = Key::Key_5;
	  m_codes["6"] = Key::Key_6; m_codes["7"] = Key::Key_7; m_codes["8"] = Key::Key_8;
	  m_codes["9"] = Key::Key_9;

	  m_codes["f1"] = Key::Key_F1; m_codes["f2"] = Key::Key_F2; m_codes["f3"] = Key::Key_F3;
	  m_codes["f4"] = Key::Key_F4; m_codes["f5"] = Key::Key_F5; m_codes["f6"] = Key::Key_F6;
	  m_codes["f7"] = Key::Key_F7; m_codes["f8"] = Key::Key_F8; m_codes["f9"] = Key::Key_F9;
	  m_codes["f10"] = Key::Key_F10; m_codes["f11"] = Key::Key_F11; m_codes["f12"] = Key::Key_F12;

      m_codes["a"] = Key::Key_A; m_codes["b"] = Key::Key_B; m_codes["c"] = Key::Key_C;
      m_codes["d"] = Key::Key_D; m_codes["e"] = Key::Key_E; m_codes["f"] = Key::Key_F;
      m_codes["g"] = Key::Key_G; m_codes["h"] = Key::Key_H; m_codes["i"] = Key::Key_I;
      m_codes["j"] = Key::Key_J; m_codes["k"] = Key::Key_K; m_codes["l"] = Key::Key_L;
      m_codes["m"] = Key::Key_M; m_codes["n"] = Key::Key_N; m_codes["o"] = Key::Key_O;
      m_codes["p"] = Key::Key_P; m_codes["q"] = Key::Key_Q; m_codes["r"] = Key::Key_R;
      m_codes["s"] = Key::Key_S; m_codes["t"] = Key::Key_T; m_codes["u"] = Key::Key_U;
      m_codes["v"] = Key::Key_V; m_codes["w"] = Key::Key_W; m_codes["x"] = Key::Key_X;
      m_codes["y"] = Key::Key_Y; m_codes["z"] = Key::Key_Z;
    
  }

  std::string toLower(const std::string s)
  {
	  std::string ret;
	  ret = s;
	  std::transform(ret.begin(),ret.end(), ret.begin(), tolower);

	  return ret;
  }

  bool translate(const std::string& keyID,
		 int& code, int& modifierMask)
  {
    std::string::size_type pos = keyID.find("-");
    std::string keyName;
    if (pos == std::string::npos)
      {
	modifierMask = 0;
	keyName = toLower(keyID);	
      }
    else
      {
	std::string mod = toLower(keyID.substr(0, pos));
	
	std::map<std::string, int>::const_iterator it 
	  = m_modifiers.find(mod);

	if (it == m_modifiers.end())
	  return false;

	modifierMask = it->second;
	keyName = toLower(keyID.substr(pos+1));	
      }

    std::map<std::string, int>::const_iterator it
      = m_codes.find(keyName);

    if (it == m_codes.end())
      return false;

    code = it->second;

    return true;
  }

private:
  std::map<std::string, int> m_codes;
  std::map<std::string, int> m_modifiers;

};

static bool translateKeyID(const std::string& keyID,
			   int& code, int& modifierMask)
{
  static KeyTranslator tr;
  
  return tr.translate(keyID, code, modifierMask);
}
}

namespace gui {

  Key::Key(int keyCode, int modifierMask)
    : m_code(keyCode), m_modifierMask(modifierMask)
  {
  }

  Key::Key(const std::string& keyName)
  {
    bool ok = translateKeyID(keyName, m_code, m_modifierMask);
    if (!ok)
      throw std::runtime_error("Malformed keyName: '" + keyName + "'"); 
  }

  int Key::code() const
  {
    return m_code;
  }

  int Key::modifierMask() const
  {
    return m_modifierMask;
  }

  bool Key::operator==(const Key& rhs) const
  {
    return (code() == rhs.code() &&
	    modifierMask() == rhs.modifierMask());
  }

  bool Key::operator!=(const Key& rhs) const
  {
    return !(*this == rhs);
  }

}
