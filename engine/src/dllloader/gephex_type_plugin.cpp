/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2005

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

#include "gephex_type_plugin.h"

#include "utils/autoptr.h"
#include "utils/sharedlibrary.h"
#include <stdexcept>

namespace dllloader
{

  namespace
  {
    int Dinit(void (*)(int,const char*, const char*))
    {
      return 1;
    }

    void DshutDown()
    {
    }
    
    int DattributesEqual(void*,void*)
    {
      /*throw std::runtime_error("Operation attributesEqual() not "
	"supported by this module!");*/
      
      return 1;
    }

    int DconvertType(void*,void*,void*)
    {
      throw std::runtime_error("Operation convertType() not supported by this "
			       "type!");
    }

    int Dserialize(void*, char*, int)
    {
      return 0;
    }

    void DdeSerialize(const char*, int, void*)
    {
    }
  }

  CTypeFunctionTable extract_type_functions(utils::AutoPtr<utils::SharedLibrary> sl)
  {
    // this table stores all resolved symbols from shared library
    // The pointers can only be used as long the lib is not deleted.
    // This is the reason why it holds a autoptr to sl
    CTypeFunctionTable ft(sl);

    // load all symbols into the struct
    // ISO C++ forbids casting between pointer-to-function and pointer-to-obj
    // so we must use a c-style cast
    ft.newInstance = (newInstanceT)(sl->loadSymbol("newInstance"));
    ft.deleteInstance = (deleteInstanceT)(sl->loadSymbol("deleteInstance"));
    ft.init = (initT)(sl->loadSymbol("init"));
    ft.shutDown = (shutDownT)(sl->loadSymbol("shutDown"));
    ft.getSpec = (getSpecT)(sl->loadSymbol("getSpec"));
    ft.getInfo = (getInfoT)(sl->loadSymbol("getInfo"));
    ft.assign = (assignT)(sl->loadSymbol("assign"));
    ft.serialize = (serializeT)(sl->loadSymbol("serialize"));
    ft.deSerialize = (deSerializeT)(sl->loadSymbol("deSerialize"));
    ft.attributesEqual = (attributesEqualT)(sl->loadSymbol("attributesEqual"));
    ft.convertType = (convertTypeT)(sl->loadSymbol("convertType"));

    // some symbols arent necessary for a proper typedll
    // add default handlers for these functions
    if ( ft.init == 0) ft.init = Dinit;
    if ( ft.shutDown == 0 ) ft.shutDown = DshutDown;
    if ( ft.attributesEqual == 0 ) ft.attributesEqual = DattributesEqual;
    if ( ft.convertType == 0 ) ft.convertType = DconvertType;
    if ( ft.serialize == 0 ) ft.serialize = Dserialize;
    if ( ft.deSerialize == 0 ) ft.deSerialize = DdeSerialize;

    // now all symbols must be defined
    // check if all of the arent 0
    if ( ft.newInstance == 0 ) 
      throw std::runtime_error("symbol newInstance missing");
    if ( ft.deleteInstance == 0 )
      throw std::runtime_error("symbol deleteInstance missing");
    if ( ft.getSpec == 0 )
      throw std::runtime_error("symbol getSpec missing");
    if ( ft.getInfo == 0 )
      throw std::runtime_error("symbol getInfo missing");
    if ( ft.serialize == 0 )
      throw std::runtime_error("symbol serialze missing");
    if ( ft.assign == 0 )
      throw std::runtime_error("symbol assign missing");
    if ( ft.shutDown == 0 )
      throw std::runtime_error("symbol shutDown missing");
    if ( ft.init == 0 )
      throw std::runtime_error("symbol init missing");
    if ( ft.convertType == 0 ) 
      throw std::runtime_error("symbol convertType missing");
    if ( ft.attributesEqual == 0 ) 
      throw std::runtime_error("symbol attributesEqual missing");
    if ( ft.deSerialize == 0 )
      throw std::runtime_error("symbol deSerialize  missing");

    // all symbols are defined
    return ft;
  }
}
