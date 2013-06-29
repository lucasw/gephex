/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

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