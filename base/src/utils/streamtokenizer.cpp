#include "streamtokenizer.h"

#include <iostream>

namespace utils
{
StreamTokenizer::StreamTokenizer(std::istream& input)
								 : m_input(input)
{
}

static bool goto_first_not_of(std::istream& s, const std::string& str)
{
	char c;
	while (s.get(c))
	{
		if (str.find(c) == std::string::npos)
		{
			s.unget();
			return true;
		}
	}
	
	return false;
}

static std::string goto_first_of(std::istream& s, const std::string& str)
{
	std::string result;
	char c;
	while (s.get(c))
	{
		if (str.find(c) != std::string::npos)
		{
			break;
		}
		result += c;
	}
	
	return result;
}
std::string StreamTokenizer::next(const std::string& delim)
{
	std::string token;
	
	if (m_input)
    {
		// start of found token
		bool first = goto_first_not_of(m_input,delim);
		
		if(first)
		{
			// length of found token
			token = goto_first_of(m_input,delim);
		}
    }
	
	return token;
}

} // end of namespace utils
