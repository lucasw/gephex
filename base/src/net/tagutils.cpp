#include "tagutils.h"

#include "convertbin.h"
#include "utils/buffer.h"


namespace net {

  
  void StringTagUtil::attachTag(utils::Buffer& dst,
				const std::string& tag,
				const utils::Buffer& b)
  {
    unsigned int l = tag.length() + 1 + sizeof(unsigned int);
    unsigned char* data = new unsigned char[l];
    
    unsigned int* length = reinterpret_cast<unsigned int*>(data);
    *length = tag.length()+1;
    
    memcpy(data+sizeof(unsigned int), tag.c_str(), tag.length()+1);
    
    dst = utils::Buffer(data, l) + b;

    delete[] data;
  }

  void StringTagUtil::removeTag(utils::Buffer& dst,
				std::string& tag,
				const utils::Buffer& src)
  {
    const unsigned char* data = src.getPtr();
    const unsigned int l = *reinterpret_cast<const unsigned int*>(data);

    //std::cout << "src = '" << /*src <<*/ "', l = '" << l << "'" << std::endl;
    
    dst = utils::Buffer(data + sizeof(unsigned int) + l,
			src.getLen() - l - sizeof(unsigned int));

    tag = std::string(reinterpret_cast<const char*>(data 
						    + sizeof(unsigned int)),
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
