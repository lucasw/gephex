#ifndef INCLUDED_IXML_CONTENT_HANDLER
#define INCLUDED_IXML_CONTENT_HANDLER

class XmlAttributes;

class IXmlContentHandler
{
public:
	//virtual void setDocumentLocator ( QXmlLocator * locator ) 
	virtual bool startDocument () = 0;
	virtual bool endDocument () = 0;
	//virtual bool startPrefixMapping ( const std::string & prefix, const std::string & uri ) 
	//virtual bool endPrefixMapping ( const std::string & prefix ) 
	virtual bool startElement ( const std::string & namespaceURI, 
								const std::string & localName,
								const std::string & qName/*,
								const XmlAttributes & atts */) = 0;

	virtual bool endElement ( const std::string & namespaceURI, 
							  const std::string & localName, 
							  const std::string & qName ) = 0;

	virtual bool characters ( const std::string & ch ) = 0;
	//virtual bool ignorableWhitespace ( const std::string & ch ) 
	//virtual bool processingInstruction ( const std::string & target, const std::string & data ) 
	//virtual bool skippedEntity ( const std::string & name ) 
	virtual std::string errorString () = 0;
};

#endif