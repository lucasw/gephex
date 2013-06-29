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

#ifndef INCLUDED_ITOKENIZER_H
#define INCLUDED_ITOKENIZER_H

#include <string>

namespace utils
{
/**
 * Mit dem Stringtokenizer kann man Strings in einzelne Token
 * zerteilen. Man kann ihn wie einen Iterator ueber die Tokens 
 * eines Strings verwenden.
 */
class ITokenizer
{
	ITokenizer(const ITokenizer&); // nicht impl.
	ITokenizer& operator=(const ITokenizer&); // nicht impl.
 public:
	 ITokenizer();
	 virtual ~ITokenizer();
  
  /**
   * Liefert das naechste Token.
   * Geht so vor: Sucht ab der aktuellen Position nach
   * dem ersten nicht whitespace (siehe delims) und gibt den
   * Teilstring von dort bis zum naechsten whitespace zurueck.
   * Die neue Position ist der erste whitespace nach dem token.
   * @param delims Ein string der die Character enthaelt die als 
   *               Whitespaces angesehen werden.
   * @return das naechste Token oder den leeren string falls kein
   *         Token mehr da ist.
   */
  virtual std::string next(const std::string& delims) = 0;
};

} //end of namespace utils

#endif
