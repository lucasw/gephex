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

#include "typeviewfactory.h"

#include <string>
#include <stdexcept>

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

// builtin typeviews
#include "typeview.h"

#include "typeviews/boundednumberview.h"
#include "typeviews/unboundednumberview.h"
#include "typeviews/slidernumberview.h"
#include "typeviews/radionumberview.h"
#include "typeviews/checkboxnumberview.h"

#include "typeviews/stringview.h"
#include "typeviews/comboboxstringview.h"
#include "typeviews/filestringview.h"

#include "typeviews/positionview.h"

#include "typeviews/colorview.h"

#include "typeviews/fontview.h"

#if defined(OPT_SERIALIZE_FRAMEBUFFER)
#include "typeviews/frameview.h"
#endif

namespace gui
{

  TypeViewFactory::TypeViewFactory(const std::string& media_path)
  {
    
    registerTypeViewConstructor("typ_NumberType",
				new HSliderNumberViewConstructor());
    registerTypeViewConstructor("typ_NumberType",
				new VSliderNumberViewConstructor());
    registerTypeViewConstructor("typ_NumberType",
				new DialNumberViewConstructor());
    registerTypeViewConstructor("typ_NumberType",
				new UnboundedNumberViewConstructor());
    registerTypeViewConstructor("typ_NumberType",
				new BoundedNumberViewConstructor());
    registerTypeViewConstructor("typ_NumberType",
				new RadioNumberViewConstructor());
    registerTypeViewConstructor("typ_NumberType",
				new CheckBoxNumberViewConstructor());

    registerTypeViewConstructor("typ_StringType",
				new StringViewConstructor());
    registerTypeViewConstructor("typ_StringType",
				new ComboboxStringViewConstructor());
    registerTypeViewConstructor("typ_StringType",
				new FileStringViewConstructor(media_path));

    registerTypeViewConstructor("typ_PositionType",
				new PositionViewConstructor());

    registerTypeViewConstructor("typ_RGBType",
				new ColorViewConstructor());

    registerTypeViewConstructor("typ_FontType",
				new FontViewConstructor());

#if defined(OPT_SERIALIZE_FRAMEBUFFER)
	registerTypeViewConstructor("typ_FrameBufferType",
				new FrameViewConstructor());
#endif
    
				
  }

  TypeViewFactory::~TypeViewFactory()
  {
  }

  void TypeViewFactory::registerTypeViewConstructor(const std::string& typeID,
						    TypeViewConstructor* con)
  {
    m_infoMap[typeID].push_back(TypeViewInfo(con->getName(),
					     con->getViewID()));

    m_constructorMap[con->getViewID()] = con;
  }

  TypeViewConstructor*
  TypeViewFactory::getConstructor(const std::string& viewID) const
  {
    ViewToConstructorMap::const_iterator 
      it = m_constructorMap.find(viewID);

    if (it == m_constructorMap.end())
      throw std::runtime_error("unknown viewID : '" + viewID +
			       "' (TypeViewFactory::getConstructor)");
    else
      return it->second;
  }

  TypeViewFactory::TypeViewInfoList
  TypeViewFactory::getCompatibleViews(const std::string& typeID) const
  {
    TypeToInfoMap::const_iterator it = m_infoMap.find(typeID);
		
    if (it == m_infoMap.end())
      {
	TypeViewInfoList emptyList;
	return emptyList;
      }
		
    return it->second;
  }

} // end of namespace gui
