#include "stringtokenizer.h"

namespace utils
{

StringTokenizer::StringTokenizer(const std::string& input,
				 std::string::size_type pos)
  : m_input(input), m_pos(pos)
{
}

std::string StringTokenizer::next(const std::string& delim)
{
	std::string token;
	
	if (m_pos != std::string::npos)
    {
		// start of found token
		std::string::size_type first = m_input.find_first_not_of(delim.c_str(), 
			m_pos);
		
		if( first != std::string::npos )
		{
			// length of found token
			std::string::size_type num = m_input.find_first_of(delim.c_str(),
				first) - first;
			// do all the work off to the side
			token = m_input.substr( first, num );
			
			// done; now commit using
			// nonthrowing operations only
			m_pos = first+num;
			if( m_pos != std::string::npos ) 
				++m_pos;
			if( m_pos >= m_input.size() ) 
				m_pos = std::string::npos;
		}
    }
	
	return token;
}

std::string::size_type StringTokenizer::getPos() const
{
	return m_pos;
}

const std::string& StringTokenizer::getString() const
{
	return m_input;
}

} // end of namespace utils
