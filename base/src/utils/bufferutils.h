#ifndef INCLUDED_BUFFER_UTILS_H
#define INCLUDED_BUFFER_UTILS_H

#include <iosfwd>

namespace utils
{
	/**
	 * Functions to serialize and deserialize a buffer
	 */
	class Buffer;

	std::ostream& operator<< (std::ostream&, const Buffer&);
	std::istream& operator>> (std::istream&, Buffer&);
}

#endif
