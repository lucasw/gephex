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
