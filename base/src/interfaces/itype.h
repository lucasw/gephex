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

#ifndef INCLUDED_ITYPE_H
#define INCLUDED_ITYPE_H

namespace utils 
{ 
  class Buffer; 
}

class TypeAttributes;

/**
 * This is the abstract base class for types that are passed between
 * modules.
 */
class IType
{
 public: 
  virtual ~IType() {}

  /**
   * Copy the contents of t into *this. Wether this is a deep or a shallow
   * copy depends on the concrete type.
   * @param t the IType that is to be copied
   */
  virtual void assign(const IType* t) = 0;
	
  /**
   * Serializes a type.
   * @return a Buffer that contains the serialized type
   */
  virtual bool serialize (utils::Buffer& b) const = 0;

  /**
   * Deserialize the contents of a Buffer and assign them to *this.
   * This is rather a constructor than a normal method.
   * @buf the Buffer that contains the serialized data.
   */
  virtual void deSerialize (const utils::Buffer& buf) = 0;

  //doof!
  virtual bool equalAttributes(const TypeAttributes& attr) const = 0;

  virtual void convert(const IType& src, const TypeAttributes& attr) = 0;

  /*
   * Returns a void pointer to the internal Type instance.
   * This pointer should only be used by the modules. DONT USE! 
   * This is going to change.  It makes sense only for
   * types that are loaded as c dll plugins. For c++ types there
   * might be no internal pointer they should return the this pointer
   * TODO!!!!
   * @return pointer to the real type instance.
   */
  virtual void* getPointer() const = 0;
  
};

#endif
