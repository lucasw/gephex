#ifndef INCLUDED_STRING_TOKENIZER_H
#define INCLUDED_STRING_TOKENIZER_H

#include <string>
#include <iosfwd>

#include "itokenizer.h"

namespace utils
{

/**
 * Mit dem Streamtokenizer kann man Streams in einzelne Token
 * zerteilen. Man kann ihn wie einen Iterator ueber die Tokens 
 * eines Strings verwenden.
 */
class StreamTokenizer : public ITokenizer
{
	StreamTokenizer(const StreamTokenizer&); //nicht impl.
	StreamTokenizer& operator=(const StreamTokenizer&); //nicht impl.
 public:
  /**
   * Neuen StreamTokenizer der auf input arbeitet erzeugen.
   * @param input Der Stream der zerlegt werden soll.
   */
  StreamTokenizer(std::istream& input);

  std::string next(const std::string& delims);
 private:
  std::istream& m_input;
  
};

} //end of namespace utils
#endif
