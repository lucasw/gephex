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

#include "tagutils.h"

#include "convertbin.h"
#include "utils/buffer.h"


namespace net {

  
  void StringTagUtil::attachTag(utils::Buffer& dst,
				const std::string& tag,
				const utils::Buffer& b)
  {
    const uint32_t payload_length = tag.length()+1;
    const unsigned int l = payload_length + sizeof(uint32_t);
    unsigned char* data = new unsigned char[l];
    
    convert_uint32_to_le(payload_length, data);
    
    memcpy(data+sizeof(uint32_t), tag.c_str(), payload_length);
    
    dst = utils::Buffer(data, l) + b;

    delete[] data;
  }

  void StringTagUtil::removeTag(utils::Buffer& dst,
				std::string& tag,
				const utils::Buffer& src)
  {
    const unsigned char* data = src.getPtr();
    const uint32_t l = convert_uint32_from_le(data);

    //std::cout << "src = '" << /*src <<*/ "', l = '" << l << "'" << std::endl;
    
    dst = utils::Buffer(data + sizeof(uint32_t) + l,
			src.getLen() - l - sizeof(uint32_t));

    tag = std::string(reinterpret_cast<const char*>(data 
						    + sizeof(uint32_t)),
		      l-1);

    //std::cout << "dst = '" << /*dst 
    //<<*/ "', tag = '" << tag << "'" << std::endl;

  }
 

  void UInt32TagUtil::attachTag(utils::Buffer& dst,
				const uint_32& tag,
				const utils::Buffer& b)
  {
    static unsigned char data[sizeof(uint_32)];
    
    convert_uint32_to_le(tag, data);
    
    dst = utils::Buffer(data, sizeof(data)) + b;
    
    //std::cout << "Attached Tag = " << tag << std::endl;
  }

  void UInt32TagUtil::removeTag(utils::Buffer& dst,
				uint_32& tag,
				const utils::Buffer& src)
  {
    const unsigned char* data = src.getPtr();
    tag = convert_uint32_from_le(data);
    
    dst = utils::Buffer(data + sizeof(uint_32),
			src.getLen() - sizeof(uint_32));
    
    /*std::cout << "Removed Tag = " << tag << std::endl;
      std::cout << "Src = " << src << std::endl;
      std::cout << "Dst = " << dst << std::endl;*/
  }

}
