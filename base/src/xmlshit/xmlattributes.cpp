#ifndef INCLUDED_XML_ATTRIBUTES
#define INCLUDED_XML_ATTRIBUTES

struct Attrib
{
	std::string qName;
	std::string value;
	std::string type;
};

class XmlAttributesImp
{
public:

};

XmlAttributes::XmlAttributes ()
{
}

virtual XmlAttributes ::~XmlAttributes ()
{
}

int XmlAttributes ::index ( const std::string & qName ) const
{
}
	//int index ( const std::string & uri, const std::string & localPart ) const
int XmlAttributes ::length () const
{
}

std::string XmlAttributes ::localName ( int index ) const
{
}

	//std::string qName ( int index ) const
	//std::string uri ( int index ) const
std::string XmlAttributes ::type ( int index ) const
{
}

	//std::string type ( const std::string & qName ) const;
	//std::string type ( const std::string & uri, const std::string & localName ) const
std::string XmlAttributes ::value ( int index ) const
{
}

	//std::string value ( const std::string & qName ) const;
	
#endif