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