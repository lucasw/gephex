#ifndef INCLUDED_TAG_UTILS_H
#define INCLUDED_TAG_UTILS_H

#include <string>

#include "basic_types.h"

namespace utils {
  class Buffer;
}

namespace net {

  /**
   * For the Tagger...
   */
  class StringTagUtil {
  public:
  
    static void attachTag(utils::Buffer& dst,
			  const std::string& tag,
			  const utils::Buffer& b);

    static void removeTag(utils::Buffer& dst,
			  std::string& tag,
			  const utils::Buffer& src);
  };

  class UInt32TagUtil {
  public:   
    static void attachTag(utils::Buffer& dst,
			  const uint_32& tag,
			  const utils::Buffer& b);

    static void removeTag(utils::Buffer& dst,
			  uint_32& tag,
			  const utils::Buffer& src);
  };

}
#endif
