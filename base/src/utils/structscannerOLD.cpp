//TODO Unterschied zwischen string::size() und string::length() nachschauen
#include "structscanner.h"

#include "stringtokenizer.h"

StructScanner::StructScanner(IStructTokenListener& listener)
: m_listener(listener)
{
}

static std::string trim(const std::string& s, const std::string& delim)
{
	std::string::size_type pos = s.find_first_not_of(delim);

	if (pos == std::string::npos)
		return std::string();

	std::string::size_type pos2 = s.find_first_of(delim,pos);
	if (pos2 == std::string::npos)
		return s.substr(pos,s.length());

	return s.substr(pos,pos2);
}

void StructScanner::divideNameFromContent(const std::string& text,
										  std::string& name,std::string& content) const
{
	std::string::size_type pos = text.find('{');
	if (pos == std::string::npos)
	{
		throw std::runtime_error("Fehler beim scannen: { nicht vorhanden!");
	}

	name = trim(text.substr(0,pos)," \n\t");

	std::string::size_type pos2 = text.rfind('}');
	if (pos2 == std::string::npos)
	{
		throw std::runtime_error("Fehler beim scannen: } nicht vorhanden!");
	}

	content = text.substr(pos+1,pos2);
}

void StructScanner::processName(const std::string& name) const
{
	m_listener.scannedStructName(name);
}

void StructScanner::processContent(const std::string& content) const
{
	StringTokenizer st(content);

	std::string var = st.next(";=");
	while (var != "")
	{
		std::string value = st.next("';");
		m_listener.scannedPair(trim(var,"\n\t "),value);

		var = trim(st.next("=")," \n\t");
	}

	/*std::string::size_type pos = content.find("=");

	if (content[pos+1] == '\'')
	{
	}
	else
	{
		StringTokenizer st(content,pos+1);
		value = st.next(" \n\t");
	}*/
}


void StructScanner::scan(const std::string& text) const throw (std::runtime_error)
{
	std::string name;
	std::string content;

	divideNameFromContent(text,name,content);

	processName(name);

	processContent(content);
}

