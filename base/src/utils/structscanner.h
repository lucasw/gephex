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

void StructScanner::divideNameFromContent(const std::string& text,
										  std::string& name,std::string& content) const;
void StructScanner::processName(const std::string& name) const;
void StructScanner::processContent(const std::string& content) const;
std::string::size_type findNextClosingBracket(const std::string& content,
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
