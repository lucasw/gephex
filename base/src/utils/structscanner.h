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

#ifndef INCLUDED_STRUCT_PARSER_H
#define INCLUDED_STRUCT_PARSER_H

#include <stdexcept>
#include <string>

#include "istructtokenlistener.h"

namespace utils
{

/**
 * Hilfsklasse zum scannen von pseudo c-structs (fuer Beschreibung siehe
 * StructReader). Sie uebernimmt das Scannen der c-structs und ruft bei
 * jedem erkannten "var=val" paar einen Listener auf.
 */
class StructScanner
{
 IStructTokenListener& m_listener;
  
  void divideNameFromContent(const std::string& text,
					    std::string& name,
					    std::string& content) const;
  void processName(const std::string& name) const;
  void processContent(const std::string& content) const;
  std::string::size_type
  findNextClosingBracket(const std::string& content,
			 std::string::size_type n) const;
 public:
  /**
   * Konstruiert neuen StructScanner.
   * @param listener Der Listener der beim scannen benachrichtigt
   *        wird wenn token erkannt werden.
   */
  StructScanner(IStructTokenListener& listener);

  /**
   * Scannt die pseudo c-struct in text.
   * @param text Ein string der eine pseudo c-struct enthaelt
   * @exception std::runtime_error Wird geschmissen wenn text
   *             Syntaxfehler enthaelt.
   */
  void scan(const std::string& text) const throw (std::runtime_error);
};

} //end of namespace utils
#endif
