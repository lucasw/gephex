#include "xpm.h"

#include <cstring>

namespace gui
{
	
	namespace {
		void copy(char**& m_ptr, int& m_len, char** ptr, int len)
		{
			m_len = len;
			m_ptr = new char*[m_len];
			
			for (int i = 0; i < m_len; ++i)
			{
				int currentLen = strlen(ptr[i])+1;
				m_ptr[i] = new char[currentLen];
				memcpy(m_ptr[i],ptr[i],currentLen);
			}
		}
		
		void kill(char**& m_ptr, int& m_len)
		{
			for (int i = 0; i < m_len; ++i)
			{
				delete[] m_ptr[i];
			}
			
			delete[] m_ptr;
			m_len = 0;
		}
		
	}
	
	Xpm::Xpm(const Xpm& x)
	{
		copy(m_ptr, m_len, x.m_ptr,x.m_len);
	}
	
	Xpm::Xpm(const char* ptr, int len)
	{
		const char* offset = ptr;		
		int index = 0;
		while (offset - ptr < len)
		{
			++index;
			offset += strlen(offset)+1;
		}
		
                //if (offset - ptr > len)
                  //printf("Ich protestiere!\n");

		m_ptr = new char*[index];
		m_len = index;
		
		offset = ptr;
		index = 0;
		while (offset - ptr < len)
		{
			int currentLen = strlen(offset)+1;
			m_ptr[index] = new char[currentLen];
			memcpy(m_ptr[index], offset, currentLen);
			
			offset += currentLen;
			++index;
		}
	}
	
	Xpm::~Xpm()
	{
		kill(m_ptr, m_len);
	}
	
	const Xpm& Xpm::operator=(const Xpm& x)
	{
		if (this == &x)
			return *this;
		
		kill(m_ptr, m_len);
		copy(m_ptr, m_len,x.m_ptr,x.m_len);
		return *this;
	}
	
	const char** Xpm::getPtr() const
	{
		return const_cast<const char**>(m_ptr);
	}
	
	
} // end of namespace gui
