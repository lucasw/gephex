#ifndef INCLUDED_STRING__H
#define INCLUDED_STRING__H

#include <string>
#include <iosfwd>

namespace utils
{

  /**
   * This is a string class that supports serialization and deserialization
   * to and from a stream via the standard << and >> operators.
   * std::string does not support this, for example:
   *
   *    std::string s("Hallo Kinderchen");
   *    stream << s;
   *    std:.string s2;
   *    stream >> s2;
   *    assert(s1 == s2);
   *
   *    The assertion will fail, s2 will just be "Hallo".
   */
  class String
  {
  public:
    String(const std::string& str = "");

    const String& operator=(const String&);

    std::string::size_type length() const { return m_data.length(); }

    const char* c_str() const{ return m_data.c_str(); }

    operator std::string() const { return m_data; }

    bool operator==(const String&s)
    {
      return m_data == s.m_data;
    }

    bool operator!=(const String&s)
    {
      return m_data != s.m_data;
    }

  private:
    String(const String&);

    std::string m_data;
  };

  std::ostream& operator<<(std::ostream& s, const utils::String& str);
  std::istream& operator>>(std::istream& s, utils::String& str);
}

#endif
