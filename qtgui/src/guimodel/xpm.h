#ifndef INCLUDED_XPM_H
#define INCLUDED_XPM_H

#include <iosfwd>

namespace gui
{

class Xpm
{
public:
	Xpm(const Xpm&);

	/**
	* Baut ein xpm aus einem serialisierten, flachen string aus nullterminierten
	* strings.
	*/
	Xpm(const char* ptr, int len);

	~Xpm();

	const Xpm& operator=(const Xpm&);

	const char** getPtr() const;

private:
	char** m_ptr;
	int m_len;
};

} // end of namespace gui

#endif
