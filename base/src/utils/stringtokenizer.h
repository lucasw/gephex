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

#ifndef INCLUDED_STRING_TOKENIZER_H
#define INCLUDED_STRING_TOKENIZER_H

#include <string>

#include "itokenizer.h"

namespace utils
{

/**
 * Mit dem Stringtokenizer kann man Strings in einzelne Token
 * zerteilen. Man kann ihn wie einen Iterator ueber die Tokens 
 * eines Strings verwenden.
 */
class StringTokenizer : public ITokenizer
{
 public:
  /**
   * Neuen StringTokenizer der auf input arbeitet erzeugen.
   * @param input Der String der zerlegt werden soll.
   * @param pos Die Position in input ab der Tokens zurueckgeliefert werden.
   */
  StringTokenizer(const std::string& input, std::string::size_type pos = 0);

  std::string next(const std::string& delims);

  /**
   * Gibt die aktuelle Position im String zurück.
   * @return aktuelle Position
   */
  std::string::size_type getPos() const;

  /**
   * Gibt den gesamten String zurück der bearbeitet wird.
   * @return der bearbeitete string
   */
  const std::string& getString() const;

 private:
  std::string m_input;
  std::string::size_type m_pos;
};

} //end of namespace utils

#endif
