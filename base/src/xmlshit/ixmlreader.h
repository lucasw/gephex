#ifndef INCLUDED_IXML_READER_H
#define INCLUDED_IXML_READER_H

class IXmlContentHandler;

class IXmlReader
{
public:
	//virtual bool feature ( const std::string & name, bool * ok = 0 ) const
	//virtual void setFeature ( const std::string & name, bool value ) 
//virtual bool hasFeature ( const std::string & name ) const = 0;
//virtual void* property ( const std::string & name, bool * ok = 0 ) const = 0;
//virtual void setProperty ( const std::string & name, void * value ) = 0; 
//virtual bool hasProperty ( const std::string & name ) const
//virtual void setEntityResolver ( QXmlEntityResolver * handler ) 
//virtual QXmlEntityResolver* entityResolver () const
//virtual void setDTDHandler ( QXmlDTDHandler * handler ) 
//virtual QXmlDTDHandler* DTDHandler () const
virtual void setContentHandler ( IXmlContentHandler * handler )  = 0;
virtual IXmlContentHandler* contentHandler () const = 0;
//virtual void setErrorHandler ( QXmlErrorHandler * handler ) 
//virtual QXmlErrorHandler* errorHandler () const
//virtual void setLexicalHandler ( QXmlLexicalHandler * handler ) 
//virtual QXmlLexicalHandler* lexicalHandler () const
//virtual void setDeclHandler ( QXmlDeclHandler * handler ) 
//virtual QXmlDeclHandler* declHandler () const
virtual bool parse ( const std::istream& input ) 

};
#endif