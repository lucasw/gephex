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

#ifndef INCLUDED_AUTO_PTR_H
#define INCLUDED_AUTO_PTR_H

#include <stdexcept>
#include <cassert>

namespace utils
{

/**
 *
 * AutoPtr is a reference counting smart pointer. In most cases
 * it can substitute a regular c pointer.
 *
 */

	/**
	 * Internal Class. Used to count the references.
	 */
  class AutoPtrRef
  {
  public:
    AutoPtrRef()
      : m_refCount(1)
    {
    }

	
    void incRefCount()
    {
      if (m_refCount <= 0)
	throw std::runtime_error("refCount <= 0!");
      ++m_refCount;
    }

    void decRefCount()
    {
      if (m_refCount <= 0)
	throw std::runtime_error("refCount <= 0!");
      --m_refCount;
	}

	int refCount() const
	{
		return m_refCount;
	}

	
  private:
    int m_refCount;    
  };
  
  template<typename T> class AutoPtr
  {
  public:
	explicit AutoPtr(T* p = 0);

	/**
	 * Creates a new AutoPtr that points to the same object.
	 * The reference count of the object is increased.
	 * @param ap The new AutPtr points to the same Object as this Pointer.
	 */
	AutoPtr(const AutoPtr<T>& ap)
		: m_ref(ap.m_ref), m_ptr(ap.m_ptr)
	{
		m_ref->incRefCount();
	}

	/**
	 * Lets the AutoPtr point to the Object that ap points to.
	 * The reference count (rc) of the Object that was referenced before
	 * is decreased and the rc of the newly referenced Object is
	 * increased.
	 * @param ap This AutPtr points to the same Object as this Pointer after
	 *           the operator is finished
	 */
	AutoPtr& operator=(const AutoPtr<T>& ap)
	{
		if (m_ptr != ap.m_ptr)
		{
			decRefCount();
			m_ptr = ap.m_ptr;
			m_ref = ap.m_ref;
			incRefCount();
		}

		return *this;
	}

	// this is needed because vc6 can't handle template constructors 
	// correctly
#if !defined(_MSC_VER)
	template <typename U>
    AutoPtr<T>(const AutoPtr<U>& ap)
	: m_ref(ap.ref()), m_ptr(ap.c_ptr())
	{
		m_ref->incRefCount();
	}

		template <typename U>
    AutoPtr<T>& operator=(const AutoPtr<U>& ap)
	{
		if (m_ptr != ap.c_ptr())
		{
			decRefCount();
			m_ptr = ap.c_ptr();
			m_ref = ap.ref();
			incRefCount();
		}

		return *this;
	}
#endif

	/**
	 * Destroys the AutoPtr.
	 * The Reference Count of the referenced Object is decreased.
	 * If it reaches 0, the Object is destroyed.
	 */
    ~AutoPtr();


	/**
	 * Returns a reference to the referenced Object, 
	 * so that this class can be used almost
	 * like an ordinary pointer.
	 * @return a reference to the referenced Object.
	 */
    T& operator*() const
    {
      return *c_ptr();
    }

	/**
	 * Returns wether the AutPtr is a 0-Pointer.
	 * @return 0 if the AutoPtr is a 0-Pointer, 1 otherwise.
	 */
    operator void*() const
    {
      return (m_ptr==0)?0:(void*)1;
    }

	/**
	 * Overloaded Operator so that this class can be used almost
	 * like an ordinary pointer.
	 */
    T* operator->() const
    {
      return c_ptr();
    }

	/**
	 * Returns an Pointer to the referenced Object.
	 * Use with care! When the AutoPtr goes out of scope, its possible
	 * that the referenced Object is deleted. Then this pointer becomes 
	 * invalid!
	 * @return Pointer to the referenced Object
	 */
    T* c_ptr() const
    {
      return m_ptr;
    }

	/**
	 * Internal Function
	 */
  AutoPtrRef* ref() const
  {
    return m_ref;
  }

    /**
	 * Tests wether two AutoPtrs point to the same Object.
	 * @return true if this points to the same Object as ap
			   false otherwise
	 */
	bool operator==(const AutoPtr<T>& ap) const
	{
		return m_ptr == ap.m_ptr;
	}

	/**
	 * Tests wether two AutoPtrs dont point to the same Object.
	 * Equivalent to !(*this == ap).
	 * @return false if this points to the same Object as ap
			   true otherwise
	 */
	bool operator!=(const AutoPtr<T>& ap) const
	{
		return !(*this == ap);
	}

  private:
    AutoPtrRef* m_ref;
	T* m_ptr;


	void decRefCount()
	{
		assert(m_ref != 0);
		m_ref->decRefCount();
		if (m_ref->refCount() == 0)
		{
			delete m_ref;
			delete m_ptr;
			m_ref = 0;
			m_ptr = 0;
		}
	}

	void incRefCount()
	{
		assert(m_ref != 0);
		m_ref->incRefCount();
	}
  };

  template <typename T>
  AutoPtr<T>::AutoPtr(T* p)
    : m_ref(new AutoPtrRef()), m_ptr(p)
  {
  }

  
  template <typename T>
  AutoPtr<T>::~AutoPtr()
  {
	if (m_ref != 0)
		decRefCount();
  }
  

}

#endif
