#ifndef INCLUDED_XML_ATTRIBUTES_H
#define INCLUDED_XML_ATTRIBUTES_H

#include <string>

class XmlAttributesImp;

class XmlAttributes
{
public:
	XmlAttributes () ;
	virtual ~XmlAttributes () ;
	int index ( const std::string & qName ) const;
	//int index ( const std::string & uri, const std::string & localPart ) const
	int length () const;
	std::string localName ( int index ) const;
	//std::string qName ( int index ) const
	//std::string uri ( int index ) const
	std::string type ( int index ) const;
	//std::string type ( const std::string & qName ) const;
	//std::string type ( const std::string & uri, const std::string & localName ) const
	std::string value ( int index ) const;
	//std::string value ( const std::string & qName ) const;
	//std::string value ( const std::string & uri, const std::string & localName ) const

private:
	XmlAttributesImp* m_impl;
};

#endif
