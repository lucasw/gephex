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
