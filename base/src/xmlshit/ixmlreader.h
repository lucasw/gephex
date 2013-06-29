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